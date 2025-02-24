#include <iostream>
#include <fstream>
#include <sstream>
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
        // Print each token's lexeme, type, and literal.
        for (const auto &token : tokens) {
            std::cout << token.lexeme << " " << token.literal << std::endl;
        }
    } else if (command == "parse") {
        Scanner scanner(fileContents);
        auto tokens = scanner.scanTokens();
        Parser parser;
        parser.parse(tokens);
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        printUsageAndExit(argv[0]);
    }
    return 0;
}
