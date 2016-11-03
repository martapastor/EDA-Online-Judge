#include <iostream>
#include <string>
using namespace std;

int colones(int v[], int n);

int main() {
  int testcases, n;
  int v[100000];

  cin >> testcases;

  for (int i = 0; i < testcases; i++) {
    cin >> n;

    for (int j = 0; j < n; j++) {
      cin >> v[j];
    }

    cout << colones(v, n) << endl;
  }

  return 0;
}

int colones(int v[], int n) {
  int num = 0;
  bool encontrado = false;

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

  return num;
}

/*
SPECIFICATION:

{0 <= n <= 10000}

func colones(int v[], int n) return int num

{num = #i: 0 <= i <= n: (exists)j: i < j < n: v[i] > v[j]}

*/
