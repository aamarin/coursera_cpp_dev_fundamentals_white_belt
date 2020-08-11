
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <exception>
#include <system_error>
#include <tuple>
#include <iomanip>
#include <algorithm>

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

  const int stream_buf_pos = stream.tellg();
  int year = 0, month = 0, day = 0;
  char delimieter1 = ' ', delimieter2 = ' ';

  stream >> year >> delimieter1 >> month >> delimieter2 >> day;

  if(stream.fail() || delimieter1 != '-' || delimieter2 != '-') {
    string output;
    stream.clear();
    stream.seekg(stream_buf_pos);
    stream >> output;
    throw invalid_argument("Wrong date format: " + output);
  }

  auto peek = stream.peek();

  if((peek != -1 && peek != ' ')) {
    string output;
    stream.clear();
    stream.seekg(stream_buf_pos);
    stream >> output;
    throw invalid_argument("Wrong date format: " + output);

  } else if(month < 1 || month > 12) {
    throw invalid_argument("Month value is invalid: " + std::to_string(month));

  } else if(day < 1 || day > 31) {
    throw invalid_argument("Day value is invalid: " + std::to_string(day));

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
  << setw(2) << date.GetDay();

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
  std::map< Date, std::vector<string> > _map;

public:
  Database() = default;
  
  void AddEvent (const Date & date, const string & event) {
    auto it = _map.find(date);

    //if(it == _map.end()) {
      auto& vect = _map[date];

      auto it2 = find(vect.begin(), vect.end(), event);

      if(it2 == vect.end())
        vect.push_back(event);

      sort(vect.begin(), vect.end());
    //}
  }

  bool DeleteEvent (const Date & date, const string & event) {
    auto it = _map.find(date);
    bool success = false;

    if(it != _map.end()) {

      auto& event_vect = it->second; 
      auto it2 = std::find(std::begin(event_vect), std::end(event_vect), event);
      if(it2 != event_vect.end()) {
        success = true;
        event_vect.erase(it2);
     } else {
        success = false;
     }
    }//if

    if(success) {
      cout << "Deleted successfully" << endl;
    } else {
      cout << "Event not found" << endl;
    }

    return success;
  }

  int DeleteDate (const Date & date) {
    auto it = _map.find(date);
    size_t size = 0;
    if(it != _map.end()) {
      size = it->second.size();
      _map.erase(it);
    }//if

    cout << "Deleted " << size << " events" << endl;;
    return size;
  }

  void Find(const Date & date) const {
    auto it = _map.find(date);

    if(it != _map.end()) {
      for(const auto& e : it->second) {
        cout << e << endl;
      }//for
    }//if
  }
  
  void Print () const {
    for(auto& [date, event_vect] : _map) {
      if(date.GetYear() < 0) continue;

      for(const auto& e : event_vect) {
        cout << date << " " << e << endl;
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
      if(command.empty()) {
        continue;
      }

      istringstream ss(command);
      string operater;
      Date date;
      string event;
      ss >> operater;

      if(operater == "Add") {
        ss >> date;
        ss >> event;

        if(event.empty()) {
          throw invalid_argument("Invalid argument: " + command);
        }

        db.AddEvent(date, event);

      } else if(operater == "Del") {
        ss >> date;

        if(ss.peek() == -1) {
           db.DeleteDate(date);
        } else {
           ss >> event;
           db.DeleteEvent(date, event);
        }

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
      return 0;
    }

  }// while

  return 0;
}