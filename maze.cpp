#include <iostream>;
#include <string>
using namespace std;

string changeString(string string1, string string2) {
	for (int i = 0; i != string2.size(); i++) { // run through delimeters
		for (int k = 0; k != string1.size(); k++) { // run through all characters of string to delimit
			if (string1[k] == string2[i]) {
				string1[k] = ' ';
			}
		}
	}
	return string1;
}

void findRun(string string1, bool toLowerCase) {
	if (toLowerCase) {
		for (int i = 0; i != string1.size(); i++){
			string1[i] = tolower(string1[i]);
}
	}
	int runlength = 0;
	int maxlength = 0;
	char letter = ' ';
	for (int k = 0; k != string1.size(); k++) {
		while (string1[k] == string1[k + 1]) {
			runlength++;
			k++;
		}
		if (runlength > maxlength) {
			maxlength = runlength;
			letter = string1[k - 1];
			runlength = 0;
		}
	}
	cout << letter;
}

int main() {
	int swatch = 1;
		if (swatch == 0) {
			string a;
			a = changeString("ShouldeHIstartemylab?", "He");
			cout << a;
		}
		else if (swatch == 1) {
			string input1 = "abbccccdda";
			string input2 = "aAabbb";
			bool f = 0;
			findRun(input2, 1);

		}
}

