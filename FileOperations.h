#ifndef FileOperations_h
#define FileOperations_h

#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>
#include "ArgumentChecker.h"

class FileOperations
{
public:
	static bool createFile(std::string fileName);
	static bool fileExists(std::string fileName);
	static bool readFile(std::string fileName, std::string& fileContent);
	static bool deleteFile(std::string fileName);
	static bool deleteFileContent(std::string fileName);
	static bool writeFileContent(std::string fileName, std::string content);
	
};
#endif

