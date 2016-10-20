#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAX_ELEMS = 10000;

void valoresAcumulados(int a[], int *b, long long int n, long long int &m);

int main() {
  int cases;
  int a[MAX_ELEMS];
  int b[MAX_ELEMS];

  cin >> cases;

  while (cases != 0) {
    int num;
    long long int n = 0, m = 0;

    a[n] = cases;
    n++;

    cin >> num;

    while(num != 0) {
      a[n] = num;
      n++;

      cin >> num;
    }

    valoresAcumulados(a, b, n, m);

    for (int j = 0; j < m - 1; j++) {
      cout << b[j] << " ";
    }
    cout << b[m-1] << endl;

    cin >> cases;
  }

  return 0;
}

void valoresAcumulados(int a[], int *b, long long int n, long long int &m) {
  b[0] = a[0];
  m = 1;

  for (int i = 1; i < n; i++) {
    b[i] = a[i] + b[i-1];
    m++;
  }
}
