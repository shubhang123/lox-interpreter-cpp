#include "../include/scanner.h"
#include "../include/token.h"
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

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    addToken(TOKEN_EOF, "", "null");
    return tokens;
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

void Scanner::addToken(TokenType type, const std::string &lexeme, const std::string &literal) {
    tokens.push_back({type, lexeme, literal, line});
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        case '(': addToken(TOKEN_LEFT_PAREN, "("); break;
        case ')': addToken(TOKEN_RIGHT_PAREN, ")"); break;
        case '{': addToken(TOKEN_LEFT_BRACE, "{"); break;
        case '}': addToken(TOKEN_RIGHT_BRACE, "}"); break;
        case '*': addToken(TOKEN_STAR, "*"); break;
        case '.': addToken(TOKEN_DOT, "."); break;
        case '+': addToken(TOKEN_PLUS, "+"); break;
        case ',': addToken(TOKEN_COMMA, ","); break;
        case '-': addToken(TOKEN_MINUS, "-"); break;
        case ';': addToken(TOKEN_SEMICOLON, ";"); break;
        case '!': {
            bool eq = match('=');
            addToken(eq ? TOKEN_BANG_EQUAL : TOKEN_BANG, eq ? "!=" : "!");
            break;
        }
        case '=': {
            bool eq = match('=');
            addToken(eq ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL, eq ? "==" : "=");
            break;
        }
        case '<': {
            bool eq = match('=');
            addToken(eq ? TOKEN_LESS_EQUAL : TOKEN_LESS, eq ? "<=" : "<");
            break;
        }
        case '>': {
            bool eq = match('=');
            addToken(eq ? TOKEN_GREATER_EQUAL : TOKEN_GREATER, eq ? ">=" : ">");
            break;
        }
        case '/':
            if (match('/')) {
                // Skip single-line comment.
                while (peek() != '\n' && !isAtEnd())
                    advance();
            } else {
                addToken(TOKEN_SLASH, "/", "null");
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
    addToken(TOKEN_STRING, lexeme, literal);
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
    addToken(TOKEN_NUMBER, lexeme, literal);
}

void Scanner::scanIdentifier() {
    std::unordered_map<std::string, TokenType> keywords{
        {"and", TOKEN_AND},
        {"class", TOKEN_CLASS},
        {"else", TOKEN_ELSE},
        {"false", TOKEN_FALSE},
        {"for", TOKEN_FOR},
        {"fun", TOKEN_FUN},
        {"if", TOKEN_IF},
        {"nil", TOKEN_NIL},
        {"or", TOKEN_OR},
        {"print", TOKEN_PRINT},
        {"return", TOKEN_RETURN},
        {"super", TOKEN_SUPER},
        {"this", TOKEN_THIS},
        {"true", TOKEN_TRUE},
        {"var", TOKEN_VAR},
        {"while", TOKEN_WHILE}
    };

    while (isAlphaNumOrUnderscore(peek()))
        advance();
    std::string lexeme = source.substr(start, current - start);
    if (keywords.find(lexeme) != keywords.end()) {
        addToken(keywords[lexeme], lexeme, "null");
    } else {
        addToken(TOKEN_IDENTIFIER, lexeme, "null");
    }
}
