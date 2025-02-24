#include <iostream>
#include <fstream>
#include <string>
#include "../include/scanner.h"
#include "../include/parser.h"
#include "../include/utils.h"

int main(int argc, char *argv[]) {
    if (argc < 3)
        printUsageAndExit(argv[0]);

    std::string command = argv[1];
    std::string filename = argv[2];
    std::string fileContents = readFileContents(filename);

    if (command == "tokenize") {
        Scanner scanner(fileContents);
        auto tokens = scanner.scanTokens();
        // Print each token's type, lexeme, and literal.
        for (const auto &token : tokens) {
            std::cout << tokenTypeToString(token.type) << " "
                      << token.lexeme << " "
                      << token.literal << std::endl;
        }
        // If any error was detected, exit with code 65.
        if (scanner.hadErrorOccurred()) {
            std::exit(65);
        }
    } else if (command == "parse") {
        Scanner scanner(fileContents);
        auto tokens = scanner.scanTokens();
        Parser parser;
        parser.parse(tokens);
        if (scanner.hadErrorOccurred()) {
            std::exit(65);
        }
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        printUsageAndExit(argv[0]);
    }
    return 0;
}