/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Algoritmos y Estructuras de datos Avanzadas
 * Curso: 2º
 * C:\Users\javie\Documents\GitHub\AYEDA\Pr1\Pr1\lib
 * Autor: Javier Farrona Cabrera
 * Correo: alu0101541983@ull.edu.es
 * Fecha 06 Feb 2025
 * Archivo: bigUnsigned.cc
 * Referencias:
 *     Enunciado de la práctica
 */

#include "../lib/BigUnsigned.h"

// Constructor por defecto: inicializa un BigUnsigned vacío (representa 0)
BigUnsigned::BigUnsigned() : número_(1, 0) {}

// Constructor con unsigned char* (cadena de caracteres)
BigUnsigned::BigUnsigned(const unsigned char* str) {
  // Convertimos el input de cadena a vector de dígitos
  while (*str) {
    if (*str < '0' || *str > '9') {
      throw std::invalid_argument(
          "Invalid character in string input. Must contain only digits.");
    }
    número_.insert(número_.begin(), *str - '0');
    ++str;
  }
}

// Constructor de copia
BigUnsigned::BigUnsigned(const BigUnsigned& other) : número_(other.número_) {}

// Operador de asignación
BigUnsigned& BigUnsigned::operator=(const BigUnsigned& other) {
  if (this != &other) {  // Evita auto-asignaciones
    número_ = other.número_;
  }
  return *this;
}

// Sobrecarga de operador de inserción (<<) para salida
std::ostream& operator<<(std::ostream& os, const BigUnsigned& number) {
  for (auto it = number.número_.rbegin(); it != number.número_.rend(); ++it) {
    os << static_cast<char>(*it + '0');
  }
  return os;
}

// Sobrecarga de operador de extracción (>>) para entrada
std::istream& operator>>(std::istream& is, BigUnsigned& number) {
  std::string input;
  is >> input;

  // Verificación básica: asegurarse de que solo contenga números
  for (char c : input) {
    if (c < '0' || c > '9') {
      throw std::invalid_argument("Invalid input. Must contain only digits.");
    }
  }

  // Convertir la cadena a número almacenado en vector
  number.número_.clear();  // Limpiamos cualquier valor previo
  for (auto it = input.rbegin(); it != input.rend(); ++it) {
    number.número_.push_back(static_cast<unsigned char>(*it - '0'));
  }

  return is;
}

// Operador de comparación ==
bool BigUnsigned::operator==(const BigUnsigned& other) const {
  return número_ == other.número_;
}

// Operador de comparación <
bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs) {
  if (lhs.número_.size() != rhs.número_.size()) {
    return lhs.número_.size() < rhs.número_.size();
  }

  // Comparar dígito por dígito empezando por los más significativos
  for (auto lhs_it = lhs.número_.rbegin(), rhs_it = rhs.número_.rbegin();
       lhs_it != lhs.número_.rend(); ++lhs_it, ++rhs_it) {
    if (*lhs_it != *rhs_it) {
      return *lhs_it < *rhs_it;
    }
  }
  return false;  // Son iguales
}

bool operator<=(const BigUnsigned& a, const BigUnsigned& b) {
  return (a < b) || (a == b);
}

bool operator>(const BigUnsigned& a, const BigUnsigned& b) { return !(a <= b); }

bool operator>=(const BigUnsigned& a, const BigUnsigned& b) { return !(a < b); }

// Operador pre-incremento ++
BigUnsigned& BigUnsigned::operator++() {
  unsigned char carry = 1;
  for (auto& digit : número_) {
    unsigned char sum = digit + carry;
    carry = sum / 10;
    digit = sum % 10;
    if (carry == 0) break;
  }
  if (carry > 0) {
    número_.push_back(carry);
  }
  return *this;
}

// Operador post-incremento ++
BigUnsigned BigUnsigned::operator++(int) {
  BigUnsigned temp(*this);  // Guardar el estado anterior
  ++(*this);                // Llama al pre-incremento
  return temp;
}

// Operador pre-decremento --
BigUnsigned& BigUnsigned::operator--() {
  if (número_.size() == 1 && número_[0] == 0) {
    throw std::underflow_error(
        "BigUnsigned underflow: cannot decrement below 0.");
  }
  unsigned char borrow = 1;
  for (auto& digit : número_) {
    if (digit >= borrow) {
      digit -= borrow;
      borrow = 0;
      break;
    } else {
      digit = 9;
    }
  }
  // Elimina ceros iniciales si existen
  while (número_.size() > 1 && número_.back() == 0) {
    número_.pop_back();
  }
  return *this;
}

// Operador post-decremento --
BigUnsigned BigUnsigned::operator--(int) {
  BigUnsigned temp(*this);  // Guardar el estado anterior
  --(*this);                // Llama al pre-decremento
  return temp;
}

// Operador suma (+)
BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs) {
  BigUnsigned result;
  result.número_.clear();

  const auto& larger =
      (lhs.número_.size() > rhs.número_.size()) ? lhs.número_ : rhs.número_;
  const auto& smaller =
      (lhs.número_.size() > rhs.número_.size()) ? rhs.número_ : lhs.número_;

  unsigned char carry = 0;

  for (size_t i = 0; i < larger.size(); ++i) {
    unsigned char digit1 = (i < smaller.size()) ? smaller[i] : 0;
    unsigned char sum = larger[i] + digit1 + carry;
    carry = sum / 10;
    result.número_.push_back(sum % 10);
  }

  if (carry > 0) {
    result.número_.push_back(carry);
  }
  return result;
}

// Operador resta (-)
BigUnsigned BigUnsigned::operator-(const BigUnsigned& other) const {
  if (*this < other) {
    throw std::invalid_argument("Cannot subtract: result would be negative.");
  }

  BigUnsigned result(
      *this);  // Creamos un nuevo objeto "result" basado en "this"
  unsigned char borrow = 0;

  for (size_t i = 0; i < result.número_.size(); ++i) {
    unsigned char subtrahend =
        (i < other.número_.size()) ? other.número_[i] : 0;

    if (result.número_[i] < subtrahend + borrow) {
      result.número_[i] +=
          10 - (subtrahend + borrow);  // Ajustamos el dígito actual
      borrow = 1;
    } else {
      result.número_[i] -=
          (subtrahend + borrow);  // Realizamos la resta normalmente
      borrow = 0;
    }
  }

  // Remover ceros iniciales si es necesario
  while (result.número_.size() > 1 && result.número_.back() == 0) {
    result.número_.pop_back();
  }

  return result;  // Devolvemos el resultado por valor
}

/*
// Getter para obtener como unsigned long int
long unsigned int BigUnsigned::getLong() const {
  long unsigned int result = 0;
  long unsigned int base = 1;
  for (unsigned char digit : número_) {
    result += digit * base;
    base *= 10;
  }
  return result;
}
*/

BigUnsigned BigUnsigned::operator*(const BigUnsigned& other) const {
  // Crear un vector suficientemente grande para el resultado
  std::vector<unsigned char> resultDigits(número_.size() + other.número_.size(),
                                          0);

  // Multiplicación dígito a dígito
  for (size_t i = 0; i < número_.size(); ++i) {
    unsigned char carry = 0;
    for (size_t j = 0; j < other.número_.size(); ++j) {
      unsigned long long mult =
          static_cast<unsigned long long>(número_[i]) * other.número_[j] +
          resultDigits[i + j] + carry;
      resultDigits[i + j] = static_cast<unsigned char>(mult % 10);
      carry = static_cast<unsigned char>(mult / 10);
    }
    // Agregar el acarreo remanente si existe
    if (carry > 0) {
      resultDigits[i + other.número_.size()] += carry;
    }
  }

  // Eliminar ceros iniciales
  while (resultDigits.size() > 1 && resultDigits.back() == 0) {
    resultDigits.pop_back();
  }

  BigUnsigned result;
  result.número_ = resultDigits;  // Asignar el resultado calculado
  return result;
}

BigUnsigned operator/(const BigUnsigned& dividend, const BigUnsigned& divisor) {
  if (divisor == BigUnsigned((const unsigned char*)"0")) {
    throw std::invalid_argument("Cannot divide by zero.");
  }

  BigUnsigned result;   // El cociente
  BigUnsigned current;  // Resto temporal durante los cálculos

  result.número_ = std::vector<unsigned char>(dividend.número_.size(), 0);

  for (size_t i = dividend.número_.size(); i-- > 0;) {
    // Mover el siguiente dígito del dividendo al resto actual
    current.número_.insert(current.número_.begin(), dividend.número_[i]);

    // Eliminar ceros iniciales en el resto
    while (current.número_.size() > 1 && current.número_.back() == 0) {
      current.número_.pop_back();
    }

    // Encuentra el dígito del cociente para esta posición
    unsigned char x = 0;
    while (divisor <= current) {
      current = current - divisor;  // Restamos al resto actual
      ++x;                          // Incrementamos el dígito del cociente
    }

    result.número_[i] =
        x;  // Asignamos el dígito del cociente en la posición adecuada
  }

  // Eliminar ceros iniciales del cociente
  while (result.número_.size() > 1 && result.número_.back() == 0) {
    result.número_.pop_back();
  }

  return result;
}

BigUnsigned BigUnsigned::operator%(const BigUnsigned& divisor) const {
  if (divisor == BigUnsigned((const unsigned char*)"0")) {
    throw std::invalid_argument("Cannot divide by zero.");
  }

  BigUnsigned current;

  for (size_t i = número_.size(); i-- > 0;) {
    // Mover el siguiente dígito al resto actual
    current.número_.insert(current.número_.begin(), número_[i]);

    // Eliminar ceros iniciales en el resto
    while (current.número_.size() > 1 && current.número_.back() == 0) {
      current.número_.pop_back();
    }

    // Resta el divisor hasta que no quepa más veces
    while (divisor <= current) {
      current = current - divisor;
    }
  }

  return current;  // Lo que queda es el residuo
}

void BigUnsigned::removeLeadingZeros() {
  while (número_.size() > 1 && número_.back() == 0) {
    número_.pop_back();
  }
}

std::string BigUnsigned::toString() const {
  if (número_.empty()) return "0";
  std::string result;
  for (auto it = número_.rbegin(); it != número_.rend(); ++it) {
    result += static_cast<char>(*it + '0');
  }
  return result;
}
