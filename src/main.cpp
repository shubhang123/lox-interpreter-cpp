#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Forward declarations.
std::string readFileContents(const std::string &filename);
bool tokenize(const std::string &input);
void printUsageAndExit(const std::string &programName);
void addToken(const std::string &type, const std::string &lexeme);

int main(int argc, char *argv[])
{
    // Disable output buffering.
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::cerr << "Logs from your program will appear here!" << std::endl;

    if (argc < 3)
    {
        printUsageAndExit(argv[0]);
    }

    const std::string command = argv[1];
    const std::string filename = argv[2];

    if (command != "tokenize")
    {
        std::cerr << "Unknown command: " << command << std::endl;
        printUsageAndExit(argv[0]);
    }

    std::string fileContents = readFileContents(filename);
    bool hadError = tokenize(fileContents);

    return hadError ? 65 : 0;
}

// Reads the entire content of a file into a single string.
std::string readFileContents(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error reading file: " << filename << std::endl;
        std::exit(1);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Helper to add tokens.
void addToken(const std::string &type, const std::string &lexeme)
{
    std::cout << type << " " << lexeme << " null" << std::endl;
}

void addToken(const std::string &type, const std::string &lexeme, const std::string &literal)
{
    std::cout << type << " " << lexeme << " " << literal << std::endl;
}

/**
 * Tokenize the input string.
 *
 * This function prints valid tokens to stdout and lexical errors to stderr.
 * It handles two-character tokens (like ==, !=, <=, >=) using a helper lambda,
 * supports the division operator (/), and ignores single-line comments (//).
 * The function also tracks line numbers, starting at 1.
 *
 * Returns true if any lexical errors were encountered.
 */
bool tokenize(const std::string &input)
{
    bool hadError = false;
    int inputSize = input.length();
    int line = 1; // Start line numbers at 1.

    // Lambda to check for a two-character operator.
    auto match = [&](int &index, char expected) -> bool
    {
        if (index + 1 < inputSize && input[index + 1] == expected)
        {
            index++; // Consume the next character.
            return true;
        }
        return false;
    };

    for (int index = 0; index < inputSize; index++)
    {
        char c = input[index];
        switch (c)
        {
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
            if (match(index, '='))
            {
                addToken("EQUAL_EQUAL", "==");
            }
            else
            {
                addToken("EQUAL", "=");
            }
            break;
        case '!':
            if (match(index, '='))
            {
                addToken("BANG_EQUAL", "!=");
            }
            else
            {
                addToken("BANG", "!");
            }
            break;
        case '<':
            if (match(index, '='))
            {
                addToken("LESS_EQUAL", "<=");
            }
            else
            {
                addToken("LESS", "<");
            }
            break;
        case '>':
            if (match(index, '='))
            {
                addToken("GREATER_EQUAL", ">=");
            }
            else
            {
                addToken("GREATER", ">");
            }
            break;
        case '/':
            if (match(index, '/'))
            {
                // Single-line comment: skip until newline or end-of-file.
                while (index + 1 < inputSize && input[index + 1] != '\n')
                {
                    index++;
                }
            }
            else
            {
                addToken("SLASH", "/");
            }
            break;
            case '"': {  // String literal processing
                std::string literal = "";
                index++; // Move past the opening quote
          
                while (index < inputSize && input[index] != '"') {
                  if (input[index] == '\n') {
                    line++;  // Handle multi-line strings
                  }
                  literal.push_back(input[index]);
                  index++;
                }
    
                if (index >= inputSize) {
                  std::cerr << "[line " << line << "] Error: Unterminated string." << std::endl;
                  hadError = true;
                } else {
                  addToken("STRING", "\"" + literal + "\"", literal);
                }
                break;
              }
        // Ignore whitespace (but update line number on newline).
        case ' ':
        case '\t':
        case '\r':
            break;
        case '\n':
            line++;
            break;
        default:
            std::cerr << "[line " << line << "] Error: Unexpected character: " << c
                      << std::endl;
            hadError = true;
            break;
        }
    }

    // Finally, add the EOF token.
    addToken("EOF", "");
    return hadError;
}

// Prints usage information and exits the program.
void printUsageAndExit(const std::string &programName)
{
    std::cerr << "Usage: " << programName << " tokenize <filename>" << std::endl;
    std::exit(1);
}
