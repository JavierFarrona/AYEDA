#pragma once

#include <iostream>
#include <string>
#include <sstream>

// Función personalizada para convertir un Alumno a cadena
inline std::string to_string(const Alumno& alumno) {
    std::ostringstream os;
    os << "Clave: " << alumno.getClave()
       << ", Nombre: " << alumno.getNombre()
       << ", Apellidos: " << alumno.getApellidos();
    return os.str();
}

class Alumno {
  public:
    // Constructor por defecto
    Alumno() : clave_(""), nombre_(""), apellidos_(""), key (0){}

    // Constructor parametrizado
    Alumno(const std::string& clave, const std::string& nombre, const std::string& apellidos)
        : clave_(clave), nombre_(nombre), apellidos_(apellidos), key_(0) {}

    Alumno(int defaultValue) {
          if (defaultValue == -1) {
              clave_ = "DEFAULT";
              nombre_ = "DEFAULT";
              apellidos_ = "DEFAULT";
              key_ = 0;
          }
    }

    // Constructor de copia
    Alumno(const Alumno& other)
        : clave_(other.clave_), nombre_(other.nombre_), apellidos_(other.apellidos_), key_(other.key_){}

    // Operador de asignación
    Alumno& operator=(const Alumno& other) {
        if (this != &other) {
            clave_ = other.clave_;
            nombre_ = other.nombre_;
            apellidos_ = other.apellidos_;
            key_ = other.key_;
        }
        return *this;
    }

    // Métodos getter
    std::string getClave() const { return clave_; }
    std::string getNombre() const { return nombre_; }
    std::string getApellidos() const { return apellidos_; }

    // Métodos setter
    void setClave(const std::string& clave) { clave_ = clave; }
    void setNombre(const std::string& nombre) { nombre_ = nombre; }
    void setApellidos(const std::string& apellidos) { apellidos_ = apellidos; }

    // Sobrecarga del operador de salida
    friend std::ostream& operator<<(std::ostream& os, const Alumno& alumno) {
        os << "Clave: " << alumno.clave_
           << ", Nombre: " << alumno.nombre_
           << ", Apellidos: " << alumno.apellidos_;
        return os;
    }

    // Sobrecarga del operador de igualdad (para comparación en la tabla hash)
    bool operator==(const Alumno& other) const {
        return clave_ == other.clave_;
    }

    void setKey() { 
        key_ = 0;
        for (char c : clave_) {
            key_ = (key_ * 31 + static_cast<unsigned>(c)) % 100000; // Hash basado en los caracteres de la clave
        }
    }

    long getKey() const { return key_; }

    

  private:
    std::string clave_;       // Clave alfanumérica del alumno
    std::string nombre_;      // Nombre del alumno
    std::string apellidos_;   // Apellidos del alumno
    long key_;
};