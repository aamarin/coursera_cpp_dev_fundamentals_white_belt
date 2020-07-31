#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <numeric>
#include <string>

class Rational {
public:
    Rational ():_numerator(0), _denominator(1) {
        ctor_init();
    }

    Rational (int numerator, int denominator):
        _numerator(numerator), _denominator(denominator) {
        if(_denominator == 0) _numerator = 1;
        ctor_init();  
    }

    int Numerator () const {
        // Implement this method
        return _numerator;
    }

    int Denominator () const {
        return _denominator;
    }

    bool operator== (const Rational& rhs) {
        return (Numerator() == rhs.Numerator() &&
                Denominator() == rhs.Denominator());
    }

    Rational operator+ (const Rational& rhs) const {
        const auto new_numerator = _gcd_val * (Numerator() + rhs.Numerator());
        const auto new_denominator = Denominator() * _gcd_val;
        return Rational(new_numerator, new_denominator);
    }

    Rational operator- (const Rational& rhs) const {
        int lcm_val = std::lcm(Denominator(), rhs.Denominator());
        const auto new_num_mult = lcm_val/Denominator();
        const auto rhs_new_num_mult = lcm_val/rhs.Denominator();

        const auto new_num = Numerator() * new_num_mult;
        const auto rhs_new_num = rhs.Numerator() * rhs_new_num_mult;
        const auto new_numerator = new_num - rhs_new_num;

        // std::cout << "new_num_mult: " << new_num_mult << std::endl; 
        // std::cout << "rhs_new_num_mult: " << rhs_new_num_mult << std::endl;
        // std::cout << "new_num: " << new_num << std::endl;
        // std::cout << "rhs_new_num: " << rhs_new_num << std::endl;
        // std::cout << "operater-: numerator: " << new_numerator << ", denominator: " << lcm_val << std::endl;

        return Rational(new_numerator, lcm_val);    
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

    void ctor_init() {
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
};

std::istream& operator>> (std::istream& stream, Rational& rational) {
    if(stream.peek() == std::char_traits<char>::eof()) {
        return stream;
    }

    int numerator = 0;
    stream >> numerator;

    stream.ignore(1); 

    int denominator = 0;
    stream >> denominator;

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

    std::cout << "OK" << std::endl;
    return 0;
}
