#ifndef CJSTRUCT_IPP
#define CJSTRUCT_IPP
#include <unordered_map>
#include <boost/pfr/core_name.hpp>

#include "CJStruct.h"

namespace JsonParser {
    template <typename T>
    void parseType(std::string & parseString, T & defaultValue);

    template <typename T>
    void parseType(std::string && parseString, T& defaultValue);

    template <typename T>
    void TypeToString(std::string& parseString, T& defaultValue);

    namespace jsonToSTLS {

        template <typename Vector>
        void parseVector(std::string& line, Vector& vector) {
            if constexpr (SFINAEgetter::is_vector<Vector>::value || SFINAEgetter::is_list<Vector>::value) {
                stringBoost::standartReplace(line);
                using tmp = typename Vector::value_type;
                using vector_values = typename SFINAEgetter::clean_type<tmp>::type;
                if (line=="]")
                    return;
                while (true) {
                    vector_values v{};
                    size_t commanow = line.find(',');
                    if (commanow >= std::numeric_limits<unsigned>::max() || (commanow=stringBoost::findRealChar(line, commanow, ','), commanow >= std::numeric_limits<unsigned>::max())) {
                        parseType(line, v);
                        vector.push_back(v);
                        break;
                    }
                    parseType(line.substr(0, commanow), v);
                    vector.push_back(v);
                    line.erase(0, commanow+1);
                }
            }
        }

        template <typename Arr>
        void parseArray(std::string& line, Arr& ar) {
            if constexpr (SFINAEgetter::is_array<Arr>::value) {
                stringBoost::standartReplace(line);
                size_t index = 0;
                using array_values = typename Arr::value_type;
                if (line=="]")
                    return;
                while (index < ar.size()) {
                    array_values v{};
                    size_t commanow = line.find(',');
                    if (commanow >= std::numeric_limits<unsigned>::max() || (commanow=stringBoost::findRealChar(line, commanow, ','), commanow >= std::numeric_limits<unsigned>::max())) {
                        parseType(line, v);
                        ar[index] = v;
                        break;
                    }
                    parseType(line.substr(0, commanow), v);
                    ar[index] = v;
                    index++;
                    line.erase(0, commanow+1);
                }
            }
        }

        template<typename Pair>
        void parsePair(std::string& line, Pair& pair) {
            if constexpr (SFINAEgetter::is_pair<Pair>::value) {
                stringBoost::standartReplace(line);
                using FirstType = typename Pair::first_type;
                using SecondType = typename Pair::second_type;
                if (line=="]")
                    return;
                FirstType Fv{};
                SecondType Sv{};
                size_t commanow = line.find(',');
                if (commanow >= std::numeric_limits<unsigned>::max() || (commanow=stringBoost::findRealChar(line, commanow, ','), commanow >= std::numeric_limits<unsigned>::max())) {
                    parseType(line, Fv);
                    pair.first = Fv;
                    pair.second = Sv;
                    return;
                }
                parseType(line.substr(0, commanow), Fv);
                pair.first = Fv;
                line.erase(0, commanow+1);
                parseType(line, Sv);
                pair.second = Sv;
            }
        }

        template<typename Set>
        void parseSet(std::string& line, Set& set) {
            if constexpr (SFINAEgetter::is_set<Set>::value) {
                stringBoost::standartReplace(line);
                using set_values = typename Set::value_type;
                if (line=="]")
                    return;
                while (true) {
                    set_values v{};
                    size_t commanow = line.find(',');
                    if (commanow >= std::numeric_limits<unsigned>::max() || (commanow=stringBoost::findRealChar(line, commanow, ','), commanow >= std::numeric_limits<unsigned>::max())) {
                        parseType(line, v);
                        set.insert(v);
                        break;
                    }
                    parseType(line.substr(0, commanow), v);
                    set.insert(v);
                    line.erase(0, commanow+1);
                }
            }
        }


        template<typename Element>
        void parseTupleElement(Element& el, std::string& line) {
            size_t commanow = line.find(',');
            if (commanow >= std::numeric_limits<unsigned>::max() || (commanow=stringBoost::findRealChar(line, commanow, ','), commanow >= std::numeric_limits<unsigned>::max())) {
                parseType(line, el);
                return;
            }
            parseType(line.substr(0, commanow), el);
            line.erase(0, commanow+1);
        }


        template<typename Element>
        void parseTupleElementString(Element& el, std::string& line) {
            TypeToString(line, el);
            line += ',';
        }

        template <typename TupleT, std::size_t... Is>
        void parseTupleImpJSON(TupleT& tp, std::index_sequence<Is...>, std::string& line) {
            if constexpr (SFINAEgetter::is_tuple<TupleT>::value) {
                ([&]() {
                    parseTupleElementString(std::get<Is>(tp), line);
                }(), ...);
            }
        }


        template <typename TupleT, std::size_t... Is>
        void parseTupleImpSTRUCT(TupleT& tp, std::index_sequence<Is...>, std::string& line) {
            if constexpr (SFINAEgetter::is_tuple<TupleT>::value) {
                ([&]() {
                    parseTupleElement(std::get<Is>(tp), line);
                }(), ...);
            }
        }

        template <typename TupleT>
        void parseTuple(std::string& line, TupleT& tp) {
            if constexpr (SFINAEgetter::is_tuple<TupleT>::value) {
                stringBoost::standartReplace(line);
                if (line=="]")
                    return;
                parseTupleImpSTRUCT(tp, std::make_index_sequence<std::tuple_size_v<TupleT>>{}, line);
            }
        }





        template <typename Map>
        void parseMap(std::string& line, Map& map ) {
            if constexpr (SFINAEgetter::is_map<Map>::value) {
                stringBoost::standartReplace(line);
                using FirstType = typename Map::key_type;
                using SecondType = typename Map::mapped_type;
                if (line=="}")
                    return;
                while (true) {
                    FirstType Fv{};
                    SecondType Sv{};
                    size_t jump = line.find(':');
                    if (jump >= std::numeric_limits<unsigned>::max() || (jump=stringBoost::findRealChar(line, jump, ':'), jump >= std::numeric_limits<unsigned>::max())) {
                        stringBoost::strip(line);
                        stringBoost::strip(line, "\"");
                        parseType(line, Fv);
                        map[Fv] = Sv;
                        break;
                    }
                    parseType(stringBoost::strip(stringBoost::strip(line.substr(0, jump)), "\""), Fv);
                    line.erase(0, jump+1);
                    jump = line.find(',');
                    if (jump >= std::numeric_limits<unsigned>::max() || (jump=stringBoost::findRealChar(line, jump, ','), jump >= std::numeric_limits<unsigned>::max())) {
                        parseType(line, Sv);
                        map[Fv] = Sv;
                        break;
                    }
                    parseType(line.substr(0, jump), Sv);
                    map[Fv] = Sv;
                    line.erase(0, jump+1);
                }
            }
        }
    }





    template <typename T>
    void parseType(std::string& parseString, T& defaultValue) {
        if constexpr (std::disjunction_v<
        std::is_same<T, long double>,
        std::is_same<T, double>,
        std::is_same<T, float>,
        std::is_same<T, unsigned long long>,
        std::is_same<T, long long>,
        std::is_same<T, unsigned long>,
        std::is_same<T, long>,
        std::is_same<T, unsigned int>,
        std::is_same<T, int>,
        std::is_same<T, unsigned short>,
        std::is_same<T, short>,
        std::is_same<T, unsigned char>,
        std::is_same<T, char>,
        std::is_same<T, wchar_t>,
        std::is_same<T, char16_t>,
        std::is_same<T, char32_t>,
        std::is_same<T, bool>,
        std::is_same<T, std::string>,
        std::is_same<T, std::wstring>,
        std::is_same<T, std::string_view>
>) {
            stringBoost::stringToType(parseString, defaultValue);
        } else if constexpr (SFINAEgetter::is_array<T>::value) {
            jsonToSTLS::parseArray<T>(parseString,defaultValue);
        } else if constexpr (SFINAEgetter::is_vector<T>::value || SFINAEgetter::is_list<T>::value) {
            jsonToSTLS::parseVector<T>(parseString,defaultValue);
        } else if constexpr (SFINAEgetter::is_pair<T>::value) {
            jsonToSTLS::parsePair<T>(parseString,defaultValue);
        } else if constexpr (SFINAEgetter::is_set<T>::value) {
            jsonToSTLS::parseSet<T>(parseString,defaultValue);
        } else if constexpr (SFINAEgetter::is_tuple<T>::value) {
            jsonToSTLS::parseTuple<T>(parseString,defaultValue);
        } else if constexpr (SFINAEgetter::is_map<T>::value) {
            jsonToSTLS::parseMap<T>(parseString,defaultValue);
        } else if constexpr (SFINAEgetter::is_struct<T>::value) {
            if (parseString=="{}")
                return;
            JsonToStruct<T>(parseString,defaultValue);
        }
    }



    template <typename T>
    void parseType(std::string&& parseString, T& defaultValue) {
        if constexpr (std::disjunction_v<
        std::is_same<T, long double>,
        std::is_same<T, double>,
        std::is_same<T, float>,
        std::is_same<T, unsigned long long>,
        std::is_same<T, long long>,
        std::is_same<T, unsigned long>,
        std::is_same<T, long>,
        std::is_same<T, unsigned int>,
        std::is_same<T, int>,
        std::is_same<T, unsigned short>,
        std::is_same<T, short>,
        std::is_same<T, unsigned char>,
        std::is_same<T, char>,
        std::is_same<T, wchar_t>,
        std::is_same<T, char16_t>,
        std::is_same<T, char32_t>,
        std::is_same<T, bool>,
        std::is_same<T, std::string>,
        std::is_same<T, std::wstring>,
        std::is_same<T, std::string_view>
>) {
            stringBoost::stringToType(parseString, defaultValue);
        } else if constexpr (SFINAEgetter::is_array<T>::value) {
            jsonToSTLS::parseArray<T>(parseString,defaultValue);
        } else if constexpr (SFINAEgetter::is_vector<T>::value || SFINAEgetter::is_list<T>::value) {
            jsonToSTLS::parseVector<T>(parseString,defaultValue);
        } else if constexpr (SFINAEgetter::is_pair<T>::value) {
            jsonToSTLS::parsePair<T>(parseString,defaultValue);
        } else if constexpr (SFINAEgetter::is_set<T>::value) {
            jsonToSTLS::parseSet<T>(parseString,defaultValue);
        } else if constexpr (SFINAEgetter::is_tuple<T>::value) {
            jsonToSTLS::parseTuple<T>(parseString,defaultValue);
        } else if constexpr (SFINAEgetter::is_map<T>::value) {
            jsonToSTLS::parseMap<T>(parseString,defaultValue);
        } else if constexpr (SFINAEgetter::is_struct<T>::value) {
            if (parseString=="{}")
                return;
            JsonToStruct<T>(parseString,defaultValue);
        }
    }





    template <class T>
    void setValues(T& val, std::unordered_map<std::string, std::string>& map) {
        boost::pfr::for_each_field_with_name(val,[&map](const std::string_view& name, auto& field) {
                if (const auto& M = map.find('"'+std::string(name)+'"'); M != map.end()) {
                    parseType(M->second, field);
                }
            });
    }



    template <typename T>
    void TypeToString(std::string& parseString, T& defaultValue) {
        if constexpr (std::disjunction_v<
        std::is_same<T, long double>,
        std::is_same<T, double>,
        std::is_same<T, float>,
        std::is_same<T, unsigned long long>,
        std::is_same<T, long long>,
        std::is_same<T, unsigned long>,
        std::is_same<T, long>,
        std::is_same<T, unsigned int>,
        std::is_same<T, int>,
        std::is_same<T, unsigned short>,
        std::is_same<T, short>,
        std::is_same<T, unsigned char>,
        std::is_same<T, char>,
        std::is_same<T, wchar_t>,
        std::is_same<T, char16_t>,
        std::is_same<T, char32_t>,
        std::is_same<T, bool>,
        std::is_same<T, std::string>,
        std::is_same<T, std::wstring>,
        std::is_same<T, std::string_view>,
        std::is_same<T, const char*>,
        std::is_same<T, const char>,
        std::is_same<T, const std::basic_string<char>>
>) {
            parseString += stringBoost::typeToString(defaultValue);
        } else if constexpr (SFINAEgetter::is_array<T>::value || (SFINAEgetter::is_vector<T>::value && !std::is_same_v<std::vector<bool>, T>) || SFINAEgetter::is_list<T>::value) {
            parseString += '[';
            for (auto &d : defaultValue) {
                TypeToString(parseString, d);
                parseString += ',';
            }
            if (parseString[parseString.size()-1] == ',')
                parseString.erase(parseString.end()-1);
            parseString += ']';
        } else if constexpr (std::is_same_v<std::vector<bool>, T>) {
            parseString += '[';
            for (auto d : defaultValue) {
                bool factv = d;
                TypeToString(parseString, factv);
                parseString += ',';
            }
            if (parseString[parseString.size()-1] == ',')
                parseString.erase(parseString.end()-1);
            parseString += ']';
        } else if constexpr (SFINAEgetter::is_set<T>::value) {
            parseString += '[';
            for (auto d : defaultValue) {
                TypeToString(parseString, d);
                parseString += ',';
            }
            if (parseString[parseString.size()-1] == ',')
                parseString.erase(parseString.end()-1);
            parseString += ']';
        }  else if constexpr (SFINAEgetter::is_pair<T>::value) {
            parseString += '[';
            TypeToString(parseString, defaultValue.first);
            parseString += ',';
            TypeToString(parseString, defaultValue.second);
            parseString += ']';
        } else if constexpr (SFINAEgetter::is_tuple<T>::value) {
            parseString += '[';
            jsonToSTLS::parseTupleImpJSON(defaultValue, std::make_index_sequence<std::tuple_size_v<T>>{}, parseString);
            if (parseString[parseString.size()-1] == ',')
                parseString.erase(parseString.end()-1);
            parseString += ']';
        } else if constexpr (SFINAEgetter::is_map<T>::value) {
            parseString += '{';
            for (auto i = defaultValue.begin(); i != defaultValue.end(); ++i) {
                auto copyFirst = i->first;
                auto copySecond = i->second;
                if (!std::disjunction_v<
                    std::is_same<std::string, decltype(copyFirst)>,
                    std::is_same<std::string_view, decltype(copyFirst)>,
                    std::is_same<char, decltype(copyFirst)>,
                    std::is_same<char8_t, decltype(copyFirst)>,
                    std::is_same<char16_t, decltype(copyFirst)>,
                    std::is_same<char32_t, decltype(copyFirst)>,
                    std::is_same<wchar_t, decltype(copyFirst)>
                    >) {
                    parseString+='"';
                    TypeToString(parseString,copyFirst);
                    parseString+='"';
                } else {
                    TypeToString(parseString,copyFirst);
                }
                parseString += ':';
                TypeToString(parseString,copySecond);
                parseString += ',';
            }
            if (parseString[parseString.size()-1] == ',')
                parseString.erase(parseString.end()-1);
            parseString += '}';
        } else if constexpr (SFINAEgetter::is_struct<T>::value) {
            StructToJson<T>(parseString, defaultValue);
        }
    }

    template <typename T>
    void StructToJson(std::string& result, T& t) {
        result += "{\n";
        boost::pfr::for_each_field_with_name(t,[&result](const std::string_view& name, auto& field) {
                result+='"';
                result+=name;
                result+="\": ";
                TypeToString(result, field);
                result+=",\n";
            });
        result.erase(result.end()-2, result.end());
        result += "\n}";
    }

    template <class T>
    void JsonToStruct(std::string& parseString, T& t) {
        size_t posstart = parseString.find_first_not_of(" \n\t");
        parseString.resize(parseString.find_last_not_of(" \n\t"));
        if (posstart != std::string::npos && parseString[posstart] == static_cast<char>(123)) {
            std::unordered_map<std::string,std::string> Map;
            parseString.erase(0,posstart+1);
        while (!parseString.empty()) {
             posstart = parseString.find(':');
             if (posstart < std::numeric_limits<unsigned>::max() || (posstart=stringBoost::findRealChar(parseString, posstart, ':'), posstart < std::numeric_limits<unsigned>::max())) {
                 std::string k = stringBoost::strip(parseString.substr(0, posstart));
                 parseString.erase(0,posstart+1);
                 size_t commanow = parseString.find(',');
                 commanow = commanow < -1 ? stringBoost::findRealChar(parseString, parseString.find(','), ',') : parseString.length();
                 Map.insert({k, stringBoost::strip(parseString.substr(0, commanow))});
                 parseString.erase(0,commanow+1);
                 if (commanow >= std::numeric_limits<unsigned>::max()) {
                     break;
                 }
             }
             }
            setValues(t, Map);
        }
        }
}

#endif