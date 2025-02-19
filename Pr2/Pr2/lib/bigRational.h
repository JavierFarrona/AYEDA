#pragma once

#ifndef BIGRATIONAL_H
#define BIGRATIONAL_H

#include "bigInteger.h"

template <unsigned char Base>
class BigRational {
public:
  // Constructores
  BigRational(const BigInteger<Base>& num = 0, const BigUnsigned<Base>& denom = 1);
  BigRational(const BigRational<Base>& other);
  BigRational(const std::string& str);

  // Asignación
  BigRational<Base>& operator=(const BigRational<Base>& other);

  // Operadores aritméticos
  BigRational<Base> operator+(const BigRational<Base>& other) const;
  BigRational<Base> operator-(const BigRational<Base>& other) const;
  BigRational<Base> operator*(const BigRational<Base>& other) const;
  BigRational<Base> operator/(const BigRational<Base>& other) const;

  // Comparación
  template <unsigned char B>
  friend bool operator==(const BigRational<B>& lhs, const BigRational<B>& rhs);
  template <unsigned char B>
  friend bool operator<(const BigRational<B>& lhs, const BigRational<B>& rhs);

  bool operator<=(const BigRational<Base>& other) const;
  bool operator>(const BigRational<Base>& other) const;
  bool operator>=(const BigRational<Base>& other) const;

  // Flujos de entrada y salida
  template <unsigned char B>
  friend std::ostream& operator<<(std::ostream& os, const BigRational<B>& rat);
  template <unsigned char B>
  friend std::istream& operator>>(std::istream& is, BigRational<B>& rat);

  // Métodos auxiliares
  std::string toString() const;
  bool isNegative() const { return numerator.isNegative(); }
  void reduce();
  bool isReduced() const;
  static BigInteger<Base> gcd(const BigInteger<Base>& a, const BigUnsigned<Base>& b);

private:
  BigInteger<Base> numerator;
  BigUnsigned<Base> denominator;
};

template <unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigRational<Base>& rat);

#endif