//============================================================================
// Name        : names_and_surnames_2.cpp
// Author      : Andre Marin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <string>

using namespace std;


// if the name is unknown, returns an empty string
string FindNameByYear (const map <int, string, greater<int>> & names, int year) {
   string name; // initially unknown name
	  auto it = names.lower_bound(year);

	  if(it != names.end()) {
		  name = it->second;
	  }

   return name;
}

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }
  string GetFullName(int year) {
    // получаем имя и фамилию по состоянию на год year
    const string first_name = FindNameByYear(first_names, year);
    const string last_name = FindNameByYear(last_names, year);

    // если и имя, и фамилия неизвестны
    if (first_name.empty() && last_name.empty()) {
      return "Incognito";

    // если неизвестно только имя
    } else if (first_name.empty()) {
      return last_name + " with unknown first name";

    // если неизвестна только фамилия
    } else if (last_name.empty()) {
      return first_name + " with unknown last name";

    // если известны и имя, и фамилия
    } else {
      return first_name + " " + last_name;
    }
  }

  string GetFullNameWithHistory(int year) {
    // получить все имена и фамилии по состоянию на конец года year
	  string s;
	  return s;
  }

private:
  map<int, string, greater<int>> first_names;
  map<int, string, greater<int>> last_names;
};


int main() {
	// Regression tests
	{
		Person person;

		person.ChangeFirstName(1965, "Polina");
		person.ChangeLastName(1967, "Sergeeva");
		assert("Incognito" == person.GetFullName(1900));
		assert("Polina with unknown last name" == person.GetFullName(1965));
		assert("Polina Sergeeva" == person.GetFullName(1990));

		person.ChangeFirstName(1970, "Appolinaria");
		assert("Polina Sergeeva" == person.GetFullName(1969));
		assert("Appolinaria Sergeeva" == person.GetFullName(1970));

		person.ChangeLastName(1968, "Volkova");
		assert("Polina Volkova" == person.GetFullName(1969));
		assert("Appolinaria Volkova" == person.GetFullName(1970));

	}

	// Regression tests
	{
		Person person;

		assert("Incognito" == person.GetFullName(2000));

		person.ChangeLastName(1968, "1968_2nd");
		person.ChangeLastName(1967, "1967_2nd");
		person.ChangeLastName(1965, "1965_2nd");
		person.ChangeLastName(1966, "1966_2nd");
		assert("Incognito" == person.GetFullName(1900));
		assert("Incognito" == person.GetFullName(1920));
		assert("Incognito" == person.GetFullName(1950));
		assert("1965_2nd with unknown first name" == person.GetFullName(1965));
		assert("1966_2nd with unknown first name" == person.GetFullName(1966));
		assert("1967_2nd with unknown first name" == person.GetFullName(1967));
		assert("1968_2nd with unknown first name" == person.GetFullName(1968));

		person.ChangeFirstName(1920, "1920_1st");
		person.ChangeFirstName(1900, "1900_1st");
		person.ChangeFirstName(1965, "1965_1st");
		person.ChangeFirstName(1950, "1950_1st");
		assert("1900_1st with unknown last name" == person.GetFullName(1900));
		assert("1920_1st with unknown last name" == person.GetFullName(1920));
		assert("1950_1st with unknown last name" == person.GetFullName(1950));
		assert("1965_1st 1965_2nd" == person.GetFullName(1965));
		assert("1965_1st 1966_2nd" == person.GetFullName(1966));
		assert("1965_1st 1967_2nd" == person.GetFullName(1967));
		assert("1965_1st 1968_2nd" == person.GetFullName(1968));
	}

	// Start of new test 1
	{
		Person person;

		person.ChangeFirstName(1900, "Eugene");
		person.ChangeLastName(1900, "Sokolov");
		person.ChangeLastName(1910, "Sokolov");
		person.ChangeFirstName(1920, "Evgeny");
		person.ChangeLastName(1930, "Sokolov");
		assert("Evgeny (Eugene) Sokolov" == person.GetFullNameWithHistory(1940));

	}

	// Start of new test 2
	{
		  Person person;

		  person.ChangeFirstName(1965, "Polina");
		  person.ChangeLastName(1967, "Sergeeva");
		  assert("Incognito" == person.GetFullNameWithHistory(1900));
		  assert("Polina with unknown last name" == person.GetFullNameWithHistory(1965));
		  assert("Polina Sergeeva" == person.GetFullNameWithHistory(1990));

		  person.ChangeFirstName(1970, "Appolinaria");
		  assert("Polina Sergeeva" == person.GetFullNameWithHistory(1969));
		  assert("Appolinaria (Polina) Sergeeva" == person.GetFullNameWithHistory(1970));

		  person.ChangeLastName(1968, "Volkova");
		  assert("Polina Volkova (Sergeeva)" == person.GetFullNameWithHistory(1969));
		  assert("Appolinaria (Polina) Volkova (Sergeeva)" == person.GetFullNameWithHistory(1970));

		  person.ChangeFirstName(1990, "Polina");
		  person.ChangeLastName(1990, "Volkova-Sergeeva");
		  assert("Polina (Appolinaria, Polina) Volkova-Sergeeva (Volkova, Sergeeva)" == person.GetFullNameWithHistory(1990));

		  person.ChangeFirstName(1966, "Pauline");
		  assert("Pauline (Polina) with unknown last name" == person.GetFullNameWithHistory(1966));

		  person.ChangeLastName(1960, "Sergeeva");
		  assert("Sergeeva with unknown first name" == person.GetFullNameWithHistory(1960));
		  assert("Pauline (Polina) Sergeeva" == person.GetFullNameWithHistory(1967));

		  person.ChangeLastName(1961, "Ivanova");
		  assert("Pauline (Polina) Sergeeva (Ivanova, Sergeeva)" == person.GetFullNameWithHistory(1967));
	}

	// Start of new test 3
	{
		  Person person;

		  person.ChangeFirstName(1965, "Polina");
		  person.ChangeFirstName(1965, "Appolinaria");
		  person.ChangeLastName(1965, "Sergeeva");
		  person.ChangeLastName(1965, "Volkova");
		  person.ChangeLastName(1965, "Volkova-Sergeeva");
		  assert("Incognito" == person.GetFullNameWithHistory(1964));
		  assert("Appolinaria Volkova-Sergeeva" == person.GetFullNameWithHistory(1965));
		  assert("Appolinaria Volkova-Sergeeva" == person.GetFullNameWithHistory(1966));
	}

	return 0;
}
