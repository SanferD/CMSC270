#include <iostream>
#include <fstream>
#include <string>

// Swap the items in locations i and j
// of the array A.
template <typename T>
void swap(T *first,T *second)
{
    T temp=*first;
    *first=*second;
    *second=temp;
}

template <typename T>
void selectionSort(T *begin,T *end)
{
    for(T *start=begin;start<end;start++)
    {
        T *min=start;
        for(T *check=start+1;check<end;check++)
            if(*check<*min) min=check;
        swap(min,start);
    }
}

// creates a file of randomly generated positive integers, num in total,
// starting at min and ending at max.
void fillFile(std::string fName,int num,int min,int max)
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

int main()
{
  std::ifstream in;
  std::ofstream out;

  int N = 100;
  int n = 0;
  int k;
  int* A = new int[N];

  std::string path = "C:/Programs/CMSC270/Assignment1/";
  std::cout << "Path is: " << path << std::endl;

  //generate a file of 1000 integers between -100 and 100.
  fillFile(path+"numbers.txt",1000,-100,100);
  in.open(path+"numbers.txt");

  int x;
  while(in >> x)
  {
    // Resize the A array if needed.
    if(n == N)
    {
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

  selectionSort(A,A+n);

  out.open(path+"sorted.txt");
  for(k = 0;k < n;k++)
    out << A[k] << std::endl;
  out.close();

  delete[] A;

  std::cout << "Done sorting and saving." << std::endl;

  return 0;
}
