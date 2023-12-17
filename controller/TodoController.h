#ifndef TODOCONTROLLER_H
#define TODOCONTROLLER_H

#include <iostream>
#include "../nlohmann/json.hpp"
#include "../model/TodoSortableProperty.h"
#include "../model/TimeUnit.h"
#include "../model/Todo.h"

using namespace std;
using namespace nlohmann;

class TodoController {
    private:
    vector<Todo*> todos;

    public:
    TodoController() = default;
    TodoController(nlohmann::json data);
    ~TodoController();

    vector<Todo*>* getTodos();
    Todo* getTodo(size_t index);
    void addTodo(Todo* todo);
    void setTodo(size_t index, Todo* todo);
    void deleteTodo(size_t index);
    void postponeTodo(size_t index, int amount, TimeUnit unit);
    vector<Todo*> sortTodos(TodoSortableProperty property);

    nlohmann::json serialize();
    void deserialize(nlohmann::json data);

    size_t getIndex(Todo* todo);
};

#endif