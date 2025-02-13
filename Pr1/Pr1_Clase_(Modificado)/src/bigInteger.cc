/**
 * @file bigInteger.cc
 * @brief Implementation of the BigInteger class for handling large signed
 * integers.
 *
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Algoritmos y Estructuras de datos Avanzadas
 * Curso: 2º
 * C:\Users\javie\Documents\GitHub\AYEDA\Pr1\Pr1\lib
 * Autor: Javier Farrona Cabrera
 * Correo: alu0101541983@ull.edu.es
 * Fecha 06 Feb 2025
 * Referencias:
 *     Enunciado de la práctica
 */

#include "../lib/bigInteger.h"

// --- Constructores ---

/**
 * @brief Construct a new BigInteger object with a default value of 0.
 */
BigInteger::BigInteger() : magnitude_(), negative_(false) {}

/**
 * @brief Construct a new BigInteger object from a BigUnsigned value.
 *
 * @param value The BigUnsigned value to initialize the BigInteger.
 */
BigInteger::BigInteger(const BigUnsigned& value)
    : magnitude_(value), negative_(false) {}

/**
 * @brief Construct a new BigInteger object from an integer value.
 *
 * @param value The integer value to initialize the BigInteger.
 */
BigInteger::BigInteger(int value) : magnitude_(), negative_(value < 0) {
  // Convert the absolute value of the integer to BigUnsigned
  magnitude_ = BigUnsigned(reinterpret_cast<const unsigned char*>(
      std::to_string(std::abs(value)).c_str()));
}

/**
 * @brief Construct a new BigInteger object from a string representation.
 *
 * @param value The string representation of the integer.
 * @throws std::invalid_argument if the input string is invalid.
 */
BigInteger::BigInteger(const std::string& value)
    : magnitude_(), negative_(false) {
  if (value.empty()) throw std::invalid_argument("Invalid input string");
  size_t start = 0;

  if (value[0] == '-') {
    negative_ = true;
    start = 1;  // Skip the sign
  }

  // Convert the remaining characters to BigUnsigned
  magnitude_ = BigUnsigned(
      reinterpret_cast<const unsigned char*>(value.substr(start).c_str()));
}

// --- Métodos de comparación ---

/**
 * @brief Equality comparison operator for BigInteger.
 *
 * @param other The BigInteger object to compare with.
 * @return true if the objects are equal.
 * @return false if the objects are not equal.
 */
bool BigInteger::operator==(const BigInteger& other) const {
  return (negative_ == other.negative_) && (magnitude_ == other.magnitude_);
}

/**
 * @brief Inequality comparison operator for BigInteger.
 *
 * @param other The BigInteger object to compare with.
 * @return true if the objects are not equal.
 * @return false if the objects are equal.
 */
bool BigInteger::operator!=(const BigInteger& other) const {
  return !(*this == other);
}

/**
 * @brief Less-than comparison operator for BigInteger.
 *
 * @param other The BigInteger object to compare with.
 * @return true if this object is less than the other.
 * @return false otherwise.
 */
bool BigInteger::operator<(const BigInteger& other) const {
  if (negative_ != other.negative_) {
    return negative_ && !other.negative_;
  }

  if (negative_) {
    return magnitude_ > other.magnitude_;  // Inverse comparison
  }
  return magnitude_ < other.magnitude_;
}

/**
 * @brief Less-than or equal-to comparison operator for BigInteger.
 *
 * @param other The BigInteger object to compare with.
 * @return true if this object is less than or equal to the other.
 * @return false otherwise.
 */
bool BigInteger::operator<=(const BigInteger& other) const {
  return (*this < other) || (*this == other);
}

/**
 * @brief Greater-than comparison operator for BigInteger.
 *
 * @param other The BigInteger object to compare with.
 * @return true if this object is greater than the other.
 * @return false otherwise.
 */
bool BigInteger::operator>(const BigInteger& other) const {
  return !(*this <= other);
}

/**
 * @brief Greater-than or equal-to comparison operator for BigInteger.
 *
 * @param other The BigInteger object to compare with.
 * @return true if this object is greater than or equal to the other.
 * @return false otherwise.
 */
bool BigInteger::operator>=(const BigInteger& other) const {
  return !(*this < other);
}

// --- Operadores aritméticos ---

/**
 * @brief Addition operator for BigInteger.
 *
 * @param other The BigInteger object to add.
 * @return BigInteger The result of the addition.
 */
BigInteger BigInteger::operator+(const BigInteger& other) const {
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

/**
 * @brief Subtraction operator for BigInteger.
 *
 * @param other The BigInteger object to subtract.
 * @return BigInteger The result of the subtraction.
 */
BigInteger BigInteger::operator-(const BigInteger& other) const {
  BigInteger negatedOther = other;
  negatedOther.negative_ = !other.negative_;
  return *this + negatedOther;
}

/**
 * @brief Multiplication operator for BigInteger.
 *
 * @param other The BigInteger object to multiply with.
 * @return BigInteger The result of the multiplication.
 */
BigInteger BigInteger::operator*(const BigInteger& other) const {
  BigInteger result(magnitude_ * other.magnitude_);
  result.negative_ = negative_ != other.negative_;
  return result;
}

/**
 * @brief Division operator for BigInteger.
 *
 * @param other The BigInteger object to divide by.
 * @return BigInteger The result of the division.
 * @throws std::invalid_argument if the divisor is zero.
 */
BigInteger BigInteger::operator/(const BigInteger& other) const {
  if (other.magnitude_ ==
      BigUnsigned(reinterpret_cast<const unsigned char*>("0"))) {
    throw std::invalid_argument("Division by zero");
  }

  BigInteger result(magnitude_ / other.magnitude_);
  result.negative_ = negative_ != other.negative_;
  return result;
}

/**
 * @brief Modulus operator for BigInteger.
 *
 * @param other The BigInteger object to divide by.
 * @return BigInteger The remainder of the division.
 * @throws std::invalid_argument if the divisor is zero.
 */
BigInteger BigInteger::operator%(const BigInteger& other) const {
  if (other.magnitude_ ==
      BigUnsigned(reinterpret_cast<const unsigned char*>("0"))) {
    throw std::invalid_argument("Modulo by zero");
  }
  BigInteger result(magnitude_ % other.magnitude_);
  result.negative_ = negative_;
  return result;
}

// --- Métodos auxiliares ---

/**
 * @brief Convert the BigInteger number to a string representation.
 *
 * @return std::string The string representation of the number.
 */
std::string BigInteger::toString() const {
  std::string result = magnitude_.toString();
  if (negative_) result.insert(result.begin(), '-');
  return result;
}

/**
 * @brief Check if the BigInteger is negative.
 *
 * @return true if the number is negative.
 * @return false otherwise.
 */
bool BigInteger::isNegative() const { return negative_; }

/**
 * @brief Remove leading zeros from the number.
 */
void BigInteger::removeLeadingZeros() { magnitude_.removeLeadingZeros(); }

// --- Operadores de entrada/salida ---

/**
 * @brief Overload of the insertion operator for outputting BigInteger objects.
 *
 * @param out The output stream.
 * @param bigint The BigInteger object to output.
 * @return std::ostream& The output stream.
 */
std::ostream& operator<<(std::ostream& out, const BigInteger& bigint) {
  return out << bigint.toString();
}

/**
 * @brief Overload of the extraction operator for inputting BigInteger objects.
 *
 * @param in The input stream.
 * @param bigint The BigInteger object to input into.
 * @return std::istream& The input stream.
 */
std::istream& operator>>(std::istream& in, BigInteger& bigint) {
  std::string input;
  in >> input;
  bigint = BigInteger(input);
  return in;
}

/**
 * @brief Unary negation operator for BigInteger.
 *
 * @return BigInteger The negated value.
 */
BigInteger BigInteger::operator-() const {
  BigInteger result = *this;      // Make a copy of the current object
  result.negative_ = !negative_;  // Change the sign
  return result;
}