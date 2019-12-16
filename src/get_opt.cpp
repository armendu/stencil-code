#include <iostream>

#include "get_opt.h"

int get_opt::get_options(int argc, char **argv)
{
  // Check no. of arguments
  if (argc < 3 || argc > 7) {
    std::cout << "Wrong number of arguments provided. \n";
    return -1;
  }
  std::cout << "Arguments: " << argc;

  return 0;
}

void get_opt::usage()
{
  std::cout << "\nSYNOPSIS\n";
  std::cout << "./output/build/stencil_code_main.o [NUMBERS IN PAIR] e.g.\n";
  std::cout << "./output/build/stencil_code_main.o 25 48 3000 2000 25673 41983\n";
}