#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>
#include "Todo.h"

using namespace std;
using namespace nlohmann;

Todo::Todo(nlohmann::json data) {
    this -> deserialize(data);
}

Todo::~Todo() {
    delete this;
}

std::string Todo::getGroup() {
    return this -> group;
}

std::string Todo::getTask() {
    return this -> task;
}

time_t Todo::getTimestamp() {
    return this -> timestamp;
}

bool Todo::getCompleted() {
    return this -> completed;
}

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

std::string Todo::toString() {
    std::stringstream stream;
    stream << this -> group << std::endl;
    stream << this -> task << std::endl;
    std::string date = asctime(localtime(&this -> timestamp));
    date.back() = '\0';
    stream << date << std::endl;
    if (this -> completed) {
        stream << "done";    
    } else {
        stream << "not done";
    }
    stream << std::endl;
    return stream.str();
}

nlohmann::json Todo::serialize() {
    nlohmann::json data;
    data["group"] = this -> group;
    data["task"] = this -> task;
    data["timestamp"] = this -> timestamp;
    data["completed"] = this -> completed;
    return data;
}

void Todo::deserialize(nlohmann::json data) {
    this
        -> setGroup(data["group"])
        -> setTask(data["task"])
        -> setTimestamp(data["timestamp"])
        -> setCompleted(data["completed"]);
}