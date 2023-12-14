#ifndef TODOCONTROLLER_H
#define TODOCONTROLLER_H

#include <iostream>
#include "../model/TodoSortableProperty.h"
#include "../model/TimeUnit.h"
#include "../model/Todo.h"
#include "../nlohmann/json.hpp"

class TodoController {
    private:
    vector<std::string> groups;
    vector<Todo> todos;

    public:
    TodoController() = default;
    ~TodoController();

    vector<Todo>* getTodos();
    Todo* getTodo(size_t index);
    void addGroup(std::string name);
    void addTodo(Todo todo);
    void setTodo(size_t index, Todo todo);
    void deleteGroup(size_t index);
    void deleteTodo(size_t index);
    void postponeTodo(size_t index, short amount, TimeUnit unit);
    vector<Todo> sortTodos(TodoSortableProperty property);

    nlohmann::json serialize();
    void deserialize(nlohmann::json data);
};

#endif