#include "../lib/bigRational.h"
#include <stdexcept>
#include <algorithm>

// Constructores
template <unsigned char Base>
BigRational<Base>::BigRational(const BigInteger<Base>& num, const BigUnsigned<Base>& denom)
    : numerator(num), denominator(denom) {
    if (denominator == BigUnsigned<Base>("0")) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    reduce();
}

template <unsigned char Base>
BigRational<Base>::BigRational(const BigRational<Base>& other)
    : numerator(other.numerator), denominator(other.denominator) {}

template <unsigned char Base>
BigRational<Base>::BigRational(const std::string& str) {
    size_t pos = str.find('/');
    if (pos == std::string::npos) {
        throw std::invalid_argument("Invalid rational number format");
    }
    numerator = BigInteger<Base>(str.substr(0, pos));
    denominator = BigUnsigned<Base>(str.substr(pos + 1));
    if (denominator == BigUnsigned<Base>("0")) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    reduce();
}

// Asignación
template <unsigned char Base>
BigRational<Base>& BigRational<Base>::operator=(const BigRational<Base>& other) {
    if (this != &other) {
        numerator = other.numerator;
        denominator = other.denominator;
    }
    return *this;
}

// Operadores aritméticos
template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator+(const BigRational<Base>& other) const {
    BigInteger<Base> num = numerator * BigInteger<Base>(other.denominator) + other.numerator * BigInteger<Base>(denominator);
    BigUnsigned<Base> denom = denominator * other.denominator;
    BigRational<Base> result(num, denom);
    result.reduce();
    return result;
}

template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator-(const BigRational<Base>& other) const {
    BigInteger<Base> num = numerator * BigInteger<Base>(other.denominator) - other.numerator * BigInteger<Base>(denominator);
    BigUnsigned<Base> denom = denominator * other.denominator;
    BigRational<Base> result(num, denom);
    result.reduce();
    return result;
}

template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator*(const BigRational<Base>& other) const {
    BigInteger<Base> num = numerator * other.numerator;
    BigUnsigned<Base> denom = denominator * other.denominator;
    BigRational<Base> result(num, denom);
    result.reduce();
    return result;
}

template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator/(const BigRational<Base>& other) const {
    if (other.numerator == BigInteger<Base>("0")) {
        throw std::invalid_argument("Division by zero");
    }
    BigInteger<Base> num = numerator * BigInteger<Base>(other.denominator);
    BigUnsigned<Base> denom = denominator * BigUnsigned<Base>(other.numerator.getMagnitude());
    if (other.numerator.isNegative()) {
        num = -num;
    }
    BigRational<Base> result(num, denom);
    result.reduce();
    return result;
}

// Comparación
template <unsigned char Base>
bool operator==(const BigRational<Base>& lhs, const BigRational<Base>& rhs) {
    return lhs.numerator * BigInteger<Base>(rhs.denominator) == rhs.numerator * BigInteger<Base>(lhs.denominator);
}

template <unsigned char Base>
bool operator<(const BigRational<Base>& lhs, const BigRational<Base>& rhs) {
    return lhs.numerator * BigInteger<Base>(rhs.denominator) < rhs.numerator * BigInteger<Base>(lhs.denominator);
}

template <unsigned char Base>
bool BigRational<Base>::operator<=(const BigRational<Base>& other) const {
    return *this < other || *this == other;
}

template <unsigned char Base>
bool BigRational<Base>::operator>(const BigRational<Base>& other) const {
    return !(*this <= other);
}

template <unsigned char Base>
bool BigRational<Base>::operator>=(const BigRational<Base>& other) const {
    return !(*this < other);
}

// Métodos auxiliares
template <unsigned char Base>
std::string BigRational<Base>::toString() const {
    return numerator.toString() + "/" + denominator.toString();
}

template <unsigned char Base>
void BigRational<Base>::reduce() {
    BigInteger<Base> gcdValue = gcd(numerator.getMagnitude(), denominator);
    numerator = numerator / gcdValue;
    denominator = denominator / BigUnsigned<Base>(gcdValue.getMagnitude());
}

template <unsigned char Base>
BigInteger<Base> BigRational<Base>::gcd(const BigInteger<Base>& a, const BigUnsigned<Base>& b) {
    BigInteger<Base> bInt(b.toString());
    BigInteger<Base> aAbs = a.isNegative() ? -a : a;
    BigInteger<Base> bAbs = bInt.isNegative() ? -bInt : bInt;
    while (!(bAbs == BigInteger<Base>("0"))) {
        BigInteger<Base> temp = bAbs;
        bAbs = aAbs % bAbs;
        aAbs = temp;
    }
    return aAbs;
}

template <unsigned char Base>
bool BigRational<Base>::isReduced() const {
    return (gcd(numerator, denominator) == BigInteger<Base>("1"));
}

// Instanciación de plantillas

// Constructores
BigRational<2>::BigRational(const BigInteger<2>& num, const BigUnsigned<2>& denom)
    : numerator(num), denominator(denom) {
    if (denominator == BigUnsigned<2>("0")) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    reduce();
}

BigRational<2>::BigRational(const BigRational<2>& other)
    : numerator(other.numerator), denominator(other.denominator) {}

BigRational<2>::BigRational(const std::string& str) {
    size_t pos = str.find('/');
    if (pos == std::string::npos) {
        throw std::invalid_argument("Invalid rational number format");
    }
    numerator = BigInteger<2>(str.substr(0, pos));
    denominator = BigUnsigned<2>(str.substr(pos + 1));
    if (denominator == BigUnsigned<2>("0")) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    reduce();
}

// Asignación
BigRational<2>& BigRational<2>::operator=(const BigRational<2>& other) {
    if (this != &other) {
        numerator = other.numerator;
        denominator = other.denominator;
    }
    return *this;
}

// Operadores aritméticos
BigRational<2> BigRational<2>::operator+(const BigRational<2>& other) const {
    BigInteger<2> num = numerator * BigInteger<2>(other.denominator) + other.numerator * BigInteger<2>(denominator);
    BigUnsigned<2> denom = denominator * other.denominator;
    BigRational<2> result(num, denom);
    result.reduce();
    return result;
}

BigRational<2> BigRational<2>::operator-(const BigRational<2>& other) const {
    BigInteger<2> num = numerator * BigInteger<2>(other.denominator) - other.numerator * BigInteger<2>(denominator);
    BigUnsigned<2> denom = denominator * other.denominator;
    BigRational<2> result(num, denom);
    result.reduce();
    return result;
}

BigRational<2> BigRational<2>::operator*(const BigRational<2>& other) const {
    BigInteger<2> num = numerator * other.numerator;
    BigUnsigned<2> denom = denominator * other.denominator;
    BigRational<2> result(num, denom);
    result.reduce();
    return result;
}

BigRational<2> BigRational<2>::operator/(const BigRational<2>& other) const {
    if (other.numerator == BigInteger<2>("0")) {
        throw std::invalid_argument("Division by zero");
    }
    BigInteger<2> num = numerator * BigInteger<2>(other.denominator);
    BigUnsigned<2> denom = denominator * BigUnsigned<2>(other.numerator.getMagnitude());
    if (other.numerator.isNegative()) {
        num = -num;
    }
    BigRational<2> result(num, denom);
    result.reduce();
    return result;
}

// Comparación
bool operator==(const BigRational<2>& lhs, const BigRational<2>& rhs) {
    return lhs.numerator * BigInteger<2>(rhs.denominator) == rhs.numerator * BigInteger<2>(lhs.denominator);
}

bool operator<(const BigRational<2>& lhs, const BigRational<2>& rhs) {
    return lhs.numerator * BigInteger<2>(rhs.denominator) < rhs.numerator * BigInteger<2>(lhs.denominator);
}

bool BigRational<2>::operator<=(const BigRational<2>& other) const {
    return *this < other || *this == other;
}

bool BigRational<2>::operator>(const BigRational<2>& other) const {
    return !(*this <= other);
}

bool BigRational<2>::operator>=(const BigRational<2>& other) const {
    return !(*this < other);
}

// Métodos auxiliares
std::string BigRational<2>::toString() const {
    return numerator.toString() + "/" + denominator.toString();
}

void BigRational<2>::reduce() {
    BigInteger<2> gcdValue = gcd(numerator.getMagnitude(), denominator);
    numerator = numerator / gcdValue;
    denominator = denominator / BigUnsigned<2>(gcdValue.getMagnitude());
}

BigInteger<2> BigRational<2>::gcd(const BigInteger<2>& a, const BigUnsigned<2>& b) {
    BigInteger<2> bInt(b.toString());
    BigInteger<2> aAbs = a.isNegative() ? -a : a;
    BigInteger<2> bAbs = bInt.isNegative() ? -bInt : bInt;
    while (!(bAbs == BigInteger<2>("0"))) {
        BigInteger<2> temp = bAbs;
        bAbs = aAbs % bAbs;
        aAbs = temp;
    }
    return aAbs;
}

bool BigRational<2>::isReduced() const {
    return (gcd(numerator, denominator) == BigInteger<2>("1"));
}

// Definición de los operadores de flujo para BigRational<2>
std::ostream& operator<<(std::ostream& os, const BigRational<2>& rat) {
    os << rat.toString();
    return os;
}

std::istream& operator>>(std::istream& is, BigRational<2>& rat) {
    std::string str;
    is >> str;
    rat = BigRational<2>(str);
    return is;
}

// Instanciación de plantillas
template class BigRational<8>;
template class BigRational<10>;
template class BigRational<16>;