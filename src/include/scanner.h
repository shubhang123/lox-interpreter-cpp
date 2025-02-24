#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <string>
#include <unordered_map>

class Scanner {
public:
    Scanner(const std::string &source);
    bool scanTokens(); // Tokenizes input and prints tokens

private:
    std::string source;
    int start, current, line;
    bool hadError;

    bool isAtEnd() const;
    char advance();
    char peek() const;
    char peekNext() const;
    bool match(char expected);
    void scanToken();
    void scanString();
    void scanNumber();
    void scanIdentifier();
};

#endif // SCANNER_H
