/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  stencil_seq.cpp
 *
 * @brief 
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: 04, Dec 04, 2019 20:23$
 */

int main() {
  float **matrix_seq = new float *[n_rows];
  int k, l;
  for (k = 0; k < n_rows; k++)
  {
    float *row = new float[n_cols];

    for (l = 0; l < n_cols; l++)
    {
      if (i == 0 && l == 0)
      {
        row[l] = 0;
      }
      else if (i == 0 && l > 0)
      {
        row[l] = 250;
      }
      else if (l == 0 && i > 0)
      {
        row[l] = 150;
      }
      else
      {
        float *prev_row = matrix_seq[i - 1];
        row[l] = (abs(sin(prev_row[l - 1])) + abs(sin(row[l - 1])) + abs(sin(prev_row[l]))) * 100;
      }
    }
    matrix_seq[i] = row;
  }
  for (size_t i = 0; i < n_rows; i++)
  {
    float *matrixRow = matrix[i];
    for (size_t j = 0; j < n_cols; j++)
    {
      if (j == 200 & i == 200)
      {
        std::cout << "Value is: " << (matrixRow[j]) << "\n";
      }
    }
  }
  return 0;
}