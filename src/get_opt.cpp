#include <iostream>

#include "get_opt.h"

int get_opt::get_options(int* arguments, int argc, char **argv)
{
  // std::cout << "Arguments: " << argc;
  // Check no. of arguments
  // if (argc < 3 || argc > 7 || argc % 2 == 0) {
  //   std::cout << "Wrong number of arguments provided. \n";
  //   return -1;
  // }

  for (int i = 0; i < argc - 1; i++)
  {
    arguments[i] = atoi(argv[i + 1]); 
  }

  return 0;
}

void get_opt::usage()
{
  std::cout << "\nSYNOPSIS\n";
  std::cout << "./output/build/stencil_code_main.o [NUMBERS IN PAIR] e.g.\n";
  std::cout << "./output/build/stencil_code_main.o 25 48 3000 2000 25673 41983\n";
}