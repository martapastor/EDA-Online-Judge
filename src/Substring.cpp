#include <iostream>
#include <string>
using namespace std;

bool substring(char v1[], char v2[], int l1, int l2, int &a, int &b);

const int MAX_ELEMS = 1000;

int main() {
	char v1[MAX_ELEMS], v2[MAX_ELEMS];
	int l1, l2;

	cin >> l1 >> l2;

	while (l1 != 0) {
		for (int i = 0; i < l1; i++) {
			cin >> v1[i];
		}

		for (int j = 0; j < l2; j++) {
			cin >> v2[j];
		}

		int a = 0, b = 0;

		if (substring(v1, v2, l1, l2, a, b)) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}

		cin >> l1 >> l2;
	}

	return 0;
}

bool substring(char v1[], char v2[], int l1, int l2, int &a, int &b) {
	bool isSubstring = false;

	// Caso base
	if (l2 == 1) {
		for (int i = 0; i < l1; i++) {
			if (v2[0] == v1[i]) {
				a = i;
				b = 0;
				return true;
			}
		}
	}
	else {
		isSubstring = substring(v1, v2, l1, l2 - 1, a, b);

		isSubstring = isSubstring && (v1[a + 1] == v2[b + 1]);

		if (!isSubstring && v1[a] == v1[a + 1]) {
			a++;
			return true;
		}
		else if (isSubstring) {
			a++;
			b++;
			return true;
		}
		else {
			return false;
		}
	}

	return isSubstring;
}

/*
SPECIFICATION:
{0 < l2 <= l1 <= 100}

func substring (char v1[], char v2[], int l1, int l2, int &a, int &b)
return bool isSubstring;

{isSubstring = (for all)i: 0 <= i < l2 - 1: (exist)j: 0 <= j < l1 - 1:
v2[i] == v1[j] && v2[i+1] = v1[j+1]}
*/

/*
COMPLEXITY:
Tamaño de los datos: n = l1; m = l2

T(n) = 	n								si m = 0
				T(n - 1) + c*n	si m > 0

				a = 1; b = 1; k = 1

				Como a = 1 : O(n^(k+1)) : O(n^2)
*/
