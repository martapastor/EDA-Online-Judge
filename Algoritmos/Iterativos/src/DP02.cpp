#include <iostream>
#include <string>
using namespace std;

void inter(int v[], int n, int &pares, int &impares);

const int MAX_ELEMS = 10000;

int main() {
  int n, v[MAX_ELEMS];

  cin >> n;

  while (n != 0) {
    for (int i = 0; i < n; i++) {
      cin >> v[i];
    }

    int pares = 0, impares = 0;

    inter(v, n, pares, impares);
    cout << pares << " " << impares << endl;

    cin >> n;
  }

  return 0;
}

void inter(int v[], int n, int &pares, int &impares) {
  for (int i = 1; i < n - 1; i++) {
    if (v[i - 1] % 2 == 0 && v[i + 1] % 2 == 0) {
      pares++;
    }
    else if (v[i - 1] % 2 == 1 && v[i + 1] % 2 == 1) {
      impares++;
    }
  }

}
