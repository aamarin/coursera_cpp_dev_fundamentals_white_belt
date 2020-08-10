
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <exception>
#include <tuple>
#include <iomanip>

// Implement the functions and methods of the classes and add your own if necessary
using namespace std;

class Date {
private:
  int _year;
  int _month;
  int _day;

public:
  int GetYear() const {
    return _year;
  }

  int GetMonth() const {
    return _month;
  }

  int GetDay() const {
    return _day;
  }

  void SetYear(const int year) {
    _year = year;
  }

  void SetMonth(const int month) {
    _month = month;
  }

  void SetDay(const int day) {
    _day = day;
  }

};

istream& operator>>(istream& stream, Date& date) {
  // stream was bad coming in
  if(!stream) {
    return stream;
  }

  int year = 0, month = 0, day = 0;
  char delimieter1 = ' ', delimieter2 = ' ';

  stream >> year >> delimieter1 >> month >> delimieter2 >> day;

  if(stream.fail()) {
    // Probably needs to print
    throw invalid_argument("Invalid argument");
  } else if(month <= 0 && month > 12) {
    throw invalid_argument("Month value is invalid: " + std::to_string(month));
  } else if(day < 1 && day > 31) {
    throw invalid_argument("Day is the invalid: " + std::to_string(day));
  } else {
    date.SetDay(day);
    date.SetMonth(month);
    date.SetYear(year);
  }

  return stream;
}

ostream& operator<<(ostream& stream, const Date& date) {
  stream << setfill ('0');

  stream << setw(4) << date.GetYear() << "-" 
  << setw(2) << date.GetMonth() << "-"
  << setw(2) << date.GetDay() << endl;

  return stream;
}

bool operator<(const Date & lhs, const Date & rhs) {
  int lhs_year = lhs.GetYear();
  int lhs_month = lhs.GetMonth();
  int lhs_day = lhs.GetDay();

  int rhs_year = rhs.GetYear();
  int rhs_month = rhs.GetMonth();
  int rhs_day = rhs.GetDay();

  return std::tie(lhs_year, lhs_month, lhs_day) < std::tie(rhs_year, rhs_month, rhs_day);
         
}

class Database {
private:
  std::map< Date, map<string, string> > _map;

public:
  Database() = default;
  
  void AddEvent (const Date & date, const string & event) {
    auto it = _map.find(date);

    // Don't re-add it
    if(it == _map.end()) {
      auto it2 = it->second.find(event);
      if(it2 != it->second.end()) {
        it2->second = event;
      }
    }
  }

  bool DeleteEvent (const Date & date, const string & event) {
    auto it = _map.find(date);
    bool success = false;

    if(it != _map.end()) {

     auto& event_map = it->second; 
     auto it2 = event_map.find(event);

     if(it2 != event_map.end()) {

      event_map.erase(it2);
      success = true;
      cout << "Deleted successfully" << endl;
     } else {
        success = false;
        cout << "Event not found" << endl;
     }
    }//if

    return success;
  }

  int DeleteDate (const Date & date) {
    auto it = _map.find(date);
    size_t size = 0;
    if(it != _map.end()) {
      size = it->second.size();
      _map.erase(it);
    }//if

    cout << "Deleted" << size << " events";
    return size;
  }

  void Find(const Date & date) const {
    auto it = _map.find(date);

    if(it != _map.end()) {
      for(const auto& [event, dummy] : it->second) {
        cout << event << endl;
      }//for
    }//if
  }
  
  void Print () const {
    for(const auto& [date, event_map] : _map) {
      if(date.GetYear() < 0) continue;

      for(const auto& [event, dummy] : event_map) {
        cout << date << " " << event << endl;
      }
    }
  }
};

int main () {
  Database db;
    
  string command;
  while (getline (cin, command)) {
    // Read commands from the ss stream and process each
    try {
      istringstream ss(command);
      string operater;
      Date date;
      string event;
      ss >> operater;
      
      if(operater == "Add") {
        ss >> date;
        ss >> event;
        db.AddEvent(date, event);
      } else if(operater == "Del") {
        ss >> date;
        ss >> event;
        db.DeleteDate(date);

        // can peek eof or fail be the conditional to delete event?
      } else if(operater == "Find") {
        ss >> date;
        db.Find(date);
      } else if(operater == "Print") {
        db.Print();
      } else {
        throw invalid_argument("Unknown command: " + operater);
      }
    } catch(exception& e) {
      cout << e.what() << endl;
    }

  }// while

  return 0;
}

// int main() {

// Database db;

// {
//   istringstream ss("Add 0-1-2 event1");
//   string operation;
//   string event;
//   Date date;
//   ss >> operation >> date >> event;
//   assert(operation == "Add");

//   db.AddEvent(date, event);
//   db.Find()
// }

// {
// "Add 1-2-3 event2"
// }

// {
// "Find 0-1-2"
// }

// {
// "Del 0-1-2"
// }

// {
// "Print"
// }

// {
// "Del 1-2-3 event2"
// }

// {
// "Add 0-13-32 event1"
// }

// // Output
// "event1"
// "Deleted 1 events"
// "0001-02-03 event2"
// "Deleted successfully"
// "Event not found"
// "Month value is invalid: 13"

//   return 0;
// }