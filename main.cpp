#include <iostream>
#include "nlohmann/json.hpp"
#include "controller/FileController.h"
#include "controller/TodoController.h"
#include "model/Todo.h"
#include "view/CommandManager.h"

using namespace std;
using namespace nlohmann;

const std::string DATA_FILENAME = "user/data.json";

int main() {
    FileController file(DATA_FILENAME);
    nlohmann::json data = file.readFromFile();
    TodoController todoController(data);

    CommandManager commandManager(&todoController, &file);

    while (true) {
        commandManager.takeInput();
        std::cout << commandManager.parseInput() << endl;
    }

    return 0;
}