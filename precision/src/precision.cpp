//============================================================================
// Name        : precision.cpp
// Author      : Andre Marin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
	ifstream input("input.txt");
	string line;

	if(!input.is_open()) {
		cout << "Error" << endl;
		return -1;
	}

	double val = 0.0;
    while( getline (input, line) ) {
    	val = stod(line);
        cout << fixed << setprecision(3) << val << endl;
    }

	return 0;
}
