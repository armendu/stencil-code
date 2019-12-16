#include <iostream>
#include <math.h>
#include <chrono>
#include <omp.h>

#include "get_opt.h"

#define N_ROWS 46080 //8092
#define N_COLS 46080 //8092
#define ERROR -1

void initialize_matrix();
void execute_in_sequence();
void execute_in_parallel();
void execute_in_parallel_2();
void print_solution();
void validate_solution();
float **matrix;
float **sequencial_matrix;

int main(int argc, char** argv)
{
  std::cout << "Running..." << std::endl;
  
  int get_opt_res = get_opt::get_options(argc, argv); 
  if(get_opt_res == ERROR)
  {
    get_opt::usage();
    return -1;
  }

  matrix = new float *[N_ROWS];
  sequencial_matrix = new float *[N_ROWS];

  initialize_matrix();

  std::cout << "Started timer." << std::endl;

  auto t1 = std::chrono::high_resolution_clock::now();
  execute_in_parallel_2();
  auto t2 = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

  std::cout << "Time taken in milliseconds: " << duration << std::endl;

  execute_in_sequence();
  
  // std::cout << "Matrix[200][200]:" << matrix[100][100] << std::endl;
  // print_solution();
  validate_solution();

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

  #pragma omp parallel for num_threads(2)
  for (int i = 0; i < N_ROWS; i++)
  {
    float *row = new float[N_COLS];
    sequencial_matrix[i] = row;

    sequencial_matrix[0][i] = 250;
    sequencial_matrix[i][0] = 150;
  }

  sequencial_matrix[0][0] = 0;
  matrix[0][0] = 0;
}

void execute_in_sequence()
{
  for (int i = 1; i < N_ROWS; i++)
  {
    for (int j = 1; j < N_COLS; j++)
    {
      sequencial_matrix[i][j] = (abs(sin(sequencial_matrix[i][j - 1])) +
                      abs(sin(sequencial_matrix[i - 1][j - 1])) +
                      abs(sin(sequencial_matrix[i - 1][j]))) *
                     100;
    }
  }
}

void execute_in_parallel()
{
  for (int i = 2; i < N_ROWS * 2; i++)
  {
    #pragma omp parallel for num_threads(10)
    for (int j = 1; j < i; j++)
    {
      int row = i - j;

      if (row < N_ROWS && j < N_COLS)
      {
        matrix[row][j] = (abs(sin(matrix[row][j - 1])) +
                          abs(sin(matrix[row - 1][j - 1])) +
                          abs(sin(matrix[row - 1][j]))) *
                         100;
      }
    }
  }
}

void execute_in_parallel_2()
{
  for (int i = 2; i < N_ROWS * 2; i++)
  {
    if (i < N_ROWS)
    {
      #pragma omp parallel for num_threads(8)
      for (int j = 1; j < i; j++)
      {
        matrix[i - j][j] = (fabs(sin(matrix[i - j - 1][j - 1])) +
                            fabs(sin(matrix[i - j][j - 1])) +
                            fabs(sin(matrix[i - j - 1][j]))) *
                           100;
      }
    }
    else
    {
      #pragma omp parallel for num_threads(8)
      for (int j = N_ROWS - 1; j >= i - N_ROWS + 1; j--)
      {
        matrix[i - j][j] = (fabs(sin(matrix[i - j - 1][j - 1])) +
                            fabs(sin(matrix[i - j][j - 1])) +
                            fabs(sin(matrix[i - j - 1][j]))) *
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

void validate_solution()
{
  for (size_t i = 0; i < N_ROWS; i++)
  {
    for (size_t j = 0; j < N_COLS; j++)
    {
     if (matrix[i][j] != sequencial_matrix[i][j])
     {
       std::cout << "Not the same\n";
     } 
    }
  }

  std::cout << "Solution is valid." << std::endl;
}