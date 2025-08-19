
# CJStruct
## UNSTABLE
[English](https://github.com/ImUserDol/CJStruct/blob/main/README.md) | [Русский](https://github.com/ImUserDol/CJStruct/blob/main/README.ru_RU.md)

**CJStruct** is a header-only C++20 library for JSON <-> struct mapping, powered by Boost.PFR’s aggregate reflection. Just call `JsonToStruct` or `StructToJson`- no manual serializers needed.

<sub><sup>This is my first C++ test project, please keep this in mind before writing angry issues :)</sup></sub>


## Features

- Automatic (de)serialization of:
    - Built-in types (`int`, `double`, `bool`, `std::string`, etc.)
    - STL containers: `std::vector`, `std::list`, `std::set`, `std::map`, `std::array`
    - Tuples/pairs: `std::tuple`, `std::pair`
    - Nested aggregate structs
- Single header (`CJStruct.h`), no macros
- C++20 (or newer) support

## Requirements

- A C++20-compliant compiler (G++/Clang/MSVC)
- [Boost.PFR](https://www.boost.org/doc/libs/release/libs/pfr/) (part of Boost ≥1.68)

## Quick Start

1. Add directory `CJStruct` to your include path.
2. Include and use:

```cpp
#include <fstream>
#include <string>
#include <boost/pfr.hpp>  
#include <CJStruct/CJStruct.h>

struct Inner { int a; bool b; };
struct MyData {
    std::vector<int> v;
    std::map<std::string,double> m;
    std::string name;
    Inner nested;
};

int main() {
    // 1) Read JSON file into a string
    std::ifstream ifs("data.json");
    std::string json((std::istreambuf_iterator<char>(ifs)),
                     std::istreambuf_iterator<char>());

    // 2) Parse JSON → struct
    MyData data{};
    JsonParser::JsonToStruct<MyData>(json, data);

    // ... modify data ...

    // 3) Serialize struct → JSON
    std::string out;
    JsonParser::StructToJson<MyData>(out, data);

    // 4) Write JSON out
    std::ofstream ofs("out.json");
    ofs << out;
}
```

## License

This project is released under the **MIT License**.  
