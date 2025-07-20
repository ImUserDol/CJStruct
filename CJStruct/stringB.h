

#ifndef STRINGB_H
#define STRINGB_H

namespace stringBoost {
        std::string strip(std::string_view inpt, const std::string_view&& newstr = "");
        void strip(std::string& inpt, const std::string_view&& newstr = "");
        void inline replace(size_t pos, std::string& line, std::string_view old_string, std::string_view new_string);
        void inline stringToType(const std::string& str, void* &default_value);
        void inline stringToType(const std::string& str, long double &default_value);
        void inline stringToType(const std::string& str, double &default_value);
        void inline stringToType(const std::string& str, float &default_value);
        void inline stringToType(const std::string& str, unsigned long long &default_value);
        void inline stringToType(const std::string& str, int& default_value);
        void inline stringToType(const std::string& str, unsigned int& default_value);
        void inline stringToType(const std::string& str, long &default_value);
        void inline stringToType(const std::string& str, unsigned long &default_value);
        void inline stringToType(const std::string& str, unsigned short &default_value);
        void inline stringToType(const std::string& str, unsigned char &default_value);
        void inline stringToType(const std::string& str, long long &default_value);
        void inline stringToType(const std::string& str, short &default_value);
        void inline stringToType(std::string_view str, char32_t &default_value);
        void inline stringToType(std::string_view str, char16_t &default_value);
        void inline stringToType(std::string_view str, wchar_t &default_value);
        void inline stringToType(std::string_view str, char &default_value);
        void inline stringToType(std::string_view str, bool &default_value);
        void inline stringToType(std::string_view str, std::string &default_value);

        inline std::string typeToString(long double v);
        inline std::string typeToString(double v);
        inline std::string typeToString(float v);
        inline std::string typeToString(unsigned long long v);
        inline std::string typeToString(long long v);
        inline std::string typeToString(unsigned long v);
        inline std::string typeToString(long v);
        inline std::string typeToString(unsigned int v);
        inline std::string typeToString(int v);
        inline std::string typeToString(unsigned short v);
        inline std::string typeToString(short v);
        inline std::string typeToString(unsigned char v);
        inline std::string typeToString(wchar_t v);
        inline std::string typeToString(char16_t v);
        inline std::string typeToString(char32_t v);
        inline std::string typeToString(bool v);
        inline std::string typeToString(std::string_view v);
        inline std::string typeToString(char v);
        // template <typename T>
        // void stringToType(const std::string& str, T& default_value);
        void inline standartReplace(std::string& line);
        unsigned countRealQuotes(std::string_view str);
        size_t findRealChar(std::string_view line, size_t commanow, char Char);
        std::tuple<unsigned, unsigned, unsigned, unsigned> CountBrackets(std::string_view line);
        inline bool findRealSquare(std::string_view line, unsigned finded);
        #include "stringB.ipp"
}


#endif //STRINGB_H
