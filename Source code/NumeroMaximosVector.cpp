#include <iostream>
#include <string>
#include <climits>
using namespace std;

void numMaxs(int v[], int elems, int &max, int &cont);

int main() {

  int testcases, elems;
  int v[20000];

  cin >> testcases;

  for (int i = 0; i < testcases; i++) {
    cin >> elems;

    int n;
    for (int j = 0; j < elems; j++) {
      cin >> n;
      v[j] = n;
    }

    int max = v[0];
    int cont = 1;
    numMaxs(v, elems, max, cont);

    cout << max << " " << cont << endl;
  }

  //system("pause");

  return 0;
}

void numMaxs(int v[], int elems, int &max, int &cont) {
  for (int i = 1; i < elems; i++) {
    if (v[i] > max) {
      max = v[i];
      cont = 1;
    }
    else if (v[i] == max) {
      cont++;
    }
  }
}


/*
SPECIFICATION:

{n >= 0 && }

proc numMaxs(long long int &n, int &max)

{}

*/
