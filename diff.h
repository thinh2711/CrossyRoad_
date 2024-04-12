#ifndef __DIFF_H__
#define __DIFF_H__
#include <string>

std::string normalize(const std::string& s);
std::string chooseWord(const std::string& fileName, int difficult);
bool contains(std::string word, char guess);

#endif 