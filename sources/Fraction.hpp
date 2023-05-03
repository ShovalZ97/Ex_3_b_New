#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

namespace ariel
{
    class Fraction
    {
    private:
        int numerator;
        int denominator;
        void reduce()
        {
            int numGcd = __gcd(abs(numerator), abs(denominator));
            numerator = numerator/ numGcd;
            denominator = denominator/ numGcd;
        }

    public:
        Fraction();
        Fraction(int numerator, int denominator);
        Fraction(float number);

        //***** + operator *****

        Fraction operator+(const Fraction &other) const;

        Fraction operator+(const float &number) const;

        friend Fraction operator+(const float &number, const Fraction &other);

        //***** - operator *****
        Fraction operator-(const Fraction &other) const;

        Fraction operator-(const float &number) const;

        friend Fraction operator-(const float &number, const Fraction &other);

        //***** / operator *****

        Fraction operator/(const Fraction &other) const;

        Fraction operator/(const float &number) const;

        friend Fraction operator/(const float &number, const Fraction &other);

        //***** * operator *****

        Fraction operator*(const Fraction &other) const;

        Fraction operator*(const float &number) const;

        friend Fraction operator*(const float &number, const Fraction &other);

        //***** ++ operator *****

        Fraction operator++(int);

        Fraction &operator++();

        //***** -- operator *****

        Fraction operator--(int);

        Fraction &operator--();

        //***** == operator *****

        bool operator==(const Fraction &other) const;

        bool operator==(const float &other) const;

        friend bool operator==(float const &number, const Fraction &other);

        //***** != operator *****

        bool operator!=(const Fraction &other) const;

        bool operator!=(const float &other) const;

        friend bool operator!=(float const &number, const Fraction &other);

        //***** > operator *****

        bool operator>(const Fraction &other) const;

        bool operator>(const float &other) const;

        friend bool operator>(const float &number, const Fraction &other);

        //***** < operator *****

        bool operator<(const Fraction &other) const;

        bool operator<(const float &other) const;

        friend bool operator<(const float &number, const Fraction &other);

        //***** >= operator *****

        bool operator>=(const Fraction &other) const;

        bool operator>=(const float &other) const;

        friend bool operator>=(const float &number, const Fraction &other);

        //***** <= operator *****

        bool operator<=(const Fraction &other) const;

        bool operator<=(const float &other) const;

        friend bool operator<=(const float &number, const Fraction &other);

        //***** << operator *****

        friend ostream &operator<<(ostream &osOutput, const Fraction &fraction);

        //***** >> operator *****

        friend istream &operator>>(std::istream &isInput, Fraction &fraction);

        int getNumerator() const;
        int getDenominator() const;
    };

}