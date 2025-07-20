#include "stringB.h"



namespace stringBoost {
    std::string strip(const std::string_view inpt, const std::string_view&& newstr) {
        auto start_it = inpt.begin();
        auto end_it = inpt.rbegin();
        if (inpt.empty() || inpt == "\"\"") {
            return {};
        }
        if (newstr == "\"" && *start_it == '"') {
            start_it++;
        }
        if (newstr != "\"") {
            while (std::isspace(*start_it)) {
                ++start_it;
            }
        }
        if (newstr == "\"" && *end_it == '"') {
            if (start_it != inpt.end())
                ++end_it;
            return std::string{start_it, end_it.base()};
        }
        if (start_it != inpt.end()) {
            while (std::isspace(*end_it))
                ++end_it;
        }
        return std::string{start_it, end_it.base()};
    }

    void strip(std::string& inpt, const std::string_view&& newstr) {
        auto start_it = inpt.begin();
        auto end_it = inpt.rbegin();
        if (inpt.empty() || inpt == "\"\"") {
            inpt = "";
            return;
        }
        if (newstr != "\"") {
            while (std::isspace(*start_it)) {
                ++start_it;
            }
        }
        if (newstr == "\"" && *end_it == '"') {
            if (start_it != inpt.end())
                ++end_it;

            inpt={start_it, end_it.base()};
            return;
        }
        if (start_it != inpt.end()) {
            while (std::isspace(*end_it))
                ++end_it;
        }
        inpt={start_it, end_it.base()};
    }
    unsigned countRealQuotes(const std::string_view str) {
        unsigned countslash = 0;
        return std::ranges::count_if(str.begin(), str.end(), [countslash](const char i) mutable {
            if (i == '\\') {
                ++countslash;
            } else if (i == '"') {
                const bool tf = countslash%2==0;
                countslash = 0;
                return tf;
            } else {
                countslash = 0;
            }
            return false;
        });
    };
    size_t findRealChar(const std::string_view line, const size_t commanow, const char Char) {
        const std::string_view sub1 = line.substr(0, commanow);
        const size_t countQuotes = countRealQuotes(sub1);
        if (const std::tuple<unsigned, unsigned, unsigned, unsigned> counts = CountBrackets(sub1); countQuotes%2==0 && std::get<0>(counts) == std::get<1>(counts) && std::get<2>(counts) == std::get<3>(counts)) {
            if (line[commanow] != Char) {
                return commanow-1;
            }
            return commanow;
        }
        if (line.substr(commanow).find(Char) == std::string::npos) {
            return std::numeric_limits<unsigned>::max();
        }
        return findRealChar(line,line.substr(commanow).find(Char) + commanow+1, Char);

    }

    std::tuple<unsigned, unsigned, unsigned, unsigned> CountBrackets(const std::string_view line) {
        auto BracketsFinder = [&line](const char searchElement) -> unsigned {
            unsigned finded = line.find(searchElement);
            unsigned count = 0;
            while (finded < -1) {
                if (findRealSquare(line, finded)) {
                    count++;
                }
                const unsigned value = line.substr(finded+1).find(searchElement);
                if (value >= -1)
                    break;
                finded = value + finded + 1;
            }
            return count;
        };
        return {BracketsFinder('{'), BracketsFinder('}'), BracketsFinder('['), BracketsFinder(']')};
    }
}


