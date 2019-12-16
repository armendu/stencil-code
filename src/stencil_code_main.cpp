#include <iostream>
#include <math.h>
#include <chrono>
#include <omp.h>

#include "get_opt.h"
#include "io.h"

#define N_ROWS    46080//8192
#define N_COLS    46080//8192
#define N_THREADS 8
#define ERROR     -1

void initialize_matrices(bool include_seq);
void execute_in_sequence();
void execute_in_parallel();
void execute_in_parallel_2();
void print_solution();
void validate_solution(int *arguments);
float **matrix;
float **sequential_matrix;

int main(int argc, char **argv)
{
  std::cout << "Running stencil code in parallel..." << std::endl;

  int *arguments = new int[argc - 1];

  int get_opt_res = get_opt::get_options(arguments, argc, argv);

  if (get_opt_res == ERROR)
  {
    get_opt::usage();
    return -1;
  }

  initialize_matrices(true);

  std::cout << "Started timer." << std::endl;

  auto t1 = std::chrono::high_resolution_clock::now();
  // execute_in_parallel_2();
  execute_in_sequence();
  auto t2 = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

  std::cout << "Time taken in milliseconds: " << duration << std::endl;

  io::write_result(duration);

  std::cout << "Running stencil code in sequence..." << std::endl;
  execute_in_sequence();

  // print_solution();
  validate_solution(arguments);

  return 0;
}

void initialize_matrices(bool include_seq)
{
  matrix = new float *[N_ROWS];
  sequential_matrix = new float *[N_ROWS];

  // #pragma omp parallel for num_threads(2)
  for (int i = 0; i < N_ROWS; i++)
  {
    float *row = new float[N_COLS];
    matrix[i] = row;

    matrix[0][i] = 250;
    matrix[i][0] = 150;
  }

  if (include_seq)
  {
    // #pragma omp parallel for num_threads(2)
    for (int i = 0; i < N_ROWS; i++)
    {
      float *row = new float[N_COLS];
      sequential_matrix[i] = row;

      sequential_matrix[0][i] = 250;
      sequential_matrix[i][0] = 150;
    }
    sequential_matrix[0][0] = 0;
  }

  matrix[0][0] = 0;
}

void execute_in_sequence()
{
  for (int i = 1; i < N_ROWS; i++)
  {
    for (int j = 1; j < N_COLS; j++)
    {
      sequential_matrix[i][j] = (abs(sin(sequential_matrix[i][j - 1])) +
                                 abs(sin(sequential_matrix[i - 1][j - 1])) +
                                 abs(sin(sequential_matrix[i - 1][j]))) *
                                100;
    }
  }
}

void execute_in_parallel()
{
  for (int i = 2; i < N_ROWS * 2; i++)
  {
    #pragma omp parallel for num_threads(N_THREADS)
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
      #pragma omp parallel for num_threads(N_THREADS)
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
      #pragma omp parallel for num_threads(N_THREADS)
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
      std::cout << matrix[i][j] << "\t\t";
    }
    std::cout << std::endl;
  }
}

void validate_solution(int *arguments)
{
  for (size_t i = 0; i < sizeof(arguments) / sizeof(*arguments); i += 2)
  {
    std::cout << "Parallel Matrix[" << arguments[i] << "][" << arguments[i + 1] << "]: ";
    std::cout << matrix[arguments[i]][arguments[i + 1]] << std::endl;
    std::cout << "Sequential Matrix[" << arguments[i] << "][" << arguments[i + 1] << "]: ";
    std::cout << sequential_matrix[arguments[i]][arguments[i + 1]] << std::endl;

    if (matrix[arguments[i]][arguments[i + 1]] != sequential_matrix[arguments[i]][arguments[i + 1]])
    {
      std::cout << "Solution is invalid." << std::endl;
      return;
    }
  }

  std::cout << "Solution is valid." << std::endl;
}