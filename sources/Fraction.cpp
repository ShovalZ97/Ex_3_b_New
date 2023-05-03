#include <ostream>
#include <iostream>
#include <algorithm>
#include "Fraction.hpp"

using namespace std;

namespace ariel
{
    Fraction::Fraction() : numerator(0), denominator(1) {}

    Fraction::Fraction(int numerator1, int denominator1) : numerator(numerator1), denominator(denominator1)
    {
        if (denominator == 0)
            throw invalid_argument("The denominator can't be zero");
        if (denominator < 0)
        {
            numerator *= -1;
            denominator *= -1;
        }
        reduce();
    }

    Fraction::Fraction(float number)
    {
        this->numerator = 1000 * number;
        this->denominator = 1000;
        reduce();
    }

    //***** + operator *****

    Fraction Fraction::operator+(const Fraction &other) const
    {
        int res1, res2, num, den;
        //Function __builtin_mul_overflow 
        //The function takes two types type1 and type2 and put the result of the multiplication in res.
        //If the multiplication of type1 and type2 overflows, the function sets *res to 0 and returns true.
        //Otherwise, it stores the result of the multiplication in *res and returns false.
        if (__builtin_mul_overflow(numerator, other.denominator, &res1) ||
            __builtin_mul_overflow(other.numerator, denominator, &res2) ||
            //Function __builtin_add_overflow
            //The function takes three arguments: the two integer operands to be added,
            //And a pointer to a boolean variable that will be set to true if the addition overflows, or false otherwise.
            __builtin_add_overflow(res1, res2, &num) ||
            __builtin_mul_overflow(denominator, other.denominator, &den))
        {
            //when return false
            throw overflow_error("The result is too big");
        }

        return Fraction(num, den);
    }
    Fraction Fraction::operator+(const float &number) const
    {
        return *this + Fraction(number);
    }
    Fraction operator+(const float &number, const Fraction &other)
    {
        return Fraction(number) + other;
    }
    //***** - operator *****

    Fraction Fraction::operator-(const Fraction &other) const
    {
        int res1, res2, num, den;

        if (__builtin_mul_overflow(numerator, other.denominator, &res1) ||
            __builtin_mul_overflow(other.numerator, denominator, &res2) ||
             //Function __builtin_sub_overflow
             //The function performs an arithmetic subtraction operation between two integers and checks whether the result overflows.
             //True if the subtraction overflows, or false otherwise.
            __builtin_sub_overflow(res1, res2, &num) ||
            __builtin_mul_overflow(denominator, other.denominator, &den))
        {
            throw overflow_error("The result is too big");
        }

        return Fraction(num, den);
    }
    Fraction Fraction::operator-(const float &number) const
    {
        return *this - Fraction(number);
    }
    Fraction operator-(const float &number, const Fraction &other)
    {
        return Fraction(number) - other;
    }

    //***** / operator *****

    Fraction Fraction::operator/(const Fraction &other) const
    {
        if (other.numerator == 0)
            throw runtime_error("The denominator can't be zero");

        int num, den;

        if (__builtin_mul_overflow(numerator, other.denominator, &num) ||
            __builtin_mul_overflow(denominator, other.numerator, &den))
        {
            throw overflow_error("The result is too big");
        }

        return Fraction(num, den);
    }
    Fraction Fraction::operator/(const float &number) const
    {
        return *this / Fraction(number);
    }
    Fraction operator/(const float &number, const Fraction &other)
    {
        return Fraction(number) / other;
    }

    //***** * operator *****

    Fraction Fraction::operator*(const Fraction &other) const
    {
        int num, den;

        if (__builtin_mul_overflow(numerator, other.numerator, &num) ||
            __builtin_mul_overflow(denominator, other.denominator, &den))
        {
            throw overflow_error("The result is too big");
        }

        return Fraction(num, den);
    }
    Fraction Fraction::operator*(const float &number) const
    {
        return *this * Fraction(number);
    }
    Fraction operator*(const float &number, const Fraction &other)
    {
        return Fraction(number) * other;
    }

    //***** ++ operator *****

    // Pre increcment
    Fraction &Fraction::operator++()
    {
        this->numerator += this->denominator;
        return *this;
    }
    // Post increcment
    Fraction Fraction::operator++(int)
    {
        Fraction num = *this;
        this->numerator += this->denominator;
        return num;
    }

    //***** -- operator *****

    Fraction Fraction::operator--(int)
    {
        Fraction num = *this;
        this->numerator -= this->denominator;
        return num;
    }
    Fraction &Fraction::operator--()
    {
        this->numerator -= this->denominator;
        return *this;
    }
    //***** == operator *****

    bool Fraction::operator==(const Fraction &other) const
    {
        const float PRECISION = 1000.0;
        int num1 = (int)(((float)numerator / (float)denominator) * PRECISION);
        int num2 = (int)(((float)other.numerator / (float)other.denominator) * PRECISION);
        return num1 == num2;
    }
    bool Fraction::operator==(const float &other) const
    {
        return *this == Fraction(other);
    }
    bool operator==(float const &number, const Fraction &other)
    {
        return Fraction(number) == other;
    }

    //***** != operator *****

    bool Fraction::operator!=(const Fraction &other) const
    {
        return !(*this == other);
    }

    bool Fraction::operator!=(const float &other) const
    {
        return *this != Fraction(other);
    }

    bool operator!=(float const &number, const Fraction &other)
    {
        return Fraction(number) != other;
    }

    //***** > operator *****

    bool operator>(const float &number, const Fraction &other)
    {
        return Fraction(number) > other;
    }
    bool Fraction::operator>(const float &number) const
    {
        return *this > Fraction(number);
    }
    bool Fraction::operator>(const Fraction &other) const
    {
        return (numerator * other.denominator) > (other.numerator * denominator);
    }

    //***** < operator *****

    bool Fraction::operator<(const Fraction &other) const
    {
        return (numerator * other.denominator) < (other.numerator * denominator);
    }

    bool Fraction::operator<(const float &number) const
    {
        return *this < Fraction(number);
    }

    bool operator<(const float &number, const Fraction &other)
    {
        return Fraction(number) < other;
    }

    //***** >= operator *****

    bool Fraction::operator>=(const float &number) const
    {
        return !(*this < number);
    }

    bool operator>=(const float &number, const Fraction &other)
    {
        return !(Fraction(number) < other);
    }

    bool Fraction::operator>=(const Fraction &other) const
    {
        return !(*this < other);
    }

    //***** <= operator *****

    bool Fraction::operator<=(const float &number) const
    {
        return !(*this > number);
    }

    bool operator<=(const float &number, const Fraction &other)
    {
        return !(Fraction(number) > other);
    }

    bool Fraction::operator<=(const Fraction &other) const
    {
        return !(*this > other);
    }

    //***** << operator *****

    ostream &operator<<(ostream &osOutput, const Fraction &fraction)
    {
        return (osOutput << fraction.numerator << '/' << fraction.denominator);
    }

    //***** >> operator *****

    istream &operator>>(std::istream &isInput, Fraction &fraction)
    {
        int numitor = 0, denitor = 0;

        isInput >> numitor >> denitor;

        if (isInput.fail())
            throw std::runtime_error("Invalid input");

        else if (denitor == 0)
            throw std::runtime_error("Denominator can't be zero");

        else if (denitor < 0)
        {
            numitor *= -1;
            denitor *= -1;
        }

        fraction.numerator = numitor;
        fraction.denominator = denitor;
        fraction.reduce();

        return isInput;
    }

    int Fraction::getNumerator() const
    {
        return this->numerator;
    }
    int Fraction::getDenominator() const
    {
        return this->denominator;
    }
}