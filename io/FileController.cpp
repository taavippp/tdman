#include <iostream>
#include <fstream>
#include <iomanip>
#include "../nlohmann/json.hpp"
#include "FileController.h"

using namespace std;
using namespace nlohmann;

nlohmann::json FileController::readFromFile(std::string filename) {
    std::ifstream file(filename);
    nlohmann::json data = nlohmann::json::parse(file);
    return data;
}

void FileController::writeToFile(nlohmann::json data, std::string filename) {
    std::ofstream file(filename);
    file << std::setw(4) << data << std::endl;
}