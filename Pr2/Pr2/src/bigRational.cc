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
    size_t pos = str.find('/');
    if (pos == std::string::npos) {
        throw std::invalid_argument("Invalid string format");
    }
    std::string numStr = str.substr(0, pos);
    std::string denomStr = str.substr(pos + 1);

    numerator = BigInteger<Base>(numStr);
    denominator = BigUnsigned<Base>(denomStr);

    if (denominator == BigUnsigned<Base>(0)) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    reduce();
}

// Operador de asignación
template <unsigned char Base>
BigRational<Base>& BigRational<Base>::operator=(const BigRational<Base>& other) {
    if (this != &other) {
        numerator = other.numerator;
        denominator = other.denominator;
    }
    return *this;
}

template <unsigned char Base>
bool operator==(const BigRational<Base>& lhs, const BigRational<Base>& rhs) {
    return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}

template <unsigned char Base>
bool operator<(const BigRational<Base>& lhs, const BigRational<Base>& rhs) {
    BigInteger<Base> den1(lhs.denominator), den2(rhs.denominator);
    BigInteger<Base> num1 = lhs.numerator * den2;
    BigInteger<Base> num2 = rhs.numerator * den1;

    return num1 < num2;
}

// Operador de suma
template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator+(const BigRational<Base>& other) const {
    BigInteger<Base> num = numerator * other.denominator + other.numerator * denominator;
    BigUnsigned<Base> denom = denominator * other.denominator;
    BigRational<Base> result(num, denom);
    result.reduce();
    return result;
}

// Operador de resta
template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator-(const BigRational<Base>& other) const {
    BigInteger<Base> num = numerator * other.denominator - other.numerator * denominator;
    BigUnsigned<Base> denom = denominator * other.denominator;
    BigRational<Base> result(num, denom);
    result.reduce();
    return result;
}

// Operador de multiplicación
template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator*(const BigRational<Base>& other) const {
    BigInteger<Base> num = numerator * other.numerator;
    BigUnsigned<Base> denom = denominator * other.denominator;
    BigRational<Base> result(num, denom);
    result.reduce();
    return result;
}

// Operador de división
template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator/(const BigRational<Base>& other) const {
    if (other.numerator == BigInteger<Base>(0)) {
        throw std::invalid_argument("Division by zero");
    }

    BigInteger<Base> num = numerator * other.denominator;
    BigUnsigned<Base> denom = denominator * other.numerator.getMagnitude();
    BigRational<Base> result(num, denom);
    result.reduce();
    return result;
}

template <unsigned char Base>
void BigRational<Base>::reduce() {
    BigInteger<Base> gcd = BigRational<Base>::gcd(numerator, denominator);
    numerator = numerator / gcd;
    denominator = denominator / gcd.getMagnitude();
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
    BigInteger<Base> y(b);
    while (!(y == BigInteger<Base>(0))) {
        BigInteger<Base> temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

// Instanciación explícita de las plantillas para los valores de Base utilizados
template class BigRational<2>;
template class BigRational<8>;
template class BigRational<10>;
template class BigRational<16>;

template std::ostream& operator<< <>(std::ostream& os, const BigRational<2>& rat);
template std::ostream& operator<< <>(std::ostream& os, const BigRational<8>& rat);
template std::ostream& operator<< <>(std::ostream& os, const BigRational<10>& rat);
template std::ostream& operator<< <>(std::ostream& os, const BigRational<16>& rat);

template std::istream& operator>> <>(std::istream& is, BigRational<2>& rat);
template std::istream& operator>> <>(std::istream& is, BigRational<8>& rat);
template std::istream& operator>> <>(std::istream& is, BigRational<10>& rat);
template std::istream& operator>> <>(std::istream& is, BigRational<16>& rat);

template bool operator== <2>(const BigRational<2>& lhs, const BigRational<2>& rhs);
template bool operator< <2>(const BigRational<2>& lhs, const BigRational<2>& rhs);

template bool operator== <8>(const BigRational<8>& lhs, const BigRational<8>& rhs);
template bool operator< <8>(const BigRational<8>& lhs, const BigRational<8>& rhs);

template bool operator== <10>(const BigRational<10>& lhs, const BigRational<10>& rhs);
template bool operator< <10>(const BigRational<10>& lhs, const BigRational<10>& rhs);

template bool operator== <16>(const BigRational<16>& lhs, const BigRational<16>& rhs);
template bool operator< <16>(const BigRational<16>& lhs, const BigRational<16>& rhs);