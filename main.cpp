#include <iostream>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>

using namespace std;

class Rational {
public:
    Rational() {
        num = 0;
        denom = 1;
    }

    Rational(int numerator, int denominator) {
        if (denominator < 0) { 
            if (numerator < 0) { 
                denominator = abs(denominator);
                numerator = abs(numerator);
            }
            else {
                denominator = abs(denominator);
                numerator = -abs(numerator);
            }
        }
        if (numerator == 0) {
            denominator = 1;
        }




        int NOD;
        NOD = gcd(abs(numerator), abs(denominator));
        if (NOD != 0) {
            num = numerator / NOD;
            denom = denominator / NOD;
        }
        


    }

    int Numerator() const {

        return num;
    }

    int Denominator() const {

        return denom;
    }

private:
    int num = 0;
    int denom = 1;
};



bool operator==(const Rational& lhs, const Rational& rhs) {
    if (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator()) {
        return 1;
    }
    else {
        return 0;
    }
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    int denom_both = lhs.Denominator() * rhs.Denominator();
    int num_first = lhs.Numerator() * rhs.Denominator();
    int num_second = rhs.Numerator() * lhs.Denominator();
    int num_both = num_first + num_second;
    return Rational(num_both, denom_both);
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    int denom_both = lhs.Denominator() * rhs.Denominator();
    int num_first = lhs.Numerator() * rhs.Denominator();
    int num_second = rhs.Numerator() * lhs.Denominator();
    int num_both = num_first - num_second;
    return Rational(num_both, denom_both);

}


Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs) {


    return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
}

ostream& operator<<(ostream& stream, const Rational& rational) {
    stream << rational.Numerator() << '/' << rational.Denominator();
    return stream;
}



istream& operator>>(istream& stream, Rational& rational) {
    int num, denom;
    char sign;
    if (stream >> num && stream >> sign && stream >> denom) {
        if (sign == '/') {
            rational = { num, denom };
        }
        else {
            rational = { 0 , 1 };
        }
    }

    return stream;

}

bool operator < (const Rational& rhs, const Rational& lhs) {
    int num_first = lhs.Numerator() * rhs.Denominator();
    int num_second = rhs.Numerator() * lhs.Denominator();
    return num_first > num_second;
     

}

bool operator > (const Rational& rhs, const Rational& lhs) {
    int num_first = lhs.Numerator() * rhs.Denominator();
    int num_second = rhs.Numerator() * lhs.Denominator();
    return num_first > num_second;
     
}



int main() {
    {
        const set<Rational> rs = { {1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2} };
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{ {1, 25}, { 1, 2 }, { 3, 4 }}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
