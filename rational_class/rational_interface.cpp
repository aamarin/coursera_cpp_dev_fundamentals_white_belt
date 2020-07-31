#include <iostream>
#include <numeric>

using namespace std;

class Rational {
public:
    Rational ():_numerator(0), _denominator(1) {
        ctor_init();
    }

    Rational (int numerator, int denominator):
        _numerator(numerator), _denominator(denominator) {
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
        // cout << "new_num_mult: " << new_num_mult << endl;
        const auto rhs_new_num_mult = lcm_val/rhs.Denominator();
        // cout << "rhs_new_num_mult: " << rhs_new_num_mult << endl;

        const auto new_num = Numerator() * new_num_mult;
        // cout << "new_num: " << new_num << endl;
        const auto rhs_new_num = rhs.Numerator() * rhs_new_num_mult;
        // cout << "rhs_new_num: " << rhs_new_num << endl;
        const auto new_numerator = new_num - rhs_new_num;
        // cout << "operater-: numerator: " << new_numerator << ", denominator: " << lcm_val << endl;

        return Rational(new_numerator, lcm_val);    
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
        // cout << "Inital: numerator: " << _numerator << ", denominator: " << _denominator 
        // << ", multiplier: " << _multiplier << ", gcd: " << _gcd_val << endl;
        _denominator = _denominator < 0 ? -1 * _denominator : _denominator;
        _numerator = _numerator < 0 ? -1 * _numerator : _numerator;
        _denominator = _denominator / _gcd_val;
        _numerator = (_numerator * _multiplier)/_gcd_val;
        // cout << "After: numerator: " << _numerator << ", denominator: " << _denominator 
        // << ", multiplier: " << _multiplier << ", gcd: " << _gcd_val << endl;
    }
};

int main() {
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
