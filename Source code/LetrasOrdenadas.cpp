#include <iostream>
#include <string>
using namespace std;

bool letrasOrdenadas(string word);

int main() {
	string testcase;

	cin >> testcase;

	while (testcase != "XXX") {

		if (letrasOrdenadas(testcase)) {
			cout << "SI" << endl;
		}
		else {
			cout << "NO" << endl;
		}

		cin >> testcase;
	}

	system("pause");

	return 0;
}

bool letrasOrdenadas(string word) {
	bool exists = true;

	for (unsigned i = 0; i < word.length() - 1; i++) {
		if(word.at(i) > word.at(i+1)) {
			exists = false;
		}
	}

	return exists;
}
