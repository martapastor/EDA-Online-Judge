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

	for (unsigned i = 0; i < word.length() - 1; i++) {
		if(word.at(i) < word.at(i+1)) {
			num++;
		}
		else if ((word.at(i) > word.at(i+1) || word.at(i) == word.at(i+1)) && max <= num) {
			max = num + 1;
			num = 0;
		}
		else if (word.at(i) > word.at(i+1) || word.at(i) == word.at(i+1)) {
			num = 0;
		}
	}

	if (num > 0 && max == 0) { // Si todas las letras están ordenadas
		max = num + 1;
	}

	return max;
}
