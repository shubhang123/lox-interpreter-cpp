#include "parser.h"
#include <cctype>
#include <iostream>

// Minimal scanner for parser tokens.
std::vector<PToken> scanTokensForParser(const std::string &source) {
    std::vector<PToken> tokens;
    size_t start = 0;
    while (start < source.size()) {
        if (std::isspace(source[start])) {
            start++;
            continue;
        }
        if (source.compare(start, 4, "true") == 0) {
            tokens.push_back({PTokenType::TRUE, "true"});
            start += 4;
        } else if (source.compare(start, 5, "false") == 0) {
            tokens.push_back({PTokenType::FALSE, "false"});
            start += 5;
        } else if (source.compare(start, 3, "nil") == 0) {
            tokens.push_back({PTokenType::NIL, "nil"});
            start += 3;
        } else if (std::isdigit(source[start])) {
            size_t end = start;
            while (end < source.size() && (std::isdigit(source[end]) || source[end] == '.'))
                end++;
            tokens.push_back({PTokenType::NUMBER, source.substr(start, end - start)});
            start = end;
        } else {
            // Skip unknown characters.
            start++;
        }
    }
    tokens.push_back({PTokenType::EOF_TOKEN, ""});
    return tokens;
}

// --- Expression Implementation ---

LiteralExpr::LiteralExpr(const std::string &value) : value(value) {}

std::string LiteralExpr::print() const {
    return value;
}

// --- Minimal Parser Implementation ---

Parser::Parser(const std::vector<PToken>& tokens)
    : tokens(tokens), current(0) {}

Expr* Parser::parse() {
    if (tokens.empty())
        return nullptr;
    PToken token = tokens[current];
    switch (token.type) {
        case PTokenType::TRUE:
        case PTokenType::FALSE:
        case PTokenType::NIL:
        case PTokenType::NUMBER:
            return new LiteralExpr(token.lexeme);
        default:
            std::cerr << "Error: Expected a literal.\n";
        return nullptr;
    }
}
