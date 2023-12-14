#include <iostream>
#include <chrono>
#include "../model/TodoSortableProperty.h"
#include "../model/TimeUnit.h"
#include "../model/Todo.h"
#include "TodoController.h"

TodoController::~TodoController() {
    delete this;
}

vector<Todo>* TodoController::getTodos() {
    return &this -> todos;
}

Todo* TodoController::getTodo(size_t index) {
    return &this -> todos[index];
}

void TodoController::addGroup(std::string name) {
    this -> groups.push_back(name);
}

void TodoController::addTodo(Todo todo) {
    this -> todos.push_back(todo);
}

void TodoController::setTodo(size_t index, Todo todo) {
    this -> todos[index] = todo;
}

void TodoController::deleteGroup(size_t index) {
    this -> groups.erase(this -> groups.begin() + index);
}

void TodoController::deleteTodo(size_t index) {
    this -> todos.erase(this -> todos.begin() + index);
}

void TodoController::postponeTodo(size_t index, short amount, TimeUnit unit) {
    Todo* todo = &this -> todos[index];
    time_t timestamp = todo -> getTimestamp();
    time_t postponeBy = amount * unit;
    todo -> setTimestamp(timestamp + postponeBy);
}

std::function<bool(Todo, Todo)> sortByCompleted = [](Todo a, Todo b) {
    return a.getCompleted() > b.getCompleted();
};

std::function<bool(Todo, Todo)> sortByGroup = [](Todo a, Todo b) {
    return a.getGroup() > b.getGroup();
};

std::function<bool(Todo, Todo)> const sortByTimestamp = [](Todo a, Todo b) {
    return a.getTimestamp() > b.getTimestamp();
};

vector<Todo> TodoController::sortTodos(TodoSortableProperty property) {
    vector<Todo> sorted(this -> todos);
    std::function<bool(Todo, Todo)> sortFunc;
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