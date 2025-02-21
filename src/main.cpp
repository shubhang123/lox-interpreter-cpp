#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string readFileContents(const std::string& filename);
bool tokenize(const std::string& input);
void printUsageAndExit(const std::string& programName);
void addToken(const std::string& type, const std::string& lexeme);

int main(int argc, char* argv[]) {
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
    bool hadError = tokenize(fileContents);

    return hadError ? 65 : 0;
}

std::string readFileContents(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error reading file: " << filename << std::endl;
        std::exit(1);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Helper to add tokens.
void addToken(const std::string& type, const std::string& lexeme) {
    std::cout << type << " " << lexeme << " null" << std::endl;
}

/**
 * Tokenize the input string.
 * 
 * This function prints valid tokens to stdout and lexical errors to stderr.
 * For two-character tokens (like ==, !=, <=, >=), a helper lambda is used.
 * Returns true if any lexical errors were encountered.
 */
bool tokenize(const std::string& input) {
    bool hadError = false;
    int inputSize = static_cast<int>(input.length());

    // Lambda to check for a two-character operator.
    auto match = [&](int& index, char expected) -> bool {
        if (index + 1 < inputSize && input[index + 1] == expected) {
            index++;  // Consume the next character.
            return true;
        }
        return false;
    };

    for (int index = 0; index < inputSize; index++) {
        char c = input[index];
        switch (c) {
            case '(':
                addToken("LEFT_PAREN", "(");
                break;
            case ')':
                addToken("RIGHT_PAREN", ")");
                break;
            case '{':
                addToken("LEFT_BRACE", "{");
                break;
            case '}':
                addToken("RIGHT_BRACE", "}");
                break;
            case '*':
                addToken("STAR", "*");
                break;
            case '.':
                addToken("DOT", ".");
                break;
            case '+':
                addToken("PLUS", "+");
                break;
            case ',':
                addToken("COMMA", ",");
                break;
            case '-':
                addToken("MINUS", "-");
                break;
            case ';':
                addToken("SEMICOLON", ";");
                break;
            case '=':
                if (match(index, '=')) {
                    addToken("EQUAL_EQUAL", "==");
                } else {
                    addToken("EQUAL", "=");
                }
                break;
            case '!':
                if (match(index, '=')) {
                    addToken("BANG_EQUAL", "!=");
                } else {
                    addToken("BANG", "!");
                }
                break;
            case '<':
                if (match(index, '=')) {
                    addToken("LESS_EQUAL", "<=");
                } else {
                    addToken("LESS", "<");
                }
                break;
            case '>':
                if (match(index, '=')) {
                    addToken("GREATER_EQUAL", ">=");
                } else {
                    addToken("GREATER", ">");
                }
                break;
            case '/':
                if (match(index, '/')) {
                    while(input[index+1] != '\n' && index +1 < inputSize){
                    index++
                }
                } else {
                    addToken("SLASH", "/");
                }
                break;
            // Ignore common whitespace.
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                break;
            default:
                std::cerr << "[line 1] Error: Unexpected character: " << c << std::endl;
                hadError = true;
                break;
        }
    }

    // Finally, add the EOF token.
    addToken("EOF", "");
    return hadError;
}

// Prints usage information and exits the program.
void printUsageAndExit(const std::string& programName) {
    std::cerr << "Usage: " << programName << " tokenize <filename>" << std::endl;
    std::exit(1);
}
