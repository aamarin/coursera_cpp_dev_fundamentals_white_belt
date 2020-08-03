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

        // no need to reduce further
        if(_denominator == 0) {
            _numerator = 1;
            return;
        }
        
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

std::istream& operator>> (std::istream& stream, Rational& rational) {
    int numerator = 0, denominator = 0;
    char delim;

    stream >> numerator >> delim >> denominator;

    if(!stream || stream.fail() || delim != '/') {
        stream.clear();
        // std::cout << stream.peek() << std::endl;
        stream.ignore(1);
        return stream;
    }

    rational = Rational(numerator, denominator);
    return stream;
}

std::ostream& operator<< (std::ostream& stream, const Rational& rational) {
   // std::cout << rational.Numerator() << "/" << rational.Denominator() << std::endl;
    stream << rational.Numerator() << "/" << rational.Denominator();
    return stream;
}

int main() {
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            std::cout << "Rational(3, 10) != 3/10" << std::endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            std::cout << "Rational(8, 12) != 2/3" << std::endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            std::cout << "Rational(-4, 6) != -2/3" << std::endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            std::cout << "Rational(4, -6) != -2/3" << std::endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            std::cout << "Rational(0, 15) != 0/1" << std::endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            std::cout << "Rational() != 0/1" << std::endl;
            return 5;
        }
    }

    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            std::cout << "4/6 != 2/3" << std::endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            std::cout << "2/3 + 4/3 != 2" << std::endl;
            return 2;
        }
    }

    {
        Rational a(2, -3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            std::cout << "2/-3 + 4/3 != 2/3" << std::endl;
            return 2;
        }
    }

    {
        Rational a(-1, -2);
        Rational b(1, 2);
        Rational c = a + b;
        bool equal = c == Rational(1, 1);
        if (!equal) {
            std::cout << "-1/-2 + 1/2 != 1" << std::endl;
            return 2;
        }
    }

    {
        Rational a(-1, 2);
        Rational b(1, 2);
        Rational c = a + b;
        bool equal = c == Rational(0, 2);
        if (!equal) {
            std::cout << "-1/2 + 1/2 != 0" << std::endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            std::cout << "5/7 - 2/9 != 31/63" << std::endl;
            return 3;
        }
    }

    {
        Rational a(1, 2);
        Rational b(1, 2);
        Rational c = a + b;
        bool equal = c == Rational(1, 1);
        if (!equal) {
            std::cout << "1/2 - 1/2 != 1" << std::endl;
            return 3;
        }
    }

    {
        Rational a(1, 2);
        Rational b(1, 3);
        Rational c = a + b;
        bool equal = c == Rational(5, 6);
        if (!equal) {
            std::cout << "1/2 + 1/3 != 5/6" << std::endl;
            return 3;
        }
    }

    {
        Rational a(5, 6);
        Rational b(1, 4);
        Rational c = a - b;
        bool equal = c == Rational(7, 12);
        if (!equal) {
            std::cout << "5/6 - 1/4 != 7/12" << std::endl;
            return 3;
        }
    }

    {
        const Rational r = Rational(1, 2) + Rational(1, 3) - Rational(1, 4);
        const bool equal = r == Rational(7, 12);
        if (!equal) {
            std::cout << "1/2 + 1/3 - 1/4 != 7/12" << std::endl;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            std::cout << "2/3 * 4/3 != 8/9" << std::endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            std::cout << "5/4 / 15/8 != 2/3" << std::endl;
            return 2;
        }
    }

    {
        std::ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            std::cout << "Rational(-6, 8) should be written as \"-3/4\"" << std::endl;
            return 1;
        }
    }

    {
        std::istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            std::cout << "5/7 is incorrectly read as " << r << std::endl;
            return 2;
        }
    }

    // {
    //     std::istringstream input(" 2/3 ");
    //     Rational r;
    //     input >> r;
    //     bool equal = r == Rational(2, 3);
    //     if (!equal) {
    //         std::cout << "2/3 is incorrectly read as " << r << std::endl;
    //         return 2;
    //     }
    // }

    {
        std::istringstream input("521 / 321");
        Rational r;
        input >> r;
        bool equal = r == Rational(521, 321);
        if (!equal) {
            std::cout << "521 / 321 is incorrectly read as " << r << std::endl;
            return 2;
        }
    }

    // {
    //     std::istringstream input("5f/8");
    //     Rational r;
    //     input >> r;
    //     bool equal = r == Rational(0, 1);
    //     if (!equal) {
    //         std::cout << "5f/8 is incorrectly read as " << r << std::endl;
    //         return 2;
    //     }
    // }

    // {
    //     std::istringstream input("5%7");
    //     Rational r;
    //     input >> r;
    //     bool equal = r == Rational(0, 1);
    //     if (!equal) {
    //         std::cout << "5%7 is incorrectly read as " << r << std::endl;
    //         return 2;
    //     }
    // }

    {
        std::istringstream input(",5/7");
        Rational r;
        input >> r;
        bool equal1 = r == Rational(0, 1);
        if (!equal1) {
            std::cout << "Not 0/1: " << r << std::endl;;
            return 1;
        }
    }

    // {
    //     std::istringstream input("+5/-4 1 /");
    //     Rational r;
    //     input >> r;
    //     bool equal1 = r == Rational(-5, 4);
    //     if (!equal1) {
    //         std::cout << "Not -5/4: " << r << std::endl;;
    //         return 1;
    //     }
    // }

    {
        std::istringstream input("");
        Rational r;
        input >> r;
        bool equal1 = r == Rational(0, 1);
        if (!equal1) {
            std::cout << "Not 0/1: " << r << std::endl;;
            return 1;
        }
    }

    {
        std::istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            std::cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << std::endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            std::cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << std::endl;
            return 4;
        }
    }

    {
        std::istringstream input("5/f 6/4");
        Rational r1(3,10), r2;
        input >> r1;
        input >> r2;
        bool equal1 = r1 == Rational(3, 10);
        bool equal2 = r2 == Rational(3, 2);
        if (!equal1 || !equal2) {
            std::cout << "Not 3/10 and 3/2: " << r1 << ' ' << r2 << std::endl;;
            return 1;
        }
    }

    {
        std::istringstream input("f /4 , 3/4");
        Rational r1(3,10), r2;
        input >> r1;
        input >> r2;
        bool equal1 = r1 == Rational(3, 10);
        bool equal2 = r2 == Rational(0, 1);
        if (!equal1 || !equal2) {
            std::cout << "Not 3/10 and 3/4: " << r1 << ' ' << r2 << std::endl;;
            return 1;
        }
    }

    {
        std::istringstream input("6 /4 , 6/f");
        Rational r1(3,2), r2;
        input >> r1;
        input >> r2;
        bool equal1 = r1 == Rational(3, 2);
        bool equal2 = r2 == Rational(0, 1);
        if (!equal1 || !equal2) {
            std::cout << "Not 3/2 and 0/1: " << r1 << ' ' << r2 << std::endl;;
            return 1;
        }
    }

    {
        std::istringstream input("1/2 f");
        Rational r1, r2(2,5);
        input >> r1;
        input >> r2;
        bool equal1 = r1 == Rational(1, 2);
        bool equal2 = r2 == Rational(2, 5);
        if (!equal1 || !equal2) {
            std::cout << "Not 1/2 and 2/5: " << r1 << ' ' << r2 << std::endl;;
            return 1;
        }
    }
    {
        std::istringstream input("5/7 10/8, 3/4");
        Rational r1, r2;
        input >> r1;
        input >> r2;
        bool equal1 = r1 == Rational(5, 7);
        bool equal2 = r2 == Rational(5, 4);
        if (!equal1 || !equal2) {
            std::cout << "Not 5/7 and 5/4:" << r1 << ' ' << r2 << std::endl;;
            return 1;
        }
    }

    {
        std::istringstream input("1/ 6/4");
        Rational r1(2,5), r2;
        input >> r1;
        input >> r2;
        bool equal1 = r1 == Rational(2, 5);
        bool equal2 = r2 == Rational(3, 2);
        if (!equal1 || !equal2) {
            std::cout << "Not 2/5 and 3/2:" << r1 << ' ' << r2 << std::endl;;
            return 1;
        }
    }
    {
        const std::set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            std::cout << "Wrong amount of items in the set" << std::endl;
            return 1;
        }

        std::vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != std::vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            std::cout << "Rationals comparison works incorrectly" << std::endl;
            return 2;
        }
    }

    {
        std::map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            std::cout << "Wrong amount of items in the map" << std::endl;
            return 3;
        }
    }
    std::cout << "OK" << std::endl;
    return 0;
}
