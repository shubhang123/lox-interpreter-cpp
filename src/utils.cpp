#include "include/utils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

std::string readFileContents(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()){
        std::cerr << "Error reading file: " << filename << std::endl;
        std::exit(1);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void printUsageAndExit(const std::string &programName) {
    std::cerr << "Usage: " << programName << " tokenize|parse <filename>" << std::endl;
    std::exit(1);
}

void addToken(const std::string &type, const std::string &lexeme, const std::string &literal) {
    std::cout << type << " " << lexeme << " " << literal << std::endl;
}
