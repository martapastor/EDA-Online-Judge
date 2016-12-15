#include <iostream>
#include <string>
using namespace std;

void convexCurve(long long int v[], int n, int &pos, long long int &min);
int search(long long int v[], int a, int b);

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

	else {
		pos = search(v, 0, n - 1);
		min = v[pos];
	}
}

int search(long long int v[], int a, int b) {
	int left, right, centre;
	int pos;

	left = a;
	right = b;

	// Caso base:
	if (right <= left) {
		pos = left;
	}
	else {
		centre = (left + right) / 2;
		if (v[centre] < v[centre + 1]) {
			pos = search(v, left, centre);
		}
		else {
			pos = search(v, centre + 1, right);
		}
	}

	return pos;
}

/*
SPECIFICATION:

{0 <= n <= 1000000}

proc convexCurve(in long long int v[], in int n, out int pos, out long long int min)

{(pos = (exist)i: 0 <= i < n: v[i] = search(v, n)) &&
(min = minElem(v, n))}



search(long long int v[], int a, int b) = (for all)i, j: a <= i <= j < b: (exist)k: i < k < j: v[i] > v[k] <= v[j]
*/

/*
COMPLEXITY:
	search: O(log n)
	main: O(n) as we have to load all the elements in the array
*/
