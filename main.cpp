#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include "rapidjson/document.h"
#include "io/FileController.h"
#include "model/Todo.h"

using namespace std;
using namespace rapidjson;

namespace json = rapidjson;

const std::string SETTINGS_FILE = "user/settings.json";

int main() {
    json::Document doc =  FileController::readFromFile(SETTINGS_FILE);
    
    if (!doc.IsObject()) {
        throw std::runtime_error("Broken JSON file user/data.json");
    }

    doc["date_opened"].SetString("13-12-2023");

    FileController::writeToFile(&doc, SETTINGS_FILE);
    return 0;
}