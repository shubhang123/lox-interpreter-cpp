#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include "../include/token.h"

class Parser {
public:
    // The parse function processes a vector of tokens.
    void parse(std::vector<Token>& tokens);

private:
    // Pointer to the token vector.
    std::vector<Token>* tokensPtr = nullptr;
    size_t current;
    size_t start;

    // Advances and returns the next token.
    const Token& advance();
    // Returns true if we've reached the end of the token vector.
    bool is_end();
};

#endif // PARSER_HPP
