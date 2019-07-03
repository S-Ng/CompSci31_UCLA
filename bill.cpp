// Code for Project 2
// Water Bill Calculator
// Simon Ng Started 4/12/2019
// Finished 4/17/2019

#include <iostream>
#include <string>
using namespace std;

int main()
{
	cout << "Initial meter reading (HCF): ";
	int initial_read;
	cin >> initial_read;

	cout << "Final meter reading (HCF): ";
	int final_read;
	cin >> final_read;
	cin.ignore(10000, '\n');

	cout << "Customer name: ";
	string cust_name;
	getline(cin, cust_name);

	cout << "Month number (1=Jan, 2=Feb, etc.): ";
	int month;
	cin >> month;

	int usage = final_read - initial_read;

	double FirstTierRate = 2.71; // USD
	double SecondTierRate; //USD
	int HCFcutoff;

	if (month >= 4 && month <= 10) { // HIGH usage months (April through October)
		SecondTierRate = 3.39; //USD
		HCFcutoff = 43;
	}else{ // LOW usage months (November through March)
		SecondTierRate = 2.87; //USD
		HCFcutoff = 29;
	}

	double charge;
	if (usage >= HCFcutoff) { // charge second tier rate on amount above HCF cutoff
		charge = (usage - HCFcutoff) * SecondTierRate + HCFcutoff * FirstTierRate;
	}else { // charge only first tier rate on amount below HCF cutoff
		charge = usage * FirstTierRate;
	}
	cout << "---" << endl;

	if (initial_read < 0) {
		cout << "The initial meter reading must be nonnegative." << endl;
	}else if (final_read < initial_read) {
		cout << "The final meter reading must be at least as large as the initial reading." << endl;
	}else if (cust_name == "") {
		cout << "You must enter a customer name." << endl;
	}else if (month > 12 || month < 1) {
		cout << "The month number must be in the range 1 through 12." << endl;
	}else {
		cout.setf(ios::fixed);
		cout.setf(ios::showpoint);
		cout.precision(2); // set 2 decimal places
		cout << "The bill for " << cust_name << " is $" << charge << endl; // print bill details
	}
}