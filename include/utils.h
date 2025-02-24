#ifndef UTILS_H
#define UTILS_H

#include <string>

std::string readFileContents(const std::string &filename);
void printUsageAndExit(const std::string &programName);
// addToken prints a token with a type, lexeme, and an optional literal (defaults to "null").
void addToken(const std::string &type, const std::string &lexeme, const std::string &literal = "null");

#endif // UTILS_H
