#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <iostream>
#include <sstream>
#include "../controller/TodoController.h"
#include "../controller/FileController.h"
#include "../model/Todo.h"
#include "../model/TimeUnit.h"
#include "../model/TodoSortableProperty.h"

using namespace std;

class CommandManager {
    public:
    enum Command {
        INVALID,
        MARK,
        ADD,
        DELETE,
        POSTPONE,
        SORT,
        LIST,
        HELP,
        EXIT,
    };

    CommandManager(TodoController* todoController, FileController* fileController);
    ~CommandManager();

    void takeInput();
    std::string parseInput();

    private:
    static std::map<std::string, Command> commands;
    static std::map<Command, std::string> outputs;
    static std::map<std::string, TimeUnit> timeUnitFlags;
    static std::map<std::string, TodoSortableProperty> sortablePropertyFlags;

    std::stringstream input;
    TodoController* todoController;
    FileController* fileController;

    Todo* takeTodoInput();
    void printTodos(vector<Todo*> todos);

    bool cmdMarkTodo();
    bool cmdAddTodo();
    bool cmdDeleteTodo();
    bool cmdPostpone();
    bool cmdSort();
    void cmdList();

    void cmdExit();
};

#endif