#include <iostream>
#include <string>
#include <stdexcept>
#include <time.h>
// This is a simple exercise of Cpp
// The goal of this progream will be to bring a linear system of equations into a Row-Echalon form.
// The matrix will be randomly generated and it's size will be given from console.
template <typename T> T** allocateMatrix(int rows,int columns){
  if (rows == 0 || columns == 0)
    {
      throw std::invalid_argument("Rows and Columns must be at least 1");
    }
    T **matrix = new T *[rows];
    for (int i = 0; i < rows; ++i)
      matrix[i] = new T[columns];
    return matrix;
}

template <typename T> void deallocateMatrix(T** matrix,uint rows,uint columns)
  {
    for (int i = 0; i < rows; ++i)
    {
      delete[] matrix[i];
    }
    delete[] matrix;
  }

int **generateMatrixA(int lines, int columns)
{
  if (lines > columns)
  {
    // we shouldn't get here we need optimization algorithm at this point
    lines = columns;
  }
  int** matrix=allocateMatrix<int>(lines,columns);
  for (int i = 0; i < lines; i++)
  {
    std::cout<<std::endl;
    for(int j=0;j<columns;j++){
      matrix[i][j]=std::rand()&0xb00000111;// we make numbers smaller
      std::cout<<matrix[i][j]<<" ";
    }    
  }
  std::cout<<std::endl; 
  return matrix; 
}

int** rowEchalonMatrix(int** A,int rows,int columns,int** b){
  int** newA=allocateMatrix<int>(columns,columns);
  

  return newA;
}

int main(int argc, char const *argv[])
{
  std::srand(time(0));
  
  uint lines,columns;
  std::cout << "Number Of lines:" << std::endl;
  std::cin>>lines;
  std::cout << "Number Of columns:" << std::endl;
  std::cin>>columns;
  int** matrix=generateMatrixA(lines,columns);

  deallocateMatrix<int>(matrix,lines,columns);
  return 0;
}