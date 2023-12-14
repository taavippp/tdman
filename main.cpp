#include <iostream>
#include "nlohmann/json.hpp"
#include "controller/FileController.h"
#include "controller/TodoController.h"
#include "model/Todo.h"

using namespace std;
using namespace nlohmann;

const std::string CONFIG_FILENAME = "user/config.json";

int main() {
    FileController configFile(CONFIG_FILENAME);
    nlohmann::json config = configFile.readFromFile();
    FileController dataFile(config["file"]);
    nlohmann::json data = dataFile.readFromFile();
    Todo* todo = new Todo;
    todo -> setTask("take a nap");
    TodoController todos = TodoController();
    todos.addTodo(*todo);
    return 0;
}