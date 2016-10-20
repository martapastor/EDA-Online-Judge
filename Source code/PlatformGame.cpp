#include <iostream>
#include <string>
using namespace std;

int availableLadders(int v[], int n);

const int MAX_ELEMS = 10000;

/*
SPECIFICATION:

	{0 <= n <= 10000 & length(v) = n}

	fun availableLadders(int v[], int n) return int num;

	{num = (summation)i: 0 <= i < n: v[i] = ((summation)j: i < j < n: v[j])}

*/


int main() {
	int testcases, n, num;
	int v[MAX_ELEMS];

	cin >> testcases;

	for (int i = 0; i < testcases; i++) {
		cin >> n;

		if (n < MAX_ELEMS + 1) {
			for (int j = 0; j < n; j++) {
				cin >> num;

				v[j] = num;
			}

			int ladders = availableLadders(v, n);

			cout << ladders << endl;
		}
	}



	system("pause");

	return 0;
}

/*
int availableLadders(int v[], int n) {
	int tmp, ladders = 0;

	for (int i = 0; i < n; i++) {
		tmp = 0;

		for (int j = i + 1; j < n; j++) {
			tmp += v[j];
		}

		if (v[i] == tmp) {
			ladders++;
		}
	}

	return ladders;
}
*/

int availableLadders(int v[], int n) {
	int tmp = 0, ladders = 0;


	for (int i = 0; i < n; i++) {
		tmp += v[i];
	}

	for (int j = 0; j < n; j++) {
		if (v[j] == tmp - v[j]) {
			ladders++;
		}

		tmp -= v[j];
	}

	return ladders;
}

/*
INVARIANT:
	I = (0 <= n <= 10000) && (ladders = (summation)i: 0 <= i <= n: v[i] = ((summation)j: i < j <= n: v[j]))


*/


/*
TERMINATION FUNCTION:
	func(ladders, n) = n - ladders;


*/