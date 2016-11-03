#include <iostream>
#include <string>
using namespace std;

bool menores(int a[], int n, int p);

const int MAX_ELEMS = 10000;

int main() {
  int testcases, n;
  int a[MAX_ELEMS];

  cin >> testcases;

  for (int i = 0; i < testcases; i++) {
    cin >> n;

    if (n < MAX_ELEMS + 1) {
      for (int j = 0; j < n; j++) {
        cin >> a[j];
      }

      int pos = -1;

      for (int i = 0; i < n; i++) {
        if (menores(a, n, i)) {
          int cont = 0;

          for (int j = 0; j < i; j++) {
            if (!menores(a, n, j)) {
              cont++;
            }
          }

          if (cont == i) {
            pos = i;
          }
        }
      }

      cout << pos << endl;
    }
  }

  //system("pause");

  return 0;
}

bool menores(int a[], int n, int p) {
  bool isCorrect = true;

  for (int i = 0; i < p + 1; i++) {
    for (int j = p + 1; j < n; j++) {
      if (a[i] > a[j] || a[i] == a[j]) {
        isCorrect = false;
      }
    }
  }

  return isCorrect;
}
