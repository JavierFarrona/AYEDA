#pragma once

/**
 * @brief Clase abstracta ExplorationFunction: tipo de dato para representar una función de exploración
 */
template <class Key>
class ExplorationFunction {
 public:
  //--------------------------MÉTODO--------------------------
  /// Sobrecarga polimórfica del operador () para calcular la función de exploración
  virtual unsigned operator() (const Key&, unsigned) const = 0;
};

#include "cuadratic_exploration.h"
#include "lineal_exploration.h"
#include "redispersion_exploration.h"
#include "double_dispersion_exploration.h"