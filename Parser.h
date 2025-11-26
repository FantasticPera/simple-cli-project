#ifndef Parser_h
#define Parser_h

#include <vector>
#include <string>
#include <iostream>


class Parser
{

public:

	Parser() = default;
	~Parser() = default;

	void parse(std::string input);

	void addFinalToken(std::vector<std::string> currToken);

	std::vector<std::vector<std::string>> getFinalTokens();

	void addTempToken(std::string currToken);

	std::vector <std::string> getTempTokens();

	void clearTempTokens();

	void clearFinalTokens();

private:

	std::vector <std::string> tempTokens;
	std::vector<std::vector<std::string>> finalTokens;

};





inline void Parser::clearTempTokens() {
	tempTokens.clear();
}

inline void Parser::addTempToken(std::string currToken) {
	this->tempTokens.push_back(currToken);
}

inline std::vector <std::string> Parser::getTempTokens() {
	return tempTokens;
}

inline void Parser::addFinalToken(std::vector<std::string> currToken) {
	this->finalTokens.push_back(currToken);
}

inline std::vector<std::vector<std::string>> Parser::getFinalTokens() {
	return finalTokens;
}

inline void Parser::clearFinalTokens() {
	finalTokens.clear();
}

#endif
