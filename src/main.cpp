#include <iostream>
#include <math.h>
#include <openmp.h>
#include "paralel_stencil_code.h"

int main()
{
  //Value is: 119.154
  int n_rows = 46080;
  int n_cols = 46080;

  std::cout << "Running..." << std::endl;

  float **matrix = new float *[n_rows];

//  for (size_t i = 0; i < n_rows; i++)
//  {
//    float *row = new float[n_cols];
//    matrix[i] = row;
//  }
//
//  for (size_t i = 0; i < n_rows; i++)
//  {
//    for (size_t j = 0; j < n_cols; j++)
//    {
//      if (i == 0 && j == 0)
//      {
//        matrix[i][j] = 0;
//      }
//      else if (i == 0 && j > 0)
//      {
//        matrix[i][j] = 250;
//      }
//      else if (j == 0 && i > 0)
//      {
//        matrix[i][j] = 150;
//      }
//      else
//      {
//        matrix[i][j] = (abs(sin(matrix[i][j - 1])) +
//                        abs(sin(matrix[i - 1][j - 1])) +
//                        abs(sin(matrix[i - 1][j]))) * 100;
//      }
//    }
//  }

#pragma omp parallel num_threads(3)
  {
    printf("https://helloacm.com\n");
  }

  paralel_stencil_code* paralelStencilCode = new paralel_stencil_code();

  paralelStencilCode->run();

  return 0;
}