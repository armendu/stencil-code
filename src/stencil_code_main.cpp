/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  main.c
 *
 * @brief Implements the funtionality for the client
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun, Jul 21, 2019 23:32$
 */

#include <iostream>
#include <math.h>
using namespace std;

int main()
{
  int n_rows = 46080;
  int n_cols = 46080;
  float **matrix = new float *[n_rows]; // [0, 0, 3, 4, 5]

  int i, j;

  for (i = 0; i < n_rows; i++)
  {
    float *row = new float[n_cols];

    for (j = 0; j < n_cols; j++)
    {
      // float* cell = &row[i];
      if (i == 0 && j == 0)
      {
        row[j] = 0;
      }
      else if (i == 0 && j > 0)
      {
        row[j] = 250;
      }
      else if (j == 0 && i > 0)
      {
        row[j] = 150;
      }
      else
      {
        row[j] = 1;
      }
    }
    matrix[i] = row;
  }

  for (size_t i = 0; i < n_rows; i++)
  {

    float *matrixRow = matrix[i];
    for (size_t j = 0; j < n_cols; j++)
    {
      if (matrixRow[j] == 150) {
        cout << matrixRow[j] << " ";
        cout << "j: " << j << "i: " << i << endl; 
      }
    }
    cout << "\n";
  }

  // float* matrixRow = &matrix[10];

  // cout << "0:" << matrixRow[0] << "\n";
  // cout << "2:"<< matrixRow[2]<< "\n";
  // cout << "Here";

  // for (int i = 0; i < n_rows; i++)
  // {
  //   float *row = malloc(sizeof(float) * n_cols);

  //   for (int j = 0; j < n_cols; j++)
  //   {
  //     if (i ==0 && j == 0)
  //     {
  //       row[j] = 0;
  //     }
  //     else if (i == 0 && j > 0)
  //     {
  //       row[j] = 250;
  //     }
  //     else if (j == 0 && i > 0)
  //     {
  //       row[j] = 150;
  //     }
  //     else
  //     {
  //       float *prev_row = kernel[i - 1];

  //       row[j] = (abs(sin(prev_row[j - 1])) + abs(sin(row[j - 1])) + abs(sin(prev_row[j]))) * 100;
  //     }
  //     printf("%.6f \n", row[j]);
  //   }

  //   kernel[i] = row;
  //   // printf("%d\n", i);
  // }

  return 0;
}