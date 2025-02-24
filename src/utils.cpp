#include "include/utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

bool isAlphaOrUnderscore(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

bool isAlphaNumOrUnderscore(char c) {
    return isAlphaOrUnderscore(c) || (c >= '0' && c <= '9');
}

std::string readFileContents(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error reading file: " << filename << std::endl;
        std::exit(1);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void addToken(const std::string &type, const std::string &lexeme) {
    std::cout << type << " " << lexeme << " null" << std::endl;
}

void addToken(const std::string &type, const std::string &lexeme, const std::string &literal) {
    std::cout << type << " " << lexeme << " " << literal << std::endl;
}
