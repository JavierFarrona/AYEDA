/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Algoritmos y Estructuras de datos Avanzadas
 * Curso: 2º
 * C:\Users\javie\Documents\GitHub\AYEDA\Pr1\Pr1\lib
 * Autor: Javier Farrona Cabrera
 * Correo: alu0101541983@ull.edu.es
 * Fecha 06 Feb 2025
 * Archivo: bigInteger.cc
 * Referencias:
 *     Enunciado de la práctica
 */

#include "../lib/BigInteger.h"

#include <algorithm>
#include <stdexcept>

// --- Constructores ---
BigInteger::BigInteger() : magnitude_(), negative_(false) {}

BigInteger::BigInteger(const BigUnsigned& value)
    : magnitude_(value), negative_(false) {}

BigInteger::BigInteger(int value) : magnitude_(), negative_(value < 0) {
  magnitude_ = BigUnsigned(reinterpret_cast<const unsigned char*>(
      std::to_string(std::abs(value)).c_str()));
}

BigInteger::BigInteger(const std::string& value)
    : magnitude_(), negative_(false) {
  if (value.empty()) throw std::invalid_argument("Invalid input string");
  size_t start = 0;

  if (value[0] == '-') {
    negative_ = true;
    start = 1;  // Saltar el signo
  }

  // Convertir el resto de caracteres en BigUnsigned
  magnitude_ = BigUnsigned(
      reinterpret_cast<const unsigned char*>(value.substr(start).c_str()));
}

// --- Métodos de comparación ---
bool BigInteger::operator==(const BigInteger& other) const {
  return (negative_ == other.negative_) && (magnitude_ == other.magnitude_);
}
bool BigInteger::operator!=(const BigInteger& other) const {
  return !(*this == other);
}
bool BigInteger::operator<(const BigInteger& other) const {
  if (negative_ != other.negative_) {
    return negative_ && !other.negative_;
  }

  if (negative_) {
    return magnitude_ > other.magnitude_;  // Comparación inversa
  }
  return magnitude_ < other.magnitude_;
}
bool BigInteger::operator<=(const BigInteger& other) const {
  return (*this < other) || (*this == other);
}
bool BigInteger::operator>(const BigInteger& other) const {
  return !(*this <= other);
}
bool BigInteger::operator>=(const BigInteger& other) const {
  return !(*this < other);
}

// --- Operadores aritméticos ---
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

BigInteger BigInteger::operator-(const BigInteger& other) const {
  BigInteger negatedOther = other;
  negatedOther.negative_ = !other.negative_;
  return *this + negatedOther;
}

BigInteger BigInteger::operator*(const BigInteger& other) const {
  BigInteger result(magnitude_ * other.magnitude_);
  result.negative_ = negative_ != other.negative_;
  return result;
}

BigInteger BigInteger::operator/(const BigInteger& other) const {
  if (other.magnitude_ ==
      BigUnsigned(reinterpret_cast<const unsigned char*>("0"))) {
    throw std::invalid_argument("Division by zero");
  }

  BigInteger result(magnitude_ / other.magnitude_);
  result.negative_ = negative_ != other.negative_;
  return result;
}

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
std::string BigInteger::toString() const {
  std::string result = magnitude_.toString();
  if (negative_) result.insert(result.begin(), '-');
  return result;
}

bool BigInteger::isNegative() const { return negative_; }

void BigInteger::removeLeadingZeros() { magnitude_.removeLeadingZeros(); }

// --- Operadores de entrada/salida ---
std::ostream& operator<<(std::ostream& out, const BigInteger& bigint) {
  return out << bigint.toString();
}

std::istream& operator>>(std::istream& in, BigInteger& bigint) {
  std::string input;
  in >> input;
  bigint = BigInteger(input);
  return in;
}

BigInteger BigInteger::operator-() const {
  BigInteger result = *this;      // Hacer una copia del objeto actual
  result.negative_ = !negative_;  // Cambiar el signo
  return result;
}

BigInteger BigInteger::mcd(const BigInteger& a, const BigInteger& b) {
  // Aseguramos que trabajamos con valores positivos
  BigInteger x = a.isNegative() ? -a : a;
  BigInteger y = b.isNegative() ? -b : b;

  // Algoritmo de Euclides
  while (y != BigInteger(0)) {
    BigInteger temp = y;
    y = x % y;  // Obtenemos el residuo
    x = temp;   // Actualizamos x con y
  }

  return x;  // Cuando y sea 0, x es el MCD
}