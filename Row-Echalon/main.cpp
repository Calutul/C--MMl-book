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

int partition(int arr[], int start, int end)
{
 
    int pivot = arr[start];
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    std::swap(arr[pivotIndex], arr[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (arr[i] <= pivot) {
            i++;
        }
 
        while (arr[j] > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            std::swap(arr[i++], arr[j--]);
        }
    }
 
    return pivotIndex;
}
 
void quickSort(int arr[], int start, int end)
{
 
    // base case
    if (start >= end)
        return;
 
    // partitioning the array
    int p = partition(arr, start, end);
 
    // Sorting the left part
    quickSort(arr, start, p - 1);
 
    // Sorting the right part
    quickSort(arr, p + 1, end);
}

void swapColumns(int** A,int column1,int column2,int elements){
  for(int i=0;i<elements;i++){
    std::swap(A[i][column1],A[i][column2]);
  }
}

void swapRows(int* array1,int* array2,int elements){
  for(int i=0;i<elements;i++){
    std::swap(array1[i],array2[i]);
  }
}

void printMatrix(int** A,int rows,int columns){
  std::cout<<std::endl<<" The value of the A matrix is:"<<std::endl;
  for (int i = 0; i < rows; i++)
  {
    std::cout<<std::endl;
    for(int j=0;j<columns;j++){
      std::cout<<A[i][j]<<" ";
    }    
  }
  std::cout<<std::endl;
}

int indexOfMaxValueFromArray(int* array,int elements){
  int max=array[0];
  int index=0;
  for(int i=0;i<elements;i++){
    if(array[i]>max){
      max=array[0];
      index=i;
    }
  }
  return index;
}


void rearrangeMatrixForRowEchalon(int** A,const int rows,const int columns){
  int* numberOfZerosOnRow=new int[rows]();
  int* numberOfZerosOnColumns=new int[columns]();
    for(int i=0;i<rows;i++){
    for(int j=0;j<columns;j++){
      if(A[i][j]==0){
        numberOfZerosOnRow[i]++;
        numberOfZerosOnColumns[i]++;
      }
    }
  }
  //quickSort(numberOfZerosOnRow,0,rows);
  //quickSort(numberOfZerosOnColumns,0,rows);
  for(int i=rows;i>0;i--){
    int maxindex=indexOfMaxValueFromArray(numberOfZerosOnRow,i);
     if(maxindex!=i){
        swapRows(A[i],A[maxindex],columns);
     }
  }
  printMatrix(A,rows,columns);
  for(int i=0;i<columns;i++){
    int maxindex=indexOfMaxValueFromArray(numberOfZerosOnColumns+i,columns-i);
     if(maxindex!=0){
        swapColumns(A,i,maxindex+i,rows);
     }
  }
  printMatrix(A,rows,columns);
}

void rowEchalonMatrix(int** A,const int rows,const int columns){
  rearrangeMatrixForRowEchalon(A,rows,columns);
  for(int i=1;i<rows;i++){
    for(int j=0;j<i-1;j++){
      
    }
  }


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
  rowEchalonMatrix(matrix,lines,columns);
  deallocateMatrix<int>(matrix,lines,columns);
  return 0;
}