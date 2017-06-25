#include <iostream>
using namespace std;

int iterativeMissing(int v[], int n1, int n2);

const int MAX_ELEMS = 100000;

int main() {

  int testcases, n1, n2;
  int v[MAX_ELEMS];

  cin >> testcases;

  for (int i = 0; i < testcases; i++) {
    cin >> n1 >> n2;
    int n = n2 - n1;
    for (int j = 0; j < n; j++) {
      cin >> v[j];
    }

    cout << iterativeMissing(v, n1, n2) << endl;
  }

  return 0;
}

// Iterative solution
int iterativeMissing(int v[], int n1, int n2) {
  int preso = n2, n = n2 - n1, tmp = n1;

  for (int i = 0; i < n; i++) {
    if (v[i] != tmp) {
        return tmp;
    }

    tmp++;
  }

  return preso;
}
