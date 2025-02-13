/**
 * @file bigUnsigned.cc
 * @brief Implementation of the BigUnsigned class for handling large unsigned
 * integers.
 *
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Algoritmos y Estructuras de datos Avanzadas
 * Curso: 2º
 * C:\Users\javie\Documents\GitHub\AYEDA\Pr1\Pr1\lib
 * Autor: Javier Farrona Cabrera
 * Correo: alu0101541983@ull.edu.es
 * Fecha 06 Feb 2025
 * Referencias:
 *     Enunciado de la práctica
 */

#include "../lib/bigUnsigned.h"

/**
 * @brief Construct a new BigUnsigned object with a default value of 0.
 */
BigUnsigned::BigUnsigned() : number_(1, 0) {}

/**
 * @brief Construct a new BigUnsigned object from a string of digits.
 *
 * @param str A C-style string containing only digit characters.
 * @throws std::invalid_argument if the string contains non-digit characters.
 */
BigUnsigned::BigUnsigned(const unsigned char* str) {
  // Convert the input string to a vector of digits
  while (*str) {
    if (*str < '0' || *str > '9') {
      throw std::invalid_argument(
          "Invalid character in string input. Must contain only digits.");
    }
    number_.insert(number_.begin(), *str - '0');
    ++str;
  }
}

/**
 * @brief Copy constructor for BigUnsigned.
 *
 * @param other The BigUnsigned object to copy from.
 */
BigUnsigned::BigUnsigned(const BigUnsigned& other) : number_(other.number_) {}

/**
 * @brief Assignment operator for BigUnsigned.
 *
 * @param other The BigUnsigned object to assign from.
 * @return BigUnsigned& A reference to the assigned object.
 */
BigUnsigned& BigUnsigned::operator=(const BigUnsigned& other) {
  if (this != &other) {  // Avoid self-assignment
    number_ = other.number_;
  }
  return *this;
}

/**
 * @brief Overload of the insertion operator for outputting BigUnsigned objects.
 *
 * @param os The output stream.
 * @param number The BigUnsigned object to output.
 * @return std::ostream& The output stream.
 */
std::ostream& operator<<(std::ostream& os, const BigUnsigned& number) {
  for (auto it = number.number_.rbegin(); it != number.number_.rend(); ++it) {
    os << static_cast<char>(*it + '0');
  }
  return os;
}

/**
 * @brief Overload of the extraction operator for inputting BigUnsigned objects.
 *
 * @param is The input stream.
 * @param number The BigUnsigned object to input into.
 * @return std::istream& The input stream.
 * @throws std::invalid_argument if the input contains non-digit characters.
 */
std::istream& operator>>(std::istream& is, BigUnsigned& number) {
  std::string input;
  is >> input;

  // Basic verification: ensure it only contains digits
  for (char c : input) {
    if (c < '0' || c > '9') {
      throw std::invalid_argument("Invalid input. Must contain only digits.");
    }
  }

  // Convert the string to a number stored in a vector
  number.number_.clear();  // Clear any previous value
  for (auto it = input.rbegin(); it != input.rend(); ++it) {
    number.number_.push_back(static_cast<unsigned char>(*it - '0'));
  }

  return is;
}

/**
 * @brief Equality comparison operator for BigUnsigned.
 *
 * @param other The BigUnsigned object to compare with.
 * @return true if the objects are equal.
 * @return false if the objects are not equal.
 */
bool BigUnsigned::operator==(const BigUnsigned& other) const {
  return number_ == other.number_;
}

/**
 * @brief Less-than comparison operator for BigUnsigned.
 *
 * @param lhs The left-hand side BigUnsigned object.
 * @param rhs The right-hand side BigUnsigned object.
 * @return true if lhs is less than rhs.
 * @return false otherwise.
 */
bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs) {
  if (lhs.number_.size() != rhs.number_.size()) {
    return lhs.number_.size() < rhs.number_.size();
  }

  // Compare digit by digit starting from the most significant
  for (auto lhs_it = lhs.number_.rbegin(), rhs_it = rhs.number_.rbegin();
       lhs_it != lhs.number_.rend(); ++lhs_it, ++rhs_it) {
    if (*lhs_it != *rhs_it) {
      return *lhs_it < *rhs_it;
    }
  }
  return false;  // They are equal
}

/**
 * @brief Less-than or equal-to comparison operator for BigUnsigned.
 *
 * @param a The left-hand side BigUnsigned object.
 * @param b The right-hand side BigUnsigned object.
 * @return true if a is less than or equal to b.
 * @return false otherwise.
 */
bool operator<=(const BigUnsigned& a, const BigUnsigned& b) {
  return (a < b) || (a == b);
}

/**
 * @brief Greater-than comparison operator for BigUnsigned.
 *
 * @param a The left-hand side BigUnsigned object.
 * @param b The right-hand side BigUnsigned object.
 * @return true if a is greater than b.
 * @return false otherwise.
 */
bool operator>(const BigUnsigned& a, const BigUnsigned& b) { return !(a <= b); }

/**
 * @brief Greater-than or equal-to comparison operator for BigUnsigned.
 *
 * @param a The left-hand side BigUnsigned object.
 * @param b The right-hand side BigUnsigned object.
 * @return true if a is greater than or equal to b.
 * @return false otherwise.
 */
bool operator>=(const BigUnsigned& a, const BigUnsigned& b) { return !(a < b); }

/**
 * @brief Pre-increment operator for BigUnsigned.
 *
 * @return BigUnsigned& A reference to the incremented object.
 */
BigUnsigned& BigUnsigned::operator++() {
  unsigned char carry = 1;
  for (auto& digit : number_) {
    unsigned char sum = digit + carry;
    carry = sum / 10;
    digit = sum % 10;
    if (carry == 0) break;
  }
  if (carry > 0) {
    number_.push_back(carry);
  }
  return *this;
}

/**
 * @brief Post-increment operator for BigUnsigned.
 *
 * @return BigUnsigned The value before incrementing.
 */
BigUnsigned BigUnsigned::operator++(int) {
  BigUnsigned temp(*this);  // Save the previous state
  ++(*this);                // Call the pre-increment
  return temp;
}

/**
 * @brief Pre-decrement operator for BigUnsigned.
 *
 * @return BigUnsigned& A reference to the decremented object.
 * @throws std::underflow_error if the value is decremented below 0.
 */
BigUnsigned& BigUnsigned::operator--() {
  if (number_.size() == 1 && number_[0] == 0) {
    throw std::underflow_error(
        "BigUnsigned underflow: cannot decrement below 0.");
  }
  unsigned char borrow = 1;
  for (auto& digit : number_) {
    if (digit >= borrow) {
      digit -= borrow;
      borrow = 0;
      break;
    } else {
      digit = 9;
    }
  }
  // Remove leading zeros if they exist
  while (number_.size() > 1 && number_.back() == 0) {
    number_.pop_back();
  }
  return *this;
}

/**
 * @brief Post-decrement operator for BigUnsigned.
 *
 * @return BigUnsigned The value before decrementing.
 */
BigUnsigned BigUnsigned::operator--(int) {
  BigUnsigned temp(*this);  // Save the previous state
  --(*this);                // Call the pre-decrement
  return temp;
}

/**
 * @brief Addition operator for BigUnsigned.
 *
 * @param lhs The left-hand side BigUnsigned object.
 * @param rhs The right-hand side BigUnsigned object.
 * @return BigUnsigned The result of the addition.
 */
BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs) {
  BigUnsigned result;
  result.number_.clear();

  const auto& larger =
      (lhs.number_.size() > rhs.number_.size()) ? lhs.number_ : rhs.number_;
  const auto& smaller =
      (lhs.number_.size() > rhs.number_.size()) ? rhs.number_ : lhs.number_;

  unsigned char carry = 0;

  for (size_t i = 0; i < larger.size(); ++i) {
    unsigned char digit1 = (i < smaller.size()) ? smaller[i] : 0;
    unsigned char sum = larger[i] + digit1 + carry;
    carry = sum / 10;
    result.number_.push_back(sum % 10);
  }

  if (carry > 0) {
    result.number_.push_back(carry);
  }
  return result;
}

/**
 * @brief Subtraction operator for BigUnsigned.
 *
 * @param other The BigUnsigned object to subtract.
 * @return BigUnsigned The result of the subtraction.
 * @throws std::invalid_argument if the result would be negative.
 */
BigUnsigned BigUnsigned::operator-(const BigUnsigned& other) const {
  if (*this < other) {
    throw std::invalid_argument("Cannot subtract: result would be negative.");
  }

  BigUnsigned result(*this);  // Create a new object "result" based on "this"
  unsigned char borrow = 0;

  for (size_t i = 0; i < result.number_.size(); ++i) {
    unsigned char subtrahend =
        (i < other.number_.size()) ? other.number_[i] : 0;

    if (result.number_[i] < subtrahend + borrow) {
      result.number_[i] +=
          10 - (subtrahend + borrow);  // Adjust the current digit
      borrow = 1;
    } else {
      result.number_[i] -=
          (subtrahend + borrow);  // Perform the subtraction normally
      borrow = 0;
    }
  }

  // Remove leading zeros if necessary
  while (result.number_.size() > 1 && result.number_.back() == 0) {
    result.number_.pop_back();
  }

  return result;  // Return the result by value
}

/**
 * @brief Multiplication operator for BigUnsigned.
 *
 * @param other The BigUnsigned object to multiply with.
 * @return BigUnsigned The result of the multiplication.
 */
BigUnsigned BigUnsigned::operator*(const BigUnsigned& other) const {
  // Create a vector large enough for the result
  std::vector<unsigned char> resultDigits(number_.size() + other.number_.size(),
                                          0);

  // Digit-by-digit multiplication
  for (size_t i = 0; i < number_.size(); ++i) {
    unsigned char carry = 0;
    for (size_t j = 0; j < other.number_.size(); ++j) {
      unsigned long long mult =
          static_cast<unsigned long long>(number_[i]) * other.number_[j] +
          resultDigits[i + j] + carry;
      resultDigits[i + j] = static_cast<unsigned char>(mult % 10);
      carry = static_cast<unsigned char>(mult / 10);
    }
    // Add any remaining carry
    if (carry > 0) {
      resultDigits[i + other.number_.size()] += carry;
    }
  }

  // Remove leading zeros
  while (resultDigits.size() > 1 && resultDigits.back() == 0) {
    resultDigits.pop_back();
  }

  BigUnsigned result;
  result.number_ = resultDigits;  // Assign the calculated result
  return result;
}

/**
 * @brief Division operator for BigUnsigned.
 *
 * @param dividend The BigUnsigned object to divide.
 * @param divisor The BigUnsigned object to divide by.
 * @return BigUnsigned The result of the division.
 * @throws std::invalid_argument if the divisor is zero.
 */
BigUnsigned operator/(const BigUnsigned& dividend, const BigUnsigned& divisor) {
  if (divisor == BigUnsigned((const unsigned char*)"0")) {
    throw std::invalid_argument("Cannot divide by zero.");
  }

  BigUnsigned result;   // The quotient
  BigUnsigned current;  // Temporary remainder during calculations

  result.number_ = std::vector<unsigned char>(dividend.number_.size(), 0);

  for (size_t i = dividend.number_.size(); i-- > 0;) {
    // Move the next digit of the dividend to the current remainder
    current.number_.insert(current.number_.begin(), dividend.number_[i]);

    // Remove leading zeros in the remainder
    while (current.number_.size() > 1 && current.number_.back() == 0) {
      current.number_.pop_back();
    }

    // Find the quotient digit for this position
    unsigned char x = 0;
    while (divisor <= current) {
      current = current - divisor;  // Subtract from the current remainder
      ++x;                          // Increment the quotient digit
    }

    result.number_[i] =
        x;  // Assign the quotient digit in the appropriate position
  }

  // Remove leading zeros from the quotient
  while (result.number_.size() > 1 && result.number_.back() == 0) {
    result.number_.pop_back();
  }

  return result;
}

/**
 * @brief Modulus operator for BigUnsigned.
 *
 * @param divisor The BigUnsigned object to divide by.
 * @return BigUnsigned The remainder of the division.
 * @throws std::invalid_argument if the divisor is zero.
 */
BigUnsigned BigUnsigned::operator%(const BigUnsigned& divisor) const {
  if (divisor == BigUnsigned((const unsigned char*)"0")) {
    throw std::invalid_argument("Cannot divide by zero.");
  }

  BigUnsigned current;

  for (size_t i = number_.size(); i-- > 0;) {
    // Move the next digit to the current remainder
    current.number_.insert(current.number_.begin(), number_[i]);

    // Remove leading zeros in the remainder
    while (current.number_.size() > 1 && current.number_.back() == 0) {
      current.number_.pop_back();
    }

    // Subtract the divisor until it no longer fits
    while (divisor <= current) {
      current = current - divisor;
    }
  }

  return current;  // The remainder
}

/**
 * @brief Remove leading zeros from the number.
 */
void BigUnsigned::removeLeadingZeros() {
  while (number_.size() > 1 && number_.back() == 0) {
    number_.pop_back();
  }
}

/**
 * @brief Convert the BigUnsigned number to a string representation.
 *
 * @return std::string The string representation of the number.
 */
std::string BigUnsigned::toString() const {
  if (number_.empty()) return "0";
  std::string result;
  for (auto it = number_.rbegin(); it != number_.rend(); ++it) {
    result += static_cast<char>(*it + '0');
  }
  return result;
}