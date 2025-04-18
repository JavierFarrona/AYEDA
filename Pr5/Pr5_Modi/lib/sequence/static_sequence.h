#pragma once

#include <vector>
#include <cassert>

#include "sequence.h"

/**
 * @brief Clase staticSequence: tipo de dato para representar un contenedor de datos en una secuencia estática, es decir que el tamaño no varía en tiempo de ejecución.
 */
template <class Key>
class staticSequence : public Sequence<Key> {
 public:
  //------CONSTRUCTOR------
  staticSequence();
  staticSequence(unsigned);

  //-------------------------GETTER-------------------------
  /// Getter del tamaño de la secuencia de elementos
  virtual unsigned getSize() const override { return size_; }

  //---------------MÉTODOS---------------
  /// Método para buscar un elemento en la secuencia
  virtual bool search (const Key&) const override;

  /// Método para insertar un elemento en la secuencia
  virtual bool insert (const Key&) override;

  /// Método para saber si la secuencia está llena
  virtual bool isFull() const override;

  /// Método para imprimir la secuencia
  virtual std::string print() const override;

  /// Sobrecarga del operador de indexación ([]) para la clase staticSequence
  virtual Key& operator[] (Position) override;
  
  /// Sobrecarga del operador de inserción del flujo de entrada (<<)
  virtual std::ostream& operator<<(std::ostream&) const override;

 private:
  //------ATRIBUTOS------
  /// sequence_: representa el vector de elementos que forman la secuencia
  std::vector<Key> sequence_;
  /// size_: representa el tamaño del bloque
  unsigned size_;
  /// blockElementsUsed_: representa el número de elementos usados en el bloque (para saber si está llena)
  unsigned blockElementsUsed_;
};

/**
 * @brief Constructor de la secuencia estática
 */
template <class Key>
staticSequence<Key>::staticSequence() {
  size_ = 0;
  blockElementsUsed_ = 0;
}

/**
 * @brief Constructor de la secuencia estática
 * @param[in] size: tamaño del bloque
 */
template <class Key>
staticSequence<Key>::staticSequence(unsigned size) {
  size_ = size;
  blockElementsUsed_ = 0;
  sequence_.resize(size, -1);  // Inicializamos el vector con valores -1 para saber si está vacío o no.
}

/**
 * @brief Método para buscar un elemento en la secuencia
 * @param[in] key: referencia (constante) de la clave a buscar
 * @return Devuelve true si el elemento se encuentra en la secuencia, false en caso contrario
 */
template <class Key>
bool staticSequence<Key>::search (const Key& key) const {
  for (const Key &element : sequence_) {
    if (element == key) { return true; }
  }
  return false;
}


/**
 * @brief Método para insertar un elemento en la secuencia
 * @param[in] key: referencia (constante) de la clave a insertar
 * @return Devuelve true si el elemento se ha insertado correctamente, false en caso contrario
 */
template <class Key> 
bool staticSequence<Key>::insert (const Key& key) {
  // Si la secuencia está llena o ya ese valor ha sido insertado, no podemos insertar ese elemento.
  if (isFull() || search(key)) { return false; } 
  for (int i = 0; i < sequence_.size(); i++) {
    if (sequence_[i] == Key(-1)) {
      sequence_[i] = key;      // Si encontramos un hueco vacío, insertamos el elemento.
      blockElementsUsed_++;    // Si hemos conseguido insertarlo porque existe un hueco vacío, incrementamos en uno el valor de los elementos usados.
      return true; 
    }
  }
  return false;
}

/**
 * @brief Método para saber si la secuencia está llena
 * @return Devuelve true si la secuencia está llena, false en caso contrario
 */
template <class Key>
bool staticSequence<Key>::isFull() const {
  // Si el número de elementos usados es igual al tamaño del bloque, la secuencia está llena.
  if (blockElementsUsed_ == size_) { return true; }
  return false;
}

/**
 * @brief Método para imprimir por pantalla la secuencia estática
 * @return Devuelve la impresión de la secuencia
 */
template <class Key>
std::string staticSequence<Key>::print() const {
  std::string result = "";
  
  result += "[";
  for (int i = 0; i < sequence_.size(); i++) {
    if (i < (sequence_.size() - 1)) {
      if (sequence_[i] == Key(-1)) { result += "ø | "; }
      else { result += std::to_string(sequence_[i]) + " | "; }
    }
    else {
      if (sequence_[i] == Key(-1)) { result += "ø"; }
      else { result += std::to_string(sequence_[i]); }
    }
  }
  result += "]";
  
  return result;
}

/**
 * @brief Sobrecarga del operador () para calcular la función de exploración cuadrática
 * @param[in] position: posición que ocupa el elemento al que se desea acceder
 * @return Devuelve la clave (Key) que ocupa la posición especificada por parámetros
 */
template <class Key>
Key& staticSequence<Key>::operator[] (Position position) {
  assert(position >= 0 && position < size_);
  return sequence_[position];
}

/**
 * @brief Sobrecarga del operador de inserción del flujo de entrada (<<)
 * @param[in] os: referencia al flujo de salida estándar
 * @return Devuelve la impresión por pantalla de la secuencia estática
 */
template <class Key>
std::ostream& staticSequence<Key>::operator<<(std::ostream& os) const {
  os << print();
  return os;
}