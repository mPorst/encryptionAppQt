#ifndef FILEHELPER_H
#define FILEHELPER_H
#endif

#include <string>
#include <QString>
#include <fstream>
#include <vector>

unsigned int FileSize(std::fstream* f);
std::string fileText(std::string filename);
std::vector<int> characterDistribution(std::string filename);
