#ifndef UTILS_H
#define UTILS_H

#include <string>

bool isAlphaOrUnderscore(char c);
bool isAlphaNumOrUnderscore(char c);
std::string readFileContents(const std::string &filename);
void addToken(const std::string &type, const std::string &lexeme);
void addToken(const std::string &type, const std::string &lexeme, const std::string &literal);

#endif // UTILS_H
