#include <iostream>
#include <cstddef>

namespace lab
{
  int** createMatrix(size_t rows, size_t cols);
  void removeMatrix(int** matrix, size_t rows);
  bool readMatrix(int** matrix, size_t rows, size_t cols);
  void transposeMatrix(const int* const* src, int** dst, size_t rows, size_t cols);
  void printMatrix(const int* const* matrix, size_t rows, size_t cols);
}

int main()
{
  const int inputError = 1;
  const int memoryError = 2;
  long long rowsInput = 0;
  long long colsInput = 0;
  std::cin >> rowsInput >> colsInput;
  if (std::cin.fail() || rowsInput < 0 || colsInput < 0) {
    std::cerr << "Error: invalid matrix size\n";
    return inputError;
  }
  const size_t rows = static_cast< size_t >(rowsInput);
  const size_t cols = static_cast< size_t >(colsInput);
  int** matrix = lab::createMatrix(rows, cols);
  if (matrix == nullptr) {
    std::cerr << "Error: not enough memory\n";
    return memoryError;
  }
  if (!lab::readMatrix(matrix, rows, cols)) {
    lab::removeMatrix(matrix, rows);
    std::cerr << "Error: invalid matrix element\n";
    return inputError;
  }
  int** transposed = lab::createMatrix(cols, rows);
  if (transposed == nullptr) {
    lab::removeMatrix(matrix, rows);
    std::cerr << "Error: not enough memory\n";
    return memoryError;
  }
  lab::transposeMatrix(matrix, transposed, rows, cols);
  lab::printMatrix(transposed, cols, rows);
  lab::removeMatrix(transposed, cols);
  lab::removeMatrix(matrix, rows);
  return 0;
}

int** lab::createMatrix(size_t rows, size_t cols)
{
  int** matrix = nullptr;
  try {
    matrix = new int*[rows];
  } catch (...) {
    return nullptr;
  }
  for (size_t i = 0; i < rows; ++i) {
    try {
      matrix[i] = new int[cols];
    } catch (...) {
      removeMatrix(matrix, i);
      return nullptr;
    }
  }
  return matrix;
}

void lab::removeMatrix(int** matrix, size_t rows)
{
  for (size_t i = 0; i < rows; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

bool lab::readMatrix(int** matrix, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      std::cin >> matrix[i][j];
      if (std::cin.fail()) {
        return false;
      }
    }
  }
  return true;
}

void lab::transposeMatrix(const int* const* src, int** dst, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      dst[j][i] = src[i][j];
    }
  }
}

void lab::printMatrix(const int* const* matrix, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      if (j != 0) {
        std::cout << " ";
      }
      std::cout << matrix[i][j];
    }
    std::cout << "\n";
  }
}
