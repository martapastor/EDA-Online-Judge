#include <iostream>
using namespace std;

bool gradient(int ini, int fin, int v[]);
int gradientSum(int ini, int fin, int v[]);
bool resuelve(int &n, int &m);

const int MAX_ELEMS = 1048576;

int main() {
  int n, m;
  int v[MAX_ELEMS];

  bool isGradient = true;

  while (resuelve(n, m)) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> v[j];
      }

      isGradient = isGradient && gradient(0, m, v);
    }

    if (isGradient) {
      cout << "YES" << endl;
    }
    else {
      cout << "NO" << endl;
    }

    isGradient = true;
  }

  return 0;
}

bool gradient(int ini, int fin, int v[]) {

  int dim = fin - ini;
  int half = (fin / 2) + (ini / 2);

  if (dim == 1) {
    return true;
  }
  else if (dim > 1) {
    bool leftHalf = gradient(ini, half, v);
    int leftSum = gradientSum(ini, half, v);

    bool rightHalf = gradient(half, fin, v);
    int rightSum = gradientSum(half, fin, v);

    if (leftHalf && rightHalf && leftSum < rightSum) {
      return true;
    }
  }

  return false;
}

int gradientSum(int ini, int fin, int v[]) {
  int sum = 0;

  for (int i = ini; i < fin; i++) {
    sum += v[i];
  }

  return sum;
}

bool resuelve(int &n, int &m) {
  cin >> n >> m;

  if (!cin) {
    return false;
  }

  return true;
}

/*
  SPECIFICATION:
  {0 < n && m < 1048576}

  func gradient(int ini, int fin, int v[]) return bool isGradient

  {isGradient = (i = (fin/2) + (ini/2)) : gradient(ini, i, v) && gradient(i, fin, v)
                && gradientSum(ini, i, v) < gradientSum(i, fin, v)}

  gradientSum (int ini, int fin, int v)= (summation)i : ini < i < fin : v[i]

*/

/*
  COMPLEXITY:

  T(n) =  const               si m = 1
          2 * T(n/2) + 2 * n  si m > 1

          a = 2, b = 2, k = 1

          Como a = b^k (2 = 2^1) : O(n^k * log n) : O(n * log n)

*/
