#ifndef STRINGB_IPP
#define STRINGB_IPP
#include "stringB.h"


void inline stringToType(const std::string_view str, std::string &default_value) {
    default_value = stringBoost::strip(stringBoost::strip(str), "\"");
}


void inline stringToType(const std::string_view str, bool &default_value) {
    if (const std::string tmp = stringBoost::strip(stringBoost::strip(str), "\""); tmp == "true" || tmp == "1") {
        default_value = true;
    } else if (tmp == "false" || tmp == "0") {
        default_value = false;
    } else {
    throw std::invalid_argument("Invalid boolean string");
    }
}


void inline stringToType(const std::string_view str, char &default_value) {
default_value = stringBoost::strip(stringBoost::strip(str), "\"")[0];
}


void inline stringToType(const std::string_view str, wchar_t &default_value) {
default_value = static_cast<wchar_t>(stringBoost::strip(stringBoost::strip(str), "\"")[0]);
}


void inline stringToType(const std::string_view str, char16_t &default_value) {
default_value = static_cast<char16_t>(stringBoost::strip(stringBoost::strip(str), "\"")[0]);
}


void inline stringToType(const std::string_view str, char32_t &default_value) {
    default_value = static_cast<char32_t>(stringBoost::strip(stringBoost::strip(str), "\"")[0]);
}


void inline stringToType(const std::string& str, short &default_value) {
    try {
        default_value = static_cast<short>(std::stoi(str));
    } catch (std::invalid_argument &_) {
        default_value = 0.0;
    }
}


void inline stringToType(const std::string& str, int &default_value) {
    try {
        default_value = std::stoi(str);
    } catch (std::invalid_argument &_) {
        default_value = 0.0;
    }
}


void inline stringToType(const std::string& str, long &default_value) {
    try {
        default_value = std::stol(str);
    } catch (std::invalid_argument &_) {
        default_value = 0.0;
    }
}


void inline stringToType(const std::string& str, long long &default_value) {
    try {
        default_value = std::stoll(str);
    } catch (std::invalid_argument &_) {
        default_value = 0.0;
    }
}


void inline stringToType(const std::string& str, unsigned char &default_value) {
    try {
        default_value = static_cast<unsigned char>(std::stoi(str));
    } catch (std::invalid_argument &_) {
        default_value = 32;
    }
}


void inline stringToType(const std::string& str, unsigned short &default_value) {
    try {
        default_value = static_cast<unsigned short>(std::stoi(str));
    } catch (std::invalid_argument &_) {
        default_value = 0.0;
    }
}


void inline stringToType(const std::string& str, unsigned int &default_value) {
    try {
        default_value = static_cast<unsigned int>(std::stoul(str));
    } catch (std::invalid_argument &_) {
        default_value = 0.0;
    }
}


void inline stringToType(const std::string& str, unsigned long &default_value) {
    try {
        default_value = std::stoul(str);
    } catch (std::invalid_argument &_) {
        default_value = 0.0;
    }
}


void inline stringToType(const std::string& str, unsigned long long &default_value) {
    try {
        default_value = std::stoull(str);
    } catch (std::invalid_argument &_) {
        default_value = 0.0;
    }
}


void inline stringToType(const std::string& str, float &default_value) {
    try {
        default_value = std::stof(str);
    } catch (std::invalid_argument &_) {
        default_value = 0.0;
    }
}


void inline stringToType(const std::string& str, double &default_value) {
    try {
        default_value = std::stod(str);
    } catch (std::invalid_argument &_) {
        default_value = 0.0;
    };
}



void inline stringToType(const std::string& str, long double &default_value) {
    try {
        default_value = std::stold(str);
    } catch (std::invalid_argument &_) {
        default_value = 0.0;
    }
}


void inline stringToType(const std::string& str, void* &default_value) {
default_value = reinterpret_cast<void*>(std::stoull(str));
}

void inline replace(size_t pos, std::string& line, const std::string_view old_string, const std::string_view new_string) {
    while ((pos = line.find(old_string)) != std::string::npos)
        line.replace(pos, old_string.length(), new_string);
}

void inline standartReplace(std::string& line) {
    strip(line);
    line.erase(0, 1);
    line.erase(line.size()-1, line.size()-1);
}

inline std::string typeToString(const long double    v) { return std::to_string(v); }
inline std::string typeToString(const double         v) { return std::to_string(v); }
inline std::string typeToString(const float          v) { return std::to_string(v); }

inline std::string typeToString(const unsigned long long v) { return std::to_string(v); }
inline std::string typeToString(const long long     v)       { return std::to_string(v); }
inline std::string typeToString(const unsigned long  v)       { return std::to_string(v); }
inline std::string typeToString(const long          v)       { return std::to_string(v); }
inline std::string typeToString(const unsigned int   v)       { return std::to_string(v); }
inline std::string typeToString(const int            v)       { return std::to_string(v); }
inline std::string typeToString(const unsigned short v)       { return std::to_string(v); }
inline std::string typeToString(const short          v)       { return std::to_string(v); }
inline std::string typeToString(const unsigned char  v)       {
    return std::to_string(static_cast<unsigned>(v));
}

inline std::string typeToString(const char v) {
    return std::string("\"")+v+'"';
}
inline std::string typeToString(const wchar_t v) {
    std::string s("\"");
    s+=std::wstring(&v).front();
    s+="\"";
    return s;
}

inline std::string typeToString(const char32_t v) {
    std::string out("\"");
    if (v <= 0x7F) {
        // 1-byte sequence: 0xxxxxxx
        out.push_back(static_cast<char>(v));
    }
    else if (v <= 0x7FF) {
        // 2-byte sequence: 110xxxxx 10xxxxxx
        out.push_back(static_cast<char>(0xC0 | ((v >> 6) & 0x1F)));
        out.push_back(static_cast<char>(0x80 | ( v       & 0x3F)));
    }
    else if (v <= 0xFFFF) {
        // 3-byte sequence: 1110xxxx 10xxxxxx 10xxxxxx
        out.push_back(static_cast<char>(0xE0 | ((v >> 12) & 0x0F)));
        out.push_back(static_cast<char>(0x80 | ((v >>  6) & 0x3F)));
        out.push_back(static_cast<char>(0x80 | ( v        & 0x3F)));
    }
    else if (v <= 0x10FFFF) {
        // 4-byte sequence: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        out.push_back(static_cast<char>(0xF0 | ((v >> 18) & 0x07)));
        out.push_back(static_cast<char>(0x80 | ((v >> 12) & 0x3F)));
        out.push_back(static_cast<char>(0x80 | ((v >>  6) & 0x3F)));
        out.push_back(static_cast<char>(0x80 | ( v        & 0x3F)));
    }
    return out+"\"";
}

inline std::string typeToString(const char16_t v) {
    if (v >= 0xD800 && v <= 0xDFFF) {
        std::string s("\"");
        s += static_cast<char>(v);
        s+='"';
        return s;
    }
    return typeToString(static_cast<char32_t>(v));
}



inline std::string typeToString(const bool v) {
    return v ? "true" : "false";
}

inline std::string typeToString(const std::string_view v) {
    std::string out("\"");
    out+=v;
    out+="\"";
    return out;
}


#endif
