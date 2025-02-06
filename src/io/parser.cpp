#include "parser.h"

#include "../enums/exception_types.h"


static const std::string NO_OPTION = "-";
static const std::regex MATERIAL_PATTERN("([0-4]),?");


Parser::Parser() :
    line_counter(0)
{}

void Parser::readLine()
{
    line.resize(0);
    std::getline(f_in, line);
    line_counter++;

    if (line.empty()) {
        throw FILE_READ_LINE_EMPTY;
    }
}

MaterialBundle Parser::parseMaterialBundle(const std::ssub_match& match) const
{
    MaterialBundle bundle;

    if (match.str() == NO_OPTION) {
        return bundle;
    }

    std::string sub_line = match.str();
    std::smatch sub_match;

    while (std::regex_search(sub_line, sub_match, MATERIAL_PATTERN)) {
        bundle.add(stoi(sub_match[1].str()));
        sub_line = sub_match.suffix();
    }

    return bundle;
}
