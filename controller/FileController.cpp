#include <iostream>
#include <fstream>
#include <iomanip>
#include "../nlohmann/json.hpp"
#include "FileController.h"

using namespace std;
using namespace nlohmann;

FileController::FileController(std::string filename) {
    this -> filename = filename;
}

FileController::~FileController() {
    delete this;
}

nlohmann::json FileController::readFromFile() {
    std::ifstream file(this -> filename);
    nlohmann::json data = nlohmann::json::parse(file);
    std::cout << "Read file '" << this -> filename << "'." << endl;
    return data;
}

void FileController::writeToFile(nlohmann::json data) {
    std::ofstream file(this -> filename);
    file << std::setw(4) << data << std::endl;
    std::cout << "Wrote to file '" << this -> filename << "'." << endl;
}