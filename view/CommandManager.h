#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <iostream>
#include <sstream>
#include "../controller/TodoController.h"

using namespace std;

// commands, flags should be stored in a map somehow
class CommandManager {
    private:
    std::stringstream input;
    TodoController* todoController;

    Todo parseTodo();

    void cmdAddGroup();
    void cmdAddTodo();
    void cmdEditGroup();
    void cmdEditTodo();
    void cmdDeleteGroup();
    void cmdDeleteTodo();
    void cmdPostpone();
    void cmdSort();
    void cmdList();

    void cmdHelp();
    void cmdExit();

    public:
    CommandManager(TodoController* todoController);
    ~CommandManager();

    void takeInput();
    bool isValidInput();
    std::string parseInput();
};

#endif