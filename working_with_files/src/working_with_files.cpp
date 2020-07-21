//============================================================================
// Name        : working_with_files.cpp
// Author      : Andre Marin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <fstream>
#include <iostream>

using namespace std;

int main() {
	ifstream input("input.txt");
	string line;

	if( input.is_open() ) {
	    while(getline(input, line)) {
	        cout << line << endl;
	    }
	} else {
	    cout << "error!" << endl;
	}

	ofstream output("output.txt");
	if( input.is_open() ) {
	    while(getline(input, line)) {
	        output << line << endl;
	    }
	} else {
	    cout << "error!" << endl;
	}

	return 0;
}
