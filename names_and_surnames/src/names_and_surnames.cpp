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

using namespace std;


//#define DEBUG_ON

class Person {

public:

   void ChangeFirstName (int year, const string& first_name) {

#ifdef DEBUG_ON
	  cout << "ChangeFirstName for " << year << endl;
#endif
	  ChangeName(year, first_name, true);
   }

   void ChangeLastName (int year, const string& last_name) {
     // add the fact that the last name changed to last_name in the year year
#ifdef DEBUG_ON
	  cout << "ChangeLastName for " << year << endl;
#endif
	  ChangeName(year, last_name, false);
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


	void addNameToMap(const int year, const string& name, const bool is_first_name) {
	   auto& [fname_bool, lname_bool] = yr_to_name_call_bool_map[year];
	   auto& [fname_str, lname_str] = yr_to_name_map[year];

	   if(is_first_name) {
		   fname_bool = true;
		   fname_str = name;
	   }
	   else {
		   lname_bool = true;
		   lname_str = name;
	   }

#ifdef DEBUG_ON
	   cout << "Adding " << (is_first_name ? "first name: " : "last name: ") << name << endl;
	   cout << year << " : first name = " << fname_str << ", last name = " << lname_str << endl;
	   cout << "Has called ChangeFirstName before? " << (fname_bool ? "Yes" : "No") << endl;
	   cout << "Has called ChangeLasttName before? " << (lname_bool ? "Yes" : "No") << endl;
#endif
	}


	void try_change_debug_trace(const map<int, pair<string,string>, greater<int>>::iterator& it_yr_to_name_map,
			   	   	   	   	    const map<int, pair<bool, bool>, greater<int>>::iterator& it_yr_to_name_call_bool_map) {
		const auto year = it_yr_to_name_map->first;
		const auto& [first_name_str, last_name_str] = it_yr_to_name_map->second;
		const auto [first_name_bool, last_name_bool] = it_yr_to_name_call_bool_map->second;
		const auto prev_year = prev(it_yr_to_name_map)->first;
		const auto& [prev_first_name_str, prev_last_name_str] = prev(it_yr_to_name_map)->second;
		const auto [prev_first_name_bool, prev_last_name_bool] = prev(it_yr_to_name_call_bool_map)->second;

		cout << year << " : first name = " << first_name_str << ", last name = " << last_name_str << endl;
		cout << year << " : first name function called? = " << first_name_bool << ", last name function called? = " << last_name_bool << endl;
		cout << prev_year << " : prev first name = " << prev_first_name_str << ", prev last name = " << prev_last_name_str << endl;
		cout << prev_year << " : prev first name function called? = " << prev_first_name_bool << ", prev last name function called? = " << prev_last_name_bool << endl;
	}


	bool try_name_change(map<int, pair<string,string>, greater<int>>::iterator& it_yr_to_name_map,
			   	   	   	 map<int, pair<bool, bool>, greater<int>>::iterator& it_yr_to_name_call_bool_map,
						 const bool is_first_name) {
		// Do nothing if the input isn't valid
		if(it_yr_to_name_map == yr_to_name_map.end() &&
		   it_yr_to_name_call_bool_map == yr_to_name_call_bool_map.end()) {

#ifdef DEBUG_ON
			cout << __FUNCTION__ << ": Invalid input, exiting...";
#endif
			return false;
		}

		const auto year = it_yr_to_name_map->first;
		const auto& [first_name_str, last_name_str] = it_yr_to_name_map->second;
		auto& [prev_first_name_str, prev_last_name_str] = prev(it_yr_to_name_map)->second;
		const auto [prev_first_name_bool, prev_last_name_bool] = prev(it_yr_to_name_call_bool_map)->second;

#ifdef DEBUG_ON
			cout << "Before: state" << endl;
			try_change_debug_trace(it_yr_to_name_map, it_yr_to_name_call_bool_map);
#endif
			string s = is_first_name ? "first" : "last";
			s.append(" name");

			auto conditional = [year, s, is_first_name](const bool was_name_changed, const string& new_name, string& name){

				if(!was_name_changed || name.empty()) {
#ifdef DEBUG_ON
					string temp = is_first_name ? "ChangeFirstName" : "ChangeLastName";
					cout << year << " " << s << ": Parent string is empty or " << temp << " not called before" << endl;
#endif
					name = new_name;
				}
			};

				 conditional(prev_first_name_bool, first_name_str, prev_first_name_str);
				 conditional(prev_last_name_bool, last_name_str, prev_last_name_str);


#ifdef DEBUG_ON
			cout << "After: state" << endl;
			try_change_debug_trace(it_yr_to_name_map, it_yr_to_name_call_bool_map);
#endif

		return true;
	}


	void ChangeName (const int year, const string& first_name, const bool is_first_name) {
#ifdef DEBUG_ON
	  cout << __FUNCTION__ << " for " << year << endl;
#endif
	   addNameToMap(year, first_name, is_first_name);

	   // iterator to next smallest key (year)
	   auto it_yr_to_name_map = yr_to_name_map.upper_bound(year);
	   auto it_yr_to_name_call_bool_map = yr_to_name_call_bool_map.upper_bound(year);

#ifdef DEBUG_ON
	   cout << "first try_name_change()" << endl;
#endif

	   bool is_change_success = false;

	   do {
		   is_change_success = try_name_change(it_yr_to_name_map, it_yr_to_name_call_bool_map, is_first_name);
		   if(!is_change_success) {
#ifdef DEBUG_ON
			   cout << "try_name_change() failed" << endl;
#endif
		   } else {
			   it_yr_to_name_map = prev(it_yr_to_name_map);
			   it_yr_to_name_call_bool_map = prev(it_yr_to_name_call_bool_map);

		   }

	   } while(it_yr_to_name_map != yr_to_name_map.begin() &&
			   it_yr_to_name_call_bool_map != yr_to_name_call_bool_map.begin() &&
			   is_change_success);
	}
};

int main() {
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
	return 0;
}



