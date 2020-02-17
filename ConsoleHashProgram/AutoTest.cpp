#include "pch.h"
#include "ctime"
#include <map>
#include "Hash.h"
#include "AutoTest.h"
#include <iomanip>
#include <iostream>

namespace test
{
	AutoTest::AutoTest(int countIteration)
	{
		this->countIteration = countIteration;
		srand(time(NULL));
	}

	int AutoTest::getCharFromSum(int x) {
		x += 256;

		while (!(((x <= 57) && (x >= 48)) || ((x <= 90) && (x >= 65)) || ((x <= 122) && (x >= 97)))) {
			if (x < 48)
				x += 24;
			else
				x -= 47;
		}
		return x;
	}

	//	We generate a random period
	std::string AutoTest::generationString() {
		std::string str;
		std::string chars = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
		int lengthString = rand() % 16 + 5;

		for (int i = 0; i < lengthString; i++)
			str += this->getCharFromSum((int)chars[rand() % chars.size() + 0]);

		return str;
	}

	void AutoTest::goTestRandom(int lengthTemp) {

		int countCollision = 0;

		std::string stringTemp;
		std::string resaultTemp;
		std::multimap <std::string, std::string> hashMap;

		for (int i = 0; i < this->countIteration; i++)
		{
			stringTemp = this->generationString();

			Hash hash;
			//	In the resaultTemp variable we enter the already hashed string, the original of which we generated above
			resaultTemp = hash.getHash(stringTemp, lengthTemp);

			hashMap.insert(std::multimap<std::string, std::string>::value_type(stringTemp, resaultTemp));
		}

		std::cout << "\t\t    (string)  |  hash\n\n";		
			
		for (auto str : hashMap) {
			for (auto otherStr : hashMap) {
				if (str.first != otherStr.first)
					if (str.second == otherStr.second) {

						countCollision++;
						
						std::cout << "Collision (I): "
							<< " (" << str.first << ") " << std::setw(5) << str.second<<" --------"
							<< std::setw(5) << " (J): " << "(" << otherStr.first << ") " << std::setw(5) << otherStr.second << std::endl;
					}
			}
		}

		std::cout << "\nCount collision: " << countCollision << " / " << this->countIteration << std::endl;
	}
}