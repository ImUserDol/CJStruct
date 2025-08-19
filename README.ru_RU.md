# CJStruct
## UNSTABLE
[English](https://github.com/ImUserDol/CJStruct/blob/main/README.md) | [Русский](https://github.com/ImUserDol/CJStruct/blob/main/README.ru_RU.md)

CJStruct — заголовочная библиотека на C++20 для автоматического преобразования JSON <-> структур. Основана на aggregate-reflection из Boost.PFR. Достаточно вызвать `JsonToStruct` или `StructToJson` — вручную писать сериализаторы не придётся.

<sub><sup>Это мой первый тестовый проект на C++, имейте это в виду перед созданием «гневных» issue :)</sup></sub>

## Возможности

- Автоматическая (де)сериализация:
    - Примитивных типов: `int`, `double`, `bool`, `std::string` и др.
    - Контейнеров STL: `std::vector`, `std::list`, `std::set`, `std::map`, `std::array`
    - Кортежей и пар: `std::tuple`, `std::pair`
    - Вложенных агрегатных (POD) структур
- Один единственный заголовок (`CJStruct.h`), без макросов
- Поддержка C++20 и выше

## Требования

- Компилятор с поддержкой C++20 (GCC/Clang/MSVC)
- Boost.PFR (версия ≥ 1.68)

## Быстрый старт

1. Добавьте папку `CJStruct` в include-path вашего проекта.
2. Подключите заголовок и используйте:

```cpp
#include <fstream>
#include <string>
#include <boost/pfr.hpp>
#include <CJStruct/CJStruct.h>

struct Inner { int a; bool b; };

struct MyData {
    std::vector<int>               v;
    std::map<std::string, double>  m;
    std::string                    name;
    Inner                          nested;
};

int main() {
    // 1) Считываем JSON-файл в строку
    std::ifstream ifs("data.json");
    std::string json((std::istreambuf_iterator<char>(ifs)),
                     std::istreambuf_iterator<char>());

    // 2) Парсим JSON → struct
    MyData data{};
    JsonParser::JsonToStruct<MyData>(json, data);

    // ... модифицируем data ...

    // 3) Сериализуем struct → JSON
    std::string out;
    JsonParser::StructToJson<MyData>(out, data);

    // 4) Записываем JSON в файл
    std::ofstream ofs("out.json");
    ofs << out;

    return 0;
}
```

## Лицензия

Этот проект распространяется под лицензией **MIT**.
