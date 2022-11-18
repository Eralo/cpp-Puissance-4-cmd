#include "Game.h"
#include<string>
#include<iostream>
using namespace std;

namespace controllers {

	Game::Game() {

		Player* players;
		this->players = new Player[12];
		this->exit = false;
		this->gameOn = false;
		Menu();
	}

	Game::~Game() {
	}

	int Game::Entry() {
		int entry;
		while (!(std::cin >> entry)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			std::cout << "Enter a valid number\n";
		}
		return entry;
	}

	void Game::Menu() {
		int choice;
		while (exit != true) {
			cout << "********************************************\n";
			cout << "1 - Start a game\n";
			cout << "2 - Add a player\n";
			cout << "3 - Delete a player\n";
			cout << "4 - Settings\n";
			cout << "5 - Exit\n";
			cout << "Enter your choice and press return.\n";

			choice = Entry();

			switch (choice) {
			case 1:
				ChoosePlayers();
				break;
			case 2:
				CreatePlayers();
				break;
			case 3:
				int num;
				cout << "What player do you want to delete ?\n";
				for (int i = 0; i < playerCount; i++) {
					cout << i << ": " << this->players[i].GetNickname() << " Score: " << this->players[i].GetScore() << "\n";
				}
				num = Entry();
				cout << "Are you sure yo uwant to delete "<< players[num].GetNickname() <<" ? 1.Yes / 2.No\n";
				choice = Entry();
				if (choice==1)DeletePlayers(choice);
				break;
			case 4:
				cout << "Current grid is " << this->width << " rows for " << this->height << " columns. Do you want to resize ? 1.Yes / 2.No\n";
				choice = Entry();
				if (choice == 1) {
					cout << "Enter number of rows: ";
					num = Entry();
					this->width = num;
					cout << "Enter number of columns: ";
					num = Entry();
					this->height = num;
				}
				break;
			
			case 5:
				exit = true;
				break;
			default:
				cout << "Not a valid choice.";
				break;
			}
		}
	}

	void Game::CreatePlayers() {
		string nickname;
		cout << "Enter nickname of a new player : ";
		cin >> nickname;
		if (nickname == "") Player p;
		Player p(nickname);
		this->players[playerCount] = p;
		this->playerCount++;
	}
	
	void Game::DeletePlayers(int num) {
		for (int i = num; i < playerCount; i++) {
			players[i] = players[i + 1];
		}
		playerCount--;
	}

	void Game::ChoosePlayers() {
		int choice1;
		int choice2;

		if (this->playerCount < 2) {
			cout << "You need to create at least 2 players ! \n";
			this->CreatePlayers();
			this->CreatePlayers();
		}
		if (this->playerCount == 2) {
			cout << "Shall " << this->players[0].GetNickname() << " begin as Red ? 1. Yes / 2. No\n";
			choice1 = Entry();
			choice1 == 1 ? Play(0, 1) : Play(1,0);
		}
		else {
			cout << "Contenders: \n";
			for (int i = 0; i < playerCount; i++) {
				cout << i << ": " << this->players[i].GetNickname() << " Score: " << this->players[i].GetScore() << "\n";
			}
			cout << "Choose first contender (Red):\n";
			choice1 = Entry();
			cout << "Choose second contender (Yellow):\n";
			choice2 = Entry();
			cout << players[choice1].GetNickname() << " will go against: " << players[choice2].GetNickname() << "\nLet the struggle begins !\n";
			Play(choice1, choice2);
		}
		
	}

	void Game::Play(int p1, int p2) {
		this->gameOn = true;
		int turnPlayer = p1;

		Board* board;
		board = new Board(this->width,this->height);

		while (this->gameOn) {
			int columnChoosen;
			board->Display();
			cout << "[" << players[turnPlayer].GetNickname() << "] your turn, which column do you choose ? : ";
			columnChoosen = Entry();

			char nextPlayer = turnPlayer == p1 ? 'R' : 'Y';

			bool next = board->AddToken(columnChoosen, nextPlayer);

			gameOn = !board->WinRules(nextPlayer);

			turnPlayer = turnPlayer == p1 ? p2 : p1;
		}

		board->Display();
		cout << "WIN FOR " << players[turnPlayer].GetNickname() << "!!!" << "\n" << std::endl;
		players[turnPlayer].SetScore(players[turnPlayer].GetScore() + 1);
		cout << "score is: " << players[turnPlayer].GetNickname() << " with " << players[turnPlayer].GetScore() << " for ";
		turnPlayer = turnPlayer == p1 ? p2 : p1;
		players[turnPlayer].SetScore(players[turnPlayer].GetScore() - 1);
		cout << players[turnPlayer].GetNickname() << " with " << players[turnPlayer].GetScore() << "\n";
		delete board;
	}
}