#ifndef LISTCONTROLLER_H
#define LISTCONTROLLER_H

#include <iostream>
#include "../model/Todo.h"

class ListController {
    private:
    vector<std::string> groups;
    vector<Todo> todos;
};

#endif