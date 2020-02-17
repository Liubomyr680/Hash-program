#pragma once
#include <string>

namespace test 
{
	class AutoTest
	{
		int countIteration;
		int getCharFromSum(int x);
		std::string generationString();
	public:
		
		AutoTest(int countIteration);
		void goTestRandom(int lengthTemp);
	};

}




