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
}


