#include <iostream>
using namespace std;

int seriePotencias(int x, int n);
bool resuelve(int &x, int &n);

int main() {
  int x, n;

  while (resuelve(x, n)) {
    cout << seriePotencias(x, n) << endl;
  }

  return 0;
}

int seriePotencias(int x, int n) {
	int suma = 0;
	int sumando = 1;

	for (int i = 0; i < n + 1; i++){
		suma = (suma*x+1) % 1000007;
	}

	return suma;
}

bool resuelve(int &x, int &n) {
  cin >> x >> n;

  if (!cin) {
    return false;
  }

  return true;
}
