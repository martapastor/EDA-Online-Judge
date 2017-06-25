#include <iostream>
#include <string>
using namespace std;

int curvaConcava(long long int v[], int n);
int search(long long int v[], int n);
bool resuelve(int &n);

const int MAX_ELEMS = 1000000;

int main() {
	long long int *v = new long long int[MAX_ELEMS];
	int n;

	while (resuelve(n)) {
		for (int i = 0; i < n; i++) {
			cin >> v[i];
		}

		cout << curvaConcava(v, n) << endl;
	}

	delete[] v;

	return 0;
}

int curvaConcava(long long int v[], int n) {
  int min = -1, pos = -1, i = 1;
  bool minFound = false;

	if (n == 1) {
		pos = 0;
		min = v[0];
	}

	else {
		pos = search(v, n);
		min = v[pos];
	}

	if (pos == -1) { // El vector es entero estrictamente creciente
		min = v[0];
	}

  return min;
}

int search(long long int v[], int n) {
	int left, right, centre;

	left = -1;
	right = n;

	while (right != left + 1) {
		centre = (left + right) / 2;
		if (v[centre - 1] < v[centre]) {
			right = centre;
		}
		else {
			left = centre;
		}
	}

	return left;
 }

 bool resuelve(int &n) {
   cin >> n;

   if (!cin) {
     return false;
   }

   return true;
 }
