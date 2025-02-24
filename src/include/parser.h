#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

// Minimal parser token types.
enum class PTokenType {
    TRUE,
    FALSE,
    NIL,
    NUMBER,
    EOF_TOKEN
};

struct PToken {
    PTokenType type;
    std::string lexeme;
};

// A function to scan tokens for the parser.
std::vector<PToken> scanTokensForParser(const std::string &source);

// Expression hierarchy for the parser.
struct Expr {
    virtual ~Expr() = default;
    virtual std::string print() const = 0;
};

struct LiteralExpr : public Expr {
    std::string value;
    LiteralExpr(const std::string &value);
    std::string print() const override;
};

// Minimal parser that expects a single literal.
class Parser {
public:
    Parser(const std::vector<PToken>& tokens);
    Expr* parse();
private:
    const std::vector<PToken>& tokens;
    size_t current;
};

#endif // PARSER_H
