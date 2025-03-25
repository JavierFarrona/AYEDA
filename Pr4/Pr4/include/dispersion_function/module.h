#pragma once

#include "dispersion_function.h"

/**
 * @brief Clase Module: tipo de dato para representar una función de dispersión por módulo
 */
template <class Key>
class Module : public DispersionFunction<Key> {
 public:
  //--------------------CONSTRUCTOR--------------------
  Module(unsigned tableSize) { tableSize_ = tableSize; }

  //-------------------------MÉTODO-------------------------
  /// Sobrecarga del operador () para calcular la función de dispersión por módulo
  virtual unsigned operator() (const Key& key) const override { return (key % tableSize_); }

 private:
  //-----ATRIBUTO-----
  /// tableSize_: tamaño de la Tabla Hash
  unsigned tableSize_;
};