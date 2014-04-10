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
  cout << "Return 1 = " << examplefunction() << endl;
  cout << "Return 2 = " << examplefunction() << endl;
  if(argc > 0) {
	int i = 0;
	for(i = 0; i < argc; i++) {
		cout << "Input " << i << " = " << argv[i] << endl;
	}
  }
  
  return 0;
}
