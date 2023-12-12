#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

class Todo {
    private:
    std::string group = "Default";
    std::string task;
    time_t timestamp = time(NULL);
    bool completed = false;

    public:
    Todo* setGroup(std::string group);
    Todo* setTask(std::string task);
    Todo* setTimestamp(time_t timestamp);
    Todo* setCompleted(bool completed);
    
    std::vector<std::string> toStrings();
};