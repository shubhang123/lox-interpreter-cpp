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

// The Scanner class encapsulates all tokenization logic.
class Scanner {
public:
    Scanner(const std::string &source)
        : source(source), start(0), current(0), line(1), hadError(false) {}

    // Scans tokens from the source and prints them.
    // Returns true if any lexical errors were encountered.
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

    // Returns true if we've reached the end of the source.
    bool isAtEnd() const {
        return current >= static_cast<int>(source.length());
    }

    // Consumes and returns the current character.
    char advance() {
        return source[current++];
    }

    // Returns the current character without consuming it.
    char peek() const {
        if (isAtEnd()) return '\0';
        return source[current];
    }

    // Returns the next character after the current one.
    char peekNext() const {
        if (current + 1 >= source.length()) return '\0';
        return source[current + 1];
    }

    // Checks if the next character matches 'expected' and consumes it if so.
    bool match(char expected) {
        if (isAtEnd() || source[current] != expected) return false;
        current++;
        return true;
    }

    // Scans a single token.
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
            case '!':
                addToken(match('=') ? "BANG_EQUAL" : "BANG", match('=') ? "!=" : "!");
                break;
            case '=':
                addToken(match('=') ? "EQUAL_EQUAL" : "EQUAL", match('=') ? "==" : "=");
                break;
            case '<':
                addToken(match('=') ? "LESS_EQUAL" : "LESS", match('=') ? "<=" : "<");
                break;
            case '>':
                addToken(match('=') ? "GREATER_EQUAL" : "GREATER", match('=') ? ">=" : ">");
                break;
            case '/':
                if (match('/')) {
                    // Skip single-line comment.
                    while (peek() != '\n' && !isAtEnd()) {
                        advance();
                    }
                } else {
                    addToken("SLASH", "/");
                }
                break;
            case '"': scanString(); break;
            case ' ':
            case '\r':
            case '\t':
                // Ignore whitespace.
                break;
            case '\n':
                line++;
                break;
            default:
                if (std::isdigit(c)) {
                    scanNumber();
                } else {
                    std::cerr << "[line " << line << "] Error: Unexpected character: " << c << "\n";
                    hadError = true;
                }
                break;
        }
    }

    // Scans a string literal.
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
        advance(); // Consume the closing '"'
        std::string lexeme = "\"" + literal + "\"";
        addToken("STRING", lexeme, literal);
    }

    // Scans a number literal.
    void scanNumber() {
        // Consume all digits in the integer part.
        while (std::isdigit(peek()))
            advance();
    
        // Check for a fractional part.
        if (peek() == '.' && std::isdigit(peekNext())) {
            advance(); // Consume the '.'
            while (std::isdigit(peek()))
                advance();
        }
        
        std::string lexeme = source.substr(start, current - start);
        double number = std::stod(lexeme);
        std::string literal;
        
        // If the number is an integer, format it as "number.0".
        if (number == static_cast<int>(number)) {
            literal = std::to_string(static_cast<int>(number)) + ".0";
        } else {
            literal = lexeme;
        }
        
        addToken("NUMBER", lexeme, literal);
    }
    

    // Emits a token without a literal value.
    void addToken(const std::string &type, const std::string &lexeme) {
        std::cout << type << " " << lexeme << " null" << std::endl;
    }

    // Emits a token with a literal value.
    void addToken(const std::string &type, const std::string &lexeme, const std::string &literal) {
        std::cout << type << " " << lexeme << " " << literal << std::endl;
    }
};

int main(int argc, char *argv[]) {
    // Disable output buffering.
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::cerr << "Logs from your program will appear here!" << std::endl;

    if (argc < 3) {
        printUsageAndExit(argv[0]);
    }

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
