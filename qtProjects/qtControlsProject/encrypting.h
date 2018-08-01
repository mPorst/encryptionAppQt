#ifndef ENCRYPTING_H
#define ENCRYPTING_H
#endif

#include <string>


// prototypes
void encryptFile(std::string file, std::string key);
std::string* lengthenKey(std::string* key, unsigned int fileLength);
void deleteUnencrypted(std::string fileName);
