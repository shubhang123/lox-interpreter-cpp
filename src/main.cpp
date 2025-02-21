#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string readFileContents(const std::string& filename);
void tokenize(const std::string& input);
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
        tokenize(fileContents);
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        printUsageAndExit(argv[0]);
        return 1;
    }

    return 0;
}

//Reads the entire content of a file into a single string.
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

void tokenize(const std::string& input) {
    for (char c : input) {
        switch (c) {
            case '(':
                std::cout << "LEFT_PAREN ( null" << std::endl;
                break;
            case ')':
                std::cout << "RIGHT_PAREN ) null" << std::endl;
                break;
            case '{':
                std::cout << "LEFT_BRACE { null"<< std::endl;
                break;
            case '}':
                std::cout << "RIGHT_BRACE } null"<< std::endl;
                break;
            case '*':
                std::cout << "STAR * null"<< std::endl;
                break;
            case '.':
                std::cout << "DOT . null"<< std::endl;
                break;
            case '+':
                std::cout << "PLUS + null"<< std::endl;
                break;
            case ',':
                std::cout << "COMMA , null"<< std::endl;
                break;
            case '-':
                std::cout << "MINUS - null"<< std::endl;
                break;
            case ';':
                std::cout << "SEMICOLON ; null"<< std::endl;
                break;
            default:
                break;
        }
    }
    std::cout << "EOF  null" << std::endl;
}

//Prints usage information and exits the program.
void printUsageAndExit(const std::string& programName) {
    std::cerr << "Usage: " << programName << " tokenize <filename>" << std::endl;
    std::exit(1);
}
