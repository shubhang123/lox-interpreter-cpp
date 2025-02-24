#include "../include/utils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

std::string readFileContents(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
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