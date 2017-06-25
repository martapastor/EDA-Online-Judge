#include <iostream>
#include <string>
using namespace std;

int suma(int v[], int n);
int cuantas(int v[], int n, int suma);

const int MAX_ELEMS = 100000;

int main() {
  int n, sum, total;
  int v[MAX_ELEMS];

  cin >> n;

  while (n != 0) {
    for (int i = 0; i < n; i++) {
      cin >> v[i];
    }

    sum = suma(v, n);
    total = cuantas(v, n, sum);

    cout << total << endl;

    cin >> n;
  }

  return 0;
}

int suma(int v[], int n) {
  int s = 0;

  for (int i = 0; i < n; i++) {
    s += v[i];
  }

  return s;
}

int cuantas(int v[], int n, int suma) {
  int num = 0, sum = 0;

  for (int i = 0; i < n; i++) {
    if (suma - sum == suma - (suma - sum)) {
      num++;
    }

    sum += v[i];
  }

  if (suma - sum == suma - (suma - sum)) {
    num++;
  }

  return num;
}

/*

{0 <= n <= 100000 & length(v) = n}

func suma(int v[], int n) return int s;

{s = (summation)i: 0 <= i < n: v[i]}

*/

/*

{0 <= n < 100000 & length(v) = n}

func cuantas(int v[], int n) return int num

{num = #i: 0 <= i < n: }

*/
