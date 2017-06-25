#include <iostream>
#include <string>
using namespace std;

void numMaxs(long long int &n, long long int &max, int &cont);

int main() {

  int testcases, elems;

  cin >> testcases;

  for (int i = 0; i < testcases; i++) {
    long long int n = 0, max = 0;
    int cont = 0;
    cin >> elems;

    for (int j = 0; j < elems; j++) {
      cin >> n;

      numMaxs(n, max, cont);
    }

    cout << max << " " << cont << endl;
  }

  //system("pause");

  return 0;
}

void numMaxs(long long int &n, long long int &max, int &cont) {
  if (n > max) {
    max = n;
    cont = 1;
  }
  else if (n == max) {
    cont++;
  }
}


/*
SPECIFICATION:

{n >= 0 && }

proc numMaxs(long long int &n, int &max)

{}

*/
