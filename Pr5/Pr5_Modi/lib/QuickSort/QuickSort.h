/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 *
 * Algoritmos y Estructuras de Datos
 * Práctica 5: Algoritmos de ordenación
 *
 * @file QuickSort.h
 * @author 
 * @date 02 MAR 2024
 * @brief Fichero de cabecera para el método de ordenación QuickSort
 */

#ifndef __QUICKSORT_H__
#define __QUICKSORT_H__

#include "../SortMethod/SortMethod.h"
#include <algorithm>

template <class Key>
class QuickSort : public SortMethod<Key>
{
public:
  QuickSort(StaticSequence<Key> &sequence) : SortMethod<Key>(sequence) {}
  void Sort(Key *sequence, int n, int& n_swap, int& n_comparisons) const override
  {
    Qsort(sequence, 0, n - 1, n_swap, n_comparisons);
  }
  int particion(Key *sequence, int inicio, int fin, int& n_swap, int& n_comparisons) const
  {
      Key pivote = sequence[fin]; // Usar el último elemento como pivote
      int i = inicio - 1;

      for (int j = inicio; j < fin; j++)
      {
          n_comparisons++;
          if (sequence[j] <= pivote)
          {
              i++;
              n_swap++;
              std::swap(sequence[i], sequence[j]);
          }
      }
      n_swap++;
      std::swap(sequence[i + 1], sequence[fin]);
      return i + 1;
  }
  void Qsort(Key *sequence, int inicio, int fin, int& n_swap, int& n_comparisons) const
  {
    if (inicio < fin)
    {
      if (showTrace)
      {
        this->showTrace(sequence, fin + 1);
      }
      int p = particion(sequence, inicio, fin, n_swap, n_comparisons);
      Qsort(sequence, inicio, p - 1, n_swap, n_comparisons);
      Qsort(sequence, p + 1, fin, n_swap, n_comparisons);
    }
  }
  ~QuickSort() {}
};

#endif // __QUICKSORT_H__