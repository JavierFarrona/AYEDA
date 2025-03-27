#pragma once

#include "exploration_function.h"

/**
 * @brief Clase RedispertionExploration: tipo de dato para representar una función de exploración por redispersión
 */
template <class Key>
class RedispersionExploration : public ExplorationFunction<Key> {
 public:
  //--------------------------CONSTRUCTOR--------------------------
  RedispersionExploration(DispersionFunction<Key>* fd) : fd_(fd) {}

  //-----------------------------MÉTODO-----------------------------
  /// Sobrecarga del operador () para calcular la función de exploración por redispersión
  virtual unsigned operator() (const Key&, unsigned) const override;

  private:
  //---------ATRIBUTO---------
  /// fd_: representa la función de dispersión
  DispersionFunction<Key>* fd_;
};

/**
 * @brief Sobrecarga del operador () para calcular la función de exploración por redispersión
 * @param[in] key: referencia (constante) al elemento a buscar
 * @param[in] i: número de intentos
 * @return Devuelve el resultado de la función de exploración por redispersión
 */
template <class Key>
unsigned RedispersionExploration<Key>::operator() (const Key& key, unsigned i) const { return fd_->operator()(key); }