#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <iostream>
#include "../rapidjson/document.h"

using namespace rapidjson;
using namespace std;

namespace json = rapidjson;

class FileController {
    public:
    static json::Document readFromFile(std::string filename);
    static bool writeToFile(json::Document* document, std::string filename);
};

#endif