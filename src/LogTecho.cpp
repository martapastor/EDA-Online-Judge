#include <iostream>
#include <string>
using namespace std;

int log (unsigned int b, unsigned int n);

int main() {
  int testcases;
  unsigned int b, n;

  cin >> testcases;

  for (int i = 0; i < testcases; i++) {
    cin >> b >> n;

    cout << log(b, n) << endl;
  }


  return 0;
}

int log(unsigned int b, unsigned int n) {
  int r;

  if (n == 1) {
    r = 0;
  }
  else if (n == b) {
    r = 1;
  }
  else {
    r = log(b, n / 2);
 
    r = r * r;

    if (n % 2 == 1) {
      r = r * b;
    }
  }

  return r;
}
