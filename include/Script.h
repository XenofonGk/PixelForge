#ifndef FORGE_SCRIPT_H
#define FORGE_SCRIPT_H
// Day 20: strings, string_view, variant, and reading a text file.
// Notes: E-STL/standard-library, E-STL/file-stream-objects
#include <string>
#include <string_view>
#include <variant>
#include <vector>

using Arg = std::variant<int, double, std::string>;

struct Command {
    std::string name;
    std::vector<Arg> args;
};

std::vector<std::string_view> split(std::string_view line); // split on spaces
Arg parseArg(std::string_view token);       // "12" -> int, "-1.5" -> double, else string
Command parseLine(std::string_view line);
double asNumber(const Arg& arg);            // int or double; else std::bad_variant_access
std::vector<Command> loadScript(const std::string& path); // skip blank and # lines

#endif
