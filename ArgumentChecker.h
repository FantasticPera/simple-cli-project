#ifndef ArgumentChecker_h
#define ArgumentChecker_h

#include <string>

class ArgumentChecker
{
public:
	static int checkArgument(std::string arg);
	static bool checkFilename(std::string filename);
};
#endif

