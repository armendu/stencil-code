#include <iostream>
#include <math.h>
#include <chrono>

int main()
{
  const int n_rows = 8192; //46080;
  const int n_cols = 8192;

  std::cout << "Running..." << std::endl;

  float **matrix = new float *[n_rows];

  for (size_t i = 0; i < n_rows; i++)
  {
    float *row = new float[n_cols];
    matrix[i] = row;
  }

  std::cout << "Starting timer." << std::endl;
  auto t1 = std::chrono::high_resolution_clock::now();

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
                        abs(sin(matrix[i - 1][j]))) *
                       100;
      }
    }
  }
  auto t2 = std::chrono::high_resolution_clock::now();
  
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

  std::cout << "Time taken in milliseconds: " << duration << std::endl;

  return 0;
}
