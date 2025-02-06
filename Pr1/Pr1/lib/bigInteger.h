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
 * Archivo: bigInteger.h
 * Referencias:
 *     Enunciado de la práctica
 */

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <iostream>
#include <string>

#include "../lib/BigUnsigned.h"  // Incluimos BigUnsigned como parte de BigInteger

class BigInteger {
 public:
  // Constructores
  BigInteger();  // Constructor por defecto (crea un BigInteger igual a 0)
  BigInteger(
      const BigUnsigned& value);  // Constructor desde BigUnsigned positivo
  BigInteger(int value);          // Constructor desde un entero
  BigInteger(const std::string& value);  // Constructor desde string

  // Operadores aritméticos
  BigInteger operator+(const BigInteger& other) const;
  BigInteger operator-(const BigInteger& other) const;
  BigInteger operator*(const BigInteger& other) const;
  BigInteger operator/(const BigInteger& other) const;
  BigInteger operator%(const BigInteger& other) const;
  BigInteger operator-() const;

  // Operadores compuestos
  BigInteger& operator+=(const BigInteger& other);
  BigInteger& operator-=(const BigInteger& other);
  BigInteger& operator*=(const BigInteger& other);
  BigInteger& operator/=(const BigInteger& other);
  BigInteger& operator%=(const BigInteger& other);

  // Comparación
  bool operator==(const BigInteger& other) const;
  bool operator!=(const BigInteger& other) const;
  bool operator<(const BigInteger& other) const;
  bool operator<=(const BigInteger& other) const;
  bool operator>(const BigInteger& other) const;
  bool operator>=(const BigInteger& other) const;

  // Operadores de entrada/salida
  friend std::ostream& operator<<(std::ostream& out, const BigInteger& bigint);
  friend std::istream& operator>>(std::istream& in, BigInteger& bigint);

  // Auxiliares
  std::string toString() const;  // Convierte BigInteger a string
  bool isNegative() const;       // Verifica si es negativo

  // Método para calcular el máximo común divisor (MCD)
  static BigInteger mcd(const BigInteger& a, const BigInteger& b);

 private:
  BigUnsigned magnitude_;  // Almacena el valor absoluto del número
  bool negative_;          // Determina si el número es negativo

  // Métodos auxiliares privados
  void removeLeadingZeros();  // Elimina ceros innecesarios
};

#endif  // BIGINTEGER_H