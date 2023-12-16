#include <iostream>
#include <chrono>
#include <functional>
#include "../nlohmann/json.hpp"
#include "../model/TodoSortableProperty.h"
#include "../model/TimeUnit.h"
#include "../model/Todo.h"
#include "TodoController.h"

TodoController::TodoController(nlohmann::json data) {
    this -> deserialize(data);
}

TodoController::~TodoController() {
    delete this;
}

vector<std::string>* TodoController::getGroups() {
    return &this -> groups;
}

vector<Todo*>* TodoController::getTodos() {
    return &this -> todos;
}

Todo* TodoController::getTodo(size_t index) {
    return this -> todos[index];
}

void TodoController::addGroup(std::string name) {
    this -> groups.push_back(name);
}

void TodoController::addTodo(Todo* todo) {
    this -> todos.push_back(todo);
}

void TodoController::setTodo(size_t index, Todo* todo) {
    this -> todos[index] = todo;
}

void TodoController::deleteGroup(size_t index) {
    this -> groups.erase(this -> groups.begin() + index);
}

void TodoController::deleteTodo(size_t index) {
    this -> todos.erase(this -> todos.begin() + index);
}

void TodoController::postponeTodo(size_t index, short amount, TimeUnit unit) {
    Todo* todo = this -> todos[index];
    time_t timestamp = todo -> getTimestamp();
    time_t postponeBy = amount * unit;
    todo -> setTimestamp(timestamp + postponeBy);
}

std::function<bool(Todo*, Todo*)> const sortByGroup = [](Todo* a, Todo* b) {
    return a -> getGroup() > b -> getGroup();
};

std::function<bool(Todo*, Todo*)> const sortByTimestamp = [](Todo* a, Todo* b) {
    return a -> getTimestamp() > b -> getTimestamp();
};

std::function<bool(Todo*, Todo*)> const sortByCompleted = [](Todo* a, Todo* b) {
    return a -> getCompleted() > b -> getCompleted();
};

vector<Todo*> TodoController::sortTodos(TodoSortableProperty property) {
    vector<Todo*> sorted(this -> todos);
    std::function<bool(Todo*, Todo*)> sortFunc;
    switch (property) {
        case TodoSortableProperty::GROUP:
            sortFunc = sortByGroup;
            break;
        case TodoSortableProperty::TIMESTAMP:
            sortFunc = sortByTimestamp;
            break;
        case TodoSortableProperty::COMPLETED:
            sortFunc = sortByCompleted;
            break;
    }
    std::sort(
        sorted.begin(),
        sorted.end(),
        sortFunc
    );
    return sorted;
}

nlohmann::json TodoController::serialize() {
    nlohmann::json output = nlohmann::json::object();
    nlohmann::json groupsJSON = nlohmann::json::array();
    nlohmann::json todosJSON = nlohmann::json::array();

    for (std::string group : this -> groups) {
        groupsJSON.push_back(group);
    }

    for (Todo* todo : this -> todos) {
        todosJSON.push_back(todo -> serialize());
    }

    output["groups"] = groupsJSON;
    output["todos"] = todosJSON;

    return output;
}

void TodoController::deserialize(nlohmann::json data) {
    nlohmann::json groupsJSON = data["groups"];
    nlohmann::json todosJSON = data["todos"];
    if (!groupsJSON.is_array() || !todosJSON.is_array()) {
        throw std::runtime_error("Invalid JSON in data file.");
    }

    for (nlohmann::json group : groupsJSON) {
        this -> addGroup(group);
    }

    for (nlohmann::json todoJSON : todosJSON) {
        Todo* todo = new Todo(todoJSON);
        this -> addTodo(todo);
    }
}