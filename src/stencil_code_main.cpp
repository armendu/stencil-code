#include <iostream>
#include <math.h>
#include <chrono>
#include <omp.h>

#define N_ROWS 8192 //46080
#define N_COLS 8192 //46080

void execute_sequential();
float **matrix;

int main()
{
  // Parallel:
  // Matrix[8400][8400]:218.726
  // Time taken in milliseconds: 169083

  // Sequential:
  // Matrix[8400][8400]:218.726
  // Time taken in milliseconds: 132362

  std::cout << "Running..." << std::endl;

  matrix = new float *[N_ROWS];

  initialize_matrix();

  std::cout << "Started timer." << std::endl;
  auto t1 = std::chrono::high_resolution_clock::now();

  execute_sequential();

  auto t2 = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

  std::cout << "Time taken in milliseconds: " << duration << std::endl;

  std::cout << "Matrix[500][500]:" << matrix[500][500] << std::endl;

  return 0;
}

void initialize_matrix()
{
  // Initilize the known members of matrix
  for (int i = 0; i < N_ROWS; i++)
  {
    float *row = new float[N_COLS];
    matrix[i] = row;

    matrix[0][i] = 250;
    matrix[i][0] = 150;
  }

  matrix[0][0] = 0;
}

void execute_sequential()
{
  for (int i = 1; i < N_ROWS; i++)
  {
    for (int j = 1; j < N_COLS; j++)
    {
      matrix[i][j] = (abs(sin(matrix[i][j - 1])) +
                      abs(sin(matrix[i - 1][j - 1])) +
                      abs(sin(matrix[i - 1][j]))) *
                     100;
    }
  }
}

int paralel()
{
  // for (int i = 0; i < N_ROWS; i++)
  // {
  //   #pragma omp parallel num_threads(2)
  //   {
  //     int threadNumber = omp_get_thread_num();

  //     for (int j = i; j < N_ROWS; j++)
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