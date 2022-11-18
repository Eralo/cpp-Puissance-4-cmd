#include "Player.h"
#include<string>
#include<iostream>
using namespace std;

namespace models {

	Player::Player() {
		this->nickname = "NoName";
		this->score = 0;
	}

	Player::Player(string name) :nickname(name), score(0) {
	}

	string Player::GetNickname() {
		return this->nickname;
	}

	int Player::GetScore() {
		return this->score;
	}

	void Player::SetScore(int tscore) {
		this->score = tscore;
	}

}