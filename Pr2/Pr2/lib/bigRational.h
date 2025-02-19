// Rational.h
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
    bool operator==(const BigRational<Base>& other) const;
    bool operator<(const BigRational<Base>& other) const;
    bool operator<=(const BigRational<Base>& other) const;
    bool operator>(const BigRational<Base>& other) const;
    bool operator>=(const BigRational<Base>& other) const;

    // Flujos de entrada y salida
    template <unsigned B>
    friend std::ostream& operator<<(std::ostream& os, const BigRational<B>& rat);
    template <unsigned B>
    friend std::istream& operator>>(std::istream& is, BigRational<B>& rat);

    // Métodos auxiliares
    std::string toString() const;
    bool isNegative() const { return numerator.isNegative(); }
    BigRational<Base> reduce() const;
    bool isReduced() const;
  static BigInteger<Base> gcd(const BigInteger<Base>& a, const BigUnsigned<Base>& b); // Declaración de gcd

  private:
    BigInteger<Base> numerator;
    BigUnsigned<Base> denominator;
    void reduce();
};

#endif