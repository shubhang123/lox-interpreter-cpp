#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Forward declarations
std::string readFileContents(const std::string& filename);
bool tokenize(const std::string& input);
void printUsageAndExit(const std::string& programName);

int main(int argc, char* argv[]) {
    // Disable output buffering (std::unitbuf automatically flushes after each insertion)
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // Debug/log message
    std::cerr << "Logs from your program will appear here!" << std::endl;

    // Basic argument check
    if (argc < 3) {
        printUsageAndExit(argv[0]);
        return 1;
    }

    const std::string command = argv[1];
    const std::string filename = argv[2];

    if (command == "tokenize") {
        std::string fileContents = readFileContents(filename);
        
        // tokenize returns `true` if any errors were encountered
        bool hadError = tokenize(fileContents);

        // If lexical errors were present, exit with code 65
        if (hadError) {
            return 65;
        }
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        printUsageAndExit(argv[0]);
        return 1;
    }

    // If no errors, exit with code 0
    return 0;
}

// Reads the entire content of a file into a single string.
std::string readFileContents(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error reading file: " << filename << std::endl;
        std::exit(1);  // Exiting if we can't open the file
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

/**
 * Tokenize the input string. 
 *
 * Prints valid tokens to stdout and prints errors to stderr in the format:
 *  [line 1] Error: Unexpected character: <character>
 * 
 * Returns true if any lexical errors were encountered, false otherwise.
 */
bool tokenize(const std::string& input) {
    bool hadError = false;
    int inputSize = input.length();


    for (int index = 0; index < inputSize; index++) {
        char c = input[index];
        switch (c) {
            case '(':
                std::cout << "LEFT_PAREN ( null" << std::endl;
                break;
            case ')':
                std::cout << "RIGHT_PAREN ) null" << std::endl;
                break;
            case '{':
                std::cout << "LEFT_BRACE { null" << std::endl;
                break;
            case '}':
                std::cout << "RIGHT_BRACE } null" << std::endl;
                break;
            case '*':
                std::cout << "STAR * null" << std::endl;
                break;
            case '.':
                std::cout << "DOT . null" << std::endl;
                break;
            case '+':
                std::cout << "PLUS + null" << std::endl;
                break;
            case ',':
                std::cout << "COMMA , null" << std::endl;
                break;
            case '-':
                std::cout << "MINUS - null" << std::endl;
                break;
            case ';':
                std::cout << "SEMICOLON ; null" << std::endl;
                break;
            case '=':
                if(index + 1 < inputSize && input[index + 1] == '='){
                    std::cout << "EQUAL_EQUAL == null" << std::endl;
                }else{
                    std::cout << "EQUAL = null" << std::endl;
                }
                break;
            // Ignore common whitespace so it doesn't produce an error.
            // (In later stages, you might handle newlines to track line numbers properly.)
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

    // Finally, print an EOF token
    std::cout << "EOF  null" << std::endl;

    return hadError;
}

// Prints usage information and exits the program.
void printUsageAndExit(const std::string& programName) {
    std::cerr << "Usage: " << programName << " tokenize <filename>" << std::endl;
    std::exit(1);
}
