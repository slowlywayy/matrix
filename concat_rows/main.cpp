#include <iostream>
#include <stdexcept>
#include <cstddef>


namespace pershinov {
  int ** concat_rows(const int * const * lhs, size_t n1, size_t m1, const int * const * rhs, size_t n2, size_t m2)
  {
    size_t rows = 0;
    if (n1 > n2) {
      rows = n1;
    } else {
      rows = n2;
    }
    int ** result = new int * [rows];
    size_t created = 0;
    try {
      for (size_t i = 0; i < rows; ++i) {
        size_t len = 0;
        if (i < n1) {
          len += m1;
        }
        if (i < n2) {
          len += m2;
        }
        result[i] = new int [len];
        size_t pos = 0;
        if (i < n1) {
          for (size_t j = 0; j < m1; ++j) {
            result[i][pos] = lhs[i][j];
            ++pos;
          }
        }
        if (i < n2) {
          for (size_t j = 0; j < m2; ++j) {
            result[i][pos] = rhs[i][j];
            ++pos;
          }
        }
        ++created;
      }
    } catch (...) {
      for (size_t k = 0; k < created; ++k) {
        delete[] result[k];
      }
      delete[] result;
      throw;
    }
    return result;
  }

  void free_rows(int ** arr, size_t rows)
  {
    if (arr == nullptr) {
      return;
    }
    for (size_t k = 0; k < rows; ++k) {
      delete[] arr[k];
    }
    delete[] arr;
  }

  int ** read_rows(size_t n, size_t m)
  {
    size_t created = 0;
    int ** result = new int * [n];
    try {
      for (size_t i = 0; i < n; ++i) {
        result[i] = new int [m];
        created++;
        for (size_t j = 0; j < m; ++j) {
          std::cin >> result[i][j];
          if (!std::cin) {
            throw std::invalid_argument("invalid input");
          }
        }
      }
    } catch (...) {
      free_rows(result, created);
      throw;
    }
    return result;
  }
}


int main()
{
  size_t n1 = 0;
  size_t m1 = 0;
  size_t n2 = 0;
  size_t m2 = 0;
  std::cin >> n1 >> m1 >> n2 >> m2;
  if (!std::cin) {
    std::cerr << "Error: invalid input\n";
    return 1;
  }
  size_t rows = 0;
  if (n1 > n2) {
    rows = n1;
  } else {
    rows = n2;
  }
  int ** lhs = nullptr;
  int ** rhs = nullptr;
  int ** result = nullptr;
  int code = 0;
  try {
    lhs = pershinov::read_rows(n1, m1);
    rhs = pershinov::read_rows(n2, m2);
    result = pershinov::concat_rows(lhs, n1, m1, rhs, n2, m2);

    for (size_t i = 0; i < rows; ++i) {
      size_t len = 0;
      if (i < n1) {
        len += m1;
      }
      if (i < n2) {
        len += m2;
      }
      for (size_t j = 0; j < len; ++j) {
        std::cout << result[i][j] << " ";
      }
      std::cout << '\n';
    }
  } catch (const std::invalid_argument & e) {
    std::cerr << "Error: " << e.what() << '\n';
    code = 1;
  } catch (const std::exception & e) {
    std::cerr << "Error: " << e.what() << '\n';
    code = 2;
  }
  pershinov::free_rows(lhs, n1);
  pershinov::free_rows(rhs, n2);
  pershinov::free_rows(result, rows);
  return code;
}
