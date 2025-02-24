#include <iostream>
#include "utils.h"
#include "scanner.h"
#include "parser.h"

int main(int argc, char *argv[]) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    if (argc < 3)
        printUsageAndExit(argv[0]);

    std::string command = argv[1];
    std::string filename = argv[2];
    std::string fileContents = readFileContents(filename);

    if (command == "tokenize") {
        Scanner scanner(fileContents);
        bool hadError = scanner.scanTokens();
        return hadError ? 65 : 0;
    } else if (command == "parse") {
        std::vector<PToken> tokens = scanTokensForParser(fileContents);
        Parser parser(tokens);
        Expr *expression = parser.parse();
        if (expression) {
            std::cout << expression->print() << "\n";
            delete expression;
        }
        return 0;
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        printUsageAndExit(argv[0]);
    }
    return 0;
}
