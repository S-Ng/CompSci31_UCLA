#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

bool decrypt(const char ciphertext[], const char crib[]);
void cleanCstring(const char dirtyCstring[], char cleanCstring[]);
bool isCribCorrect(const char ciphertext[], const char translator[], const char cleanCrib[]);
int letterIndex(char toFind, const char toSearch[]);
//*/

int main() {
	
	char crib[] = "   hush???hUSh---     --- until    JanuARY !!  "; // test nonletter character cleaning and case management
	char cipher[] = "DiebjiggK, zyxZYXzyx--Abca abCa    bdefg## $$hidbijk6437 wvuWVUwvu\n\n8 9\n";
	assert(decrypt(cipher, crib));

	char crib2[] = "   hsh???hUSh---     --- until    JanuARY !!  "; // confirm a nonexistent crib gives false
	assert(!decrypt(cipher, crib2));
	
	char crib3[] = "conspiracy theory"; // test no words (gives false)
	char cipher3[] = "";
	assert(!decrypt(cipher3, crib3));

	char crib4[] = "conspiracy theory"; // test longer phrase
	char cipher4[] = "Zysqjs zbguncyqzo jdsbyo eybmnu bg Wqzsvbbf.\nUnysqx eybmgxrsuu ymtbyu kcq Jicjjsy.\nNbuj sajysts rcvsyqr qgx sajysts zbgusykqjcks nbucjcbgu bg xcuzmuucbg wbymtu.\nZU 31 cu zdqrrsgecge!";
	assert(decrypt(cipher4, crib4));

	char crib5[] = "alan turing"; // test span over new line (gives false)
	char cipher5[] = "bwra wmwt\nqeirtk spst\n";
	assert(!decrypt(cipher5, crib5));

	char crib6[] = "alan turing"; // test span over new line (gives false)
	char cipher6[] = "bwra wmwt\nqeirtk spst\n";
	assert(!decrypt(cipher6, crib6));
	
	assert(decrypt("kvbz pqzzyfq bz zqxjqk", "secret")); // test 1 writes kvCREpSRRyfSECRERSxjSk
	assert(!decrypt("kvbz pqzzyfq bz gqbjw", "secret")); // test 2

	//decrypt("kvbz pqzzyfq bz zqxjqk", "secret");

	cout << "all tests passed" << endl;

	//*/
}


bool decrypt(const char ciphertext[], const char crib[]) {

	// Clean crib and chipher
	char cleanCrib[81];
	cleanCstring(crib, cleanCrib);

	char cleanCipher[81*60+1];
	cleanCstring(ciphertext, cleanCipher);

	if (cleanCrib[0] == '\0' || strlen(crib) > 80) // crib is empty string, or longer than 80 characters return false. do not print
		return false;

	// Identify crib location in ciphertext
	int cipherStart = 0;
	char translator[27];

	while (ciphertext[cipherStart] != '\0') { // ciphertext is not at end
		char abc[] = "abcdefghijklmnopqrstuvwxyz";
		strcpy(translator, abc); // reset translator
		int cribLoc = 0;
		for (int i = cipherStart; cleanCrib[cribLoc] != '\0'; i++) { // iterate through cipher distance of crib
			int letter = letterIndex(tolower(cleanCrib[cribLoc]), abc); // get index of letter in crib
			if (letter >= 0 /*&& isalpha(cleanCipher[i])/*&& toupper(cleanCrib[cribLoc]) == toupper(translator[letter])*/) { // letter in translator not already assigned
				translator[letter] = toupper(cleanCipher[i]); // assign cipher text letter into translator
				abc[letter] = toupper(abc[letter]);
			}
			cribLoc++;
		}
		if (isCribCorrect(cleanCipher, translator, cleanCrib)) {
			char output[81 * 60 + 1];
			strcpy(output, ciphertext);
			for (int k = 0; output[k] != '\0'; k++)
				output[k] = tolower(ciphertext[k]);
			for (int i = 0; ciphertext[i] != '\0'; i++) { // iterate through cipher
				int letter = letterIndex(toupper(ciphertext[i]), translator);
				if (letter >= 0) {
					output[i] = abc[letter];
				}
			}
			cout << output << endl;
			return true; // matched crib 
		}
		cipherStart++; // move ciphertext frame with crib
	}
	return false; // didn't find crib in ciphertext
}




bool isCribCorrect(const char cleanCipher[], const char translator[], const char cleanCrib[]) { 
	// check whether the translator created works for the crib
	const char abc[] = "abcdefghijklmnopqrstuvwxyz";

	// Convert crib with translator
	char encodedCrib[81];
	strcpy(encodedCrib, cleanCrib); // make converted crib outline from cleaned crib
	for (int i = 0; encodedCrib[i] != '\0'; i++) { // iterate through crib
		if (isalpha(cleanCrib[i])) {// crib element is letter (not a space)
			int cribLetter = letterIndex(tolower(cleanCrib[i]), abc);
			encodedCrib[i] = translator[cribLetter]; // convert crib into translator
		}
	}

	// find whether converted crib exists in ciphertext
	int j = -1;
	while (cleanCipher[j] != '\0') { // while not at the end of string
		j++; // move past newline character

		for (; cleanCipher[j] != '\n' && cleanCipher[j] != '\0'; j++) { // iterate through one line at a time (until newline)
			for (int k = 0; encodedCrib[k] != '\0'; k++) { // iterate through crib
				int j2 = j + k;
				if (toupper(encodedCrib[k]) != toupper(cleanCipher[j2])) { // not correct alignment
					break;
				}
				else if (k == strlen(encodedCrib)-1) {// converted translator matches with segment of ciphertext
					return true;
				}
			}
		}
	}
	return false; // no match found
}


void cleanCstring(const char dirtyCstring[], char cleanCstring[]) { // retains letter case
	strcpy(cleanCstring, dirtyCstring);
	int cleanCstringLoc = 0;
	bool addSpace = false;
	for (int i = 0; cleanCstring[i] != '\0'; i++) { // iterate through entire cstring
		if (isalpha(cleanCstring[i])) { // character is letter, so add to cleaned cstring
			cleanCstring[cleanCstringLoc] = dirtyCstring[i]; // fill cleancstring with  letters
			addSpace = true; // add a space if nonletter and previous character was a letter
			cleanCstringLoc++; // move to next spot in cleaned cstring
		}
		else if (dirtyCstring[i] == '\n') {
			cleanCstring[cleanCstringLoc] = '\n'; // retain newlines
			cleanCstringLoc++; // move to next spot in cleaned cstring
		}
		else if (addSpace) { // remove extra characters and fill with spaces
			addSpace = false; // just added space, shouldn't add another until another letter segment is found
			for (int j = i; dirtyCstring[j] != '\0'; j++) {
				if (isalpha(dirtyCstring[j])) { // have another letter after nonletter characters, so add space
					cleanCstring[cleanCstringLoc] = ' ';
					cleanCstringLoc++; // move to next spot in cleaned cstring
					break;
				}
			}
		}
	}
	cleanCstring[cleanCstringLoc] = '\0'; // set zero byte at end of cleaned cstring
}


int letterIndex(char toFind, const char toSearch[]) {// find the index of the letter in question
	for (int k = 0; toSearch[k] != '\0'; k++) { // iterate through alphabet
		if (toFind == toSearch[k]) // found letter
			return k;
	}
	return -999; // not an alphabetical character or space
}
//*/