#include "../lib/bigRational.h"
#include <numeric>

// Constructor por defecto y con parámetros
template <unsigned char Base>
BigRational<Base>::BigRational(const BigInteger<Base>& num, const BigUnsigned<Base>& denom)
    : numerator(num), denominator(denom) {
    if (denominator == BigUnsigned<Base>(0)) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    reduce();
}

// Constructor de copia
template <unsigned char Base>
BigRational<Base>::BigRational(const BigRational<Base>& other)
    : numerator(other.numerator), denominator(other.denominator) {}

// Constructor desde string
template <unsigned char Base>
BigRational<Base>::BigRational(const std::string& str) {
    // Implementación para inicializar desde string
    // Se asume que el string está en el formato "numerator/denominator"
    size_t pos = str.find('/');
    if (pos == std::string::npos) {
        throw std::invalid_argument("Invalid input string");
    }
    numerator = BigInteger<Base>(str.substr(0, pos));
    denominator = BigUnsigned<Base>(str.substr(pos + 1));
    if (denominator == BigUnsigned<Base>(0)) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    reduce();
}

// Operador de suma
template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator+(const BigRational<Base>& other) const {
    BigInteger<Base> num = numerator * other.denominator + other.numerator * denominator;
    BigUnsigned<Base> denom = denominator * other.denominator;
    return BigRational<Base>(num, denom).reduce();
}

// Operador de resta
template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator-(const BigRational<Base>& other) const {
    BigInteger<Base> num = numerator * other.denominator - other.numerator * denominator;
    BigUnsigned<Base> denom = denominator * other.denominator;
    return BigRational<Base>(num, denom).reduce();
}

// Operador de multiplicación
template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator*(const BigRational<Base>& other) const {
    BigInteger<Base> num = numerator * other.numerator;
    BigUnsigned<Base> denom = denominator * other.denominator;
    return BigRational<Base>(num, denom).reduce();
}

// Operador de división
template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator/(const BigRational<Base>& other) const {
    if (other.numerator == BigInteger<Base>(0)) {
        throw std::invalid_argument("Division by zero");
    }
    BigInteger<Base> num = numerator * other.denominator;
    BigUnsigned<Base> denom = denominator * other.numerator;
    return BigRational<Base>(num, denom).reduce();
}


template <unsigned char Base>
BigRational<Base> BigRational<Base>::reduce() const {
    BigInteger<Base> gcd = std::gcd(numerator, denominator);
    return BigRational<Base>(numerator / gcd, denominator / gcd);
}


template <unsigned char Base>
std::string BigRational<Base>::toString() const {
    return numerator.toString() + "/" + denominator.toString();
}


template <unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigRational<Base>& rat) {
    os << rat.toString();
    return os;
}


template <unsigned char Base>
std::istream& operator>>(std::istream& is, BigRational<Base>& rat) {
    std::string str;
    is >> str;
    rat = BigRational<Base>(str);
    return is;
}

template <unsigned char Base>
BigInteger<Base> BigRational<Base>::gcd(const BigInteger<Base>& a, const BigUnsigned<Base>& b) {
    BigInteger<Base> x = a;
    BigUnsigned<Base> y = b;
    while (y != BigUnsigned<Base>(0)) {
        BigInteger<Base> temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

