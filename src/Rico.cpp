#include <iostream>
#include <string>
using namespace std;

int cuandoRico(int n);

const int MAX_ELEMS = 100000;

int main() {
  int testcases, n;

  cin >> testcases;

  for (int i = 0; i < testcases; i++) {
    cin >> n;

    cout << cuandoRico(n) << endl;
  }

  return 0;
}

int cuandoRico(int n) {
  int numDias = 2, total = 2, pos = 2;
  long int v[MAX_ELEMS];

  v[0] = 1;
  v[1] = 1;

  if (n == 0) {
    numDias = 0;
  }

  else if (n == 1) {
    numDias = 1;
  }
  else if (n  == 2) {
    numDias = 2;
  }
  else {
    numDias = 2;

    while (total < n) {
      v[pos] = 2 * v[pos - 2] + v[pos - 1];

      total += v[pos];

      pos++;
      numDias++;
    }
  }

  return numDias;
}
