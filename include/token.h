#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

// Define our token types.
enum TokenType {
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_STAR,
    TOKEN_DOT,
    TOKEN_PLUS,
    TOKEN_COMMA,
    TOKEN_MINUS,
    TOKEN_SEMICOLON,
    TOKEN_BANG,
    TOKEN_BANG_EQUAL,
    TOKEN_EQUAL,
    TOKEN_EQUAL_EQUAL,
    TOKEN_LESS,
    TOKEN_LESS_EQUAL,
    TOKEN_GREATER,
    TOKEN_GREATER_EQUAL,
    TOKEN_SLASH,

    // Literals
    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_NUMBER,

    // Keywords
    TOKEN_AND,
    TOKEN_CLASS,
    TOKEN_ELSE,
    TOKEN_FALSE,
    TOKEN_FOR,
    TOKEN_FUN,
    TOKEN_IF,
    TOKEN_NIL,
    TOKEN_OR,
    TOKEN_PRINT,
    TOKEN_RETURN,
    TOKEN_SUPER,
    TOKEN_THIS,
    TOKEN_TRUE,
    TOKEN_VAR,
    TOKEN_WHILE,

    TOKEN_EOF
};

struct Token {
    TokenType type;
    std::string lexeme;
    std::string literal;  // For storing literal values (e.g. number or string)
    int line;
};

// Helper function to convert a token type to a string.
inline std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TOKEN_LEFT_PAREN:       return "LEFT_PAREN";
        case TOKEN_RIGHT_PAREN:      return "RIGHT_PAREN";
        case TOKEN_LEFT_BRACE:       return "LEFT_BRACE";
        case TOKEN_RIGHT_BRACE:      return "RIGHT_BRACE";
        case TOKEN_STAR:             return "STAR";
        case TOKEN_DOT:              return "DOT";
        case TOKEN_PLUS:             return "PLUS";
        case TOKEN_COMMA:            return "COMMA";
        case TOKEN_MINUS:            return "MINUS";
        case TOKEN_SEMICOLON:        return "SEMICOLON";
        case TOKEN_BANG:             return "BANG";
        case TOKEN_BANG_EQUAL:       return "BANG_EQUAL";
        case TOKEN_EQUAL:            return "EQUAL";
        case TOKEN_EQUAL_EQUAL:      return "EQUAL_EQUAL";
        case TOKEN_LESS:             return "LESS";
        case TOKEN_LESS_EQUAL:       return "LESS_EQUAL";
        case TOKEN_GREATER:          return "GREATER";
        case TOKEN_GREATER_EQUAL:    return "GREATER_EQUAL";
        case TOKEN_SLASH:            return "SLASH";
        case TOKEN_IDENTIFIER:       return "IDENTIFIER";
        case TOKEN_STRING:           return "STRING";
        case TOKEN_NUMBER:           return "NUMBER";
        case TOKEN_AND:              return "AND";
        case TOKEN_CLASS:            return "CLASS";
        case TOKEN_ELSE:             return "ELSE";
        case TOKEN_FALSE:            return "FALSE";
        case TOKEN_FOR:              return "FOR";
        case TOKEN_FUN:              return "FUN";
        case TOKEN_IF:               return "IF";
        case TOKEN_NIL:              return "NIL";
        case TOKEN_OR:               return "OR";
        case TOKEN_PRINT:            return "PRINT";
        case TOKEN_RETURN:           return "RETURN";
        case TOKEN_SUPER:            return "SUPER";
        case TOKEN_THIS:             return "THIS";
        case TOKEN_TRUE:             return "TRUE";
        case TOKEN_VAR:              return "VAR";
        case TOKEN_WHILE:            return "WHILE";
        case TOKEN_EOF:              return "EOF";
        default:                     return "UNKNOWN";
    }
}

#endif // TOKEN_HPP
