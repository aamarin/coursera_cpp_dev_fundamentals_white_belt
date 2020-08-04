#include <iostream>
using namespace std;

#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <numeric>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <set>
#include <limits>

class Rational {
public:
    Rational ():_numerator(0), _denominator(1) {}

    Rational (int numerator, int denominator):
        _numerator(numerator), _denominator(denominator) {

        _multiplier = multiplier(); 
        _gcd_val = std::gcd(_numerator, _denominator);
        // std::cout << "Inital: numerator: " << _numerator << ", denominator: " << _denominator 
        // << ", multiplier: " << _multiplier << ", gcd: " << _gcd_val << std::endl;
        _denominator = _denominator < 0 ? -1 * _denominator : _denominator;
        _numerator = _numerator < 0 ? -1 * _numerator : _numerator;
        _denominator = _denominator / _gcd_val;
        _numerator = (_numerator * _multiplier)/_gcd_val;
        // std::cout << "After: numerator: " << _numerator << ", denominator: " << _denominator 
        // << ", multiplier: " << _multiplier << ", gcd: " << _gcd_val << std::endl;
    }

    int Numerator () const {
        // Implement this method
        return _numerator;
    }

    int Denominator () const {
    int Denominator () const {
        return _denominator;
    }

    bool operator== (const Rational& rhs) const {
        return (Numerator() == rhs.Numerator() &&
                Denominator() == rhs.Denominator());
    }

    bool operator< (const Rational& rhs) const {
        const auto& [curr_lcm_numerator, rhs_lcm_numerator, lcm_denominator] = build_lcm_values(rhs);
        return curr_lcm_numerator < rhs_lcm_numerator;
    }

    Rational operator+ (const Rational& rhs) const {
        const auto& [curr_lcm_numerator, rhs_lcm_numerator, lcm_denominator] = build_lcm_values(rhs);
        const auto new_numerator = curr_lcm_numerator + rhs_lcm_numerator;
        return Rational(new_numerator, lcm_denominator);
    }

    Rational operator- (const Rational& rhs) const {
        const auto& [curr_lcm_numerator, rhs_lcm_numerator, lcm_denominator] = build_lcm_values(rhs);
        const auto new_numerator = curr_lcm_numerator - rhs_lcm_numerator;

        return Rational(new_numerator, lcm_denominator);    
    }

    Rational operator* (const Rational& rhs) const {
        return Rational(Numerator() * rhs.Numerator(), Denominator() * rhs.Denominator());
    }

    Rational operator/ (const Rational& rhs) const {
        if(rhs.Numerator() == 0) {
        std::cout << "Division by zero" << std::endl;
        throw std::domain_error("Division by zero");
        }
        return Rational(Numerator() * rhs.Denominator(), Denominator() * rhs.Numerator());
    }

private:
    // Add fields
    int _numerator;
    int _denominator;
    int _multiplier;
    int _gcd_val;

    std::tuple<int, int, int> build_lcm_values(const Rational& rhs) const {
        int lcm_val = std::lcm(Denominator(), rhs.Denominator());
        const auto new_num_mult = lcm_val/Denominator();
        const auto rhs_new_num_mult = lcm_val/rhs.Denominator();

        const auto new_num = Numerator() * new_num_mult;
        const auto rhs_new_num = rhs.Numerator() * rhs_new_num_mult;

        // std::cout << "new_num_mult: " << new_num_mult << std::endl; 
        // std::cout << "rhs_new_num_mult: " << rhs_new_num_mult << std::endl;
        // std::cout << "new_num: " << new_num << std::endl;
        // std::cout << "rhs_new_num: " << rhs_new_num << std::endl;
        // std::cout << "operater-: numerator: " << new_numerator << ", denominator: " << lcm_val << std::endl;

        return std::make_tuple(new_num, rhs_new_num, lcm_val);
    }

    int multiplier() const {
        if(_numerator < 0 && _denominator < 0) {
            return 1;
        }

        if(_numerator < 0 || _denominator < 0) {
            return -1;
        }

        // both positive
        return 1;
    }
};


std::ostream& operator<< (std::ostream& stream, const Rational& rational) {
   // std::cout << rational.Numerator() << "/" << rational.Denominator() << std::endl;
    stream << rational.Numerator() << "/" << rational.Denominator();
    return stream;
}

std::istream& operator>> (std::istream& stream, Rational& rational) {
    int numerator = 0, denominator = 0;
    char delim;

    stream >> numerator;
    stream >> delim;
    stream  >> denominator;

    if(!stream || stream.fail() || denominator == 0) {
        std::cout << "Invalid argument" << std::endl;
        throw std::invalid_argument("Invalid argument");
        return stream;
    }

    rational = Rational(numerator, denominator);
    return stream;
}

static void perform_operation(Rational r1, Rational r2, char d) {

    Rational r;

    switch (d)
    {
    case '+':
        r = (r1 + r2);
        std::cout << r << std::endl;
        break;
    case '-':
        r = (r1 -  r2);
        std::cout << r << std::endl;
        break;
    case '*':
        r = (r1 * r2);
        std::cout << r << std::endl;
        break;
    case '/':
        r = (r1 / r2);
        std::cout << r << std::endl;
        break;
    default:
        std::cout << "Division by zero" << std::endl;
        throw std::domain_error("Division by zero");
        break;
    }
}

int main() {

    Rational r1;
    char delim;
    Rational r2;

    try
    {
        std::cin >> r1 >> delim >> r2;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
    
    
    try
    {
        perform_operation(r1, r2, delim);
    }
    catch(const std::domain_error& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}