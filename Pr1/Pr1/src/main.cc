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
 * Archivo: main.cc
 * Referencias:
 *     Enunciado de la práctica
 */

#include <iostream>

#include "../lib/bigInteger.h"
#include "../lib/bigUnsigned.h"

int main() {
  // Crear dos números grandes a partir de cadenas
  BigUnsigned num1((const unsigned char*)"123456");
  BigUnsigned num2((const unsigned char*)"789");

  // Mostrar números iniciales
  std::cout << "Número 1: " << num1 << std::endl;
  std::cout << "Número 2: " << num2 << std::endl;

  // Suma de los dos números
  BigUnsigned suma = num1 + num2;
  std::cout << "Suma: " << suma << std::endl;

  // Comparación de los números
  if (num1 < num2) {
    std::cout << "Número 1 es menor que Número 2." << std::endl;
  } else if (num1 == num2) {
    std::cout << "Número 1 es igual a Número 2." << std::endl;
  } else {
    std::cout << "Número 1 es mayor que Número 2." << std::endl;
  }

  // Incremento y decremento
  std::cout << "Pre-incremento de Número 1: " << ++num1 << std::endl;
  std::cout << "Post-incremento de Número 2: " << num2++ << std::endl;
  std::cout << "Número 2 después del post-incremento: " << num2 << std::endl;

  // Resta de los números
  BigUnsigned resta = num1 - num2;
  std::cout << "Resta (Número 1 - Número 2): " << resta << std::endl;

  // Multiplicación
  BigUnsigned product = num1 * num2;
  std::cout << "Producto: " << product << std::endl;

  // División
  BigUnsigned quotient = num1 / num2;
  std::cout << "Cociente: " << quotient << std::endl;

  // Módulo
  BigUnsigned remainder = num1 % num2;
  std::cout << "Residuo: " << remainder << std::endl;

  // Entrada desde el usuario
  BigUnsigned num3;
  std::cout << "Introduce un número grande: ";
  std::cin >> num3;
  std::cout << "El número que ingresaste fue: " << num3 << std::endl;

  BigInteger a("-48");
  BigInteger b("18");

  std::cout << "MCD de " << a << " y " << b << " es: " << BigInteger::mcd(a, b)
            << std::endl;

  BigInteger c("12345678901234567890");
  BigInteger d("-98765432109876543210");

  std::cout << "MCD de " << c << " y " << d << " es: " << BigInteger::mcd(c, d)
            << std::endl;

  return 0;
}
