/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 *
 * Algoritmos y Estructuras de Datos
 * Práctica 5: Algoritmos de ordenación
 *
 * @file ShakeSort.h
 * @author 
 * @date 02 MAR 2024
 * @brief Fichero de cabecera para el método de ordenación ShakeSort
 */

 #ifndef __SHAKESORT_H__
 #define __SHAKESORT_H__
 
 #include "../SortMethod/SortMethod.h"
 #include <algorithm>
 #include <stdexcept>
 
 template <class Key>
 class ShakeSort : public SortMethod<Key>
 {
 public:
   ShakeSort(StaticSequence<Key> &sequence) : SortMethod<Key>(sequence) {}
 
   void Sort(Key *sequence, int n, int& n_swap, int& n_comparisons) const override
   {
     bool swapped = true;
     int start = 0;
     int end = n - 1;
 
     while (swapped)
     {
       swapped = false;
 
       // Traverse the array from left to right
       for (int i = start; i < end; ++i)
       {
         n_comparisons++;
         if (sequence[i] > sequence[i + 1])
         {
           n_swap++;
           std::swap(sequence[i], sequence[i + 1]);
           swapped = true;
         }
       }
 
       // If no elements were swapped, the array is sorted
       if (!swapped)
         break;
 
       swapped = false;
       --end;
 
       // Traverse the array from right to left
       for (int i = end - 1; i >= start; --i)
       {
         n_comparisons++;
         if (sequence[i] > sequence[i + 1])
         {
           n_swap++;
           std::swap(sequence[i], sequence[i + 1]);
           swapped = true;
         }
       }
 
       ++start;
     }
   }
 
   ~ShakeSort() {}
 };
 
 #endif // __SHAKESORT_H__