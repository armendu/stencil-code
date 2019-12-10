#include <iostream>
#include <math.h>
#include <chrono>
#include <omp.h>

int sequential();

int main()
{
  // Parallel:
  // Matrix[8400][8400]:218.726
  // Time taken in milliseconds: 169083

  // Sequential:
  // Matrix[8400][8400]:218.726
  // Time taken in milliseconds: 132362
  const int n_rows = 46080;
  const int n_cols = 46080;//8192;

  std::cout << "Running..." << std::endl;

  float **matrix = new float *[n_rows];

  for (size_t i = 0; i < n_rows; i++)
  {
    float *row = new float[n_cols];
    matrix[i] = row;
  }

  std::cout << "Started timer." << std::endl;
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

  std::cout << "Matrix[8400][8400]:" << matrix[8400][8400] << std::endl;

  auto t2 = std::chrono::high_resolution_clock::now();
  
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

  std::cout << "Time taken in milliseconds: " << duration << std::endl;

  return 0;
}

int sequential(const int n_rows, const int n_cols)
{
  // for (size_t i = 0; i < n_rows; i++)
  // {
  //   for (size_t j = 0; j < n_cols; j++)
  //   {
  //     if (i == 0 && j == 0)
  //     {
  //       matrix[i][j] = 0;
  //     }
  //     else if (i == 0 && j > 0)
  //     {
  //       matrix[i][j] = 250;
  //     }
  //     else if (j == 0 && i > 0)
  //     {
  //       matrix[i][j] = 150;
  //     }
  //     else
  //     {
  //       matrix[i][j] = (abs(sin(matrix[i][j - 1])) +
  //                       abs(sin(matrix[i - 1][j - 1])) +
  //                       abs(sin(matrix[i - 1][j]))) *
  //                      100;
  //     }
  //   }
  // }

  return 0;
}

int paralel()
{
  // for (int i = 0; i < n_rows; i++)
  // {
  //   #pragma omp parallel num_threads(2)
  //   {
  //     int threadNumber = omp_get_thread_num();

  //     for (int j = i; j < n_rows; j++)
  //     {

  //       //If it is first thread,
  //       // changa values iterating into rows
  //       if (threadNumber == 0)
  //       {
  //         int row = i;
  //         int col = j;

  //         if (row == 0 && col == 0)
  //         {
  //           matrix[0][0] = 0;
  //         }
  //         else if (row == 0)
  //         {
  //           matrix[row][col] = 250;
  //         }
  //         else
  //         {
  //           matrix[row][col] = (abs(sin(matrix[row][col - 1])) +
  //                               abs(sin(matrix[row - 1][col - 1])) +
  //                               abs(sin(matrix[row - 1][col]))) *
  //                              100;
  //         }
  //       }

  //       //If it is second thread,
  //       // changa values iterating into columns
  //       else if (threadNumber == 1)
  //       {
  //         int row = j;
  //         int col = i;

  //         if (row == 0 && col == 0)
  //         {
  //           matrix[0][0] = 0;
  //         }
  //         else if (col == 0)
  //         {
  //           matrix[row][col] = 150;
  //         }
  //         else
  //         {
  //           matrix[row][col] = (abs(sin(matrix[row][col - 1])) +
  //                               abs(sin(matrix[row - 1][col - 1])) +
  //                               abs(sin(matrix[row - 1][col]))) *
  //                              100;
  //         }
  //       }
  //     }
  //   }
  // }

  return 0;
}