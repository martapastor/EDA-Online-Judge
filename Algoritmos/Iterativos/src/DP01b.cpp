#include <iostream>
using namespace std;

int log(int b, int n);

int main() {
  int testcases;
  int b, n;

  cin >> testcases;

  for (int i = 0; i < testcases; i++) {
    cin >> b >> n;

    cout << log(b, n) << endl;
  }

  return 0;
}

int log(int b, int n) {
  int r = 0, tmp = 1;

  while (tmp <= n) {
    if (tmp == 1) {
      tmp = b;
    }
    else {
      tmp *= b;
    }

    r++;
  }

  if (r == 0) {
    return r;
  }
  else {
    return r - 1;
  }
}
