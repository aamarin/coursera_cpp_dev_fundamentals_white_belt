//============================================================================
// Name        : names_and_surnames.cpp
// Author      : Andre Marin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <iterator>

#define DEBUG_ON

using namespace std;

class Person {

	void addFirstNameToMaps(int year, const string& first_name) {
		   auto& [fname_bool, lname_bool] = yr_to_name_call_bool_map[year];
		   fname_bool = true;

		   auto& [fname_str, lname_str] = yr_to_name_map[year];
		   fname_str = first_name;

#ifdef DEBUG_ON
		   cout << "addFirstNameToMaps" << endl;
		   cout << year << " : first name = " << fname_str << ", last name = " << lname_str << endl;
		   cout << fname_bool << " " << lname_bool << endl;
#endif
	}

	void addLastNameToMaps(int year, const string& last_name) {
		   auto& [fname_bool, lname_bool] = yr_to_name_call_bool_map[year];
		   lname_bool = true;

		   auto& [fname_str, lname_str] = yr_to_name_map[year];
		   lname_str = last_name;

#ifdef DEBUG_ON
		   cout << "addLastNameToMaps" << endl;
		   cout << year << " : first name = " << fname_str << ", last name = " << lname_str << endl;
		   cout << fname_bool << " " << lname_bool << endl;
#endif
	}

	bool try_change_first_name(map<int, pair<string,string>, greater<int>>::iterator& it_yr_to_name_map,
							   map<int, pair<bool, bool>, greater<int>>::iterator& it_yr_to_name_call_bool_map) {
		// Do nothing if the input isn't valid
		if(it_yr_to_name_map == yr_to_name_map.end() && it_yr_to_name_call_bool_map == yr_to_name_call_bool_map.end()) {
			cout << "try_change_first_name: Invalid input, exiting...";
			return false;
		}

		// auto [first_name_bool, last_name_bool] = it_yr_to_name_call_bool_map->second;
		auto year = it_yr_to_name_map->first;
		auto& [first_name_str, last_name_str] = it_yr_to_name_map->second;
		auto [first_name_bool, last_name_bool] = it_yr_to_name_call_bool_map->second;
		auto prev_year = prev(it_yr_to_name_map)->first;
		auto& [prev_first_name_str, prev_last_name_str] = prev(it_yr_to_name_map)->second;
		auto [prev_first_name_bool, prev_last_name_bool] = prev(it_yr_to_name_call_bool_map)->second;

#ifdef DEBUG_ON
	cout << "Before: try_change_first_name" << endl;
	cout << year << " : first name = " << first_name_str << ", last name = " << last_name_str << endl;
	cout << year << " : first name function called? = " << first_name_bool << ", last name function called? = " << last_name_bool << endl;
	cout << prev_year << " : prev first name = " << prev_first_name_str << ", prev last name = " << prev_last_name_str << endl;
	cout << prev_year << " : prev first name function called? = " << prev_first_name_bool << ", prev last name function called? = " << prev_last_name_bool << endl;
#endif

	 if(!prev_first_name_bool || prev_first_name_str.empty()) {
		 cout << "try_change_first_name: Parent string is empty or ChangeFirstName not called before" << endl;
		 prev_first_name_str = first_name_str;
	 }

#ifdef DEBUG_ON
	cout << "After: try_change_first_name" << endl;
	cout << year << " : first name = " << first_name_str << ", last name = " << last_name_str << endl;
	cout << year << " : first name function called? = " << first_name_bool << ", last name function called? = " << last_name_bool << endl;
	cout << prev_year << " : prev first name = " << prev_first_name_str << ", prev last name = " << prev_last_name_str << endl;
	cout << prev_year << " : prev first name function called? = " << prev_first_name_bool << ", prev last name function called? = " << prev_last_name_bool << endl;
#endif

	 return true;
}

	bool try_change_last_name(map<int, pair<string,string>, greater<int>>::iterator& it_yr_to_name_map,
			   	   	   	      map<int, pair<bool, bool>, greater<int>>::iterator& it_yr_to_name_call_bool_map) {
		// Do nothing if the input isn't valid
		if(it_yr_to_name_map == yr_to_name_map.end() && it_yr_to_name_call_bool_map == yr_to_name_call_bool_map.end()) {
			cout << "try_change_last_name: Invalid input, exiting...";
		   return false;
		}

		auto year = it_yr_to_name_call_bool_map->first;
		auto& [first_name_str, last_name_str] = it_yr_to_name_map->second;
		auto [first_name_bool, last_name_bool] = it_yr_to_name_call_bool_map->second;
		auto prev_year = prev(it_yr_to_name_map)->first;
		auto& [prev_first_name_str, prev_last_name_str] = prev(it_yr_to_name_map)->second;
		auto [prev_first_name_bool, prev_last_name_bool] = prev(it_yr_to_name_call_bool_map)->second;

#ifdef DEBUG_ON
	cout << "Before: try_change_first_name" << endl;
	cout << year << " : first name = " << first_name_str << ", last name = " << last_name_str << endl;
	cout << year << " : first name function called? = " << first_name_bool << ", last name function called? = " << last_name_bool << endl;
	cout << prev_year << " : prev first name = " << prev_first_name_str << ", prev last name = " << prev_last_name_str << endl;
	cout << prev_year << " : prev first name function called? = " << prev_first_name_bool << ", prev last name function called? = " << prev_last_name_bool << endl;
#endif
		if(!prev_last_name_bool || prev_last_name_str.empty()) {
			cout << "try_change_last_name: " << year << " Parent string is empty or ChangeLastName not called before" << endl;
			prev_last_name_str = last_name_str;
		}

#ifdef DEBUG_ON
	cout << "After: try_change_last_name" << endl;
	cout << year << " : first name = " << first_name_str << ", last name = " << last_name_str << endl;
	cout << year << " : first name function called? = " << first_name_bool << ", last name function called? = " << last_name_bool << endl;
	cout << prev_year << " : prev first name = " << prev_first_name_str << ", prev last name = " << prev_last_name_str << endl;
	cout << prev_year << " : prev first name function called? = " << prev_first_name_bool << ", prev last name function called? = " << prev_last_name_bool << endl;
#endif
		return true;
	}

public:

   void ChangeFirstName (int year, const string& first_name) {
     // add the fact of the name change to first_name in the year year

#ifdef DEBUG_ON
	  cout << "ChangeFirstName for " << year << endl;
#endif
	   addFirstNameToMaps(year, first_name);

	   // iterator to next smallest key (year)
	   auto it_yr_to_name_map = yr_to_name_map.upper_bound(year);
	   auto it_yr_to_name_call_bool_map = yr_to_name_call_bool_map.upper_bound(year);
	   cout << "first try_change_first_name()" << endl;

	   if(!try_change_first_name(it_yr_to_name_map, it_yr_to_name_call_bool_map)) {
		   cout << "try_change_first_name() failed, skipping" << endl;
		   return;
	   }

	   it_yr_to_name_map = prev(it_yr_to_name_map);
	   it_yr_to_name_call_bool_map = prev(it_yr_to_name_call_bool_map);

	   if(it_yr_to_name_map != yr_to_name_map.begin() && it_yr_to_name_call_bool_map != yr_to_name_call_bool_map.begin()) {
		   cout << "Second try_change_first_name()" << endl;
//		   it_yr_to_name_map = prev(it_yr_to_name_map);
//		   it_yr_to_name_call_bool_map = prev(it_yr_to_name_call_bool_map);
		   if(!try_change_first_name(it_yr_to_name_map, it_yr_to_name_call_bool_map)) {
			   cout << "try_change_first_name() part 2 failed, skipping" << endl;
			   return;
		   }
	   }
   }

   void ChangeLastName (int year, const string& last_name) {
     // add the fact that the last name changed to last_name in the year year
#ifdef DEBUG_ON
	  cout << "ChangeLastName for " << year << endl;
#endif
	   addLastNameToMaps(year, last_name);

	   // iterator to next smallest key (year)
	   auto it_yr_to_name_map = yr_to_name_map.upper_bound(year);
	   auto it_yr_to_name_call_bool_map = yr_to_name_call_bool_map.upper_bound(year);
	   cout << "first try_change_lst_name()" << endl;

	   if(!try_change_last_name(it_yr_to_name_map, it_yr_to_name_call_bool_map)) {
		   cout << "try_change_last_name() failed, skipping" << endl;
		   return;
	   }

	   it_yr_to_name_map = prev(it_yr_to_name_map);
	   it_yr_to_name_call_bool_map = prev(it_yr_to_name_call_bool_map);

	   if(it_yr_to_name_map != yr_to_name_map.begin() && it_yr_to_name_call_bool_map != yr_to_name_call_bool_map.begin()) {
		   cout << "Second try_change_last_name()" << endl;
//		   it_yr_to_name_map = prev(it_yr_to_name_map);
//		   it_yr_to_name_call_bool_map = prev(it_yr_to_name_call_bool_map);
		   if(!try_change_last_name(it_yr_to_name_map, it_yr_to_name_call_bool_map)) {
			   cout << "try_change_last_name() part 2 failed, skipping" << endl;
			   return;
		   }

	   }
   }

   string GetFullName (int year) {
     // get the first and last name at the end of the year year
	  auto it = yr_to_name_map.lower_bound(year);

	  if(it == yr_to_name_map.end()) return "Incognito";

#ifdef DEBUG_ON
	  cout << "GetFullName for " << it->first << endl;
#endif

	  string s;
	  auto [name, surname] = it->second;
	  if(name.empty() && !surname.empty()) {
		  s.append(surname).append(" with unknown first name");
	  } else if(!name.empty() && surname.empty()) {
		  s.append(name).append(" with unknown last name");
	  } else {
		  s.append(name).append(" ").append(surname);
	  }

	  return s;
}

private:
   // private fields
   map<int, pair<string,string>, greater<int>> yr_to_name_map;
   map<int, pair<bool, bool>, greater<int>> yr_to_name_call_bool_map;
};

int main() {
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
	cout <<  person.GetFullName(1967) << endl;

	assert("1965_1st 1967_2nd" == person.GetFullName(1967));
	assert("1965_1st 1968_2nd" == person.GetFullName(1968));

	return 0;
}

//int main() {
//  Person person;
//
//  person.ChangeFirstName(1965, "Polina");
//  person.ChangeLastName(1967, "Sergeeva");
//  for (int year : {1900, 1965, 1990}) {
//    cout << person.GetFullName(year) << endl;
//  }
//
//  person.ChangeFirstName(1970, "Appolinaria");
//  for (int year : {1969, 1970}) {
//    cout << person.GetFullName(year) << endl;
//  }
//
//  person.ChangeLastName(1968, "Volkova");
//  for (int year : {1969, 1970}) {
//    cout << person.GetFullName(year) << endl;
//  }
//
//  return 0;
//}

