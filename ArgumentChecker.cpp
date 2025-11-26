#include "ArgumentChecker.h"
using namespace std;

int ArgumentChecker::checkArgument(std::string arg) {

	/*0-> it's file
	1->argument is valid
	2->argument mistake is one the right side
	3->argument mistake is on the left side*/

	if (arg.find('"') == string::npos or (arg[0] == '"' and arg.size() == 1)) return 0;
	else {
		if (arg[0] != '"') return 2;
		if (arg[arg.size() - 1] != '"') return 3;
		return 1;
	}
}

bool ArgumentChecker::checkFilename(string filename) {
	string invalidCharacters = "\\ : *? \" < > |";
	if (filename.find_first_of(invalidCharacters) == string::npos) return true;
	else return false;
}