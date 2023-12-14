#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <iostream>
#include "../nlohmann/json.hpp"

using namespace std;
using namespace nlohmann;

class FileController {
    private:
    std::string filename;

    public:
    FileController() = default;
    FileController(std::string filename);
    ~FileController();

    nlohmann::json readFromFile();
    void writeToFile(nlohmann::json data);
};

#endif