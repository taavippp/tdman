#include <iostream>
#include <fstream>
#include "../rapidjson/istreamwrapper.h"
#include "../rapidjson/ostreamwrapper.h"
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h" 
#include "FileController.h"

using namespace rapidjson;
using namespace std;

namespace json = rapidjson;

json::Document FileController::readFromFile(std::string filename) {
    ifstream file(filename.c_str());
    json::Document document;
    
    IStreamWrapper wrapper(file);
    document.ParseStream(wrapper);

    return document;
}

bool FileController::writeToFile(json::Document* document, std::string filename) {
    ofstream file(filename.c_str());
    OStreamWrapper wrapper(file);

    PrettyWriter<OStreamWrapper> writer(wrapper);
    return document -> Accept(writer);
}