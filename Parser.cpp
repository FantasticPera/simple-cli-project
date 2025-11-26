#include "Parser.h"

using namespace std;


void  Parser::parse(string input) {

	
	if (input.length() > 512) {
		input = input.substr(0, 512);
	}

	string currToken;
	bool inQMarks = false;

	for (int i = 0; i < input.length(); i++) {

		char c = input[i];

		if (c == '"') {
			inQMarks = !inQMarks;
			if (!inQMarks and (input[i + 1] == ' ' or input[i + 1] == '"' or input.empty())) {
				currToken += "\"";
				Parser::addTempToken(currToken);
				currToken.clear();
				i++;
				continue;
			}
		}

		if (inQMarks and c == '\\' and input[i+1] == 'n') {
			currToken = currToken + '\n';
			i++;
		}

		else if ((c == '<' or c == '>' or c == '|') and !inQMarks) {
			if (!currToken.empty()) {
				Parser::addTempToken(currToken);
				currToken.clear();
			}
			Parser::addTempToken(string(1, c));
		}



		else if (c == ' ' and !inQMarks) {
			if (!currToken.empty()) {
				Parser::addTempToken(currToken);
				currToken.clear();
			}
		}

		else {
			currToken = currToken + c;
		}

	}

	if (!currToken.empty()) {
		Parser::addTempToken(currToken);
		currToken.clear();
	}

	vector<string> words = Parser::getTempTokens();
	vector<string> temp;

	if (!words.empty()) {
		for (int i = 0; i < words.size(); i++) {
			if (words[i] != "|") {
				temp.push_back(words[i]);
			}
			else {
				Parser::addFinalToken(temp);
				temp.clear();
			}
		}
	}

	if (!temp.empty()) {
		Parser::addFinalToken(temp);
		temp.clear();
	}



}




