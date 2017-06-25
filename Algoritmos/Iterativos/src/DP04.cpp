#include <iostream>
using namespace std;

void longerMeseta(int v[], int n, int &ini, int &fin);

const int MAX_ELEMS = 100000;

int main() {
  int n, v[MAX_ELEMS];
  int ini, fin;

  cin >> n;

  while (n != 0) {
    for (int i = 0; i < n; i++) {
      cin >> v[i];
    }

    ini = 0, fin = 0;

    longerMeseta(v, n, ini, fin);
    cout << ini << " " << fin << endl;

    cin >> n;
  }

  return 0;
}

void longerMeseta(int v[], int n, int &ini, int &fin) {
  int tmpIni = n - 1, tmpFin = n - 1, tmpLength = 0, length = 0;

  for (int i = n - 1; i > 0; i--) {
    if (v[i] == v[i - 1]) {
      tmpIni = i - 1;
      tmpLength++;
    }
    else {
      if (tmpLength >= length) {
        ini = tmpIni;
        fin = tmpFin;
        length = tmpLength;
      }
      
      tmpIni = i - 1;
      tmpFin = i - 1;
      tmpLength = 0;
    }
  }

  if (tmpLength == n - 1) {
    ini = tmpIni;
    fin = tmpFin;
  }
  else if (tmpLength >= length) {
    ini = tmpIni;
    fin = tmpFin;
  }
  else if (ini == 1 && fin == 1) {
    ini = 0;
    fin = 0;
  }
}
