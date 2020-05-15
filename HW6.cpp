/*
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
*/

// 1 4 9 16 25 36 49 64 81 100 

#include <iostream>
using namespace std;

int* computeSquares(int& n)
{
	int arr[10];
	n = 10;
	for (int k = 0; k < n; k++)
		arr[k] = (k + 1) * (k + 1);
	cout << arr << endl;
	return arr;
}

void f()
{
	int junk[100];
	for (int k = 0; k < 100; k++)
		junk[k] = 123400000 + k;
}

int main()
{
	int m;
	int* ptr = computeSquares(m);
	cout << ptr << endl;
	//f();
	for (int i = 0; i < m; i++) {
		cout << ptr[i] << ' ';

	}
}

/*

string* fp;
string fish[5];
string* fp = fish + 4;
*fp = "yellowfish";
*(fish + 3) = "salmon";
fp -= 3;
fp[1] = "sole";
fp[0] = "eel";
bool d = (fp == fish);
bool b = (*fp == *(fp+1));

/*
double computeAverage(const double* scores, int nScores)
{
	const double* ptr = scores;
	double tot = 0;
	int i = 0;
	while (i != nScores)
	{
		tot += *(ptr+i);
		i++;
	}
	return tot / nScores;
}


// This function searches through str for the character chr.
// If the chr is found, it returns a pointer into str where
// the character was first found, otherwise nullptr (not found).'

// no square brackets

const char* findTheChar(const char* str, char chr)
{
	for (; *str != 0; str++)
		if (*str == chr)
			return str;

	return nullptr;
}

#include <iostream>

using namespace std;

int* minimart(int* a, int* b)
{
	if (*a < *b)
		return a;
	else
		return b;
}

void swap1(int* a, int *b)
{
	cout << "a " << a << " b " << b << endl;

	int* temp = a;

	a = b;
	b = temp;
	cout << "a " << a << " b " << b << endl;

}

void swap2(int* a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;

}

int main()
{
	int array[6] = { 5, 3, 4, 17, 22, 19 };

	int* ptr = minimart(array, &array[2]);
	ptr[1] = 9;
	ptr += 2;
	*ptr = -1;
	*(array + 1) = 79;

	cout << "diff=" << &array[5] - ptr << endl;

	cout << "Array 0 preswap " << array << endl;
	cout << "Array 1 preswap " << &array[1] << endl;
	swap1(array, &array[1]);
	cout << "Array 0 potswap " << array << endl;
	cout << "Array 1 potswap " << &array[1] << endl;
	swap2(array, &array[2]);

	for (int i = 0; i < 6; i++)
		cout << array[i] << endl;
}


void deleteG(char* msg) {
	for (;*msg != 0; msg++) { // iterate through all characters in message by moving msg pointer along array
		if (*msg == 'g' || *msg == 'G') { // found 'g' or 'G'
			char* temp = msg; // temporary pointer to delete 'g' or 'G'
			for (;*temp != 0; temp++) { // iterate through remaining elements
				*temp = *(temp + 1); // copy next character into space left by 'g' or most recently 
			}
		}
	}
}
int main()
{
	char msg[100] = "I recall the glass gate next to Gus in Lagos, near the gold bridge.";
	deleteG(msg);
	cout << msg;  // prints   I recall the lass ate next to us in Laos, near the old bride.
}
//*/