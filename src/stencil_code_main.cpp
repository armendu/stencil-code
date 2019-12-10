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
  const int n_rows = 46080;
  const int n_cols = 46080;
  float **matrix = new float *[n_rows];

  for (size_t i = 0; i < n_rows; i++)
  {
    float *row = new float[n_cols];
    matrix[i] = row;
  }

  // Timer t = Timer();
  
  // t.setInterval([&]() {
  //     cout << "Hey.. After each 1s..." << endl;
  // }, 1000); 
  
  // t.setTimeout([&]() {
  //     cout << "Hey.. After 5.2s. But I will stop the timer!" << endl;
  //     t.stop();
  // }, 5200);

  for (size_t i = 0; i < n_rows; i++)
  {
    for (size_t j = 0; j < n_cols; j++)
    {
      if (i == 0 && j == 0)
      {
        matrix[i][j] = 0;
      }
      else if (i == 0 && j > 0)
      {
        matrix[i][j] = 250;
      }
      else if (j == 0 && i > 0)
      {
        matrix[i][j] = 150;
      }
      else
      {
        matrix[i][j] = (abs(sin(matrix[i][j - 1])) +
         abs(sin(matrix[i - 1][j - 1])) +
         abs(sin(matrix[i - 1][j]))) * 100;
      }
    }
  }

  return 0;
}