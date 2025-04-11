/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * Algoritmos y Estructuras de Datos
 * Práctica 5: Algoritmos de ordenación
 * 
 * @file Persona.h
 * @brief Fichero de cabecera para la clase Persona
*/

#ifndef __PERSONA_H__
#define __PERSONA_H__

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Persona
{
public:
  Persona() : nombre_("Nombre"), dni_(generarDniAleatorio()), letra_('A' + rand() % 26) {}
  Persona(const std::string &nombre, long int dni, char letra) : nombre_(nombre), dni_(dni), letra_(letra) {}

  // Getters
  std::string getNombre() const { return nombre_; }
  long int getDni() const { return dni_; }
  char getLetra() const { return letra_; }

  // Setters
  void setNombre(const std::string &nombre) { nombre_ = nombre; }
  void setDni(long int dni) { dni_ = dni; }
  void setLetra(char letra) { letra_ = letra; }

  // Operador de conversión para usar el DNI como clave
  operator long() const { return dni_; }

  // Sobrecarga de operadores de entrada y salida
  friend std::istream &operator>>(std::istream &is, Persona &persona)
  {
    std::cout << "\nIngrese el nombre: ";
    is >> persona.nombre_;
    std::cout << "Ingrese el DNI: ";
    is >> persona.dni_;
    std::cout << "Ingrese la letra: ";
    is >> persona.letra_;
    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, const Persona &persona)
  {
    os << "Nombre: " << persona.nombre_ << ", DNI: " << persona.dni_ << persona.letra_;
    return os;
  }

  

private:
  std::string nombre_;
  long int dni_;
  char letra_;

  static long int generarDniAleatorio()
  {
    return 10000000 + rand() % 90000000; // Genera un número entre 10000000 y 99999999
  }
};

#endif // __PERSONA_H__