#include <iostream>
using namespace std;

int numAbadias (int v[], int n);

const int MAX_ELEMS = 100000;

int main() {
  int n, v[MAX_ELEMS];

  cin >> n;

  while (n != 0) {
    for (int i = 0; i < n; i++) {
      cin >> v[i];
    }

    cout << numAbadias(v, n) << endl;

    cin >> n;
  }

  return 0;
}

int numAbadias (int v[], int n) {
  int total = 1, max = v[n - 1];

  for (int i = n - 1; i >= 0; i--) {
    if (v[i] > max) {
      max = v[i];
      total++;
    }
  }

  return total;
}
