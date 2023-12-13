#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <iostream>
#include "../nlohmann/json.hpp"

using namespace std;
using namespace nlohmann;

class FileController {
    public:
    static nlohmann::json readFromFile(std::string filename);
    static void writeToFile(nlohmann::json data, std::string filename);
};

#endif