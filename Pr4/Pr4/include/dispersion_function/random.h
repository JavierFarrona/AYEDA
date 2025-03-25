#pragma once

#include <random>

#include "dispersion_function.h"

/**
 * @brief Clase Random: tipo de dato para representar una función de dispersión aleatoria
 */
template <class Key>
class Random : public DispersionFunction<Key> {
 public:
  //--------------------CONSTRUCTOR--------------------
  Random(unsigned tableSize) { tableSize_ = tableSize; }

  //--------------------------MÉTODO--------------------------
  /// Sobrecarga del operador () para calcular la función de dispersión aleatoria
  virtual unsigned operator() (const Key& key) const override { 
    srand(key);                     // Crea una semilla aleatoria
    return (rand() % tableSize_);   // Devuelve un número aleatorio del valor de esa semilla
  }

 private:
  //-----ATRIBUTO-----
  /// tableSize_: tamaño de la Tabla Hash
  unsigned tableSize_;
};