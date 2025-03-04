#include "../lib/bigRational.h"

// Constructor por defecto
template <unsigned char Base>
BigRational<Base>::BigRational(const BigInteger<Base>& num, const BigUnsigned<Base>& denom)
    : numerator(num), denominator(denom) {
    if (denominator == BigUnsigned<Base>("0")) {
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
        throw std::invalid_argument("Invalid input string");
    }
    numerator = BigInteger<Base>(str.substr(0, pos));
    denominator = BigUnsigned<Base>(str.substr(pos + 1, str.size() - pos - 1));
    if (denominator == BigUnsigned<Base>("0")) {
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

// Operador de suma
template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator+(const BigRational<Base>& other) const {
    BigInteger<Base> newNumerator = numerator * BigInteger<Base>(other.denominator) + other.numerator * BigInteger<Base>(denominator);
    BigUnsigned<Base> newDenominator = denominator * other.denominator;
    return BigRational<Base>(newNumerator, newDenominator);
}

// Operador de resta
template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator-(const BigRational<Base>& other) const {
    BigInteger<Base> newNumerator = numerator * BigInteger<Base>(other.denominator) - other.numerator * BigInteger<Base>(denominator);
    BigUnsigned<Base> newDenominator = denominator * other.denominator;
    return BigRational<Base>(newNumerator, newDenominator);
}

// Operador de multiplicación
template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator*(const BigRational<Base>& other) const {
    BigInteger<Base> newNumerator = numerator * other.numerator;
    BigUnsigned<Base> newDenominator = denominator * other.denominator;
    return BigRational<Base>(newNumerator, newDenominator);
}

// Operador de división
template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator/(const BigRational<Base>& other) const {
    if (other.numerator == BigInteger<Base>(0)) {
        throw std::invalid_argument("Division by zero");
    }
    BigInteger<Base> newNumerator = numerator * BigInteger<Base>(other.denominator);
    BigUnsigned<Base> newDenominator = denominator * other.numerator.getMagnitude();
    if (other.numerator.isNegative()) {
        newNumerator = -newNumerator;
    }
    return BigRational<Base>(newNumerator, newDenominator);
}

// Operador de comparación de igualdad
template <unsigned char Base>
bool operator==(const BigRational<Base>& lhs, const BigRational<Base>& rhs) {
    return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}

// Operador de comparación menor que
template <unsigned char Base>
bool operator<(const BigRational<Base>& lhs, const BigRational<Base>& rhs) {
    return lhs.numerator * BigInteger<Base>(rhs.denominator) < rhs.numerator * BigInteger<Base>(lhs.denominator);
}

// Operador de comparación menor o igual que
template <unsigned char Base>
bool BigRational<Base>::operator<=(const BigRational<Base>& other) const {
    return *this < other || *this == other;
}

// Operador de comparación mayor que
template <unsigned char Base>
bool BigRational<Base>::operator>(const BigRational<Base>& other) const {
    return !(*this <= other);
}

// Operador de comparación mayor o igual que
template <unsigned char Base>
bool BigRational<Base>::operator>=(const BigRational<Base>& other) const {
    return !(*this < other);
}

// Método toString
template <unsigned char Base>
std::string BigRational<Base>::toString() const {
    return numerator.toString() + "/" + denominator.toString();
}

// Método para reducir la fracción
template <unsigned char Base>
void BigRational<Base>::reduce() {
    BigInteger<Base> gcdValue = gcd(numerator, denominator);
    numerator = numerator / gcdValue;
    denominator = denominator / gcdValue.getMagnitude();
}

// Método para verificar si la fracción está reducida
template <unsigned char Base>
bool BigRational<Base>::isReduced() const {
    return gcd(numerator, denominator) == BigInteger<Base>(1);
}

// Método para calcular el máximo común divisor
template <unsigned char Base>
BigInteger<Base> BigRational<Base>::gcd(const BigInteger<Base>& a, const BigUnsigned<Base>& b) {
    BigInteger<Base> bInt(b);
    return bInt == BigInteger<Base>(0) ? a : gcd(bInt, a.getMagnitude() % bInt.getMagnitude());
}

// Especialización de la plantilla para base binaria

// Constructor por defecto
BigRational<2>::BigRational(const BigInteger<2>& num, const BigUnsigned<2>& denom)
    : numerator(num), denominator(denom) {
    if (denominator == BigUnsigned<2>(0)) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    reduce();
}

// Constructor de copia
BigRational<2>::BigRational(const BigRational<2>& other)
    : numerator(other.numerator), denominator(other.denominator) {}

// Constructor desde string
BigRational<2>::BigRational(const std::string& str) {
    size_t pos = str.find('/');
    if (pos == std::string::npos) {
        throw std::invalid_argument("Invalid input string");
    }
    numerator = BigInteger<2>(str.substr(0, pos));
    denominator = BigUnsigned<2>(str.substr(pos + 1));
    if (denominator == BigUnsigned<2>(0)) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    reduce();
}

// Operador de asignación
BigRational<2>& BigRational<2>::operator=(const BigRational<2>& other) {
    if (this != &other) {
        numerator = other.numerator;
        denominator = other.denominator;
    }
    return *this;
}

// Operador de suma
BigRational<2> BigRational<2>::operator+(const BigRational<2>& other) const {
    BigInteger<2> newNumerator = numerator * BigInteger<2>(other.denominator) + other.numerator * BigInteger<2>(denominator);
    BigUnsigned<2> newDenominator = denominator * other.denominator;
    return BigRational<2>(newNumerator, newDenominator);
}

// Operador de resta
BigRational<2> BigRational<2>::operator-(const BigRational<2>& other) const {
    BigInteger<2> newNumerator = numerator * BigInteger<2>(other.denominator) - other.numerator * BigInteger<2>(denominator);
    BigUnsigned<2> newDenominator = denominator * other.denominator;
    return BigRational<2>(newNumerator, newDenominator);
}

// Operador de multiplicación
BigRational<2> BigRational<2>::operator*(const BigRational<2>& other) const {
    BigInteger<2> newNumerator = numerator * other.numerator;
    BigUnsigned<2> newDenominator = denominator * other.denominator;
    return BigRational<2>(newNumerator, newDenominator);
}

// Operador de división
BigRational<2> BigRational<2>::operator/(const BigRational<2>& other) const {
    if (other.numerator == BigInteger<2>(0)) {
        throw std::invalid_argument("Division by zero");
    }
    BigInteger<2> newNumerator = numerator * BigInteger<2>(other.denominator);
    BigUnsigned<2> newDenominator = denominator * other.numerator.getMagnitude();
    if (other.numerator.isNegative()) {
        newNumerator = -newNumerator;
    }
    return BigRational<2>(newNumerator, newDenominator);
}

// Operador de comparación de igualdad
bool operator==(const BigRational<2>& lhs, const BigRational<2>& rhs) {
    return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}

// Operador de comparación menor que
bool operator<(const BigRational<2>& lhs, const BigRational<2>& rhs) {
    return lhs.numerator * BigInteger<2>(rhs.denominator) < rhs.numerator * BigInteger<2>(lhs.denominator);
}

// Operador de comparación menor o igual que
bool BigRational<2>::operator<=(const BigRational<2>& other) const {
    return *this < other || *this == other;
}

// Operador de comparación mayor que
bool BigRational<2>::operator>(const BigRational<2>& other) const {
    return !(*this <= other);
}

// Operador de comparación mayor o igual que
bool BigRational<2>::operator>=(const BigRational<2>& other) const {
    return !(*this < other);
}

// Método toString
std::string BigRational<2>::toString() const {
    return numerator.toString() + "/" + denominator.toString();
}

// Definición del operador de inserción para BigRational con base 2
std::ostream& operator<<(std::ostream& os, const BigRational<2>& num) {
    os << num.toString();
    return os;
}

// Método para reducir la fracción
void BigRational<2>::reduce() {
    BigInteger<2> gcdValue = gcd(numerator, denominator);
    numerator = numerator / gcdValue;
    denominator = denominator / gcdValue.getMagnitude();
}

// Método para verificar si la fracción está reducida
bool BigRational<2>::isReduced() const {
    return gcd(numerator, denominator) == BigInteger<2>(1);
}

// Método para calcular el máximo común divisor
BigInteger<2> BigRational<2>::gcd(const BigInteger<2>& a, const BigUnsigned<2>& b) {
    BigInteger<2> bInt(b);
    return bInt == BigInteger<2>(0) ? a : gcd(bInt, a.getMagnitude() % bInt.getMagnitude());
}

// Instanciación de plantillas
template class BigRational<8>;
template class BigRational<10>;
template class BigRational<16>;