#include "include/scanner.h"
#include "include/utils.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <unordered_map>

// Helper functions.
static bool isAlphaOrUnderscore(char c) {
    return ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            c == '_');
}

static bool isAlphaNumOrUnderscore(char c) {
    return isAlphaOrUnderscore(c) || (c >= '0' && c <= '9');
}

Scanner::Scanner(const std::string &source)
    : source(source), start(0), current(0), line(1), hadError(false) {}

bool Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    addToken("EOF", "", "null");
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
        case '<': {
            bool eq = match('=');
            addToken(eq ? "LESS_EQUAL" : "LESS", eq ? "<=" : "<");
            break;
        }
        case '>': {
            bool eq = match('=');
            addToken(eq ? "GREATER_EQUAL" : "GREATER", eq ? ">=" : ">");
            break;
        }
        case '/':
            if (match('/')) {
                // Skip single-line comment.
                while (peek() != '\n' && !isAtEnd())
                    advance();
            } else {
                addToken("SLASH", "/", "null");
            }
            break;
        case '"': scanString(); break;
        case ' ':
        case '\r':
        case '\t':
            break;
        case '\n': line++; break;
        default:
            if (std::isdigit(c))
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
    std::string lexeme = "\"" + literal + "\"";
    addToken("STRING", lexeme, literal);
}

void Scanner::scanNumber() {
    while (std::isdigit(peek()))
        advance();

    if (peek() == '.' && std::isdigit(peekNext()))
        advance();

    while (std::isdigit(peek()))
        advance();

    std::string lexeme = source.substr(start, current - start);
    double number = std::stod(lexeme);
    std::string literal;
    if (number == static_cast<int>(number))
        literal = std::to_string(static_cast<int>(number)) + ".0";
    else {
        std::ostringstream oss;
        oss << number;
        literal = oss.str();
    }
    addToken("NUMBER", lexeme, literal);
}

void Scanner::scanIdentifier() {
    std::unordered_map<std::string, std::string> keywords{
        {"and", "AND"},
        {"class", "CLASS"},
        {"else", "ELSE"},
        {"false", "FALSE"},
        {"for", "FOR"},
        {"fun", "FUN"},
        {"if", "IF"},
        {"nil", "NIL"},
        {"or", "OR"},
        {"print", "PRINT"},
        {"return", "RETURN"},
        {"super", "SUPER"},
        {"this", "THIS"},
        {"true", "TRUE"},
        {"var", "VAR"},
        {"while", "WHILE"}
    };

    while (isAlphaNumOrUnderscore(peek()))
        advance();
    std::string lexeme = source.substr(start, current - start);
    if (keywords.find(lexeme) != keywords.end()) {
        addToken(keywords[lexeme], lexeme, "null");
    } else {
        addToken("IDENTIFIER", lexeme, "null");
    }
}
