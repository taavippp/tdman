#include <iostream>
#include <ctime>
#include <vector>
#include "Todo.h"

using namespace std;

Todo* Todo::setGroup(std::string group) {
    this -> group = group;
    return this;
}

Todo* Todo::setTask(std::string task) {
    this -> task = task;
    return this;
}

Todo* Todo::setTimestamp(time_t timestamp) {
    this -> timestamp = timestamp;
    return this;
}

Todo* Todo::setCompleted(bool completed) {
    this -> completed = completed;
    return this;
}

std::vector<std::string> Todo::toStrings() {
    std::vector<std::string> output;
    output.push_back(this -> group);
    output.push_back(this -> task);
    std::string date = asctime(localtime(&this -> timestamp));
    date.back() = '\0';
    output.push_back(
        date
    );
    output.push_back(this -> completed ? "[x]" : "[ ]");
    return output;
}