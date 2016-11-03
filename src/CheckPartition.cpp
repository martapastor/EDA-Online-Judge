#include <iostream>
#include <string>
using namespace std;

bool checkPart(int a[], int n, int p);

const int MAX_ELEMS = 10000;

int main() {

  int testcases, n, p;
  int a[MAX_ELEMS];

  cin >> testcases;

  for (int i = 0; i < testcases; i++) {
    cin >> n;
    cin >> p;

    if (n < MAX_ELEMS) {
      for (int j = 0; j < n; j++) {
        cin >> a[j];
      }

      bool isCorrect = checkPart(a, n, p);

      if (isCorrect) {
        cout << "SI" << endl;
      }
      else {
        cout << "NO" << endl;
      }
    }
  }

    //system("pause");

  return 0;
}

bool checkPart(int a[], int n, int p) {
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
