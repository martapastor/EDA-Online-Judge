#include <iostream>
#include <string>
using namespace std;

int esValle(int v[], int n);
int esPico(int v[], int n);

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

      int valle = esValle(v, n);
      int pico = esPico(v, n);

      cout << pico << " " << valle << endl;
    }

  }

  //system("pause");

  return 0;
}

int esValle(int v[], int n) {
  int cont = 0;

  for (int i = 1; i < n-1; i++) {
    if (v[i] < v[i-1] && v[i] < v[i+1]) {
      cont++;
    }
  }

  return cont;
}

int esPico(int v[], int n) {
  int cont = 0;

  for (int i = 1; i < n-1; i++) {
    if (v[i] > v[i-1] && v[i] > v[i+1]) {
      cont++;
      //cout <<  "Picos contados:" << cont << "    -1: " << v[i-1] << "    +1: " << v[i+1] << endl;
    }
  }

  return cont;
}
