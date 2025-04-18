
/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 *
 * Algoritmos y Estructuras de Datos
 * Práctica 5: Algoritmos de ordenación
 *
 * @file HeapSort.h
 * @author
 * @date 02 MAR 2024
 * @brief Fichero de cabecera para el método de ordenación HeapSort
 */
#ifndef __HEAPSORT_H__
#define __HEAPSORT_H__

#include "../SortMethod/SortMethod.h"
#include <algorithm>

template <class Key>
class HeapSort : public SortMethod<Key>
{
public:
  HeapSort(StaticSequence<Key> &sequence) : SortMethod<Key>(sequence) {}
  void Sort(Key *sequence, int n, int& n_swap, int& n_comparisons) const override
  {
    for (int i = n / 2 - 1; i >= 0; i--)
    {
      Baja(i, sequence, n, n_swap, n_comparisons);
    }
    for (int i = n - 1; i > 0; i--)
    {
      n_swap++;
      std::swap(sequence[0], sequence[i]);
      Baja(0, sequence, i, n_swap, n_comparisons);
    }
  }
  void Baja(int i, Key *sequence, int n, int& n_swap, int& n_comparisons) const
  {
    int h = i;
    int h1 = 2 * i + 1;
    int h2 = h1 + 1;
    n_comparisons++;
    if (h1 < n && sequence[h1] > sequence[h])
    {
      h = h1;
    }
    n_comparisons++;
    if (h2 < n && sequence[h2] > sequence[h])
    {
      h = h2;
    }

    if (h != i)
    {
      n_swap++;
      std::swap(sequence[i], sequence[h]);
      Baja(h, sequence, n, n_swap, n_comparisons);
    }
  }
  ~HeapSort() {}
};

#endif // __HEAPSORT_H__