#include "../lib/Ordenation_Algorithms.h"

int main(int argc, const char *const argv[])
{
  std::cout << "Práctica 5: Algoritmos de ordenación\n";
  std::cout << "=====================================\n";

  auto options = parse_args(argc, argv);
  if (!options)
  {
    Usage();
    return 1;
  }

  NIF *sequence = new NIF[options->sequenceSize];
  int n = options->sequenceSize;

  std::cout << "Initialazing sequence...\n";
  initilazingSequence(sequence, n, *options);

  StaticSequence<NIF> sequenceObj(sequence, n);
  sortingTipe(sequence, sequenceObj, n, *options);

  std::cout << "Sorted sequence: ";
  imprimirSecuencia(sequence, n);
  std::cout << std::endl;

  delete[] sequence;


  return 0;
}
