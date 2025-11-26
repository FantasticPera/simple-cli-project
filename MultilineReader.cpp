#include "MultilineReader.h"
using namespace std;


string MultilineReader::readMultiline() {
	string input;
	char c;
	while (true) {
		if (_kbhit()) { // is character pressed on keyboard
			c = _getch();
			if (c == 26){ // 26 stands for ctrl+z

				if (input[input.size()] != '\n' and !input.empty()) {
					cout << '\n';
				}
				break;
			}
			if (c == '\r') { //enter character
				cout << '\n';
				input = input + '\n';
			}
			else if (c == '\b') { // backspace character
				if (!input.empty()) {
					input.pop_back();
					cout << "\b \b";
				}
			}
			else {
				cout << c;
				input = input + c;
			}
		}
	}
	return input;
}