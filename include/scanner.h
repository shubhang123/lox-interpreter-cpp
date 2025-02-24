#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <vector>
#include "../include/token.h"
class Scanner {
public:
    Scanner(const std::string &source);
    // Scans tokens and returns them as a vector.
    std::vector<Token> scanTokens();
    bool hadErrorOccurred() const { return hadError; }


private:
    const std::string source;
    int start;
    int current;
    int line;
    bool hadError;

    bool isAtEnd() const;
    char advance();
    char peek() const;
    char peekNext() const;
    bool match(char expected);

    // Adds a token to the tokens vector.
    void addToken(TokenType type, const std::string &lexeme, const std::string &literal = "null");

    void scanToken();
    void scanString();
    void scanNumber();
    void scanIdentifier();

    std::vector<Token> tokens;
};

#endif // SCANNER_HPP