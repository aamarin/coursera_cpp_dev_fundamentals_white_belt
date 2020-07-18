//============================================================================
// Name        : LectureTitleStructure.cpp
// Author      : Andre Marin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>

using namespace std;

struct Specialization {
	string _s;
	explicit Specialization(const string& s):_s(s) {}
};

struct Course {
	string _s;
	explicit Course(const string& s):_s(s) {}
};

struct Week {
	string _s;
	explicit Week(const string& s):_s(s) {}
};

struct LectureTitle {
  string specialization;
  string course;
  string week;
	explicit LectureTitle(const Specialization& s,
						  const Course& c,
						  const Week& w){
		specialization = s._s;
		course = c._s;
		week = w._s;
	}
};



int main() {
	LectureTitle title(
	    Specialization("C++"),
	    Course("White belt"),
	    Week("4th")
	);
	return 0;
}
