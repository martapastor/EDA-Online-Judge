#include <iostream>
using namespace std;

bool bongoExists (int v[], int n, int currentNum, int &num);

const int MAX_ELEMS = 100000;

int main() {
  int testcases, n, currentNum;
  int v[MAX_ELEMS];

  cin >> testcases;

  for (int i = 0; i < testcases; i++) {
    cin >> n >> currentNum;

    for (int j = 0; j < n; j++) {
      cin >> v[j];
    }

    int num = 0;

    if (bongoExists(v, n, currentNum, num)) {
      cout << num << endl;
    }
    else {
      cout << "NO" << endl;
    }
  }

  return 0;
}

// Iterative solution
bool bongoExists (int v[], int n, int currentNum, int &num) {
  bool exists = false;

  for (int i = 0; i < n; i++) {
    if (currentNum + i == v[i]) {
      num = v[i];
      return true;
    }
  }

  return exists;
}
