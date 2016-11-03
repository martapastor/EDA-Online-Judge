#include <iostream>
#include <cmath>
using namespace std;

bool illuminati(long long int v[], int n);
int fib(int i);

const int MAX_ELEMS = 100;

int main() {
  int n;
  long long int v[MAX_ELEMS];

  cin >> n;

  while (n != 0) {
    for (int i = 0; i < n; i++) {
      cin >> v[i];
    }

    if (illuminati(v, n)) {
      cout << "YES" << endl;
    }
    else {
      cout << "NO" << endl;
    }

    cin >> n;
  }

  return 0;
}


bool illuminati(long long int v[], int n) {
  bool isIlluminati = true;

  for (int i = 0; i < n; i++) {
    if(v[i] < fib(i)) {
      isIlluminati = false;
    }
  }

  return isIlluminati;
}

int fib(int n) {
  int i = 1, j = 0, tmp;

  for (int k = 0; k < n; k++) {
    tmp = i + j;
    j = i;
    i = tmp;
  }

  return j;
}

/*
SPECIFICATION:

{0 <= n <= 100 & length(v) = n}

func illuminati(int v[], int n) return bool r

{r = (for all)i: 0 <= i < n: v[i] >= fib(i)}

*/

/*

{n >= 0}

func fib(int i) return int n

{n = fib(i)}

*/
