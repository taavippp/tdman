#include <iostream>
#include <chrono>
#include <functional>
#include <algorithm>
#include "../nlohmann/json.hpp"
#include "../model/TodoSortableProperty.h"
#include "../model/TimeUnit.h"
#include "../model/Todo.h"
#include "TodoController.h"

TodoController::TodoController(nlohmann::json data) {
    this -> deserialize(data);
}

TodoController::~TodoController() {
    for (Todo* todo : this -> todos) {
        delete todo;
    }
    delete this;
}

vector<Todo*>* TodoController::getTodos() {
    return &this -> todos;
}

Todo* TodoController::getTodo(size_t index) {
    return this -> todos[index];
}

void TodoController::addTodo(Todo* todo) {
    this -> todos.push_back(todo);
}

void TodoController::setTodo(size_t index, Todo* todo) {
    this -> todos[index] = todo;
}

void TodoController::deleteTodo(size_t index) {
    this -> todos.erase(this -> todos.begin() + index);
}

void TodoController::postponeTodo(size_t index, int amount, TimeUnit unit) {
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
    nlohmann::json todosJSON = nlohmann::json::array();

    for (Todo* todo : this -> todos) {
        todosJSON.push_back(todo -> serialize());
    }

    output["todos"] = todosJSON;

    return output;
}

void TodoController::deserialize(nlohmann::json data) {
    nlohmann::json todosJSON = data["todos"];
    if (!todosJSON.is_array()) {
        throw std::runtime_error("Invalid JSON in data file.");
    }

    for (nlohmann::json todoJSON : todosJSON) {
        Todo* todo = new Todo(todoJSON);
        this -> addTodo(todo);
    }
}

size_t TodoController::getIndex(Todo* todo) {
    auto it = find(todos.begin(), todos.end(), todo);
    if (it != todos.end()) {
        size_t index = it - todos.begin();
        return index;
    } else {
        return -1;
    }
}