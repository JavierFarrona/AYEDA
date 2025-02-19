// Integer.h
#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#include "./bigUnsigned.h"

template <unsigned char Base>
class BigInteger {
  public:
    // Constructores
    BigInteger();
    BigInteger(const BigUnsigned<Base>& mag);
    BigInteger(const BigInteger<Base>& other);
    BigInteger(const std::string& str);
    BigInteger(int value);


    // Operadores aritméticos
    BigInteger<Base> operator+(const BigInteger<Base>& other) const;
    BigInteger<Base> operator-(const BigInteger<Base>& other) const;
    BigInteger<Base> operator*(const BigInteger<Base>& other) const;
    BigInteger<Base> operator/(const BigInteger<Base>& other) const;
    BigInteger<Base> operator%(const BigInteger<Base>& other) const;
    BigInteger<Base> operator-() const;

    // Flujos de entrada y salida
    friend std::ostream& operator<<(std::ostream& os, const BigInteger<Base>& num);
    friend std::istream& operator>>(std::istream& is, BigInteger<Base>& num);

    // Comparación
    bool operator==(const BigInteger<Base>& other) const;
    bool operator<(const BigInteger<Base>& other) const;
    bool operator<=(const BigInteger<Base>& other) const;
    bool operator>(const BigInteger<Base>& other) const;
    bool operator>=(const BigInteger<Base>& other) const;

    // Incremento y decremento
    BigInteger<Base>& operator++();    // Preincremento
    BigInteger<Base> operator++(int);  // Postincremento
    BigInteger<Base>& operator--();    // Predecremento
    BigInteger<Base> operator--(int);  // Postdecremento

    // Asignación
    BigInteger<Base>& operator=(const BigInteger<Base>& other);

    // Métodos auxiliares
    std::string toString() const;  // Convierte el número en string
    void removeLeadingZeros();     // Elimina ceros a la izquierda
    unsigned char getBase() const { return magnitude_.getBase(); }
    bool isNegative() const { return negative_; }

  private:
    BigUnsigned<Base> magnitude_;
    bool negative_;
};

//-------------------------------------------------------------------------------------------

// Especialización de la plantilla para base binaria
template<>
class BigInteger<2> {
  public:
    // Constructores
    BigInteger(int n = 0);
    BigInteger(const std::string& str);
    BigInteger(const BigUnsigned<2>& mag); // Nuevo constructor

    // Asignación
    BigInteger<2>& operator=(const BigInteger<2>& other);

    // Flujos de entrada y salida
    friend std::istream& operator>>(std::istream& is, BigInteger<2>& num);
    friend std::ostream& operator<<(std::ostream& os, const BigInteger<2>& num);

    // Comparación
    bool operator==(const BigInteger<2>& other) const;
    bool operator<(const BigInteger<2>& other) const;
    bool operator<=(const BigInteger<2>& other) const;
    bool operator>(const BigInteger<2>& other) const;
    bool operator>=(const BigInteger<2>& other) const;

    // Incremento y decremento
    BigInteger<2>& operator++();    // Preincremento
    BigInteger<2> operator++(int);  // Postincremento
    BigInteger<2>& operator--();    // Predecremento
    BigInteger<2> operator--(int);  // Postdecremento

    // Operadores aritméticos
    BigInteger<2> operator+(const BigInteger<2>& other) const;
    BigInteger<2> operator-(const BigInteger<2>& other) const;
    BigInteger<2> operator*(const BigInteger<2>& other) const;
    BigInteger<2> operator/(const BigInteger<2>& other) const;
    BigInteger<2> operator%(const BigInteger<2>& other) const;
    BigInteger<2> operator-() const;

    // Métodos auxiliares
    std::string toString() const;  // Convierte el número en string
    void removeLeadingZeros();     // Elimina ceros a la izquierda
    bool isNegative() const { return negative; }
    BigInteger<2> complement_2() const;

  private:
    BigUnsigned<2> magnitude;
    bool negative;
};

#endif