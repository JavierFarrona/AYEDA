// Rational.cpp
#include "../lib/bigRational.h"

template <unsigned char Base>
void BigRational<Base>::reduce() {
  BigInteger<Base> a = numerator;
  BigUnsigned<Base> b = denominator;
  while (b != BigUnsigned<Base>(0)) {
    BigUnsigned<Base> temp = b;
    b = a % b;
    a = temp;
  }
  numerator = numerator / a;
  denominator = denominator / a;
}

template <unsigned char Base>
BigRational<Base>::BigRational(const BigInteger<Base>& num, const BigUnsigned<Base>& denom)
    : numerator(num), denominator(denom) {
  reduce();
}

template <unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigRational<Base>& rat) {
  os << rat.numerator << "/" << rat.denominator;
  return os;
}
