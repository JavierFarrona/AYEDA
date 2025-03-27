#pragma once

/**
 * @brief Clase abstracta Sequence: tipo de dato para representar una secuencia
 */
template <class Key>
class Sequence {
 public:
  //-----------------MÉTODOS-----------------
  /// Método polimórfico para buscar un elemento en la secuencia
  virtual bool search (const Key&) const = 0;

  /// Método polimórfico para insertar un elemento en la secuencia
  virtual bool insert (const Key&) = 0;

  /// Método polimórfico para saber si la secuencia está llena
  virtual bool isFull() const = 0;

  /// Método polimórfico para imprimir la secuencia
  virtual std::string print() const = 0;
};

// Incluimos las clases que heredan de Sequence
#include "static_sequence.h"
#include "dynamic_sequence.h"