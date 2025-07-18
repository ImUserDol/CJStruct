#include <list>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <iostream>

#include <boost/pfr.hpp>


//Don't forget to change the path to include directory!!!
//Не забудьте поменять путь до вашей директории include!!!
#include "../CJStruct/CJStruct.h"

struct Li {
    int kili;
    int hi;
};


struct ComplexStruct {
    std::vector<int> vec_int;
    std::map<std::string, double> map_str_double;
    std::tuple<int, std::string, double> tup;
    std::pair<std::string, bool> pr;
    std::array<float, 3> arr_float{};
    std::set<char> set_char;
    std::list<std::string> list_str;
    std::string mini;
    Li Oi{};
};


int main() {
    std::string testString = R"({
  "vec_int": [10, 20, 30, 40, 50],
  "map_str_double": {
    "pi": 3.1415,
    "e": 2.718,
    "phi": 1.618
  },
  "tup": [42, "hello world", 3.14],
  "pr": ["key", true],
  "arr_float": [1.1, 2.2, 3.3],
  "set_char": ["a", "b", "c", "z"],
  "list_str": ["first", "se\\\"cond", "third"],
  "Oi": {"kili": 100, "hi": 1}
})";
    ComplexStruct cs{};
    //DeSerialize json string to Struct
    JsonParser::JsonToStruct<ComplexStruct>(testString, cs);
    std::string myJson{};
    //Serialize Struct to json string
    JsonParser::StructToJson<ComplexStruct>(myJson, cs);
    std::cout << myJson << std::endl;
    return 0;
}