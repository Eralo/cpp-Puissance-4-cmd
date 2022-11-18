#pragma once
#include<string>
using namespace std;

namespace models {

	class Case
	{
	private:
		int x, y;
		char value;

	public:
		Case();
		Case(int, int, char);
		char GetValue();
		void SetValue(char);
	};

}