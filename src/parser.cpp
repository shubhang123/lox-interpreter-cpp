#include "../include/parser.h"
#include "../include/token.h"
#include <vector>
#include <iostream>

void Parser::parse(std::vector<Token>& tokens) {
    current = 0;
    start = 0;
    tokensPtr = &tokens;

    // Process tokens until the end is reached.
    while (!is_end()) {
        const Token& token = advance();
        switch (token.type) {
            case TOKEN_TRUE:
                std::cout << "true" << std::endl;
            break;
            case TOKEN_FALSE:
                std::cout << "false" << std::endl;
            break;
            case TOKEN_NIL:
                std::cout << "nil" << std::endl;
            break;
            case TOKEN_NUMBER:
                // Print the literal value for numbers.
                    std::cout << token.literal << std::endl;
            case TOKEN_STRING:
                std::cout<< token.literal << std::endl;
            break;
            default:
                // For other tokens, you might extend the parsing logic.
                    break;
        }
    }
}

const Token& Parser::advance() {
    return (*tokensPtr)[current++];
}

bool Parser::is_end() {
    return current >= tokensPtr->size();
}
