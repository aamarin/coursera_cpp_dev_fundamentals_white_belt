//============================================================================
// Name        : names_and_surnames.cpp
// Author      : Andre Marin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <map>
#include <string>
#include <cassert>

using namespace std;

// if name is unknown, returns an empty string
string FindNameByYear (const map <int, string> & names, int year) {
  string name; // initially unknown name
  
  // iterate over the entire history in ascending order of the dictionary key, that is, in chronological order
  for (const auto & item: names) {
    // if the next year is not more than the given one, update the name
    if (item.first <= year) {
      name = item.second;
    } else {
      // otherwise it's time to stop, since this entry and all subsequent ones refer to the future
      break;
    }
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

string GetFullName (int year) {
    // get first and last name as of year year
    const string first_name = FindNameByYear (first_names, year);
    const string last_name = FindNameByYear (last_names, year);
    
    // if both first and last name are unknown
    if (first_name.empty () && last_name.empty ()) {
      return "Incognito";
    
    // if only the name is unknown
    } else if (first_name.empty ()) {
      return last_name + "with unknown first name";
      
    // if only the last name is unknown
    } else if (last_name.empty ()) {
      return first_name + "with unknown last name";
      
    // if both name and surname are known
    } else {
      return first_name + "" + last_name;
    }
  }

  string GetFullNameWithHistory(int year) {
	  return "";
  }

private:
  map<int, string> first_names;
  map<int, string> last_names;
};

int main() {

	{
		Person person;

		person.ChangeFirstName(1900, "Eugene");
		person.ChangeLastName(1900, "Sokolov");
		person.ChangeLastName(1910, "Sokolov");
		person.ChangeFirstName(1920, "Evgeny");
		person.ChangeLastName(1930, "Sokolov");
		assert("Evgeny (Eugene) Sokolov" == person.GetFullNameWithHistory(1940));
	}

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
		assert("Polina (Appolinaria, Polina) Volkova-Sergeeva (Volkova, Sergeeva)" ==  person.GetFullNameWithHistory(1990));
		
		person.ChangeFirstName(1966, "Pauline");
		assert("Pauline (Polina) with unknown last name" == person.GetFullNameWithHistory(1966));
		
		person.ChangeLastName(1960, "Sergeeva");
		assert("Sergeeva with unknown first name" == person.GetFullNameWithHistory(1960));
		assert("Pauline (Polina) Sergeeva" == person.GetFullNameWithHistory(1967));
		
		person.ChangeLastName(1961, "Ivanova");
		assert("Pauline (Polina) Sergeeva (Ivanova, Sergeeva)" == person.GetFullNameWithHistory(1967));
	}

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



