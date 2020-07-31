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
        return (_numerator * _multiplier)/gcd_val;
    }

    int Denominator () const {
        return _denominator/gcd_val;
    }

private:
    // Add fields
    int _numerator;
    int _denominator;
    int _multiplier;
    int gcd_val;
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
        gcd_val = std::gcd(_numerator, _denominator);
        _denominator = _denominator < 0 ? -1 * _denominator : _denominator;
        _numerator = _numerator < 0 ? -1 * _numerator : _numerator;
        // cout << "numerator: " << _numerator << ", denominator: " << _denominator << ", multiplier: " << _multiplier << ", gcd: " << gcd_val << endl;
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
