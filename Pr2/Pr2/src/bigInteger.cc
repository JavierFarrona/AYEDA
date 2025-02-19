// Integer.cpp
#include "../lib/bigInteger.h"

// Constructor por defecto
template <unsigned char Base>
BigInteger<Base>::BigInteger() : magnitude_(), negative_(false) {}

// Constructor desde BigUnsigned
template <unsigned char Base>
BigInteger<Base>::BigInteger(const BigUnsigned<Base>& value) : magnitude_(value), negative_(false) {}

// Constructor desde entero
template <unsigned char Base>
BigInteger<Base>::BigInteger(int value) : magnitude_(), negative_(value < 0) {
  magnitude_ = BigUnsigned<Base>(reinterpret_cast<const unsigned char*>(std::to_string(std::abs(value)).c_str()));
}

// Constructor desde string
template <unsigned char Base>
BigInteger<Base>::BigInteger(const std::string& str) : magnitude_(), negative_(false) {
  if (str.empty()) throw std::invalid_argument("Invalid input string");
  size_t start = 0;
  if (str[0] == '-') {
    negative_ = true;
    start = 1;
  }
  magnitude_ = BigUnsigned<Base>(reinterpret_cast<const unsigned char*>(str.substr(start).c_str()));
}

// Constructor de copia
template <unsigned char Base>
BigInteger<Base>::BigInteger(const BigInteger<Base>& other) {
    magnitude_ = other.magnitude_;
    negative_ = other.negative_;
}

// Operador de asignación
template <unsigned char Base>
BigInteger<Base>& BigInteger<Base>::operator=(const BigInteger<Base>& other) {
    if (this != &other) {
        magnitude_ = other.magnitude_;
        negative_ = other.negative_;
    }
    return *this;
}

template <unsigned char Base>
bool BigInteger<Base>::operator==(const BigInteger<Base>& other) const {
  return (negative_ == other.negative_) && (magnitude_ == other.magnitude_);
}

template <unsigned char Base>
bool BigInteger<Base>::operator<(const BigInteger<Base>& other) const {
  if (negative_ != other.negative_) {
    return negative_ && !other.negative_;
  }
  if (negative_) {
    return magnitude_ > other.magnitude_;
  }
  return magnitude_ < other.magnitude_;
}

template <unsigned char Base>
bool BigInteger<Base>::operator<=(const BigInteger<Base>& other) const {
  return (*this < other) || (*this == other);
}

template <unsigned char Base>
bool BigInteger<Base>::operator>(const BigInteger<Base>& other) const {
  return !(*this <= other);
}

template <unsigned char Base>
bool BigInteger<Base>::operator>=(const BigInteger<Base>& other) const {
  return !(*this < other);
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator+(const BigInteger<Base>& other) const {
  if (negative_ == other.negative_) {
    BigInteger result(magnitude_ + other.magnitude_);
    result.negative_ = negative_;
    return result;
  }
  if (magnitude_ >= other.magnitude_) {
    BigInteger result(magnitude_ - other.magnitude_);
    result.negative_ = negative_;
    return result;
  } else {
    BigInteger result(other.magnitude_ - magnitude_);
    result.negative_ = other.negative_;
    return result;
  }
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator-(const BigInteger<Base>& other) const {
  BigInteger negatedOther = other;
  negatedOther.negative_ = !other.negative_;
  return *this + negatedOther;
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator*(const BigInteger<Base>& other) const {
  BigInteger result(magnitude_ * other.magnitude_);
  result.negative_ = negative_ != other.negative_;
  return result;
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator/(const BigInteger<Base>& other) const {
  if (other.magnitude_ == BigUnsigned<Base>(reinterpret_cast<const unsigned char*>("0"))) {
    throw std::invalid_argument("Division by zero");
  }
  BigInteger result(magnitude_ / other.magnitude_);
  result.negative_ = negative_ != other.negative_;
  return result;
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator%(const BigInteger<Base>& other) const {
  if (other.magnitude_ == BigUnsigned<Base>(reinterpret_cast<const unsigned char*>("0"))) {
    throw std::invalid_argument("Modulo by zero");
  }
  BigInteger result(magnitude_ % other.magnitude_);
  result.negative_ = negative_;
  return result;
}

template <unsigned char Base>
std::string BigInteger<Base>::toString() const {
  std::string result = magnitude_.toString();
  if (negative_) result.insert(result.begin(), '-');
  return result;
}

template <unsigned char Base>
void BigInteger<Base>::removeLeadingZeros() {
  magnitude_.removeLeadingZeros();
}

/*
template<unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigInteger<Base>& num) {
    // Aquí debes implementar la lógica para convertir el objeto BigInteger a una cadena
    // y enviarla al flujo de salida. Esto es solo un ejemplo básico.
    os << num.toString(); // Asumiendo que tienes un método toString() en BigInteger
    return os;
}

template <unsigned char Base>
std::istream& operator>>(std::istream& in, BigInteger<Base>& bigint) {
  std::string input;
  in >> input;
  bigint = BigInteger<Base>(input);
  return in;
}
*/
template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator-() const {
  BigInteger result = *this;
  result.negative_ = !negative_;
  return result;
}

//-------------------------------------------------------------------------------------------

// Especialización de la plantilla para base binaria

// Constructor desde entero
BigInteger<2>::BigInteger(int n) : magnitude(), negative(n < 0) {
  magnitude = BigUnsigned<2>(std::to_string(std::abs(n)));
}

// Constructor desde string
BigInteger<2>::BigInteger(const std::string& str) : magnitude(), negative(false) {
  if (str.empty()) throw std::invalid_argument("Invalid input string");
  size_t start = 0;
  if (str[0] == '-') {
    negative = true;
    start = 1;
  }
  magnitude = BigUnsigned<2>(str.substr(start));
}

// Constructor de copia
BigInteger<2>::BigInteger(const BigUnsigned<2>& mag) : magnitude(mag), negative(false) {}

// Asignación
BigInteger<2>& BigInteger<2>::operator=(const BigInteger<2>& other) {
  if (this != &other) {
    magnitude = other.magnitude;
    negative = other.negative;
  }
  return *this;
}

// Flujos de entrada y salida
std::istream& operator>>(std::istream& is, BigInteger<2>& num) {
  std::string str;
  is >> str;
  num = BigInteger<2>(str);
  return is;
}

std::ostream& operator<<(std::ostream& os, const BigInteger<2>& num) {
  if (num.negative) os << '-';
  os << num.magnitude.toString();
  return os;
}

// Comparación
bool BigInteger<2>::operator==(const BigInteger<2>& other) const {
  return (negative == other.negative) && (magnitude == other.magnitude);
}

bool BigInteger<2>::operator<(const BigInteger<2>& other) const {
  if (negative != other.negative) {
    return negative && !other.negative;
  }
  if (negative) {
    return magnitude > other.magnitude;
  }
  return magnitude < other.magnitude;
}

bool BigInteger<2>::operator<=(const BigInteger<2>& other) const {
  return (*this < other) || (*this == other);
}

bool BigInteger<2>::operator>(const BigInteger<2>& other) const {
  return !(*this <= other);
}

bool BigInteger<2>::operator>=(const BigInteger<2>& other) const {
  return !(*this < other);
}

// Incremento y decremento
BigInteger<2>& BigInteger<2>::operator++() {
  *this = *this + BigInteger<2>(1);
  return *this;
}

BigInteger<2> BigInteger<2>::operator++(int) {
  BigInteger<2> temp = *this;
  ++(*this);
  return temp;
}

BigInteger<2>& BigInteger<2>::operator--() {
  *this = *this - BigInteger<2>(1);
  return *this;
}

BigInteger<2> BigInteger<2>::operator--(int) {
  BigInteger<2> temp = *this;
  --(*this);
  return temp;
}

// Operadores aritméticos
BigInteger<2> BigInteger<2>::operator+(const BigInteger<2>& other) const {
  BigInteger<2> result;
  if (negative == other.negative) {
    result.magnitude = magnitude + other.magnitude;
    result.negative = negative;
  } else {
    if (magnitude >= other.magnitude) {
      result.magnitude = magnitude - other.magnitude;
      result.negative = negative;
    } else {
      result.magnitude = other.magnitude - magnitude;
      result.negative = other.negative;
    }
  }
  return result;
}

BigInteger<2> BigInteger<2>::operator-(const BigInteger<2>& other) const {
  BigInteger<2> negatedOther = other;
  negatedOther.negative = !other.negative;
  return *this + negatedOther;
}

BigInteger<2> BigInteger<2>::operator*(const BigInteger<2>& other) const {
  BigInteger<2> result(magnitude * other.magnitude);
  result.negative = negative != other.negative;
  return result;
}

BigInteger<2> BigInteger<2>::operator/(const BigInteger<2>& other) const {
  if (other.magnitude == BigUnsigned<2>("0")) {
    throw std::invalid_argument("Division by zero");
  }
  BigInteger<2> result(magnitude / other.magnitude);
  result.negative = negative != other.negative;
  return result;
}

BigInteger<2> BigInteger<2>::operator%(const BigInteger<2>& other) const {
  if (other.magnitude == BigUnsigned<2>("0")) {
    throw std::invalid_argument("Modulo by zero");
  }
  BigInteger<2> result(magnitude % other.magnitude);
  result.negative = negative;
  return result;
}

BigInteger<2> BigInteger<2>::operator-() const {
  BigInteger<2> result = *this;
  result.negative = !negative;
  return result;
}

// Métodos auxiliares
std::string BigInteger<2>::toString() const {
  std::string result = magnitude.toString();
  if (negative) result.insert(result.begin(), '-');
  return result;
}

void BigInteger<2>::removeLeadingZeros() {
  magnitude.removeLeadingZeros();
}

// bigInteger.cc
BigInteger<2> BigInteger<2>::complement_2() const {
  BigInteger<2> result = *this;
  for (auto bit : result.magnitude.getBits()) {
    bit = !bit;
  }
  return ++result;
}

template class BigInteger<8>;
template class BigInteger<10>;
template class BigInteger<16>;