#pragma once

#include "exploration_function.h"

/**
 * @brief Clase LinealExploration: tipo de dato para representar una función de exploración lineal
 */
template <class Key>
class LinealExploration : public ExplorationFunction<Key> {
 public:
  //-----------------------------MÉTODO-----------------------------
  /// Sobrecarga del operador () para calcular la función de exploración lineal
  virtual unsigned operator() (const Key&, unsigned) const override;
};

/**
 * @brief Sobrecarga del operador () para calcular la función de exploración lineal
 * @param[in] key: referencia (constante) al elemento a buscar
 * @param[in] i: número de intentos
 * @return Devuelve el resultado de la función de exploración lineal
 */
template <class Key>
unsigned LinealExploration<Key>::operator() (const Key& key, unsigned i) const { return (key + i); }