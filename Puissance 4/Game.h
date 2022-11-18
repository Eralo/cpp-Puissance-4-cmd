#pragma once
#include<string>
#include"Board.h"
#include"Player.h"
using namespace std;
using namespace models;

namespace controllers {

	class Game
	{
	private:
		Player* players;
		int playerCount=1;
		bool gameOn = false, exit = false;
		int Entry();
		int width=7;
		int height=6;

	public:
		Game();
		~Game();
		void Menu();
		void CreatePlayers();
		void DeletePlayers(int);
		void ChoosePlayers();
		void Play(int, int);
	};

}