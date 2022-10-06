#include <iostream>
#include <string>
#include <stdexcept>
#include <time.h>
// This is a simple exercise of Cpp
// The goal of this progream will be to bring a linear system of equations into a Row-Echalon form.
// The matrix will be randomly generated and it's size will be given from console.
template <typename T>
T **allocateMatrix(const int rows, const int columns)
{
  if (rows == 0 || columns == 0)
  {
    throw std::invalid_argument("Rows and Columns must be at least 1");
  }
  T **matrix = new T *[rows];
  for (int i = 0; i < rows; ++i)
    matrix[i] = new T[columns];
  return matrix;
}

template <typename T>
void deallocateMatrix(T **matrix, const uint rows, const uint columns)
{
  for (int i = 0; i < rows; ++i)
  {
    delete[] matrix[i];
  }
  delete[] matrix;
}

int **generateMatrixA(int lines, const int columns)
{
  std::srand(time(0));
  if (lines > columns)
  {
    // we shouldn't get here we need optimization algorithm at this point
    lines = columns;
  }
  int **matrix = allocateMatrix<int>(lines, columns);
  for (int i = 0; i < lines; i++)
  {
    std::cout << std::endl;
    for (int j = 0; j < columns; j++)
    {
      matrix[i][j] = std::rand() & 1+2+4; // we make numbers smaller
      std::cout << matrix[i][j] << " ";
    }
  }
  std::cout << std::endl;
  return matrix;
}

void swapRows(int *array1, int *array2, const int elements)
{
  for (int i = 0; i < elements; i++)
  {
    std::swap(array1[i], array2[i]);
  }
}

void printZerosBeforeNumber(int element, const int size)
{
  int numberOfZeros = 0;
  while (element > 10)
  {
    numberOfZeros++;
    element = element / 10;
  }
  for (int i = 0; i < size - numberOfZeros; i++)
  {
    std::cout << " ";
  }
}

void printArray(int *Array, const int rows, const int numberOfCharsPerNumber = 5)
{
  for (int i = 0; i < rows; i++)
  {
    printZerosBeforeNumber(Array[i], numberOfCharsPerNumber);
    std::cout << Array[i] << " ";
  }
  std::cout << std::endl;
}

void printMatrix(int **A, const int rows, const int columns)
{
  std::cout << std::endl;
  for (int i = 0; i < rows; i++)
  {
    printArray(A[i], columns);
  }
  std::cout << std::endl;
}

void makeFirstElementNonZero(int **matrix, int rowOffset, int columnOffset, const int rows, const int columns)
{
  if (matrix[rowOffset][columnOffset]!=0)
  {
    return;
  }

  for (int i = 1; i < columns; i++)
  {
    if (matrix[rowOffset][columnOffset + i] != 0)
    {
      swapColumns(matrix, columnOffset, columnOffset + i, rows);
      return;
    }
  }
}

void addRows(int **A, const int targetRowIndex, const int sourceRowsIndex, const int elementsInRow, const float factor)
{
  for (int i = 0; i < elementsInRow; i++)
  {
    A[targetRowIndex][i] += A[sourceRowsIndex][i] * factor;
  }
}

void makeFirstElementOneAndOthersZero(int **matrix, int rowOffset, int columnOffset, const int rows, const int columns)
{
  if (matrix[rowOffset][columnOffset] != 1)
  {
    for (int i = 1; i < rows; i++)
    {
      if (matrix[rowOffset + i][columnOffset] != 0)
      {
        float factor = (float)(1 - matrix[rowOffset][columnOffset]) / (float)matrix[rowOffset + i][columnOffset];
        addRows(matrix, rowOffset, rowOffset + i, columnOffset+columns, factor);
      }
    }
  }
   
  for (int i = 1; i < rows; i++)
  {
    if (matrix[rowOffset + i][columnOffset] != 0)
    {
      float factor =  -(float)matrix[rowOffset + i][columnOffset] / (float)matrix[rowOffset][columnOffset];
      addRows(matrix, rowOffset + i, rowOffset, columnOffset+columns, factor);
    }
  }
}

void rowEchalon(int **matrix, int rowOffset, int columnOffset, const int rows, const int columns)
{
  if (rows >= 1 && columns >= 1)
  {
    std::cout << "Marime actuala a matricii considerate:" << rows << " " << columns << "  starting with index: " << rowOffset << " " << columnOffset;
    printMatrix(matrix, rowOffset + rows, columnOffset + columns);
    makeFirstElementNonZero(matrix, rowOffset, columnOffset, rows, columns);
    makeFirstElementOneAndOthersZero(matrix, rowOffset, columnOffset, rows, columns);
    rowEchalon(matrix, rowOffset + 1, columnOffset + 1, rows - 1, columns - 1);
  }
}

int main(int argc, char const *argv[])
{
    uint lines, columns;
  std::cout << "Number Of lines:" << std::endl;
  std::cin >> lines;
  std::cout << "Number Of columns:" << std::endl;
  std::cin >> columns;
  int **matrix = generateMatrixA(lines, columns);
  rowEchalon(matrix, 0, 0, lines, columns);
  deallocateMatrix<int>(matrix, lines, columns);
  return 0;
}
