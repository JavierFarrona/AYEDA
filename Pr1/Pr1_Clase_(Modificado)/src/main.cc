/**
 * @file main.cc
 * @brief Main file for demonstrating the usage of BigInteger and BigUnsigned
 * classes.
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

#include <iostream>

#include "../lib/bigInteger.h"
#include "../lib/bigUnsigned.h"

/**
 * @brief Calculate the greatest common divisor (GCD) of two BigInteger values
 * using the Euclidean algorithm.
 *
 * @param a The first BigInteger value.
 * @param b The second BigInteger value.
 * @return BigInteger The GCD of the two values.
 */
BigInteger mcd(const BigInteger& a, const BigInteger& b) {
  // Ensure we work with positive values
  BigInteger x = a.isNegative() ? -a : a;
  BigInteger y = b.isNegative() ? -b : b;

  // Euclidean algorithm
  while (y != BigInteger(0)) {
    BigInteger temp = y;
    y = x % y;  // Get the remainder
    x = temp;   // Update x with y
  }

  return x;  // When y is 0, x is the GCD
}

int main() {

  // Calculate GCD of two BigInteger values
  BigInteger a("-48");
  BigInteger b("18");

  std::cout << "MCD de " << a << " y " << b << " es: " << mcd(a, b)
            << std::endl;

  BigInteger c("12345678901234567890");
  BigInteger d("-98765432109876543210");

  std::cout << "MCD de " << c << " y " << d << " es: " << mcd(c, d)
            << std::endl;

  return 0;
}
