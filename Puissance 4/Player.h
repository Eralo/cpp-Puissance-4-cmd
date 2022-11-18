#pragma once
#include<string>
using namespace std;

namespace models {

	class Player
	{
	private:
		int id;
		string nickname;
		int score=0;

	public:
		Player();
		Player(string name);
		string GetNickname();
		int GetScore();
		void SetScore(int);
	};
}