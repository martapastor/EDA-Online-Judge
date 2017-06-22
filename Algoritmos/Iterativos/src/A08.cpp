#include <iostream>
using namespace std;

// bool resuelve(int &n, int *v[]);
void segmentoPares(int v[], int n, int &ini, int &fin, int &length);

const int MAX_ELEMS = 100000;

int main () {
  int testcases, n, v[MAX_ELEMS];
  int ini = 0, fin = 0, length = 0;

  cin >> testcases;

  for (int i = 0; i < testcases; i++) {
    cin >> n;

    for (int j = 0; j < n; j++) {
      cin >> v[j];
    }

    segmentoPares(v, n, ini, fin, length);

    if (length == 0) {
      cout << "Vacio" << endl;
    }
    else {
      cout << length << " -> [" << ini << "," << fin << ")" << endl;
    }

    ini = 0, fin = 0, length = 0;
  }

  return 0;
}

/*
bool resuelve(int &n, int *v[]) {
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> v[i];
  }

  if (!cin) {
    return false;
  }

  return true;
}
*/

void segmentoPares(int v[], int n, int &ini, int &fin, int &length) {
  int tmp_ini = -1, tmp_fin = -1, tmp_length = 0;

  for (int i = 0; i < n; i++) {
    if (v[i] % 2 == 0 && tmp_ini == -1) {
      tmp_length++;
      tmp_ini = i;
      tmp_fin = i + 1;
    }
    else if (v[i] % 2 == 0 && tmp_ini != -1) {
      tmp_length++;
      tmp_fin++;
    }
    else if (v[i] % 2 == 1) {
      tmp_length = 0;
      tmp_ini = -1;
      tmp_fin = -1;
    }

    if (tmp_length >= length) {
      length = tmp_length;
      ini = tmp_ini;
      fin = tmp_fin;
    }

  }
}
