#ifndef TODO_H
#define TODO_H

#include <iostream>
#include <vector>
#include <ctime>
#include "../nlohmann/json.hpp"

using namespace std;
using namespace nlohmann;

class Todo {
    private:
    std::string group = "Default";
    std::string task;
    time_t timestamp = time(NULL);
    bool completed = false;

    public:
    Todo() = default;
    Todo(nlohmann::json data);
    ~Todo();

    std::string getGroup();
    std::string getTask();
    time_t getTimestamp();
    bool getCompleted();

    Todo* setGroup(std::string group);
    Todo* setTask(std::string task);
    Todo* setTimestamp(time_t timestamp);
    Todo* setCompleted(bool completed);
    
    std::string toString();
    nlohmann::json serialize();
    void deserialize(nlohmann::json data);
};

#endif