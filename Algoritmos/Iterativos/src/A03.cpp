#include <iostream>
#include <string>
using namespace std;

int colones(int v[], int n);

const int MAX_ELEMS = 100000;

int main() {
  int testcases, n;
  int *v = new int[MAX_ELEMS];

  cin >> testcases;

  for (int i = 0; i < testcases; i++) {
    cin >> n;

    for (int j = 0; j < n; j++) {
      cin >> v[j];
    }

    cout << colones(v, n) << endl;
  }

  delete[] v;

  return 0;
}

int colones(int v[], int n) {
  int num = 0;
  bool encontrado = false;

  /*
  for (int i = 0; i < n; i++) {
    int j = i + 1;
    while (!encontrado && j < n) {
      if (v[i] > v[j]) {
        encontrado = true;
        num++;
      }
      j++;
    }

    j = 0;
    encontrado = false;
  }
  */

  int min = v[n-1];

  for (int i = n - 2; i >= 0; i--) {
    if (v[i] < min) {
      min = v[i];
    }
    else if (v[i] > min) {
      num++;
    }
  }

  return num;
}

/*
SPECIFICATION:

{0 <= n <= 10000}

func colones(int v[], int n) return int num

{num = #i: 0 <= i <= n: (exists)j: i < j < n: v[i] > v[j]}

*/
