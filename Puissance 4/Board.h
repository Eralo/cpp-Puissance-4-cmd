#pragma once
#include<string>
#include"Case.h"
using namespace std;

namespace models {

	class Board
	{
	private:
		int nbCol = 7, nbRow = 6;
		Case** board;

	public:
		Board();
		Board(int row, int column);
		~Board();
		void Display();
		bool AddToken(int, char);
		bool WinRules(char);
	};

}