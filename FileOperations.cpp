#include "FileOperations.h"
using namespace std;

bool FileOperations::createFile(std::string fileName) {

	if (!ArgumentChecker::checkFilename(fileName)) {
		cerr << "Error - Invalid file name, file name cannot contain character: \\ / : * ? \" < > | " << endl;
		return false;
	}

	if (fileExists(fileName)) {
		cerr << "Error - File with name: " << fileName << " already exists" << endl;
		return false;
	}

	ofstream outFile(fileName);
	if (outFile.is_open()) {
		outFile.close();
		return true;
	}
	else {
		cerr << "Error - An error occurred while creating a file" << endl;
		outFile.close();
		return false;
	}
}

bool FileOperations::fileExists(std::string fileName) {
	ifstream dummyFile(fileName);
	if (dummyFile.is_open()) return true;
	else return false;
}

bool FileOperations::readFile(string fileName, string& fileContent) {
	if (!ArgumentChecker::checkFilename(fileName)) {
		cerr << "Error - Invalid file name, file name cannot contain character: \\ / : * ? \" < > | " << endl;
		return false;
	}

	ifstream inFile(fileName);
	if (inFile.is_open()) {
		string line;
		if (getline(inFile, line)) {
			fileContent += line;
			while (getline(inFile, line)) {
				fileContent += "\n" + line;
			}
		}
		inFile.close();
		return true;
	}
	else {
		cerr << "Error - An error occurred while reading the file." << endl;
		return false;
	}
}

bool FileOperations::deleteFile(std::string fileName)
{
	if (!ArgumentChecker::checkFilename(fileName)) {
		cerr << "Error - Invalid file name, file name cannot contain character: \\ / : * ? \" < > | " << endl;
		return false;
	}

	if (remove(fileName.c_str()) == 0) {
		return true;
	}
	else {
		cerr << "Error - An error occurred while deleting the file" << endl;
		return false;
	}
}

bool FileOperations::deleteFileContent(std::string fileName)
{
	if (!ArgumentChecker::checkFilename(fileName)) {
		cerr << "Error - Invalid file name, file name cannot contain character: \\ / : * ? \" < > | " << endl;
		return false;
	}

	if (!fileExists(fileName)) {
		cerr << "Error - File does not exist, cannot delete content." << endl;
		return false;
	}

	ofstream outFile(fileName, ios::trunc);
	if (outFile.is_open()) {
		outFile.close();
		return true;
	}
	else {
		cerr << "Error - An error occurred while deleting file content." << endl;
		return false;
	}
}

bool FileOperations::writeFileContent(std::string fileName, std::string content)
{
	if (!ArgumentChecker::checkFilename(fileName)) {
		cerr << "Error - Invalid file name, file name cannot contain character: \\ / : * ? \" < > | " << endl;
		return false;
	}

	ofstream outFile(fileName, ios::app);
	if (outFile.is_open()) {
		outFile << content;
		outFile.close();
		return true;
	}
	else {
		cerr << "Error - An error occurred while deleting file content." << endl;
		return false;
	}
}
