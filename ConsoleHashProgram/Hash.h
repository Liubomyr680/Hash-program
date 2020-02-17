#pragma once
#include <string>


class Hash {

	std::string hash;
	int receivingExistCodes(int x);
	int getControlSum(std::string str);
public:
	std::string getHash(std::string userString, unsigned int lengthHash);
};

