// Rational.h
#ifndef BIGRATIONAL_H
#define BIGRATIONAL_H
#include "bigInteger.h"

template <unsigned char Base>
class BigRational {
private:
  BigInteger<Base> numerator;
  BigUnsigned<Base> denominator;
  void reduce();
public:
  BigRational(const BigInteger<Base>& num = 0, const BigUnsigned<Base>& denom = 1);
  friend std::ostream& operator<<(std::ostream& os, const BigRational& rat);
};

#endif