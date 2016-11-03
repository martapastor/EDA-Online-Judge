#include <iostream>
#include <string>
using namespace std;

void convexCurve(long long int v[], int n, int &pos, long long int &min);
int search(long long int v[], int n);

const int MAX_ELEMS = 1000000;

int main() {
	long long int *v = new long long int[MAX_ELEMS];
	int n, pos = -1;
	long long int min = -1;

	cin >> n;

	while (n != 0) {
		for (int i = 0; i < n; i++) {
			cin >> v[i];
		}

		convexCurve(v, n, pos, min);

		cout << pos << " " << min << endl;

		cin >> n;
	}

	delete[] v;

	return 0;
}

void convexCurve(long long int v[], int n, int &pos, long long int &min) {
	bool minFound = false;
	int i = 1;


	if (n == 1) {
		pos = 0;
		min = v[0];
	}

	/*
	else if (v[i-1] < v[i]) {
		pos = 0;
		min = v[0];
	}
	else {
		while (!minFound && i < n) {
			if (v[i - 1] > v[i] && v[i] <= v[i + 1]) {
				pos = i;
				min = v[i];
				minFound = true;
			}
			else {
				i++;
			}
		}

		if (v[n-2] > v[n-1]) {
			pos = n - 1;
			min = v[n - 1];
		}
	}
	*/
	else {
		pos = search(v, n);
		min = v[pos];
	}

	if (pos == -1) { // El vector es entero estrictamente creciente
		pos = 0;
		min = v[pos];
	}
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


/*
SPECIFICATION:

{0 <= n <= 1000000}

proc convexCurve(in long long int v[], in int n, out int pos, out long long int min)

{(pos = (exist)i: 0 <= i < n: v[i] = search(v, n)) &&
 (min = search(v, n))}



search(long long int v[], int n) = (for all)i, j: 0 <= i <= j < n: (exist)k: i < k < j: v[i] > v[k] <= v[j]
*/
