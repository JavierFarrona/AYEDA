#pragma once

/**
 * @brief Clase abstracta DispersionFunction: tipo de dato para representar una función de dispersión
 */
template <class Key>
class DispersionFunction {
 public:
  //---------------------MÉTODO---------------------
  /// Sobrecarga polimórfica del operador () para calcular la función de dispersión
  virtual unsigned operator() (const Key&) const = 0;
};

#include "module.h"
#include "sum_based.h"
#include "random.h"
