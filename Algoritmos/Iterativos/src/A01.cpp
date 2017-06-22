#include <iostream>
#include <string>
using namespace std;

int mayorVidente(int v[], int n);
// bool esVidente (int v[], int k, int n);

const int MAX_ELEMS = 100000;

int main() {

  int testcases, n;
  int v[MAX_ELEMS];

  cin >> testcases;

  for (int i = 0; i < testcases; i++) {
    cin >> n;

    for (int j = 0; j < n; j++) {
      cin >> v[j];
    }

    int p = mayorVidente(v, n);
    if (p == -1) {
      cout << "No" << endl;
    }
    else {
      cout << "Si " << p << endl;
    }
  }

  return 0;
}

int mayorVidente(int v[], int n) {
  int sum = 0;

  for (int i = n - 1; i >= 0; i--) {
    if (v[i] == sum) {
      return i;
    }

    sum += v[i];
  }

  return -1;
}

/*
Esta solución es correcta pero no suficientmente eficiente:

int mayorVidente(int v[], int n) {
  int p = -1;

  for (int i = 0; i < n; i++) {
    if (esVidente(v, i, n)) {
      p = i;
    }
  }

  return p;
}

bool esVidente (int v[], int k, int n) {
  int sum = 0;

  for (int i = k + 1; i < n; i++) {
    sum += v[i];
  }

  if (sum == v[k]) {
    return true;
  }

  return false;
}
*/

// El algoritmo debe devolver el mayor elemento vidente del vector, es decir, el elemento situado
// más a la derecha del vector y que cumpla la condición de ser vidente (esto significa que no
// haya a su derecha otros elementos que cumplan la condición de ser videntes)

// Un elemento del vector es vidente si su valor es igual a la suma del valor de todos los
// elementos a su derecha.
