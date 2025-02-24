#ifndef SCANNER_H
#define SCANNER_H

#include <string>

class Scanner {
public:
    Scanner(const std::string &source);
    // Tokenize the input and print tokens.
    bool scanTokens();

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

    void scanToken();
    void scanString();
    void scanNumber();
    void scanIdentifier();
};

#endif // SCANNER_H
