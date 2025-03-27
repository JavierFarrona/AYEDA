#pragma once

#ifndef BIGUNSIGNED_H
#define BIGUNSIGNED_H

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

template <unsigned char Base>
class BigUnsigned {
  public:
    // Constructores
    BigUnsigned();                            // Por defecto
    BigUnsigned(const unsigned char*);        // Con char
    BigUnsigned(const std::string& str);
    BigUnsigned(const BigUnsigned<Base>& other);

    // Asignación
    BigUnsigned<Base>& operator=(const BigUnsigned<Base>& other);

    // Flujos de entrada y salida
    template <unsigned B>
    friend std::ostream& operator<<(std::ostream& os, const BigUnsigned<B>& num);
    template <unsigned B>
    friend std::istream& operator>>(std::istream& is, BigUnsigned<B>& num);

    // Comparación
    bool operator==(const BigUnsigned<Base>& other) const;
    bool operator<(const BigUnsigned<Base>& other) const;
    bool operator<=(const BigUnsigned<Base>& other) const;
    bool operator>(const BigUnsigned<Base>& other) const;
    bool operator>=(const BigUnsigned<Base>& other) const;

    // Incremento y decremento
    BigUnsigned<Base>& operator++();    // Preincremento
    BigUnsigned<Base> operator++(int);  // Postincremento
    BigUnsigned<Base>& operator--();    // Predecremento
    BigUnsigned<Base> operator--(int);  // Postdecremento

    // Operadores aritméticos
    BigUnsigned<Base> operator+(const BigUnsigned<Base>& other) const;
    BigUnsigned<Base> operator-(const BigUnsigned<Base>& other) const;
    BigUnsigned<Base> operator*(const BigUnsigned<Base>& other) const;
    BigUnsigned<Base> operator/(const BigUnsigned<Base>& other) const;
    BigUnsigned<Base> operator%(const BigUnsigned<Base>& other) const;

    // Métodos auxiliares
    std::string toString() const;  // Convierte el número en string
    void removeLeadingZeros();     // Elimina ceros a la izquierda
    unsigned char getBase() const { return Base; }

  private:
    std::vector<unsigned char> digits;
};

// Especialización de la plantilla para base binaria
template<>
class BigUnsigned<2> {
  public:
    // Constructores
    BigUnsigned(unsigned n = 0);
    BigUnsigned(const std::string& str);

    // Asignación
    BigUnsigned<2>& operator=(const BigUnsigned<2>& other);

    // Flujos de entrada y salida
    friend std::istream& operator>>(std::istream& is, BigUnsigned<2>& num);
    friend std::ostream& operator<<(std::ostream& os, const BigUnsigned<2>& num);

    // Comparación
    bool operator==(const BigUnsigned<2>& other) const;
    bool operator<(const BigUnsigned<2>& other) const;
    bool operator<=(const BigUnsigned<2>& other) const;
    bool operator>(const BigUnsigned<2>& other) const;
    bool operator>=(const BigUnsigned<2>& other) const;

    // Incremento y decremento
    BigUnsigned<2>& operator++();    // Preincremento
    BigUnsigned<2> operator++(int);  // Postincremento
    BigUnsigned<2>& operator--();    // Predecremento
    BigUnsigned<2> operator--(int);  // Postdecremento

    // Operadores aritméticos
    BigUnsigned<2> operator+(const BigUnsigned<2>& other) const;
    BigUnsigned<2> operator-(const BigUnsigned<2>& other) const;
    BigUnsigned<2> operator*(const BigUnsigned<2>& other) const;
    BigUnsigned<2> operator/(const BigUnsigned<2>& other) const;
    BigUnsigned<2> operator%(const BigUnsigned<2>& other) const;

    // Métodos auxiliares
    std::string toString() const;  // Convierte el número en string
    void removeLeadingZeros();     // Elimina ceros a la izquierda
    BigUnsigned<2> complement_2() const; // Calcula el complemento a 2 de un número
    std::vector<bool>& getBits();  // Devuelve una referencia a los bits

  private:
    std::vector<bool> bits;
};

// Definición de los operadores de flujo
template <unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigUnsigned<Base>& num) {
    os << num.toString();
    return os;
}

template <unsigned char Base>
std::istream& operator>>(std::istream& is, BigUnsigned<Base>& num) {
    std::string input;
    is >> input;
    num = BigUnsigned<Base>(input);
    return is;
}

#endif