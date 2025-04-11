#pragma once

#include <iostream>
#include <string>
#include "nif.h"

class Persona {
  public:
    // Constructor por defecto
    Persona() : nombre_(""), apellidos_(""), letra_(' '), key_() {}

    // Constructor parametrizado
    Persona(const std::string& nombre, const std::string& apellidos, const NIF& nif, char letra)
        : nombre_(nombre), apellidos_(apellidos), nif_(nif), letra_(letra),  {}

    // Constructor de copia
    Persona(const Persona& other)
        : nombre_(other.nombre_), apellidos_(other.apellidos_), nif_(other.nif_), letra_(other.letra_) {}

    // Operador de asignación
    Persona& operator=(const Persona& other) {
        if (this != &other) {
            nombre_ = other.nombre_;
            apellidos_ = other.apellidos_;
            nif_ = other.nif_;
            letra_ = other.letra_;
        }
        return *this;
    }

    // Métodos getter
    std::string getNombre() const { return nombre_; }
    std::string getApellidos() const { return apellidos_; }
    NIF getNif() const { return nif_; }
    char getLetra() const { return letra_; }

    // Métodos setter
    void setNombre(const std::string& nombre) { nombre_ = nombre; }
    void setApellidos(const std::string& apellidos) { apellidos_ = apellidos; }
    void setNif(const NIF& nif) { nif_ = nif; }
    void setLetra(char letra) { letra_ = letra; }

    // Sobrecarga del operador de salida
    friend std::ostream& operator<<(std::ostream& os, const Persona& persona) {
        os << "Nombre: " << persona.nombre_
           << ", Apellidos: " << persona.apellidos_
           << ", NIF: " << persona.nif_
           << ", Letra: " << persona.letra_;
        return os;
    }

    // Sobrecarga del operador de igualdad (para comparación en la tabla hash)
    bool operator==(const Persona& other) const {
        return nif_ == other.nif_ && letra_ == other.letra_;
    }

  private:
    std::string nombre_;      // Nombre de la persona
    std::string apellidos_;   // Apellidos de la persona
    NIF nif_;                 // NIF de la persona (usando la clase NIF)
    char letra_;              // Letra asociada al NIF
    long key_;             // Clave para la tabla hash (opcional)
};