#include "Script.h"
#include "Common.h"
#include <cctype>
#include <fstream>
#include <stdexcept>

std::vector<std::string_view> split(std::string_view line) {
    // TODO Day 20: use find_first_not_of, find and substr. Ignore repeated spaces. Do not copy characters.
    NOT_IMPLEMENTED();
}
Arg parseArg(std::string_view token) {
    // TODO Day 20: allow one leading '-', digits, and at most one '.'. Build int with std::stoi or double with std::stod. Anything else stays a string.
    NOT_IMPLEMENTED();
}
Command parseLine(std::string_view line) {
    // TODO Day 20: the first token is the name; the rest go through parseArg. Throw std::invalid_argument for an empty line.
    NOT_IMPLEMENTED();
}
double asNumber(const Arg& arg) {
    // TODO Day 20: use arg.index() to choose std::get<int> or std::get<double>. Let std::get<double> throw for a string.
    NOT_IMPLEMENTED();
}
std::vector<Command> loadScript(const std::string& path) {
    // TODO Day 20: open with ifstream and throw std::runtime_error on failure. Use std::getline, and skip blank lines and lines starting with #.
    NOT_IMPLEMENTED();
}
