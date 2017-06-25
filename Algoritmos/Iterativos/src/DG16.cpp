#include <iostream>
using namespace std;

int xxxx(int v[], int n);

const int MAX_ELEMS = 100000;

int main() {

  int testcases, n, v[MAX_ELEMS];

  cin >> testcases;

  for (int i = 0; i < testcases; i++) {
    cin >> n;

    for (int j = 0; j < n; j++) {
      cin >> v[j];
    }

    cout << xxxx(v, n) << endl;  
  }

  return 0;
}

int xxxx(int v[], int n) {
  int sum = 0;
  int max = v[0], rep = 1;

  for (int i = 1; i < n; i++) {
    if (v[i] > max) {
      sum += max * rep;

      max = v[i];
      rep = 1;
    }
    else if (v[i] == max) {
      rep++;
    }
    else {
      sum += v[i];
    }
  }

  return sum;
}

// La función xxxx devuelve la suma de los elementos que verificación la condición de que
// el elemento en dicha posición no sea un máximo, es decir, que no sea el elemento más alto
// en el array.
