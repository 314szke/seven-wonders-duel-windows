    #pragma once

#include <fstream>
#include <regex>
#include <sstream>
#include <string>

#include "../finance/material_bundle.h"


class Parser {
protected:
    Parser();

    void readLine();

    template<typename T>
    T parseNumber(const std::ssub_match& match, T default_value) {
        if (match.str() == "-") {
            return default_value;
        }
        T variable;
        std::stringstream ss;
        ss << match.str();
        ss >> variable;
        return variable;
    }
    
    MaterialBundle parseMaterialBundle(const std::ssub_match& match) const;

    std::ifstream f_in;
    std::string line;
    uint32_t line_counter;
};
