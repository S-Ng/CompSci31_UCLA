#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
using namespace std;

// Declare all functions
int countMatches(const string a[], int n, string target);
int detectMatch(const string a[], int n, string target);
bool detectSequence(const string a[], int n, string target, int& begin, int& end);
int detectMin(const string a[], int n);
int moveToBack(string a[], int n, int pos);
int moveToFront(string a[], int n, int pos);
int detectDifference(const string a1[], int n1, const string a2[], int n2);
int deleteDups(string a[], int n);
bool contains(const string a1[], int n1, const string a2[], int n2);
int meld(const string a1[], int n1, const string a2[], int n2, string result[], int max);
int split(string a[], int n, string splitter);
string strToUpper(string str);
void strArrComp(string a1[], string a2[], int len);
bool isNondecreasingOrder(const string a[], int n);

int main() {
	const int len = 6;
	string list[len] = { "BE110", "BE167L", "CS31", "LS7C", "Scand40", "CS31" };
	// Test countMatches
	bool TestcountMatches = true;
	if (TestcountMatches) {
		assert(countMatches(list, len, "CS31") == 2); // function works
		assert(countMatches(list, 3, "CS31") == 1); // size limit works
		assert(countMatches(list, 2, "CS31") == 0); // size limit works
		assert(countMatches(list, len, "Fdsa") == 0); // doesn't accept absent strings
		assert(countMatches(list, len, "Scand") == 0); // partial equality doesnt matter
		assert(countMatches(list, len, "SCand40") == 0); // case matters
		assert(countMatches(list, len, "Scand40") == 1); // case matters
		assert(countMatches(list, 0, "BE110") == 0); // 0 is fine and doesn't look at BE110
		assert(countMatches(list, -1, "BE110") == -1); // negatives not allowed
		cout << "all countMatches tests succeeded" << endl;
	}
	// Test detectMatch
	bool TestdetectMatch = true;
	if (TestdetectMatch) {
		assert(detectMatch(list, len, "CS31") == 2); // function works
		assert(detectMatch(list, len, "CS31") != 5); // function doesn't count later occurrances
		assert(detectMatch(list, 2, "CS31") == -1); // returns -1 if not found
		assert(detectMatch(list, len, "Scand") == -1); // partial equality doesnt matter
		assert(detectMatch(list, len, "SCand40") == -1); // case matters
		assert(detectMatch(list, len, "Scand40") == 4); // case matters/function works
		assert(detectMatch(list, 0, "BE110") == -1); // 0 is fine and doesn't look at BE110
		assert(detectMatch(list, -1, "BE110") == -1); // negatives not allowed
		cout << "all detectMatch tests succeeded" << endl;
	}
	// Test detectSequece
	bool TestdetectSequence = true;
	if (TestdetectSequence) {
		string list[len] = { "BE110", "CS31", "CS31", "CS31", "Scand40", "CS31" };
		int b = 999;
		int e = 999;
		assert(detectSequence(list, -1, "CS31", b, e) == false); // negative array length
		assert(b == 999 && e == 999); // b and e unchanged for false result
		assert(detectSequence(list, len, "CS31", b, e) == true); // function returns true for present target
		assert(detectSequence(list, -1, "CS31", b, e) == false); // negative array length
		assert(detectSequence(list, 0, "BE110", b, e) == false); // BE110 not evaluated at 0
		assert(detectSequence(list, len, "CompSci31", b, e) == false); // return false for no target occurances
		detectSequence(list, len, "CS31", b, e);
		assert(b == 1 && e == 3); // fill b and e correctly
		b = 999; e = 999;
		detectSequence(list, 3, "CS31", b, e);
		assert(b == 1 && e == 2); // array length cutoff works
		b = 999; e = 999;
		detectSequence(list, len, "Scand40", b, e);
		assert(b == 4 && e == 4); // same b and e for one occurance
		cout << "all detectSequence tests succeeded" << endl;
	}
	// Test detectMin
	bool TestdetectMin = true;
	if (TestdetectMin) {

		string list1[len] = { "BE110", "BE167L", "CS31", "LS7C", "Scand40", "CS31" };
		assert(detectMin(list1, len) == 0); // first element can be smallest
		assert(detectMin(list1, -2) == -1); // negative array length caught

		string list2[len] = { "BE167", "be110", "CS31", "LS7C", "Scand40", "CS31" };
		assert(detectMin(list2, len) == 1); // BE110 is smallest despite capitalization

		string list3[len] = { "BE167", "be110", "be110", "LS7C", "Scand40", "CS31" };
		assert(detectMin(list3, len) == 1); // first be110 is returned as lowest

		string list4[len] = { "BE167", "be110", "be110", "LS7C", "AOS30", "CS31" };
		assert(detectMin(list4, len) == 4); // returns AOS30

		string list5[len] = { "BE167", "be110", "110", "LS7C", "AOS30", "CS31" };
		assert(detectMin(list5, len) == 2); // returns 110

		string list6[len] = { "BE110", "be110", "BE", "BE110", "Be110", "be110" };
		assert(detectMin(list6, len) == 2); // returns BE

		string list7[len] = { "BE167", "be110", "B110", "LS7C", "AOS30", "CS31" };
		assert(detectMin(list7, len) == 4); // character value has precedence over length

		string list8[len] = { "BE167", "be110", "B110", "LS7C", "AOS30", "AAA" };
		assert(detectMin(list8, len) == 5); // last element correctly evaluated

		cout << "all detectMin tests succeeded" << endl;

	}
	/*Investigate .compare() function
	string str1 = "Bd110";
	string str2 = "BE110";
	for (int i = 0; i != str1.size(); i++)
		str1[i] = toupper(str1[i]);
	if (str1.compare(str2) == 0)
		cout << "Equal" << endl;
	else if (str1.compare(str2) < 0)
		cout << "Str1 smaller than Str2" << endl;
	else if (str1.compare(str2) > 0)
		cout << "Str1 larger than Str2" << endl;*/
	// Test moveToBack
	bool TestmoveToBack = true;
	if (TestmoveToBack) {
		string list1[len] = { "BE110", "BE167L", "CS31", "LS7C", "Scand40", "CS31" };
		assert(moveToBack(list1, len, 0) == 0); // returns position moved to back
		assert(moveToBack(list1, -1, 4) == -1); // negatives array length tested
		string list2[len] = { "BE167L", "CS31", "LS7C", "Scand40", "CS31", "BE110" };
		strArrComp(list1, list2, len); // was rearrangement successful
		assert(moveToBack(list2, len, 2) == 2); // returns position moved to back
		string list3[len] = { "BE167L", "CS31", "Scand40", "CS31", "BE110", "LS7C" };
		strArrComp(list3, list2, len); // was rearrangement successful
		cout << "all moveToBack tests succeeded" << endl;
	}
	// Test moveToFront
	bool TestmoveToFront = true;
	if (TestmoveToFront) {
		string list1[len] = { "BE110", "BE167L", "CS31", "LS7C", "Scand40", "CS31" };
		assert(moveToFront(list1, len, 3) == 3); // outputs pos
		assert(moveToFront(list1, -1, 0) == -1); // negative array length
		string list2[len] = { "LS7C", "BE110", "BE167L", "CS31", "Scand40", "CS31" };
		strArrComp(list1, list2, len); // was rearrangement successful
		cout << "all moveToFront tests succeeded" << endl;
	}
	// Test detectDifference
	bool TestdetectDifference = true;
	if (TestdetectDifference) {
		string list4[len] = { "BE110", "BE167L", "CS31", "LS7C", "Scand40", "CS31" };
		string list2[len] = { "BE110", "BE167L", "CompSci31", "LS7C", "Scand40", "CS31" };
		assert(detectDifference(list4, len, list2, len) == 2);
		string list3[len - 1] = { "BE110", "BE167L", "CS31", "LS7C", "Scand40" };
		assert(detectDifference(list4, len, list3, len - 1) == 5); //[ITS THE POSITION 4 BUT NUMBER 5. WHICH TAKES PRECENDENCE?]
		assert(detectDifference(list4, len, list2, 2) == 2); // test liming array size
		assert(detectDifference(list4, len, list2, 1) == 1); // test limiting array size
		assert(detectDifference(list4, -1, list2, 1) == -1); // negative array length not allowed

		cout << "all detectDifference tests succeeded" << endl;
	}
	// Test deleteDups
	bool testdeleteDups = true;
	if (testdeleteDups) {
		string list1[len] = { "BE110", "BE110", "CS31", "CS31", "Scand40", "CS31" };
		//cout << deleteDups(list1, len);
		assert(deleteDups(list1, len) == 4); // outputs 4 retained elements
		string list1_1[len] = { "BE110", "CS31", "Scand40", "CS31" , "BE110", "CS31" };
		strArrComp(list1, list1_1, 4); // test that it correctly cuts duplicates		
		string list2[len] = { "BE167L", "CS31", "CS31", "CS31", "CS31", "CS31" };
		assert(deleteDups(list2, len) == 2); // outputs 2 retained elements (can remove from end)		
		assert(deleteDups(list1, -1) == -1); // negative array length returns -1
		string list3[2] = { "BE167L", "CS31" };
		strArrComp(list2, list3, 2); // test that it correctly cuts duplicates		
		cout << "all deleteDups tests succeeded" << endl;
	}
	// Test contains
	bool testcontains = true;
	if (testcontains) {
		string big[10] = { "danvers", "thor", "stark", "banner", "romanoff", "stark" };
		string little1[10] = { "thor", "banner", "romanoff" };
		assert(contains(big, 6, little1, 3)); // searches past inbetween elements
		string little2[10] = { "stark", "thor" };
		assert(!contains(big, 6, little2, 2)); // doesn't search entire array each time
		string little3[10] = { "thor", "stark", "stark" };
		assert(contains(big, 6, little3, 3));  // registers multiple of same element
		string little4[10] = { "thor", "thor", "stark" };
		assert(!contains(big, 6, little4, 3));  // returns false
		assert(contains(big, 6, little4, 0));  // returns true
		assert(!contains(big, -1, little4, 0)); // negative array length
		string little5[10] = { "danvers", "thor", "stark", "banner", "romanoff", "stark", "simon", "simon" };
		assert(!contains(big, 6, little5, 8)); // longer compare array than search array
		cout << "all contains tests were successful" << endl;
	}
	// Test isNondecreasingOrder
	bool testisNondecreasingOrder = true;
	if (testisNondecreasingOrder) {
		string str[3] = { "abs", "bca", "bca" };
		if (isNondecreasingOrder(str, 3))
			cout << "isNondecreasingOrder test successful" << endl;
	}
	// Test meld
	bool testmeld = true;
	if (testmeld) {
		string x[5] = { "banner", "rhodes", "rogers", "stark", "tchalla" };
		string y[4] = { "danvers", "rogers", "rogers", "thor" };
		string z[20];
		assert(meld(x, 5, y, 4, z, 20) == 9);  // returns correct size of result
		string comp[20] = { "banner", "danvers" ,"rhodes" ,"rogers", "rogers", "rogers", "stark", "tchalla", "thor" };
		strArrComp(z, comp, 20); // generally works as desired
		string y2[4] = {  "rogers", "danvers", "rogers", "thor" };
		assert(meld(x, 5, y2, 4, z, 20) == -1); // one input not in nondecreasing order
		assert(meld(x, 5, y, 4, z, 8) == -1); // max < size needed for array [but having max is unecessary. It's not used at all]
		assert(meld(x, -1, y, 4, z, 10) == -1); // negative array size
		cout << "all meld tests succeeded" << endl;
	}
	// Test split
	bool testsplit = true;
	if (testsplit) {
		string f[6] = { "rhodes", "banner", "stark", "danvers", "thor", "rogers" };
		assert(split(f, 6, "romanoff")==4);  //  returns 4
			// f might now be
			//	"rhodes"  "banner"  "rogers"  "danvers"  "thor"  "stark"
			// or   "rogers"  "danvers"  "banner"  "rhodes"  "stark"  "thor"
			// or several other orderings.
			// The first 4 elements are < "romanoff"; the last 2 aren't.
		string g[4] = { "romanoff", "rogers", "thor", "banner" };
		assert(split(g, 4, "rogers")==1);  //  returns 1
		string list1[len] = { "BE110", "BE167L", "CS31", "LS7C", "Scand40", "CS31" };
		assert(split(list1, len, "AOS50") == len); // no elements shorter than splitter
		assert(split(list1, -1, "BE100") == -1); // negative array length
		cout << "all split tests succeeded" << endl;
	}
	string h[7] = { "romanoff", "thor", "rogers", "banner", "", "danvers", "rogers" };
	assert(countMatches(h, 7, "rogers") == 2);
	assert(countMatches(h, 7, "") == 1);
	assert(countMatches(h, 7, "rhodes") == 0);
	assert(countMatches(h, 0, "rogers") == 0);
	assert(detectMatch(h, 7, "rogers") == 2);
	assert(detectMatch(h, 2, "rogers") == -1);
	int bg;
	int en;
	assert(detectSequence(h, 7, "banner", bg, en) && bg == 3 && en == 3);

	string g[4] = { "romanoff", "thor", "banner", "danvers" };
	assert(detectMin(g, 4) == 2);
	assert(detectDifference(h, 4, g, 4) == 2);
	assert(contains(h, 7, g, 4));
	assert(moveToBack(g, 4, 1) == 1 && g[1] == "banner" && g[3] == "thor");

	string f[4] = { "danvers", "banner", "thor", "rogers" };
	assert(moveToFront(f, 4, 2) == 2 && f[0] == "thor" && f[2] == "banner");

	string e[5] = { "danvers", "danvers", "danvers", "thor", "thor" };
	//cout << deleteDups(e, 5);
	string comp[5] = { "danvers","thor", "thor", "danvers", "danvers" };
	//strArrComp(e, comp, 5);
	assert(deleteDups(e, 5) == 2); // outputs 3
	assert(e[1] == "thor");


	string x[4] = { "rhodes", "rhodes", "tchalla", "thor" };
	string y[4] = { "banner", "danvers", "rhodes", "rogers" };
	string z[10];
	assert(meld(x, 4, y, 4, z, 10) == 8 && z[5] == "rogers");

	assert(split(h, 7, "rogers") == 3);

	cout << "All provided tests succeeded" << endl;
}

int countMatches(const string a[], int n, string target) {
	/*
	Return the number of strings in the array that are equal to target.[Of course, in this and other functions, if n is negative, the paragraph above that starts "Notwithstanding" trumps this by requiring that the function return −1.Also, in the description of this function and the others, when we say "the array", we mean the n elements that the function is aware of.] As noted above, case matters: Do not consider "thor" to be equal to "ThoR".Here's an example:
	string d[9] = {
		"thor", "romanoff", "danvers", "danvers", "stark", "stark", "stark", "danvers", "danvers"
	};
	int i = countMatches(d, 9, "danvers");  // returns 4
	int j = countMatches(d, 5, "stark");  // returns 1
	int k = countMatches(d, 9, "barton");  // returns 0
	*/
	if (n < 0) // invalid input
		return -1;
	int matches = 0;
	for (int i = 0; i != n; i++) {
		if (a[i] == target)
			matches++;
	}
	return matches;
}
int detectMatch(const string a[], int n, string target) {
	/*
	Return the position of a string in the array that is equal to target; if there is more than one such string,
	return the smallest position number of such a matching string.Return −1 if there is no such string.
	As noted above, case matters: Do not consider "tHOR" to be equal to "Thor".
	string people[5] = { "danvers", "thor", "stark", "banner", "romanoff" };
	int j = detectMatch(people, 5, "banner");  // returns 3
	*/
	if (n < 0) // invalid input
		return -1;
	int i = 0;
	for (i = 0; i != n; i++) {
		if (a[i] == target)
			return i; // return position of first match
	}
	return -1; // target string not present
}
bool detectSequence(const string a[], int n, string target, int& begin, int& end) {
	/*
	Find the earliest occurrence in a of one or more consecutive strings that are equal to target; set begin to the position of the
	first occurrence of target, set end to the last occurrence of target in that earliest consecutive sequence, and return true.If n is
	negative or if no string in a is equal to target, leave begin and end unchanged and return false.Here's an example:

	string d[9] = {
		"thor", "romanoff", "danvers", "danvers", "stark", "stark", "stark", "danvers", "danvers"
	};
	int b;
	int e;
	bool b1 = detectSequence(d, 9, "danvers", b, e);  //  returns true and
		   //  sets b to 2 and e to 3
	bool b2 = detectSequence(d, 9, "romanoff", b, e); //  returns true and
		   //  sets b to 1 and e to 1
	bool b3 = detectSequence(d, 9, "rogers", b, e);   //  returns false and
		   //  leaves b and e unchanged
		   */
	if (n < 0) // negative array length
		return false;

	for (int i = 0; i != n; i++) {
		if (a[i] == target) { // first occurance
			begin = i; // set begin to first occurance
			while (a[i] == target && i != n) {
				end = i; // set end 
				i++;
			}
			return true; // begin and end set. break out of loop
		}
	}
	return false; // no occurance of target
}
int detectMin(const string a[], int n) {
	/*
	Return the position of a string in the array such that that string is <= every string in the array.
	If there is more than one such string, return the smallest position number of such a string.
	Return −1 if the function should examine no elements of the array.Here's an example:
	string people[5] = { "danvers", "thor", "stark", "banner", "romanoff" };
	int j = detectMin(people, 5);  // returns 3, since  banner  is earliest
					   // in alphabetic order
	*/

	if (n <= 0) // invalid input or if function should examine no elements of the array
		return -1;
	int lowestLoc = 0; // default lowest character location is first string
	string lowestStr = strToUpper(a[0]); // default lowest capitalized string is first array entry
	for (int i = 1; i != n; i++) {
		string compStr = strToUpper(a[i]); // capitalize next string to compare
		if (compStr.compare(lowestStr) < 0) { // new string is smaller or lower character than previously lowest string
			lowestLoc = i;
			lowestStr = compStr;
		}
	}
	return lowestLoc;
}
int moveToBack(string a[], int n, int pos) {
	/*
	Eliminate the item at position pos by copying all elements after it one place to the left.Put the item that was thus eliminated
	into the last position of the array.Return the original position of the item that was moved to the end.Here's an example:
	string people[5] = { "danvers", "thor", "stark", "banner", "romanoff" };
	int j = moveToBack(people, 5, 1);  // returns 1
		// people now contains:  "danvers"  "stark"  "banner", "romanoff"  "thor"
	*/
	if (n < 0) // invalid input
		return -1;
	string strToBack = a[pos];
	for (int i = pos + 1; i != n; i++) { // iterate though positions after string to move back
		a[i - 1] = a[i]; // copy value of current string into previous location (starting with copying one after pos into pos)
	}
	
	a[n-1] = strToBack; // move element at pos to back
	return pos;
}
int moveToFront(string a[], int n, int pos) {
	/*
	Eliminate the item at position pos by copying all elements before it one place to the right.
	Put the item that was thus eliminated into the first position of the array.Return the original position of the item that was moved to the beginning.Here's an example:
	string people[5] = { "danvers", "thor", "stark", "banner", "romanoff" };
	int j = moveToFront(people, 5, 2);  // returns 2
		// people now contains:  "stark"  "danvers"  "thor"  "banner", "romanoff"
	*/
	if (n < 0) // invalid input
		return -1;
	string strToFront = a[pos];
	for (int i = pos; i > 0; i--) { // iterate though positions
		a[i] = a[i - 1]; // copy value of string left
	}
	a[0] = strToFront; // move element at pos to back
	return pos;
}
int detectDifference(const string a1[], int n1, const string a2[], int n2) {
	/*Return the position of the first corresponding elements of a1 and a2 that are not equal.
	n1 is the number of interesting elements in a1, and n2 is the number of interesting elements in a2.
	If the arrays are equal up to the point where one or both runs out, return whichever value of n1 and n2 is less than or equal to the other.
	Here's an example:
	string cast[5] = { "danvers", "thor", "stark", "banner", "romanoff" };
	string roles[4] = { "danvers", "thor", "barton", "rhodes" };
	int k = detectDifference(cast, 5, roles, 4);  //  returns 2
	int m = detectDifference(cast, 2, roles, 1);  //  returns 1*/

	int limit = n2; // default n2 is limiting factor
	if (n1 < n2) // n1 smaller than n2
		limit = n1; // n1 is limiting factor

	if (limit < 0) // invalid input
		return -1;
	for (int i = 0; i != limit; i++) {
		if (a1[i] != a2[i]) {
			return i;
		}
	}
	return limit;
}
int deleteDups(string a[], int n) {
	/*For every sequence of consecutive identical items in a, retain only one item of that sequence.
	Suppose we call the number of retained items r.Then when this functions returns, elements 0 through r - 1 of a must
	contain the retained items(in the same relative order they were in originally), and the remaining elements may have
	whatever values you want. Return the number of retained items.Here's an example:
	string d[9] = {
		"thor", "romanoff", "danvers", "danvers", "stark", "stark", "stark", "danvers", "danvers"
	};
	int p = deleteDups(d, 9);  //  returns 5
		   //  d[0] through d[4] now contain  "thor" "romanoff" "danvers" "stark" "danvers"
		   //  We no longer care what strings are in d[5] and beyond.
		   
	string e[5] = { "danvers", "danvers", "danvers", "thor", "thor" };
	string comp[5] = { "danvers","thor", "thor", "danvers", "danvers" };
	*/
	if (n < 0) // invalid input
		return -1;
	int moved = 0;
	for (int i = 1; i != n-moved; i++) {
		if (a[i - 1] == a[i]) { // compare consecutive strings starting at beginning
			moveToBack(a, n, i); // move duplicate string to the end and all others forward
			i--;
			moved++;
		}
	}
	return n-moved;
}
bool contains(const string a1[], int n1, const string a2[], int n2) {
	/*If all n2 elements of a2 appear in a1, in the same order(though not necessarily consecutively), then return true.
	Return false if a1 does not so contain a2. (Of course, every sequence, even a sequence of 0 elements, contains a sequence of 
	0 elements.) Return false (instead of −1) if this function is passed any bad arguments.Here's an example:
	string big[10] = { "danvers", "thor", "stark", "banner", "romanoff", "stark" };
	string little1[10] = { "thor", "banner", "romanoff" };
	bool b1 = contains(big, 6, little1, 3);  // returns true
	string little2[10] = { "stark", "thor" };
	bool b2 = contains(big, 6, little2, 2);  // returns false
	string little3[10] = { "thor", "stark", "stark" };
	bool b3 = contains(big, 6, little3, 3);  // returns true
	string little4[10] = { "thor", "thor", "stark" };
	bool b4 = contains(big, 6, little4, 3);  // returns false
	bool b5 = contains(big, 6, little4, 0);  // returns true*/
	//string big[10] = { "danvers", "thor", "stark", "banner", "romanoff", "stark" };
	//string little2[10] = { "stark", "thor" };
	if (n1 < n2 || n2 < 0) // fewer elements in bigger array than smaller one or a negative input
		return false;

	int start = 0;
	int matches = 0;
	for (int i = 0; i != n2; i++) { // iterate through little array
		for (int k = start; k != n1; k++) { // iterate though big array
			if (a2[i] == a1[k]) { // entry in little arary matches big array
				start = k+1; // next iteration, can only look at elements past k
				matches++; // count that a match was made
				break;
			}
		}
	}
	if (matches == n2)
		return true;
	else
		return false;
}
int meld(const string a1[], int n1, const string a2[], int n2, string result[], int max) {
	/*If a1 has n1 elements in nondecreasing order, and a2 has n2 elements in nondecreasing order, 
	place in result all the elements of a1 and a2, arranged in nondecreasing order, and return the number of 
	elements so placed.Return −1 if the result would have more than max elements or if a1 and/or a2 are not in nondecreasing order. 
	(Note: nondecreasing order means that no item is > the one that follows it.) Here's an example:
string x[5] = { "banner", "rhodes", "rogers", "stark", "tchalla" };
string y[4] = { "danvers", "rogers", "rogers", "thor" };
string z[20];
int n = meld(x, 5, y, 4, z, 20);  // returns 9
	// z has  banner danvers rhodes rogers rogers rogers stark tchalla thor*/
	
	if (n2 < 0 || n1 < 0 || // n1 or n2 negative
		!isNondecreasingOrder(a1, n1) || !isNondecreasingOrder(a2, n2) || // or a1 and/or a2 are not in nondecreasing order
		(n1+n2) > max) // or result would have more than max elements
		return -1;

	int len = n1 + n2;
	for (int i = 0; i != n1; i++)
		result[i] = a1[i]; // copy a1 into result
	for (int k = n1; k != len; k++)
		result[k] = a2[k-n1]; // copy a2 into result

	while (!isNondecreasingOrder(result, len)) { // repeat until result is in nondecreasing order
		for (int j = 0; j != len; j++) {
			if (strToUpper(result[j]).compare(strToUpper(result[j + 1])) > 0) // first element is larger than previous element, move to back
				moveToBack(result, len, j); // move larger element to back
		}
	}
	return (len);
}
int split(string a[], int n, string splitter) {
	/*Rearrange the elements of the array so that all the elements whose value is < splitter come before all the other elements, 
	and all the elements whose value is > splitter come after all the other elements.Return the position of the first element that, 
	after the rearrangement, is not < splitter, or n if there are no such elements.Here's an example:

	string f[6] = { "rhodes", "banner", "stark", "danvers", "thor", "rogers" };
int r = split(f, 6, "romanoff");  //  returns 4
	// f might now be
	//	"rhodes"  "banner"  "rogers"  "danvers"  "thor"  "stark"
	// or   "rogers"  "danvers"  "banner"  "rhodes"  "stark"  "thor"
	// or several other orderings.
	// The first 4 elements are < "romanoff"; the last 2 aren't.
string g[4] = { "romanoff", "rogers", "thor", "banner" };
int s = split(g, 4, "rogers");  //  returns 1
	// g must now be either	"banner"  "rogers"  "romanoff"  "thor" or	"banner"  "rogers"  "thor"  "romanoff"
	// All elements < "rogers" (i.e., "banner") come before all others.
	// All elements > "rogers" (i.e., "thor" and "romanoff") come after all others.*/

	if (n < 0) // invalid input
		return -1;

	int postSplitLoc = 0;
	for (int i = 0; i != n; i++) { // iterate through entire string
		if (strToUpper(a[i]).compare(strToUpper(splitter)) < 0) { // evaluated string is less than splitter
			moveToFront(a, n, i); // move smaller string to the front
			postSplitLoc++; // will give final position of first element that, after the rearrangement, is not < splitter
		}
	}
	if (postSplitLoc == 0)
		return n;
	else
		return postSplitLoc;
}
string strToUpper(string str) {
	//strToUpper capitalizes all letters in a string
	for (int i = 0; i != str.size(); i++)
		if (isalpha(str[i])) // if a letter (this shouldn't actually matter. toupper works with non-alphabetic characters)
			str[i] = toupper(str[i]); // convert to uppercase
	return str;
}
void strArrComp(string a1[], string a2[], int len) {
	for (int i = 0; i != len;i++)
		assert(a1[i] == a2[i]);
}
bool isNondecreasingOrder(const string a[], int n) {

	int lessthan = 0;
	for (int i = 1; i != n; i++) {
		string a1 = a[i - 1];
		string a2 = a[i];
		int result = strToUpper(a1).compare(strToUpper(a2));
		if (result < 0 || result == 0) // a1[i-1] is less than or = a1[i] (capitalized)
			lessthan++;
	}
	if (lessthan == n - 1)
		return true;
	else
		return false;
}