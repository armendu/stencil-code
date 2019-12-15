#include <iostream>
#include <math.h>
#include <chrono>
#include <omp.h>

#define N_ROWS 8092 //46080
#define N_COLS 8092 //46080

void initialize_matrix();
void execute_in_sequence();
void execute_in_paralel();
void print_solution();
float **matrix;

int main()
{
  std::cout << "Running..." << std::endl;

  matrix = new float *[N_ROWS];

  initialize_matrix();

  std::cout << "Started timer." << std::endl;
  auto t1 = std::chrono::high_resolution_clock::now();

  execute_in_paralel();
  // execute_in_sequence();

  auto t2 = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

  std::cout << "Time taken in milliseconds: " << duration << std::endl;

  // std::cout << "Matrix[200][200]:" << matrix[100][100] << std::endl;

  return 0;
}

void initialize_matrix()
{
  #pragma omp parallel for num_threads(2)
  for (int i = 0; i < N_ROWS; i++)
  {
    float *row = new float[N_COLS];
    matrix[i] = row;

    matrix[0][i] = 250;
    matrix[i][0] = 150;
  }

  matrix[0][0] = 0;
}

void execute_in_sequence()
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

void execute_in_paralel()
{
  for (int i = 1; i < N_ROWS * 2; i++)
  {
      #pragma omp parallel for num_threads(10)
      for (int j = 1; j <= i; j++)
      {
        // int row = i - omp_get_thread_num();
        int row = i - j + 1;
        
        if( row < N_ROWS && j < N_COLS ) {
          matrix[row][j] = (abs(sin(matrix[row][j - 1])) +
                          abs(sin(matrix[row - 1][j - 1])) +
                          abs(sin(matrix[row - 1][j]))) *
                         100;
        }
      }
    }
	}

void print_solution()
{
  for (int i = 0; i < N_ROWS; i++)
  {
    for (int j = 0; j < N_COLS; j++)
    {
      std::cout<< matrix[i][j] << "\t\t";
    }
    std::cout << std::endl;
  }
}