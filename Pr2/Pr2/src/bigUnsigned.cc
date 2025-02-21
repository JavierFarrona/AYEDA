#include "../lib/bigUnsigned.h"

// Constructor por defecto
template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned() : digits(1, 0) {}

// Constructor con char
template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(const unsigned char* str) {
  digits.clear();
  while (*str) {
    unsigned char value;
    if (*str >= '0' && *str <= '9') {
      value = *str - '0';
    } else if (*str >= 'A' && *str <= 'F') {
      value = *str - 'A' + 10;
    } else if (*str >= 'a' && *str <= 'f') {
      value = *str - 'a' + 10;
    } else {
      throw std::invalid_argument("Invalid character in input.");
    }

    if (value >= Base) {
      throw std::invalid_argument("Digit out of range for the specified base.");
    }

    digits.push_back(value);
    ++str;
  }

  std::reverse(digits.begin(), digits.end());
}

// Constructor desde string
template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(const std::string& str) {
    digits.clear();
    for (char c : str) {
        unsigned char value;
        if (c >= '0' && c <= '9') {
        value = c - '0';
        } else if (c >= 'A' && c <= 'F') {
        value = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'f') {
        value = c - 'a' + 10;
        } else {
        throw std::invalid_argument("Invalid character in input.");
        }

        if (value >= Base) {
        throw std::invalid_argument("Digit out of range for the specified base.");
        }

        digits.push_back(value);
    }

    std::reverse(digits.begin(), digits.end());
}

// Constructor de copia
template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(const BigUnsigned<Base>& other) {
  if (this->getBase() != other.getBase()) {
    throw std::invalid_argument("Cannot copy numbers with different bases.");
  }
  digits = other.digits;
}


// Asignación
template <unsigned char Base>
BigUnsigned<Base>& BigUnsigned<Base>::operator=(const BigUnsigned<Base>& other) {
  if (!(this == &other)) {
    digits = other.digits;
  }
  return *this;
}
/*
// Flujos de entrada y salida
template<unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigUnsigned<Base>& num) {
    // Implementa la lógica para convertir `num` a una cadena y enviarla al flujo de salida
    // Por ejemplo:
    os << num.toString(); // Asumiendo que tienes un método `toString` en tu clase
    return os;
}

template <unsigned char Base>
std::istream& operator>>(std::istream& is, BigUnsigned<Base>& num) {
  std::string input;
  is >> input;

  num.digits.clear();
  for (char c : input) {
    unsigned char value;
    if (c >= '0' && c <= '9') {
      value = c - '0';
    } else if (c >= 'A' && c <= 'F') {
      value = c - 'A' + 10;
    } else if (c >= 'a' && c <= 'f') {
      value = c - 'a' + 10;
    } else {
      throw std::invalid_argument("Invalid character in input.");
    }

    if (value >= Base) {
      throw std::invalid_argument("Digit out of range for the specified base.");
    }

    num.digits.push_back(value);
  }

  std::reverse(num.digits.begin(), num.digits.end());
  return is;
}
*/
// Comparación
template <unsigned char Base>
bool BigUnsigned<Base>::operator==(const BigUnsigned<Base>& other) const {
  return ((digits == other.digits) && (this->getBase() == other.getBase()));
}

template <unsigned char Base>
bool BigUnsigned<Base>::operator<(const BigUnsigned<Base>& other) const {
  if (this->getBase() != other.getBase()) {
    throw std::invalid_argument("Cannot compare numbers with different bases.");
  }

  if (digits.size() != other.digits.size()) {
    return digits.size() < other.digits.size();
  }

  for (auto it1 = digits.rbegin(), it2 = other.digits.rbegin(); it1 != digits.rend(); ++it1, ++it2) {
    if (*it1 != *it2) {
      return *it1 < *it2;
    }
  }

  return false; // Son iguales
}

template <unsigned char Base>
bool BigUnsigned<Base>::operator<=(const BigUnsigned<Base>& other) const {
  return *this < other || *this == other;
}

template <unsigned char Base>
bool BigUnsigned<Base>::operator>(const BigUnsigned<Base>& other) const {
  return !(*this <= other);
}

template <unsigned char Base>
bool BigUnsigned<Base>::operator>=(const BigUnsigned<Base>& other) const {
  return !(*this < other);
}

// Incremento y decremento
template <unsigned char Base>
BigUnsigned<Base>& BigUnsigned<Base>::operator++() {
    unsigned char carry = 1;
    for (auto& digit : digits) {
      digit += carry;
      if (digit >= Base) {
        digit -= Base;
        carry = 1;
      } else {
        carry = 0;
        break;
      }
    }
    if (carry) {
      digits.push_back(1);
    }
    return *this;
}

template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator++(int) {
  BigUnsigned<Base> temp = *this;
  ++(*this);
  return temp;
}

template <unsigned char Base>
BigUnsigned<Base>& BigUnsigned<Base>::operator--() {
  if (digits.empty() || (digits.size() == 1 && digits[0] == 0)) {
    throw std::underflow_error("Cannot decrement zero.");
  }

  unsigned char borrow = 1;
  for (auto& digit : digits) {
    if (digit < borrow) {
      digit += Base - borrow;
      borrow = 1;
    } else {
      digit -= borrow;
      borrow = 0;
      break;
    }
  }

  removeLeadingZeros();
  return *this;
}

template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator--(int) {
  BigUnsigned<Base> temp = *this;
  --(*this);
  return temp;
}

// Operadores aritméticos
template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator+(const BigUnsigned<Base>& other) const {
  if (this->getBase() != other.getBase()) {
    throw std::invalid_argument("Cannot add numbers with different bases.");
  }

  BigUnsigned<Base> result;
  result.digits.clear();

  const size_t maxSize = std::max(digits.size(), other.digits.size());
  unsigned char carry = 0;

  for (size_t i = 0; i < maxSize || carry; ++i) {
    unsigned char digit1 = (i < digits.size()) ? digits[i] : 0;
    unsigned char digit2 = (i < other.digits.size()) ? other.digits[i] : 0;

    unsigned char sum = digit1 + digit2 + carry;
    carry = sum >= Base ? 1 : 0;
    if (carry) sum -= Base;

    result.digits.push_back(sum);
  }

  return result;
}

template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator-(const BigUnsigned<Base>& other) const {
  if (this->getBase() != other.getBase()) {
    throw std::invalid_argument("Cannot subtract numbers with different bases.");
  }

  if (*this < other) {
    throw std::underflow_error("Result of subtraction would be negative.");
  }

  BigUnsigned<Base> result;
  result.digits.clear();

  unsigned char borrow = 0;
  for (size_t i = 0; i < digits.size(); ++i) {
    unsigned char digit1 = digits[i];
    unsigned char digit2 = (i < other.digits.size()) ? other.digits[i] : 0;

    if (digit1 < digit2 + borrow) {
      result.digits.push_back(digit1 + Base - digit2 - borrow);
      borrow = 1;
    } else {
      result.digits.push_back(digit1 - digit2 - borrow);
      borrow = 0;
    }
  }

  result.removeLeadingZeros();
  return result;
}

template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator*(const BigUnsigned<Base>& other) const {
  if (this->getBase() != other.getBase()) {
    throw std::invalid_argument("Cannot multiply numbers with different bases.");
  }

  BigUnsigned<Base> result;
  result.digits.resize(digits.size() + other.digits.size(), 0);

  for (size_t i = 0; i < digits.size(); ++i) {
    unsigned char carry = 0;
    for (size_t j = 0; j < other.digits.size() || carry; ++j) {
      unsigned char digit2 = (j < other.digits.size()) ? other.digits[j] : 0;
      unsigned long long current = result.digits[i + j] + static_cast<unsigned long long>(digits[i]) * digit2 + carry;
      result.digits[i + j] = current % Base;
      carry = current / Base;
    }
  }

  result.removeLeadingZeros();
  return result;
}

template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator/(const BigUnsigned<Base>& other) const {
  if (this->getBase() != other.getBase()) {
    throw std::invalid_argument("Cannot divide numbers with different bases.");
  }

  if (other == BigUnsigned<Base>()) {
    throw std::invalid_argument("Cannot divide by zero.");
  }

  BigUnsigned<Base> dividend = *this;
  BigUnsigned<Base> divisor = other;
  BigUnsigned<Base> quotient;
  BigUnsigned<Base> remainder;

  for (int i = dividend.digits.size() - 1; i >= 0; --i) {
    remainder.digits.insert(remainder.digits.begin(), dividend.digits[i]);
    remainder.removeLeadingZeros();

    unsigned char count = 0;
    while (remainder >= divisor) {
      remainder = remainder - divisor;
      ++count;
    }

    quotient.digits.insert(quotient.digits.begin(), count);
  }

  quotient.removeLeadingZeros();
  return quotient;
}

template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator%(const BigUnsigned<Base>& other) const {
  if (this->getBase() != other.getBase()) {
    throw std::invalid_argument("Cannot modulo numbers with different bases.");
  }

  if (other == BigUnsigned<Base>()) {
    throw std::invalid_argument("Cannot modulo by zero.");
  }

  BigUnsigned<Base> dividend = *this;
  BigUnsigned<Base> divisor = other;
  BigUnsigned<Base> remainder;

  for (int i = dividend.digits.size() - 1; i >= 0; --i) {
    remainder.digits.insert(remainder.digits.begin(), dividend.digits[i]);
    remainder.removeLeadingZeros();

    while (remainder >= divisor) {
      remainder = remainder - divisor;
    }
  }

  remainder.removeLeadingZeros();
  return remainder;
}

// Métodos auxiliares
template <unsigned char Base>
std::string BigUnsigned<Base>::toString() const {
  static const char* out_digits = "0123456789ABCDEF";
  std::string result;
  for (auto it = this->digits.rbegin(); it != this->digits.rend(); ++it) {
    result += out_digits[*it];
  }
  return result.empty() ? "0" : result;
}

template <unsigned char Base>
void BigUnsigned<Base>::removeLeadingZeros() {
  while (digits.size() > 1 && digits.back() == 0) {
    digits.pop_back();
  }
}

//-------------------------------------------------------------------------------------------

// Especialización de la plantilla para base binaria
// Constructor desde entero
BigUnsigned<2>::BigUnsigned(unsigned n) {
  bits.clear();
  while (n > 0) {
    bits.push_back(n % 2);
    n /= 2;
  }
  if (bits.empty()) {
    bits.push_back(0);
  }
}

// Constructor desde string
BigUnsigned<2>::BigUnsigned(const std::string& str) {
    for (char c : str) {
        if (c == '0') {
            bits.push_back(false);
        } else if (c == '1') {
            bits.push_back(true);
        } else {
            throw std::invalid_argument("Invalid binary digit");
        }
    }
    std::reverse(bits.begin(), bits.end()); // Almacenar los bits en orden inverso
}

// Asignación
BigUnsigned<2>& BigUnsigned<2>::operator=(const BigUnsigned<2>& other) {
  if (this != &other) {
    bits = other.bits;
  }
  return *this;
}

// Flujos de entrada y salida
std::istream& operator>>(std::istream& is, BigUnsigned<2>& num) {
  std::string str;
  is >> str;
  num = BigUnsigned<2>(str);
  return is;
}

std::ostream& operator<<(std::ostream& os, const BigUnsigned<2>& num) {
  for (auto it = num.bits.rbegin(); it != num.bits.rend(); ++it) {
    os << *it;
  }
  return os;
}

// Comparación
bool BigUnsigned<2>::operator==(const BigUnsigned<2>& other) const {
  return bits == other.bits;
}

bool BigUnsigned<2>::operator<(const BigUnsigned<2>& other) const {
  if (bits.size() != other.bits.size()) {
    return bits.size() < other.bits.size();
  }
  for (auto it1 = bits.rbegin(), it2 = other.bits.rbegin(); it1 != bits.rend(); ++it1, ++it2) {
    if (*it1 != *it2) {
      return *it1 < *it2;
    }
  }
  return false;
}

bool BigUnsigned<2>::operator<=(const BigUnsigned<2>& other) const {
  return *this < other || *this == other;
}

bool BigUnsigned<2>::operator>(const BigUnsigned<2>& other) const {
  return !(*this <= other);
}

bool BigUnsigned<2>::operator>=(const BigUnsigned<2>& other) const {
  return !(*this < other);
}

// Incremento y decremento
BigUnsigned<2>& BigUnsigned<2>::operator++() {
  bool carry = true;
  for (auto aux : bits) {
    aux = aux ^ carry;
    carry = aux == 0 && carry;
    if (!carry) break;
  }
  if (carry) bits.push_back(true);
  return *this;
}

BigUnsigned<2> BigUnsigned<2>::operator++(int) {
  BigUnsigned<2> temp = *this;
  ++(*this);
  return temp;
}

BigUnsigned<2>& BigUnsigned<2>::operator--() {
  if (bits.empty() || (bits.size() == 1 && bits[0] == 0)) {
    throw std::underflow_error("Cannot decrement zero.");
  }
  bool borrow = true;
  for (auto bit : bits) {
    bit = bit ^ borrow;
    borrow = bit == 1 && borrow;
    if (!borrow) break;
  }
  removeLeadingZeros();
  return *this;
}

BigUnsigned<2> BigUnsigned<2>::operator--(int) {
  BigUnsigned<2> temp = *this;
  --(*this);
  return temp;
}

// Operadores aritméticos
BigUnsigned<2> BigUnsigned<2>::operator+(const BigUnsigned<2>& other) const {
  BigUnsigned<2> result;
  result.bits.clear();
  bool carry = false;
  size_t maxSize = std::max(bits.size(), other.bits.size());
  for (size_t i = 0; i < maxSize || carry; ++i) {
    bool bit1 = (i < bits.size()) ? bits[i] : false;
    bool bit2 = (i < other.bits.size()) ? other.bits[i] : false;
    bool sum = bit1 ^ bit2 ^ carry;
    carry = (bit1 && bit2) || (bit1 && carry) || (bit2 && carry);
    result.bits.push_back(sum);
  }
  return result;
}

BigUnsigned<2> BigUnsigned<2>::operator-(const BigUnsigned<2>& other) const {
  BigUnsigned<2> result;
  result.bits.clear();

  bool borrow = false;
  for (size_t i = 0; i < bits.size(); ++i) {
    bool bit1 = bits[i];
    bool bit2 = (i < other.bits.size()) ? other.bits[i] : false;

    bool diff = bit1 ^ bit2 ^ borrow;
    borrow = (!bit1 && bit2) || (borrow && !bit1) || (borrow && bit2);

    result.bits.push_back(diff);
  }

  result.removeLeadingZeros();
  return result;
}

BigUnsigned<2> BigUnsigned<2>::operator*(const BigUnsigned<2>& other) const {
    BigUnsigned<2> result(0);  // Inicializamos el resultado en 0
    BigUnsigned<2> temp = *this;  // Copia del operando para desplazamientos

    for (size_t i = 0; i < other.bits.size(); ++i) {
        if (other.bits[i]) {
            BigUnsigned<2> shifted = temp;  // Copia del multiplicando
            shifted.bits.insert(shifted.bits.begin(), i, false);  // Desplazamiento en binario
            result = result + shifted;  // Sumamos al resultado
        }
    }

    result.removeLeadingZeros();  // Eliminamos ceros a la izquierda
    return result;
}



// Implementación optimizada de la división y el módulo para base 2
BigUnsigned<2> BigUnsigned<2>::operator/(const BigUnsigned<2>& other) const {
  if (other == BigUnsigned<2>("0")) {
    throw std::invalid_argument("Division by zero");
  }

  BigUnsigned<2> result;
  result.bits.resize(bits.size(), 0);

  BigUnsigned<2> remainder;
  for (int i = bits.size() - 1; i >= 0; --i) {
    remainder.bits.insert(remainder.bits.begin(), bits[i]);
    remainder.removeLeadingZeros();
    if (remainder >= other) {
      remainder = remainder - other;
      result.bits[i] = 1;
    }
  }

  result.removeLeadingZeros();
  return result;
}

BigUnsigned<2> BigUnsigned<2>::operator%(const BigUnsigned<2>& other) const {
  if (other == BigUnsigned<2>("0")) {
    throw std::invalid_argument("Division by zero");
  }

  BigUnsigned<2> remainder(*this);

  while (remainder >= other) {
    remainder = remainder - other;
  }

  return remainder;
}

// Método toString
std::string BigUnsigned<2>::toString() const {
    std::string result;
    for (auto it = bits.rbegin(); it != bits.rend(); ++it) {
        result += (*it ? '1' : '0');
    }
    return result.empty() ? "0" : result;
}

void BigUnsigned<2>::removeLeadingZeros() {
  while (bits.size() > 1 && bits.back() == false) {
    bits.pop_back();
  }
}

BigUnsigned<2> BigUnsigned<2>::complement_2() const {
  BigUnsigned<2> result = *this;
  for (auto aux : result.bits) {
    aux = !aux;
  }
  return ++result;
}

std::vector<bool>& BigUnsigned<2>::getBits() {
  return bits;
}

template class BigUnsigned<8>;
template class BigUnsigned<10>;
template class BigUnsigned<16>;