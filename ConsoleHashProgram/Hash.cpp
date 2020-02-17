#include "pch.h"
#include "Hash.h"


int Hash::receivingExistCodes(int x) {
	x += 256;

	while (!(((x <= 57) && (x >= 48)) || ((x <= 90) && (x >= 65)) || ((x <= 122) && (x >= 97)))) {
		if (x < 48)
			x += 24;
		else
			x -= 47;
	}
	return x;
}

int Hash::getControlSum(std::string str) {

	unsigned int sault = 0;

	for (int i = 0; i < str.size(); i++)
		sault += (int)str[i];

	return sault;
}

std::string Hash::getHash(std::string userString, unsigned int lengthHash) {

	if (lengthHash > 3)
	{		
		unsigned int unrealLenHashstr = 1;		
		unsigned int realHashLength = 0;
		
		unsigned int originalSoult = this->getControlSum(userString);
		unsigned int originalLengthStr = userString.size();

		// Getting the length of the string closest to the specified hash length
		while (unrealLenHashstr <= lengthHash)
			realHashLength = (unrealLenHashstr *= 2);

		// 	This loop is needed if we enter a string for an example of 20 characters and want to get a hash of 5 characters
		while (unrealLenHashstr < originalLengthStr)
			unrealLenHashstr *= 2;

		// Make the hash length at least twice as long as the original one
		if ((unrealLenHashstr - originalLengthStr) < unrealLenHashstr)
			unrealLenHashstr *= 2;
		
		int addCharCount = unrealLenHashstr - originalLengthStr;
		
		for (int i = 0; i < addCharCount; i++)
			userString += this->receivingExistCodes(userString[i] + userString[i + 1]);

		int maxSault = this->getControlSum(userString);
		int maxLengthStr = userString.size();
	
		while (userString.size() != realHashLength)
		{
			for (int i = 0, center = userString.size() / 2; i < center; i++)
				this->hash += this->receivingExistCodes(userString[center - i] + userString[center + i]);

			userString = this->hash;
			this->hash.clear();
		}
		
		for (int i = 0; this->hash.size() < (lengthHash - 4); i++)
		{
			if (i % 2 == 0)
				this->hash += this->receivingExistCodes(userString[i] + userString[i+1]);
			else
				this->hash += userString[i];
		}
		
		this->hash += this->receivingExistCodes(originalSoult);
		this->hash += this->receivingExistCodes(originalLengthStr);
		
		this->hash += this->receivingExistCodes(maxSault);
		this->hash += this->receivingExistCodes(maxLengthStr);

		return this->hash;
	}
	return "";
}
