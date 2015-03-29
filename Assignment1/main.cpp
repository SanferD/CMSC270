#include <iostream>
#include <fstream>
#include <string>

// Sort the items between begin and end.
// end should point just past the end of the
// range of values being sorted.
template <typename T>
void sort(T *begin,T *end)
{
  // Sort the array using insertion sort
  T *mover = begin; // mover points to the element being inserted.
  mover++;
  while(mover != end) {
    T value = *mover; // The value of the item being inserted
    // The current pointer will scan through the part of the array
    // that appears before the mover location.
    T *current = mover;
    while(current != begin) {
      // previous points to the location before current
      T *previous = current;
      previous--;
      // As long as we keep seeing numbers that are greater than
      // the value we are inserting, we will keep moving things
      // aside to make room for the value we want to insert.
      if(*previous > value) {
        *current = *previous;
        current--;
      } else
        break;
    }
    // Drop the value into place and move on to the next
    // item to insert.
    *current = value;
    mover++;
  }
}

// Swap the items in locations i and j
// of the array A.
template <typename T>
void swap(T *A,int i, int j)
{
  int temp = *(A + i);
  *(A + i) = *(A + j);
  *(A + j) = temp;
}

template <typename T>
void selectionSort(T *A,int N)
{
  for(int k=0; k< N;k++) {
    int min = k;
    for(int n = k+1; n < N; n++){
      if (*(A + n) < *(A + min) ) {
        min = n;
      }
    }
    swap(A,min,k);
  }
}

// creates a file of randomly generated positive integers, num in total,
// starting at min and ending at max.
void fillFile(std::string fName, int num,
              unsigned int min, unsigned int max)
{
    std::ofstream out;
    out.open(fName);

    for(int i=0;i!=num;i++)
    {
        int val = (min<max) ? std::rand() % (max-min) + min
                            : std::rand() % (min-max) + max;
        out << val << std::endl;
    }
}

int main (int argc, const char * argv[])
{
  std::ifstream in;
  std::ofstream out;

  int N = 100;
  int n = 0;
  int k;
  int* A = new int[N];

  std::string path = "C:/Programs/CMSC270/Assignment1/";
  std::cout << "Path is: " << path << std::endl;


  fillFile(path+"numbers.txt",666,21,270);
  in.open(path+"numbers.txt");

  int x;
  while(in >> x) {
    // Resize the A array if needed.
    if(n == N) {
      int* B = new int[2*N];
      for(k = 0;k < n;k++)
        B[k] = A[k];
      delete[] A;
      A = B;
      N *= 2;
    }
    A[n] = x;
    n++;
  }
  in.close();

  std::cout << "Read " << n << " integers from the file." << std::endl;

  selectionSort(A,n);

  out.open(path+"sorted.txt");
  for(k = 0;k < n;k++)
    out << A[k] << std::endl;
  out.close();

  delete[] A;

  std::cout << "Done sorting and saving." << std::endl;

  return 0;
}
