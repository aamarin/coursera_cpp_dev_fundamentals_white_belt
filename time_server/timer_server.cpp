#include <iostream>
#include <exception>
#include <system_error>
#include <string>
using namespace std;

string AskTimeServer() {
    /* For testing purposes, insert code here that implements different behavior of this function:
       * normal return string value
       * throwing a system_error exception
       * throwing another exception with a message.
    */
   throw std::domain_error(" error");
   return "No";
}

class TimeServer {
public:
    string GetCurrentTime () {
        /* Implement this method:
            * if AskTimeServer () returned a value, write it to last_fetched_time and return
            * if AskTimeServer () threw a system_error exception, return the current value
            last_fetched_time fields
            * if AskTimeServer () threw another exception, forward it further.
        */
       try
       {
            last_fetched_time = std::move(AskTimeServer());
       }
       catch(const std::system_error& s)
       {
           std::cerr << s.what() << std::endl;
           return last_fetched_time;
       }
     
        return last_fetched_time;
    }

private:
    string last_fetched_time = "00:00:00";
};

int main() {

    // Changing the implementation of the AskTimeServer function, make sure that this code works correctly
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    } catch (system_error& e) {
        cout << "Exception got: " << e.what() << endl;
    }

    return 0;
}
