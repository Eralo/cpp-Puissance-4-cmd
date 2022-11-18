#include "Case.h"
#include<string>
#include<iostream>
using namespace std;

namespace models {

	Case::Case() {
		this->value = '.';
	}

	Case::Case(int tx, int ty, char tvalue) : x(tx), y(ty), value(value) {
	}


	char Case::GetValue() {
		return this->value;
	}

	void Case::SetValue(char tvalue) {
		this->value = tvalue;
	}

}