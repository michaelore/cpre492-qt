#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

// Function that will compute the parallel data
int examplefunction()
{
    double j = 0.0;
    for(int i = 0; i < 100000000; i++) {
        j += pow(1.0, i);
    }
    //std::cerr << "Hello World!";
    return j;
}

int main(int argc, char *argv[])
{
  // Compute result
  cout << "Return 1 = " << examplefunction();
  cout << "Return 2 = " << examplefunction();
  
  return 0;
}
