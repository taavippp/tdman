#include <iostream>
#include "nlohmann/json.hpp"
#include "io/FileController.h"
#include "model/Todo.h"

using namespace std;
using namespace nlohmann;

const std::string CONFIG_FILE = "user/config.json";

int main() {
    nlohmann::json config = FileController::readFromFile(CONFIG_FILE);
    std::cout << "Loaded configuration file." << endl;
    nlohmann::json data = FileController::readFromFile(config["file"]);
    std::cout << "Loaded data file " << config["file"] << "." << endl;
    
    return 0;
}