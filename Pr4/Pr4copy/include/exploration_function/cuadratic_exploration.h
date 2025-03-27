#pragma once

#include "exploration_function.h"

/**
 * @brief Clase CuadraticExploration: tipo de dato para representar una función de exploración cuadrática
 */
template <class Key>
class CuadraticExploration : public ExplorationFunction<Key> {
 public:
  //-----------------------------MÉTODO-----------------------------
  /// Sobrecarga del operador () para calcular la función de exploración cuadrática
  virtual unsigned operator() (const Key&, unsigned) const override;
};

/**
 * @brief Sobrecarga del operador () para calcular la función de exploración cuadrática
 * @param[in] key: referencia (constante) al elemento a buscar
 * @param[in] i: número de intentos
 * @return Devuelve el resultado de la función de exploración cuadrática
 */
template <class Key>
unsigned CuadraticExploration<Key>::operator() (const Key& key, unsigned i) const { return (key * key) * i; }