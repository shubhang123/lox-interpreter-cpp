#include "scanner.h"
#include "utils.h"

Scanner::Scanner(const std::string &source)
    : source(source), start(0), current(0), line(1), hadError(false) {}

bool Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    addToken("EOF", "");
    return hadError;
}

bool Scanner::isAtEnd() const {
    return current >= static_cast<int>(source.length());
}

char Scanner::advance() {
    return source[current++];
}

char Scanner::peek() const {
    return isAtEnd() ? '\0' : source[current];
}

char Scanner::peekNext() const {
    return (current + 1 >= static_cast<int>(source.length())) ? '\0' : source[current + 1];
}

bool Scanner::match(char expected) {
    if (isAtEnd() || source[current] != expected)
        return false;
    current++;
    return true;
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        case '(': addToken("LEFT_PAREN", "("); break;
        case ')': addToken("RIGHT_PAREN", ")"); break;
        case '{': addToken("LEFT_BRACE", "{"); break;
        case '}': addToken("RIGHT_BRACE", "}"); break;
        case '*': addToken("STAR", "*"); break;
        case '.': addToken("DOT", "."); break;
        case '+': addToken("PLUS", "+"); break;
        case ',': addToken("COMMA", ","); break;
        case '-': addToken("MINUS", "-"); break;
        case ';': addToken("SEMICOLON", ";"); break;
        case '!': {
            bool eq = match('=');
            addToken(eq ? "BANG_EQUAL" : "BANG", eq ? "!=" : "!");
            break;
        }
        case '=': {
            bool eq = match('=');
            addToken(eq ? "EQUAL_EQUAL" : "EQUAL", eq ? "==" : "=");
            break;
        }
        case '/':
            if (match('/')) {
                while (peek() != '\n' && !isAtEnd())
                    advance();
            } else {
                addToken("SLASH", "/");
            }
            break;
        case '"': scanString(); break;
        case ' ':
        case '\r':
        case '\t': break;
        case '\n': line++; break;
        default:
            if (isdigit(c))
                scanNumber();
            else if (isAlphaOrUnderscore(c))
                scanIdentifier();
            else {
                std::cerr << "[line " << line << "] Error: Unexpected character: " << c << "\n";
                hadError = true;
            }
            break;
    }
}

void Scanner::scanString() {
    std::string literal;
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        literal.push_back(advance());
    }
    if (isAtEnd()) {
        std::cerr << "[line " << line << "] Error: Unterminated string.\n";
        hadError = true;
        return;
    }
    advance(); // Consume closing '"'
    addToken("STRING", "\"" + literal + "\"", literal);
}

void Scanner::scanNumber() {
    while (isdigit(peek()))
        advance();
    if (peek() == '.' && isdigit(peekNext())) {
        advance();
        while (isdigit(peek()))
            advance();
    }
    std::string lexeme = source.substr(start, current - start);
    addToken("NUMBER", lexeme, lexeme);
}

void Scanner::scanIdentifier() {
    while (isAlphaNumOrUnderscore(peek()))
        advance();
    std::string lexeme = source.substr(start, current - start);
    addToken("IDENTIFIER", lexeme);
}
