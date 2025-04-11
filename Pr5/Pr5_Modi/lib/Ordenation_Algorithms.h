/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * Algoritmos y Estructuras de Datos
 * Práctica 5: Algoritmos de ordenación
 * 
 * @file Ordenation_Algorithms.h
 * @author 
 * @date 02 MAR 2024
 * @brief Fichero de cabecera para los algoritmos de ordenación
 */

#ifndef __ORDENATION_ALGORITHMS_H__
#define __ORDENATION_ALGORITHMS_H__

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <optional>
#include <fstream>

// static int RUN = 32;

// Class Sequence and StaticSequence
#include "./StaticSequence/StaticSequence.h"

// Class SortMethod
#include "./SortMethod/SortMethod.h"

// Cuadratic sort methods
#include "./SortAlgorithm/QuadraticSorts.h"

// Logarithmic sort methods
#include "./SortAlgorithm/LogarithmSorts.h"

// Other sort methods
#include "./SortAlgorithm/OtherSorts.h"

//Class Persona
#include "./NIF/persona.h"

struct program_options
{
  unsigned int sequenceSize = 0;
  int sortMethod = 0;
  std::string traceOption;
  std::string init;
  std::string filename;
  bool isManual = false;
  bool isRandom = false;
  bool isFile = false;
};

/**
 * @brief Show the usage of the program
*/
void Usage()
{
  std::cout << "Usage: ./";
  std::cout << "-size <s> : sequence size\n";
  std::cout << "-ord <m> : is the code of the sorting method\n";
  std::cout << "\t m = 1 -> Insertion\n";
  std::cout << "\t m = 2 -> Sacudida\n";
  std::cout << "\t m = 3 -> Quick\n";
  std::cout << "\t m = 4 -> Heap\n";
  std::cout << "\t m = 5 -> Shell\n";
  std::cout << "\t m = 6 -> Tabla\n";
  std::cout << "-init <i> [f]: is the code of the initialization method\n";
  std::cout << "\t i = manual -> manual initialization\n";
  std::cout << "\t i = random -> random initialization\n";
  std::cout << "\t i = file  f -> initialization from file\n";
  std::cout << "-trace <y|n> : show trace of the sorting algorithm\n";
}

/**
 * @brief Parse the arguments of the program
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @return program_options struct with the options
*/
std::optional<program_options> parse_args(int argc, const char *const argv[])
{
  program_options options;
  std::vector<std::string> args(argv + 1, argv + argc);
  if (args.empty())
  {
    return std::nullopt;
  }

  for (auto it = args.begin(); it != args.end(); ++it)
  {
    if (*it == "-size")
    {
      if (++it == args.end())
      {
        return std::nullopt;
      }
      options.sequenceSize = std::stoi(*it);
    }
    else if (*it == "-ord")
    {
      if (++it == args.end())
      {
        return std::nullopt;
      }
      options.sortMethod = std::stoi(*it);
    }
    else if (*it == "-init")
    {
      if (++it == args.end())
      {
        return std::nullopt;
      }
      options.init = *it;
      if (options.init == "manual")
      {
        options.isManual = true;
      }
      else if (options.init == "random")
      {
        options.isRandom = true;
      }
      else if (options.init == "file")
      {
        options.isFile = true;
        if (++it != args.end())
        {
          options.filename = *it;
        }
        else
        {
          return std::nullopt;
        }
      }
      else
      {
        return std::nullopt;
      }
    }
    else if (*it == "-trace")
    {
      if (++it == args.end())
      {
        return std::nullopt;
      }
      options.traceOption = *it;
      if (options.traceOption == "y" || options.traceOption == "Y")
      {
        showTrace = true;
      }
      else if (options.traceOption == "n" || options.traceOption == "N")
      {
        showTrace = false;
      }
      else
      {
        return std::nullopt;
      }
    }
  }
  return options;
}

/**
 * @brief Print the sequence
 * @param sequence Array of Persona
 * @param n Size of the array
*/
void imprimirSecuencia(const Persona *sequence, int n)
{
  for (int i = 0; i < n; i++)
  {
    std::cout << sequence[i] << " ";
  }
}

/**
 * @brief Initialize the sequence
 * @param sequence Array of Persona
 * @param n Size of the array
 * @param options program_options struct with the options
*/
void initilazingSequence(Persona *sequence, int n, program_options &options)
{
  if (options.init == "manual")
  {
    std::cout << "Introduce " << n << " elements: ";
    for (int i = 0; i < n; i++)
    {
      std::cin >> sequence[i];
    }
  }
  else if (options.init == "random")
  {
    std::cout << "Random sequence: ";
    for (int i = 0; i < n; i++)
    {
      sequence[i] = Persona();
    }
    imprimirSecuencia(sequence, n);
    std::cout << std::endl;
  }
  else if (options.init == "file")
  {
    std::ifstream file(options.filename);
    if (!file)
    {
      std::cerr << "Error opening file" << std::endl;
      exit(1);
    }
    for (int i = 0; i < n; i++)
    {
      file >> sequence[i];
    }
    file.close();
  }
  else
  {
    std::cout << "Opción no válida" << std::endl;
    exit(1);
  }
}

/**
 * @brief Sort the sequence
 * @param sequence Array of Persona
 * @param sequenceObj StaticSequence object
 * @param n Size of the array
 * @param options program_options struct with the options
*/
void sortingTipe(Persona *sequence, StaticSequence<Persona> &sequenceObj, int n, program_options &options)
{
  Persona originalSequence[n];
  std::copy(sequence, sequence + n, originalSequence);

  switch (options.sortMethod)
  {
  case 1:
  {
    int n_swaps = 0;
    int n_comparisons = 0;
    InsertionSort<Persona> insertionSort(sequenceObj);
    insertionSort.Sort(sequence, n, n_swaps, n_comparisons);
    break;
  }
  case 2:
  {
    int n_swaps = 0;
    int n_comparisons = 0;
    ShakeSort<Persona> shakeSort(sequenceObj);
    shakeSort.Sort(sequence, n, n_swaps, n_comparisons);
    break;
  }
  case 3:
  {
    int n_swaps = 0;
    int n_comparisons = 0;
    QuickSort<Persona> quickSort(sequenceObj);
    quickSort.Sort(sequence, n, n_swaps, n_comparisons);
    break;
  }
  case 4:
  {
    int n_swaps = 0;
    int n_comparisons = 0;
    HeapSort<Persona> heapSort(sequenceObj);
    heapSort.Sort(sequence, n, n_swaps, n_comparisons);
    break;
  }
  case 5:
  {
    int n_swaps = 0;
    int n_comparisons = 0;
    double alpha = 0;
    while (alpha <= 0 || alpha >= 1)
    {
      std::cout << "Introduzca el valor de alpha (0 < alpha < 1): ";
      std::cin >> alpha;
    }

    ShellSort<Persona> shellSort(sequenceObj, alpha);
    shellSort.Sort(sequence, n, n_swaps, n_comparisons);
    break;
  }
  case 6:
  {
    int n_swaps = 0;
    int n_comparisons = 0;

    // Restaurar la secuencia original
    std::copy(originalSequence, originalSequence + n, sequence);

    std::cout << "Secuencia inicial: ";
    imprimirSecuencia(sequence, n);
    std::cout << std::endl;

    InsertionSort<Persona> insertionSort(sequenceObj);
    insertionSort.Sort(sequence, n, n_swaps, n_comparisons);
    std::cout << "Número de intercambios: " << n_swaps << std::endl;
    std::cout << "Número de comparaciones: " << n_comparisons << std::endl;
    std::cout << "Secuencia ordenada: ";
    imprimirSecuencia(sequence, n);

    std::cout << std::endl;

    n_swaps = 0;
    n_comparisons = 0;

    // Restaurar la secuencia original
    std::copy(originalSequence, originalSequence + n, sequence);

    std::cout << "Secuencia inicial: ";
    imprimirSecuencia(sequence, n);
    std::cout << std::endl;

    ShakeSort<Persona> shakeSort(sequenceObj);
    shakeSort.Sort(sequence, n, n_swaps, n_comparisons);
    std::cout << "Número de intercambios: " << n_swaps << std::endl;
    std::cout << "Número de comparaciones: " << n_comparisons << std::endl;
    std::cout << "Secuencia ordenada: ";
    imprimirSecuencia(sequence, n);

    std::cout << std::endl;

    n_swaps = 0;
    n_comparisons = 0;

    // Restaurar la secuencia original
    std::copy(originalSequence, originalSequence + n, sequence);

    std::cout << "Secuencia inicial: ";
    imprimirSecuencia(sequence, n);
    std::cout << std::endl;

    QuickSort<Persona> quickSort(sequenceObj);
    quickSort.Sort(sequence, n, n_swaps, n_comparisons);
    std::cout << "Número de intercambios: " << n_swaps << std::endl;
    std::cout << "Número de comparaciones: " << n_comparisons << std::endl;
    std::cout << "Secuencia ordenada: ";
    imprimirSecuencia(sequence, n);

    std::cout << std::endl;

    n_swaps = 0;
    n_comparisons = 0;

    // Restaurar la secuencia original
    std::copy(originalSequence, originalSequence + n, sequence);

    std::cout << "Secuencia inicial: ";
    imprimirSecuencia(sequence, n);
    std::cout << std::endl;

    HeapSort<Persona> heapSort(sequenceObj);
    heapSort.Sort(sequence, n, n_swaps, n_comparisons);
    std::cout << "Número de intercambios: " << n_swaps << std::endl;
    std::cout << "Número de comparaciones: " << n_comparisons << std::endl;
    std::cout << "Secuencia ordenada: ";
    imprimirSecuencia(sequence, n);
    
    std::cout << std::endl;

    n_swaps = 0;
    n_comparisons = 0;

    // Restaurar la secuencia original
    std::copy(originalSequence, originalSequence + n, sequence);

    std::cout << "Secuencia inicial: ";
    imprimirSecuencia(sequence, n);
    std::cout << std::endl;

    double alpha = 0;
    while (alpha <= 0 || alpha >= 1)
    {
      std::cout << "Introduzca el valor de alpha (0 < alpha < 1): ";
      std::cin >> alpha;
    }

    ShellSort<Persona> shellSort(sequenceObj, alpha);
    shellSort.Sort(sequence, n, n_swaps, n_comparisons);
    std::cout << "Número de intercambios: " << n_swaps << std::endl;
    std::cout << "Número de comparaciones: " << n_comparisons << std::endl;
    std::cout << "Secuencia ordenada: ";
    imprimirSecuencia(sequence, n);

    std::cout << std::endl;
    break;
  }
  default:
  {
    std::cout << "Opción no válida" << std::endl;
    break;
  }
  }
}

#endif // __ORDENATION_ALGORITHMS_H__
