#ifndef CJSTRUCT_H
#define CJSTRUCT_H
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>
#include "stringB.h"
#include "SFINAE.h"
#include "stringB.cpp"
#include <string>

namespace JsonParser {
    template <class T>
    void JsonToStruct(std::string& parseString, T& t);

    template <typename T>
    void StructToJson(std::string& result, T& t);
}
#include "CJStruct.ipp"

#endif //CJSTRUCT_H
