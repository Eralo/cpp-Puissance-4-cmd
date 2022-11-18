#include "Board.h"
#include<string>
#include<iostream>
using namespace std;

namespace models {

    Board::Board() {
        board = new Case * [9];
    }

    Board::Board(int row, int column) : nbCol(column), nbRow(row) {
        board = new Case * [row];
        for (int i = 0; i < row; i++) {
            board[i] = new Case[column];
        }
    }

    Board::~Board() {
        delete board;
    }

    void Board::Display() {

        string str;
        for (int t1 = 0; t1 < this->nbCol; ++t1) {
            str += "  " + to_string(t1 + 1) + " ";
        }
        str += "\n";
        for (int t2 = 0; t2 < this->nbCol; ++t2) {
            str += "*---";
        }
        str += "*\n";
        for (int x = 0; x < this->nbRow; ++x) {
            for (int y = 0; y < nbCol; ++y) {
                str += "| ";
                str += this->board[x][y].GetValue();
                str += " ";
            }
            str += "|\n";
        }
        for (int t2 = 0; t2 < this->nbCol; ++t2) {
            str += "*---";
        }
        str += "*\n";
        cout << str << endl;
    }


    bool Board::AddToken(int tColumn, char token) {
        if (this->board[0][tColumn - 1].GetValue() != '.') {
            cout << this->board[0][tColumn - 1].GetValue()<<endl;
            return false;
        }
        for (int x = this->nbRow - 1; x > -1; --x) {
            if (this->board[x][tColumn - 1].GetValue() == '.') {
                this->board[x][tColumn - 1].SetValue(token);;
                return true;
            }
        }
    }

    bool Board::WinRules(char player) {     //strenghten algorythm if possible ? Has to be adaptable to all sizes.
 
            //horizontal
        for (int y = 0; y < nbCol-3; y++) {
            for (int x = 0; x < nbRow; x++) {
                if (board[x][y].GetValue() == player) {
                    if (board[x][y+1].GetValue() == player) {
                        if (board[x][y+2].GetValue() == player) {
                            if (board[x][y+3].GetValue() == player) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
            //vertical

        for (int x = 0; x < nbRow-3; x++) {
            for (int y = 0; y < nbCol; y++) {
                if (board[x][y].GetValue() == player){
                    if (board[x + 1][y].GetValue() == player) {
                        if (board[x + 2][y].GetValue() == player) {
                            if (board[x + 3][y].GetValue() == player) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        //diagonal: top left to bottom right
        for (int x = 3; x < nbRow; x++) {
            for (int y = 3; y < nbCol - 3; y++) {
                if (board[x][y].GetValue() == player) {
                    if (board[x - 1][y - 1].GetValue() == player) {
                        if (board[x - 2][y - 2].GetValue() == player) {
                            if (board[x - 3][y - 3].GetValue() == player) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
            //diagonal: top right to bottom left
        for (int x = 3; x < nbRow; x++) {
            for (int y = 0; y < nbCol -3; y++) {
                if (board[x][y].GetValue() == player) {
                    if (board[x - 1][y + 1].GetValue() == player) {
                        if (board[x - 2][y + 2].GetValue() == player) {
                            if (board[x - 3][y + 3].GetValue() == player) {
                                return true;
                            }
                        }
                    }
                }
            }
        }

        return false;
    }
}