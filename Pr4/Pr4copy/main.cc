#include "include/hash_table.h"
#include "include/alumno.h"
#include "./include/dispersion_function/module.h" // Asegúrate de incluir la función de dispersión

int main() {
    // Crear una tabla hash para Alumno
    HashTable<Alumno, staticSequence<Alumno>> hashTable(
        10,                           // Tamaño de la tabla
        new Module<Alumno>(10),       // Función de dispersión
        nullptr,                      // Sin función de exploración
        1                             // Tamaño del bloque
    );

    // Crear objetos Alumno
    Alumno a1("A12345", "Carlos", "Gómez");
    Alumno a2("B67890", "Ana", "López");

    // Insertar en la tabla hash
    hashTable.insert(a1);
    hashTable.insert(a2);

    // Buscar en la tabla hash
    if (hashTable.search(a1)) {
        std::cout << "Alumno encontrado: " << a1 << std::endl;
    }

    if (hashTable.search(a2)) {
        std::cout << "Alumno encontrado: " << a2 << std::endl;
    }

    // Mostrar la tabla hash
    std::cout << hashTable << std::endl;

    return 0;
}