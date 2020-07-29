#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Student {
    string first_name;
    string last_name;
    size_t day;
    size_t month;
    size_t year;
};

int main()
{
    size_t num_students = 0;
    cin >> num_students;

    vector<Student> list;
    string line;

    for(size_t student = 0; student < num_students; ++student) {
            Student s;

            cin >> s.first_name;
            cin >> s.last_name;
            cin >> s.day;
            cin >> s.month;
            cin >> s.year;

            list.emplace_back(s);
    }

    size_t num_requests = 0;
    cin >> num_requests;
    
    for( size_t request = 0; request < num_requests; ++request) {
        string query;
        cin >> query;

        int student_num = 0;
        cin >> student_num;

        if((student_num - 1) > list.size() || student_num <= 0) {
            cout << "bad request" << endl;
            continue;
        }

        const auto& curr_student = list[student_num - 1];

        if(query == "name") {
            cout << curr_student.first_name << " " << curr_student.last_name << endl;
        } else if(query == "date") {
            cout << curr_student.day << "." << curr_student.month << "." << curr_student.year << endl;
        }else {
            cout << "bad request" << endl;
        }
    }

    return 0;
}