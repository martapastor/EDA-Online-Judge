#include <iostream>
#include <string>
using namespace std;

void paresImpares (int v[], int n, bool &existe, int &p);
bool pares(int v[], int s, int t);
bool impares(int v[], int s, int t);

const int MAX_ELEMS = 10000;

int main() {

  int testcases, n;
  int v[MAX_ELEMS];

  cin >> testcases;

  for (int i = 0; i < testcases; i++) {
    cin >> n;

    if (n < MAX_ELEMS + 1) {
      for (int j = 0; j < n; j++) {
        cin >> v[j];
      }

      int p = 0;
      bool existe = false;

      paresImpares(v, n, existe, p);

      if (existe) {
        cout << "Si " << p << endl;
      }
      else {
        cout << "No" << endl;
      }
    }
  }

  // system("pause");

  return 0;
}

void paresImpares (int v[], int n, bool &existe, int &p) {
  int q = 0;

  while (q < n && v[q] % 2 == 0) {
    q++;
  }

  bool esPar = pares(v, 0, q);
  bool esImpar = impares(v, q, n);

  if (esPar && esImpar) {
    existe = true;
    p = q;
  }
  else {
    existe = false;
  }
}

bool pares(int v[], int s, int t) {
  bool esPar = true;
  for (int i = s; i < t; i++) {
    if (v[i] % 2 != 0) {
      esPar = false;
    }
  }

  return esPar;
}

bool impares(int v[], int s, int t) {
  bool esImpar = true;
  for (int i = s; i < t; i++) {
    if (v[i] % 2 == 0) {
      esImpar = false;
    }
  }

  return esImpar;
}
