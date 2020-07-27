//============================================================================
// Name        : table.cpp
// Author      : Andre Marin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>      // std::setw
#include <vector>
#include <sstream>
using namespace std;

void print(vector<vector<int>> str_v, size_t rows, size_t columns) {
	for(size_t i = 0; i < rows; ++i) {
		for(size_t j = 0; j < columns; ++j) {
			cout << "row(" << i << "): " << str_v[i][j] << endl;
		}
	}
}
int main() {
	ifstream input("input.txt");

	if(!input.is_open()) {
		cout << "Error opening input.txt" << endl;
		return -1;
	}

	size_t rows = 0, columns = 0;
	input >> rows >> columns;
	input.ignore(1);

//	cout << rows << endl;
//	cout << columns << endl;
	vector<vector<int>> str_v(rows);
	string line;

	for(size_t i = 0; i < str_v.size(); ++i) {
		input >> line;
		//cout << "line: " << line << endl;
		std::stringstream ss(line);

		string token;
		while(getline(ss, token, ',')) {
			//cout << "line[j]: " << line[j] << endl;
			str_v[i].push_back(stoi(token));
		}
	}
	//print(str_v, rows, columns);

	for(size_t row = 0; row < str_v.size(); ++row) {
		const auto& row_list = str_v[row];

		int col = 0;
		for(; col < row_list.size(); ++col) {
			const auto row_size = str_v.size() - 1;
			const auto col_size = row_list.size() - 1;
			const auto space = col == row_list.size() - 1 ? "" : " ";

			string newline;
			if( (row != row_size) && (col == col_size) ) {
				newline = "\n";
			}
			else {
				newline = "";
			}
			cout << setw(10) << str_v[row][col] << space << newline;
		}
		//cout << endl;
	}

	return 0;
}
