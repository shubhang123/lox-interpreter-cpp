#include <iostream>
#include "include/scanner.h"
#include "include/utils.h"

void printUsageAndExit(const std::string &programName) {
    std::cerr << "Usage: " << programName << " tokenize <filename>" << std::endl;
    std::exit(1);
}

int main(int argc, char *argv[]) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::cerr << "Logs from your program will appear here!" << std::endl;

    if (argc < 3)
        printUsageAndExit(argv[0]);

    const std::string command = argv[1];
    const std::string filename = argv[2];

    if (command != "tokenize") {
        std::cerr << "Unknown command: " << command << std::endl;
        printUsageAndExit(argv[0]);
    }

    std::string fileContents = readFileContents(filename);
    Scanner scanner(fileContents);
    bool hadError = scanner.scanTokens();

    return hadError ? 65 : 0;
}
