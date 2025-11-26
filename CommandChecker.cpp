#include "CommandChecker.h"

using namespace std;

bool CommandChecker::checkCommands(vector<vector<string>>& commands) {

	if (commands.size() == 0) return false;

	//sintaksna provera
	string commandsReplica;
	string errorLine;
	int position = 0;
	bool synErrorFound = false;
	bool inQMarks = false;
	for (int i = 0; i < commands.size(); i++) { // pipeline section
		for (int j = 0; j < commands[i].size(); j++) { //word in section
			bool nextToQMarks = false;
			
			if (commands[i][j].find('"') != string::npos and commands[i][j][0] != '"') nextToQMarks = true;
			for (int k = 0; k < commands[i][j].size(); k++) { // character in section
				char c = commands[i][j][k];

				if (c == '"') {
					inQMarks = !inQMarks;
					errorLine += " ";
					nextToQMarks = true;
				}
				else if (inQMarks) {
					errorLine += " ";
				}

				else if ((c >= '0' and c <= '9')) {
					// It's only allowed in "" or in head command
					if (inQMarks or (commands[i][0] == "head" and j == 1)) {
						errorLine += " ";
					}
					else {
						errorLine += "^";
						synErrorFound = true;
					}
				}

				else if (((c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z') or c == '<' or c == '>' or c == '-' or c == '.' or c == '/') and !nextToQMarks) {
					errorLine += " ";
				}
				else {
					errorLine += "^";
					synErrorFound = true;
				}
			}
			commandsReplica += commands[i][j] + " ";
			errorLine += " ";

		}

		if (commands.size() != i+1) {
			commandsReplica += "| ";
			errorLine += "  ";
		}

	}

	if (synErrorFound) {
		cerr << "Error - unexpected characters: " << endl;
		cout << commandsReplica << endl;
		cout << errorLine << endl;
		return false;

	}



	//Checking if the command name exists in every group
	int j = 0;
	for (auto commandGroup : commands) {
		j++;
		if (!commandGroup.empty()) {
			if (!CommandManager::commandExists(commandGroup[0])) {
				cerr << "Error - Unknown command: " << commandGroup[0] << endl;
				return false;
			}
		}
		else {
			cerr << "Error - No commands found in pipeline section "<< j << "." << endl;
			return false;
		}
	}

	//Checking the pipeline pattern
	if (commands.size() > 1) {
		for (int i = 0; i < commands.size(); i++) {
			string commandName = commands[i][0];
			CommandFeatures commandFeature = CommandManager::getCommandFeature(commandName);

			if (i == 0) {
				if (!commandFeature.sends) { //if the first command does not send argument
					cerr << "Error - Command: " << commandName << " does not send output" << endl;
					return false;
				}
			}
			else if (i == commands.size() - 1) { // if the last command does not recieve input argument
				if (!commandFeature.receives) {
					cerr << "Error - Command: " << commandName << " does not receive input" << endl;
					return false;
				}
			}
			else { //if all other commands in between do not both send and recieve argumetns
				if (!commandFeature.sends or !commandFeature.receives) {
					cerr << "Error - Command: " << commandName << " does not properly hande I/O" << endl;
					return false;
				}
			}

		}
	}

	//Redirection checking
	int inRedIndex = -1;
	int outRedIndex = -1;
	for (int i = 0; i < commands.size(); i++) {
		auto& commandGroup = commands[i]; //reference of the original

		auto inRed = std::find(commandGroup.begin(), commandGroup.end(), "<");

		if (inRed != commandGroup.end() and i != 0) {
			cerr << "Error - Invalid use of in redirection ('<')." << endl;
			return false;
		}

		auto outRed = std::find(commandGroup.begin(), commandGroup.end(), ">");
		// > and >> not on the first or last place in the pipeline
		if (commands.size() == 1) {
			if (outRed != commandGroup.end() and (i != 0 and i != commands.size() - 1)) { 
				cerr << "Error - Invalid use of out redirection ('>', '>>')." << endl;
				return false;
			}
		}
		else {
			if (outRed != commandGroup.end() and i != commands.size() - 1) {
				cerr << "Error - Invalid use of out redirection ('>', '>>')." << endl;
				return false;
			}
		}

		if (inRed != commandGroup.end()) inRedIndex = i;

		if (outRed != commandGroup.end()) {
			outRedIndex = i;
			auto next = outRed + 1;
			//merging two >
			if (next != commandGroup.end() && *next == ">") {
				*outRed = ">>";
				commands[i].erase(next);
			}
		}

	}




	//Checking argument of the commands

	for (int i = 0; i < commands.size(); i++) {

		string commandName = commands[i][0];
		if (commandName == "time" or commandName == "date") {
			if (outRedIndex == i) {
				if (commands[i].size() != 3) {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}
			}
			else if (commands[i].size() != 1) {
				cerr << "Error - Unexpected arguments" << endl;
				return false;
			}
		}
		else if (commandName == "echo") {

			//has in and out
			if (inRedIndex == i and outRedIndex == i) {
				if (commands[i].size() != 5) {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}
			}
			//only in
			else if (inRedIndex == i) {
				if (commands[i].size() != 3) {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}
			}
			//only out or without out
			else if (commands[i].size() >= 2) {


				if (i == 0) {
					if (ArgumentChecker::checkArgument(commands[i][1]) > 1) {
						cerr << "Error - Invalid argument" << endl;
						return false;
					}
					else if (ArgumentChecker::checkArgument(commands[i][1]) == 0) {
						if (!ArgumentChecker::checkFilename(commands[i][1])) {
							cerr << "Error - Invalid file name, file name cannot contain character: \\ / : * ? \" < > | " << endl;
							return false;
						}
					}
				}

				if (outRedIndex == i) {
					if ((commands[i].size() != 4 and i == 0) or (i != 0 and commands[i].size() != 3)) {
						cerr << "Error - Unexpected arguments" << endl;
						return false;
					}
				}
				// no redirection
				else if (((commands[i].size() > 2 or commands[i].size() < 1) and i == 0) or (commands[i].size() != 1 and i != 0)) {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}

			}
			else if (((commands[i].size() > 2 or commands[i].size() < 1) and i == 0) or (commands[i].size() != 1 and i != 0)) {
				cerr << "Error - Unexpected arguments" << endl;
				return false;
			}
		}
		else if (commandName == "touch") {

			if (inRedIndex == i) {
				if (commands[i].size() != 3) {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}

				if (ArgumentChecker::checkArgument(commands[i][1]) > 1) {
					cerr << "Error - Invalid argument" << endl;
					return false;
				}
			}

			else if ((commands[i].size() != 2 and i== 0) or (commands[i].size() != 1 and i != 0)) {
				cerr << "Error - Unexpected arguments" << endl;
				return false;
			}

		}
		else if (commandName == "wc") {

			//Checking option
			if (commands[0].size() >= 2) {
				if (commands[i][1] != "-w" and commands[i][1] != "-c") {
					cerr << "Error - Unexpected option: " << commands[0][1] << endl;
					return false;
				}
			}

			//Multi-line case
			if (commands[0].size() < 2) {
				cerr << "Error - Unexpected arguments" << endl;
				return false;
			}

			//has in and out
			if (inRedIndex == i and outRedIndex == i) {
				if (commands[i].size() != 6) {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}
			}
			//only has in
			else if (inRedIndex == i) {
				if (commands[i].size() != 4) {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}
			}
			//only out
			else if (commands[i].size() >= 3) {

				if (i == 0) {
					if (ArgumentChecker::checkArgument(commands[i][2]) > 1) {
						cerr << "Error - Invalid argument" << endl;
						return false;
					}
					else if (ArgumentChecker::checkArgument(commands[i][2]) == 0) {
						if (!ArgumentChecker::checkFilename(commands[i][2])) {
							cerr << "Error - Invalid file name, file name cannot contain character: \\ / : * ? \" < > | " << endl;
							return false;
						}
					}
				}

				if (outRedIndex == i) {
					if ((commands[i].size() != 5 and i == 0) or (i != 0 and commands[i].size() != 4)) {
						cerr << "Error - Unexpected arguments" << endl;
						return false;
					}
				}

				else if ((commands[i].size() != 3 and i == 0) or (i != 0 and commands[i].size() != 2)) {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}
			}


		}
		else if (commandName == "prompt") {
			if (commands[i].size() == 2) {
				if (ArgumentChecker::checkArgument(commands[i][1]) != 1) {
					cerr << "Error - Invalid argument" << endl;
					return false;
				}
			}
			else if (commands[0].size() == 1) {
				
				cerr << "Error - argument is not provided" << endl;
				return false;
			}
			else if (commands[0].size() > 2) {
				cerr << "Error - Unexpected arguments" << endl;
				return false;
			}
		}
		else if (commandName == "truncate") {
			if (inRedIndex == i) {
				if (commands[i].size() != 3) {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}

				if (ArgumentChecker::checkArgument(commands[i][1]) > 1) {
					cerr << "Error - Invalid argument" << endl;
					return false;
				}
			}

			else if ((commands[i].size() != 2 and i == 0) or (commands[i].size() != 1 and i != 0)) {
				cerr << "Error - Unexpected arguments" << endl;
				return false;
			}
		}
		else if (commandName == "rm") {
			if (inRedIndex == i) {
				if (commands[i].size() != 3) {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}

				if (ArgumentChecker::checkArgument(commands[i][1]) > 1) {
					cerr << "Error - Invalid argument" << endl;
					return false;
				}
			}

			else if ((commands[i].size() != 2 and i == 0) or (commands[i].size() != 1 and i != 0)) {
				cerr << "Error - Unexpected arguments" << endl;
				return false;
			}
		}
		else if (commandName == "tr") {
			//no redirection
			if (inRedIndex == -1 and outRedIndex == -1) {
				if (commands[i].size() == 4 or commands[i].size() == 3) {
					if (ArgumentChecker::checkArgument(commands[i][1]) > 1) {
						cerr << "Error - Invalid argument" << endl;
						return false;
					}
					else if (ArgumentChecker::checkArgument(commands[i][1]) == 0) {
						if (!ArgumentChecker::checkFilename(commands[i][1])) {
							cerr << "Error - Invalid file name, file name cannot contain characters: \\ / : * ? \" < > | " << endl;
							return false;
						}
					}

					if (ArgumentChecker::checkArgument(commands[i][2]) > 1) {
						cerr << "Error - invalid [what] content." << endl;
						return false;
					}

					if (commands[i].size() == 4) {
						if (ArgumentChecker::checkArgument(commands[i][3]) > 1) {
							cerr << "Error - invalid [with] content." << endl;
							return false;
						}
					}
				}
				//Multi-line case
				else if (commands[i].size() == 2) {
					if (ArgumentChecker::checkArgument(commands[i][1]) > 1) {
						cerr << "Error - invalid [what] content." << endl;
						return false;
					}
				}
				else {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}
			}
			// has in and out
			if (inRedIndex == i and outRedIndex == i) {
				if (commands[i].size() == 6 or commands[i].size() == 7) {

					if (ArgumentChecker::checkArgument(commands[i][1]) > 1) {
						cerr << "Error - invalid [what] content." << endl;
						return false;
					}

					if (commands[i].size() == 7) {
						if (ArgumentChecker::checkArgument(commands[i][2]) > 1) {
							cerr << "Error - invalid [with] content." << endl;
							return false;
						}
					}

				}
				else {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}
			}

			//only has in
			else if (inRedIndex == i) {
				if (commands[i].size() == 4 or commands[i].size() == 5) {

					if (ArgumentChecker::checkArgument(commands[i][1]) > 1) {
						cerr << "Error - invalid [what] content." << endl;
						return false;
					}

					if (commands[i].size() == 5) {
						if (ArgumentChecker::checkArgument(commands[i][2]) > 1) {
							cerr << "Error - invalid [with] content." << endl;
							return false;
						}
					}

				}
				else {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}
			}

			//only has out
			else if (outRedIndex == i) {
				if (((commands[i].size() == 5 or commands[i].size() == 6) and i == 0) or ((commands[i].size() == 4 or commands[i].size() == 5) and i != 0)) {

					if (i == 0) {
						if (ArgumentChecker::checkArgument(commands[i][1]) > 1) {
							cerr << "Error - Invalid argument" << endl;
							return false;
						}
						else if (ArgumentChecker::checkArgument(commands[i][1]) == 0) {
							if (!ArgumentChecker::checkFilename(commands[i][1])) {
								cerr << "Error - Invalid file name, file name cannot contain characters: \\ / : * ? \" < > | " << endl;
								return false;
							}
						}

						if (ArgumentChecker::checkArgument(commands[i][2]) > 1) {
							cerr << "Error - invalid [what] content." << endl;
							return false;
						}

						if (commands[i].size() == 6) {
							if (ArgumentChecker::checkArgument(commands[i][3]) > 1) {
								cerr << "Error - invalid [with] content." << endl;
								return false;
							}
						}
					}

					else {
						if (ArgumentChecker::checkArgument(commands[i][1]) > 1) {
							cerr << "Error - invalid [what] content." << endl;
							return false;
						}

						if (commands[i].size() == 5) {
							if (ArgumentChecker::checkArgument(commands[i][2]) > 1) {
								cerr << "Error - invalid [with] content." << endl;
								return false;
							}
						}
					}
				}
				else {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}
			}


		}
		else if (commandName == "head") {
			

			if (commands[i].size() >= 2) {
				string option = commands[i][1];
				int nCount;

				if (option.size() < 2) {
					cerr << "Error - Unexpected option: " << commands[0][1] << endl;
					return false;
				}
				if (option.substr(0, 2) != "-n") {
					cerr << "Error - Unexpected option: " << option.substr(0, 2) << endl;
					return false;
				}

				try {
					nCount = stoi(option.substr(2));
				}
				catch (exception& e) {
					cerr << "Error - Invalid option: " << commands[0][1] << endl;
					return false;
				}

				if (nCount < 0 or nCount > 99999) {
					cerr << "Error - Invalid number of rows in option." << endl;
					return false;
				}




			}
			else {
				cerr << "Error - Unexpected arguments" << endl;
				return false;
			}


			//has in and out

			if (inRedIndex == i and outRedIndex == i) {
				if (commands[i].size() != 6) {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}

			}

			//only has in

			else if (inRedIndex == i) {
				if (commands[i].size() != 4) {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}
			}

			//only has out
			else if (outRedIndex == i) {

				if (commands[i].size() > 2 and commands[i].size() <= 5) {

					if ((commands[i].size() != 5 and i==0) or (commands[i].size() != 4 and i != 0)) {
						cerr << "Error - Unexpected arguments" << endl;
						return false;
					}

					if (i == 0) {
						if (ArgumentChecker::checkArgument(commands[i][2]) > 1) {
							cerr << "Error - Invalid argument" << endl;
							return false;
						}
						else if (ArgumentChecker::checkArgument(commands[i][2]) == 0) {
							if (!ArgumentChecker::checkFilename(commands[i][2])) {
								cerr << "Error - Invalid file name, file name cannot contain characters: \\ / : * ? \" < > | " << endl;
								return false;
							}
						}
					}
				}

				else if (commands[i].size() != 2) {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}

			}
			else if (((commands[i].size() < 2  or commands[i].size() > 3) and i == 0) or (commands[i].size() != 2 and i != 0)) {
				cerr << "Error - Unexpected arguments" << endl;
				return false;
			}
		}
		else if (commandName == "batch") {
			//has in and out
			if (inRedIndex == i and outRedIndex == i) {
				if (commands[i].size() != 5) {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}
			}
			
			//only in 
			else if (inRedIndex == i) {
				if (commands[i].size() != 3) {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}
			}

			else if (commands[i].size() >= 2) {


				if (i == 0) {
					if (ArgumentChecker::checkArgument(commands[i][1]) > 1) {
						cerr << "Error - Invalid argument" << endl;
						return false;
					}
					else if (ArgumentChecker::checkArgument(commands[i][1]) == 0) {
						if (!ArgumentChecker::checkFilename(commands[i][1])) {
							cerr << "Error - Invalid file name, file name cannot contain character: \\ / : * ? \" < > | " << endl;
							return false;
						}
					}
				}
				//only out red

				if (outRedIndex == i) {
					if ((commands[i].size() != 4 and i == 0) or (i != 0 and commands[i].size() != 3)) {
						cerr << "Error - Unexpected arguments" << endl;
						return false;
					}
				}
				// no redirection
				else if ((commands[i].size() != 2 and i == 0) or (commands[i].size() != 1 and i != 0)) {
					cerr << "Error - Unexpected arguments" << endl;
					return false;
				}
			}
			else if ((commands[i].size() != 2 and i == 0) or (commands[i].size() != 1 and i != 0)) {
				cerr << "Error - Unexpected arguments" << endl;
				return false;
			}
		}
		
	}
	return true;
}

