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
		int entry=0;
		while (!(std::cin >> entry)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			std::cout << "Enter a valid number\n";
		}
		if (entry >= 500) {
			cout << "Please enter a smaller number.\n";
			Entry();
		}
		else return entry;
	}

	void Game::Menu() {
		int choice;
		while (exit != true) {
			cout << "********************************************\n";
			cout << "1 - Start a game\n";
			cout << "2 - Display players\n";
			cout << "3 - Add a player\n";;
			cout << "4 - Delete a player\n";
			cout << "5 - Settings\n";
			cout << "6 - Exit\n";
			cout << "Enter your choice and press return.\n";

			choice = Entry();

			switch (choice) {
			case 1:
				ChoosePlayers();
				break;
			case 2:
				cout << "All players:\n";
				for (int i = 1; i < playerCount; i++) {
					cout << i << ": " << this->players[i].GetNickname() << " Score: " << this->players[i].GetScore() << "\n";
				}
				break;
			case 3:
				CreatePlayers();
				break;
			case 4:
				int num;
				cout << "What player do you want to delete ?\n";
				for (int i = 1; i < playerCount; i++) {
					cout << i << ": " << this->players[i].GetNickname() << " Score: " << this->players[i].GetScore() << "\n";
				}
				num = Entry();
				cout << "Are you sure yo uwant to delete "<< players[num].GetNickname() <<" ? 1.Yes / 2.No\n";
				choice = Entry();
				if (choice==1)DeletePlayers(choice);
				break;
			case 5:
				cout << "Current grid is " << this->width << " rows for " << this->height << " columns. Do you want to resize ? 1.Yes / 2.No\n";
				choice = Entry();
				if (choice == 1) {
					cout << "Keep in mid high numbers may not be supported! Enter number of rows: \n";
					num = Entry();
					this->width = num;
					cout << "Enter number of columns: \n";
					num = Entry();
					this->height = num;
				}
				break;
			
			case 6:
				exit = true;
				break;
			default:
				cout << "Not a valid choice.\n";
				break;
			}
		}
	}

	void Game::CreatePlayers() {
		if (playerCount == 13) {
			cout << "Reached the maximum number of player. Please delete before adding one.\n";
			exit;
		}
		string nickname;
		cout << "Enter nickname of a new player : \n";
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

		if (this->playerCount < 3) {
			cout << "You need to create at least 2 players ! \n";
			this->CreatePlayers();
			this->CreatePlayers();
		}
		if (this->playerCount == 3) {
			cout << "Shall " << this->players[1].GetNickname() << " begin as Red ? 1. Yes / 2. No\n";
			choice1 = Entry();
			choice1 == 1 ? Play(1, 2) : Play(2,1);
		}
		else {
			cout << "Contenders: \n";
			for (int i = 1; i < playerCount; i++) {
				cout << i << ": " << this->players[i].GetNickname() << " Score: " << this->players[i].GetScore() << "\n";
			}
			cout << "Choose first contender (Red):\n";
			choice1 = Entry();
			if (choice1 > playerCount + 1) {
				cout << "Invalid choice\n";
				ChoosePlayers();
			}
			cout << "Choose second contender (Yellow):\n";
			choice2 = Entry();
			if (choice2 > playerCount + 1 || choice2 == choice1) {
				cout << "Invalid choice\n";
				ChoosePlayers();
			}
			cout << players[choice1].GetNickname() << " will go against: " << players[choice2].GetNickname() << "\nLet the struggle begins !\n";
			Play(choice1, choice2);
		}
		
	}

	void Game::Play(int p1, int p2) {
		this->gameOn = true;
		int turnPlayer = p1;

		Board* board;
		board = new Board(this->width,this->height);
		int columnChoosen;

		while (this->gameOn) {
			board->Display();
			cout << "[" << players[turnPlayer].GetNickname() << "] your turn, which column do you choose ? : ";
			
			columnChoosen = Entry();
			if (columnChoosen >= 1 && !(columnChoosen >= this->width)) { //for some reason 7 can be used with default width, if condition is columnChoosen <=width.

				char nextPlayer = turnPlayer == p1 ? 'R' : 'Y';

				bool next = board->AddToken(columnChoosen, nextPlayer);

				gameOn = !board->WinRules(nextPlayer);

				turnPlayer = turnPlayer == p1 ? p2 : p1;
			}
			else cout << "Please enter a number within range.\n";
		}

		board->Display();

		turnPlayer = turnPlayer == p1 ? p2 : p1;
		cout << "WIN FOR " << players[turnPlayer].GetNickname() << "!!!" << "\n" << std::endl;
		players[turnPlayer].SetScore(players[turnPlayer].GetScore() + 1);
		cout << "score is: " << players[turnPlayer].GetNickname() << " with " << players[turnPlayer].GetScore() << "\nfor ";
		turnPlayer = turnPlayer == p1 ? p2 : p1;
		players[turnPlayer].SetScore(players[turnPlayer].GetScore() - 1);
		cout << players[turnPlayer].GetNickname() << " with " << players[turnPlayer].GetScore() << "\n";

		delete board;
	}
}