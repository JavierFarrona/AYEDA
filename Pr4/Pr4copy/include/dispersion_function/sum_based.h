#pragma once

#include "dispersion_function.h"

/**
 * @brief Función auxiliar para calcular la suma de los caracteres de una cadena
 * @param[in] key: clave a la que se le calculará la suma de sus caracteres
 * @return Devuelve la suma de los caracteres de la clave
 */
unsigned sum(const std::string& key) {
  unsigned sum = 0;

  for (char caracter : key) { sum += caracter; }
  
  return sum;
}

/**
 * @brief Función auxiliar para calcular la suma de los dígitos de un número
 * @param[in] key: clave a la que se le calculará la suma de sus dígitos
 * @return Devuelve la suma de los dígitos de la clave
 */
unsigned sum(int key) {
  unsigned sum = 0;

  while (key % 10 != 0) {
    sum += key % 10;
    key /= 10;
  }

  return sum;
}

/**
 * @brief Clase SumBased: tipo de dato para representar una función de dispersión basada en la suma
 */
template <class Key>
class SumBased : public DispersionFunction<Key> {
 public:
  //---------------------CONSTRUCTOR---------------------
  SumBased(unsigned tableSize) { tableSize_ = tableSize; }

  //--------------------------MÉTODO--------------------------
  /// Sobrecarga del operador () para calcular la función de dispersión basada en la suma
  virtual unsigned operator() (const Key& key) const override { return (sum(key) % tableSize_); }

 private:
  //-----ATRIBUTO-----
  /// tableSize_: tamaño de la Tabla Hash
  unsigned tableSize_;
};