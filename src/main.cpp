#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>   // for isdigit()
#include <cstdlib>  // for std::exit()

// Reads the entire content of a file into a single string.
std::string readFileContents(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error reading file: " << filename << std::endl;
        std::exit(1);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void printUsageAndExit(const std::string &programName) {
    std::cerr << "Usage: " << programName << " tokenize <filename>" << std::endl;
    std::exit(1);
}

// Simple token printing helpers.
void addToken(const std::string &type, const std::string &lexeme) {
    std::cout << type << " " << lexeme << " null" << std::endl;
}

void addToken(const std::string &type, const std::string &lexeme, const std::string &literal) {
    std::cout << type << " " << lexeme << " " << literal << std::endl;
}

// The Scanner class encapsulates tokenization logic.
class Scanner {
public:
    Scanner(const std::string &source)
        : source(source), start(0), current(0), line(1), hadError(false) {}

    // Scans tokens and prints them. Returns true if any errors occurred.
    bool scanTokens() {
        while (!isAtEnd()) {
            start = current;
            scanToken();
        }
        addToken("EOF", "");
        return hadError;
    }

private:
    const std::string source;
    int start;
    int current;
    int line;
    bool hadError;

    bool isAtEnd() const {
        return current >= static_cast<int>(source.length());
    }

    char advance() {
        return source[current++];
    }

    char peek() const {
        return isAtEnd() ? '\0' : source[current];
    }

    char peekNext() const {
        return (current + 1 >= static_cast<int>(source.length())) ? '\0' : source[current + 1];
    }

    bool match(char expected) {
        if (isAtEnd() || source[current] != expected)
            return false;
        current++;
        return true;
    }

    void scanToken() {
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
                    while (peek() != '\n' && !isAtEnd())
                        advance();
                } else {
                    addToken("SLASH", "/");
                }
                break;
            case '"': scanString(); break;
            case ' ':
            case '\r':
            case '\t':
                break;
            case '\n': line++; break;
            default:
                if (std::isdigit(c)) {
                    scanNumber();
                } else if (c - 'a' < 26 || c == '_'){
                    scanIdentifier();
                }else {
                    std::cerr << "[line " << line << "] Error: Unexpected character: " << c << "\n";
                    hadError = true;
                }
                break;
        }
    }

    void scanString() {
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
        advance(); // Consume closing "
        std::string lexeme = "\"" + literal + "\"";
        addToken("STRING", lexeme, literal);
    }

    void scanNumber() {
        while (std::isdigit(peek()))
            advance();
    
        if (peek() == '.' && std::isdigit(peekNext())) {
            advance(); // Consume '.'
            while (std::isdigit(peek()))
                advance();
        }
        
        std::string lexeme = source.substr(start, current - start);
        double number = std::stod(lexeme);
        std::string literal;
        if (number == static_cast<int>(number))
            literal = std::to_string(static_cast<int>(number)) + ".0";
        else
            literal = lexeme;
        
        addToken("NUMBER", lexeme, literal);
    }

    void scanIdentifier() {
        while (std::isalnum(peek()) || peek() == '_') advance();
        std::string lexeme = source.substr(start, current - start);
        addToken("IDENTIFIER", lexeme);
    }
};

int main(int argc, char *argv[]) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::cerr << "Logs from your program will appear here!" << std::endl;

    if (argc < 3)
        printUsageAndExit(argv[0]);

    const std::string command = argv[1];
    const std::string filename = argv[2];

    if (command != "tokenize") {
        std::cerr << "Unknown command: " << command << std::endl;
        printUsageAndExit(argv[0]);
    }

    std::string fileContents = readFileContents(filename);
    Scanner scanner(fileContents);
    bool hadError = scanner.scanTokens();

    return hadError ? 65 : 0;
}
