#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <format>
#include "../nlohmann/json.hpp"
#include "CommandManager.h"
#include "../controller/TodoController.h"
#include "../controller/FileController.h"
#include "../model/Todo.h"
#include "../model/TimeUnit.h"
#include "../model/TodoSortableProperty.h"

using namespace std;
using namespace nlohmann;

std::map<std::string, CommandManager::Command> CommandManager::commands = {
    {"mark", Command::MARK},
    {"add", Command::ADD},
    {"delete", Command::DELETE},
    {"postpone", Command::POSTPONE},
    {"sort", Command::SORT},
    {"list", Command::LIST},
    {"help", Command::HELP},
    {"exit", Command::EXIT},
};

std::map<CommandManager::Command, std::string> CommandManager::outputs = {
    {Command::INVALID, "Invalid command."},
    {Command::MARK, "Changed task completion."},
    {Command::ADD, "Added new task."},
    {Command::DELETE, "Deleted task."},
    {Command::POSTPONE, "Postponed task."},
    {Command::SORT, ""},
    {Command::LIST, ""},
    {Command::HELP, "The following commands are available:\n"
    "mark N - marks task number N as done/not done\n"
    "add - add a new task to the list\n"
    "delete N - delete task number N\n"
    "postpone N A U - postpone task number N by A (m)inutes/(h)ours/(d)ays/(w)eeks\n"
    "sort P - sort and print all tasks by (g)roup/(t)imestamp/(c)ompletion\n"
    "help - displays this text\n"
    "exit - exits the program\n"
    },
};

std::map<std::string, TimeUnit> CommandManager::timeUnitFlags = {
    {"m", TimeUnit::MINUTE},
    {"h", TimeUnit::HOUR},
    {"d", TimeUnit::DAY},
    {"w", TimeUnit::WEEK},
};

std::map<std::string, TodoSortableProperty> CommandManager::sortablePropertyFlags = {
    {"g", TodoSortableProperty::GROUP},
    {"t", TodoSortableProperty::TIMESTAMP},
    {"c", TodoSortableProperty::COMPLETED},
};

CommandManager::CommandManager(TodoController* todoController, FileController* fileController) {
    this -> todoController = todoController;
    this -> fileController = fileController;
}

CommandManager::~CommandManager() {
    delete this;
}

void CommandManager::takeInput() {
    std::cout << "tdman > ";
    std::string line;
    getline(std::cin, line);
    this -> input = stringstream(line);
}

std::string CommandManager::parseInput() {
    std::string cmds, output, flag;
    bool success = true;
    this -> input >> cmds;
    CommandManager::Command cmd = CommandManager::commands[cmds];
    output = CommandManager::outputs[cmd];
    switch (cmd) {
        case Command::MARK:
            success = cmdMarkTodo();
            break;
        case Command::ADD:
            success = cmdAddTodo();
            break;
        case Command::DELETE:
            success = cmdDeleteTodo();
            break;
        case Command::POSTPONE:
            success = cmdPostpone();
            break;
        case Command::SORT:
            success = cmdSort();
            break;
        case Command::LIST:
            cmdList();
            break;
        case Command::EXIT:
            cmdExit();
            break;
    }

    if (!success) {
        output = CommandManager::outputs[Command::INVALID];
    }
    return output;
}

Todo* CommandManager::takeTodoInput() {
    std::string line;
    Todo* todo = new Todo;
    std::cout << "Group: ";
    getline(std::cin, line);
    if (line != "") {
        todo -> setGroup(line);
    }
    std::cout << "Task: ";
    getline(std::cin, line);
    todo -> setTask(line);
    return todo;
}

void CommandManager::printTodos(vector<Todo*> todos) {
    for (int i = 0; i < todos.size(); i++) {
        Todo* todo = todos[i];
        size_t index = todoController -> getIndex(todo);
        std::cout << "Nr. " << index << std::endl;
        std::cout << todo -> toString();
        if (i != todos.size() - 1) {
            std::cout << "---" << std::endl;
        }
    }
}

bool CommandManager::cmdMarkTodo() {
    std::string temp;
    size_t index;
    this -> input >> temp;
    try {
        index = stoll(temp);
    } catch (std::exception e) {
        return false;
    }
    size_t size = todoController -> getTodos() -> size();
    if (index < 0 || index >= size) {
        return false;
    }
    Todo* todo = todoController -> getTodo(index);
    todo -> setCompleted(!todo -> getCompleted());
    return true;
}

bool CommandManager::cmdAddTodo() {
    Todo* todo = takeTodoInput();
    if (todo -> getTimestamp() == 0) {
        return false;
    }
    todoController -> addTodo(todo);
    return true;
}

bool CommandManager::cmdDeleteTodo() {
    std::string temp;
    size_t index;
    this -> input >> temp;
    try {
        index = stoll(temp);
    } catch (std::exception e) {
        return false;
    }
    size_t size = todoController -> getTodos() -> size();
    if (index < 0 || index >= size) {
        return false;
    }
    todoController -> deleteTodo(index);
    return true;
}

bool CommandManager::cmdPostpone() {
    std::string tempi, tempa;
    size_t index;
    int amount;
    std::string flag;
    this -> input >> tempi >> tempa >> flag;
    try {
        index = stoll(tempi);
        amount = stoi(tempa);
    } catch (std::exception e) {
        return false;
    }
    TimeUnit unit = timeUnitFlags[flag];
    if (unit == 0) {
        return false;
    }
    size_t size = todoController -> getTodos() -> size();
    if (index < 0 || index >= size) {
        return false;
    }
    todoController -> postponeTodo(index, amount, unit);
    return true;
}

bool CommandManager::cmdSort() {
    std::string flag;
    TodoSortableProperty property;
    this -> input >> flag;
    property = sortablePropertyFlags[flag];
    if (property == TodoSortableProperty::INVALID) {
        return false;
    }
    vector<Todo*> sorted = todoController -> sortTodos(property);
    
    printTodos(sorted);

    return true;
}

void CommandManager::cmdList() {
    vector<Todo*>* todos;
    todos = todoController -> getTodos();
    
    printTodos(*todos);

    return;
}

void CommandManager::cmdExit() {
    nlohmann::json data = todoController -> serialize();
    fileController -> writeToFile(data);
    std::cout << "Exiting." << endl;
    exit(0);
}