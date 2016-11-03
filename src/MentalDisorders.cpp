#include <iostream>
#include <string>
using namespace std;

int const MAX_STACK = 10000;
int const MAX_ELEM = 100000;

int mentalDisorders(int v[], int n);
int processTestCase();

int main() {

	/*
	int v1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int n1 = 10;

	int v2[] = { 2, 4, 6, 8 };
	int n2 = 4;

	int v3[] = { 1, 3, 5, 7 };
	int n3 = 4;

	int v4[] = { 2, 4, 6, 7, 8, 9 };
	int n4 = 6;

	cout << mentalDisorders(v1, n1) << endl;
	cout << mentalDisorders(v2, n2) << endl;
	cout << mentalDisorders(v3, n3) << endl;
	cout << mentalDisorders(v4, n4) << endl;
	*/

	int cases;
	cin >> cases;

	for (int i = 0; i < cases && cases < MAX_STACK; i++) {
		cout << processTestCase() << endl;
	}

	system("pause");

	return 0;
}

int processTestCase() {
	int n;
	cin >> n;

	int v[MAX_ELEM];
	for (int i = 0; i < n && n < MAX_ELEM; i++) {
		cin >> v[i];
	}

	return mentalDisorders(v, n);
}

int mentalDisorders(int v[], int n) {
	int counter = 0;

	for (int i = 0; i < n; i++) {
		if (v[i] % 2 == 0)
			counter++;
	}
	
	return counter;
}

/*
SPECIFICATION:

{n >= 0 & length(v) = n}

func mentalDisorders(int v[], int n) return int counter

{counter = (summation)i: 0 <= i < n: v[i] % 2 = 0}
*/