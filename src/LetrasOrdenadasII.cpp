#include <iostream>
#include <string>
using namespace std;

int letrasOrdenadas(string word);

int main() {
	string testcase;

	cin >> testcase;

	while (testcase != "XXX") {

		cout << testcase.length() << " " << letrasOrdenadas(testcase) << endl;

		cin >> testcase;
	}

	//system("pause");

	return 0;
}

int letrasOrdenadas(string word) {
	int num = 0, max = 0;

	if (word.length() == 1) {
		return 1;
	}

	for (unsigned i = 0; i < word.length() - 1; i++) {
		if (word.at(i) < word.at(i+1)) {
			num++;

			if (num >= max) {
				max = num + 1;
			}
		}
		else if (word.at(i) > word.at(i+1) || word.at(i) == word.at(i+1)) {
			if (num >= max) {
				max = num + 1;
			}

			num = 0;
		}

	}

	return max;
}
