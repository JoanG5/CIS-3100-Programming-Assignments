#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
const int NUMOFPERIOD = 12;
const int LOANLOWERBOUND = 0;
const int LOANUPPERBOUND = 99999999;
const float RATELOWERBOUND = 0;
const float RATEUPPERBOUND = 30;
const int YEARUPPERBOUND = 99;
const int YEARLOWERBOUND = 1;
const int PRINCIPLEUPPERBOUND = 9999999;
const int PRINCIPLELOWERBOUND = 0;
const int PERCENTAGE = 100;

int n(double num);
int num1(double num);
int num2(double num);
string zero(int num);
double decimal(double num);

int main() {
	ofstream myfile;
	double loan_amount = -1;
	double interest_rate = -1;
	int years = -1;
	double principle = -1;
	string file_name;
	double monthly_payment;
	//Validation
	while (loan_amount <= LOANLOWERBOUND || loan_amount > LOANUPPERBOUND) {
		cout << "Enter Loan amount (0-99999999), for example 300000.90: ";
		cin >> loan_amount;
	}
	while (interest_rate <= RATELOWERBOUND || interest_rate > RATEUPPERBOUND) {
		cout << "Enter annual interest rate(0-30), for example 4.25 meaning 4.25%: ";
		cin >> interest_rate;
	}
	while (years < YEARLOWERBOUND || years > YEARUPPERBOUND) {
		cout << "Enter no. of years as integer(1-99), for example 30: ";
		cin >> years;
	}
	while (principle < PRINCIPLELOWERBOUND || principle > PRINCIPLEUPPERBOUND) {
		cout << "Enter additional principle per month (0-9999999), for example 300: ";
		cin >> principle;
	}
	cout << "Send the mortgage amortization table to a file (enter file name): ";
	cin >> file_name;
	myfile.open(file_name);
	monthly_payment = (loan_amount * ((interest_rate / PERCENTAGE) / NUMOFPERIOD)) / (1
		- 1 / pow(1 + (interest_rate / PERCENTAGE) / NUMOFPERIOD, (years * NUMOFPERIOD)));
	double actual_payment = monthly_payment + principle;
	//Display

	myfile.width(9);
	myfile << left << " " << "MORTGAGE AMORTIZATION TABLE" << '\n' << endl;

	myfile << fixed << setprecision(2) << showpoint;
	myfile.width(25);
	//
	if (n(loan_amount) > 0) {
		myfile << left << "Amount:";
		myfile.width(3);
		myfile << left << '$' << n(loan_amount) << zero(num2(loan_amount)) << num2(loan_amount) << zero(num1(loan_amount)) << num1(loan_amount) + decimal(loan_amount) << endl;
	}
	else if (num2(loan_amount) > 0) {
		myfile << left << "Amount:";
		myfile.width(6);
		myfile << left << '$' << num2(loan_amount) << zero(num1(loan_amount)) << num1(loan_amount) + decimal(loan_amount) << endl;
	}
	else {
		myfile << left << "Amount:";
		myfile.width(8);
		myfile << left << '$' << num1(loan_amount) + decimal(loan_amount) << endl;
	}
	//
	myfile.width(25);
	myfile << left << "Interest Rate:" << interest_rate << '%' << endl;
	myfile.width(25);
	myfile << left << "Term(Years):" << years << endl;
	myfile.width(25);
	//
	if (n(monthly_payment) > 0) {
		myfile << left << "Monthly Payment:";
		myfile.width(4);
		myfile << left << '$' << n(monthly_payment) << zero(num2(monthly_payment)) << num2(monthly_payment) << zero(num1(monthly_payment)) << num1(monthly_payment) + decimal(monthly_payment) << endl;
	}
	else if (num2(monthly_payment) > 0) {
		myfile << left << "Monthly Payment:";
		myfile.width(6);
		myfile << left << '$' << num2(monthly_payment) << zero(num1(monthly_payment)) << num1(monthly_payment) + decimal(monthly_payment) << endl;
	}
	else {
		myfile << left << "Monthly Payment:";
		myfile.width(8);
		myfile << left << '$' << num1(monthly_payment) + decimal(monthly_payment) << endl;
	}
	//
	myfile.width(25);
	if (n(principle) > 0) {
		myfile << left << "Additional Principal:";
		myfile.width(4);
		myfile << left << '$' << n(principle) << zero(num2(principle)) << num2(principle) << zero(num1(principle)) << num1(principle) + decimal(principle) << endl;
	}
	else if (num2(principle) > 0) {
		myfile << left << "Additional Principal:";
		myfile.width(6);
		myfile << left << '$' << num2(principle) << zero(num1(principle)) << num1(principle) + decimal(principle) << endl;
	}
	else {
		myfile << left << "Additional Principal:";
		myfile.width(8);
		myfile << left << '$' << num1(principle) + decimal(principle) << endl;
	}
	//
	myfile.width(25);
	if (n(actual_payment) > 0) {
		myfile << left << "Actual Payment:";
		myfile.width(4);
		myfile << left << '$' << n(actual_payment) << zero(num2(actual_payment)) << num2(actual_payment) << zero(num1(actual_payment)) << num1(actual_payment) + decimal(principle) << endl;
	}
	else if (num2(actual_payment) > 0) {
		myfile << left << "Actual Payment:";
		myfile.width(6);
		myfile << left << '$' << num2(actual_payment) << zero(num1(actual_payment)) << num1(actual_payment) + decimal(principle) << endl;
	}
	else {
		myfile << left << "Actual Payment:";
		myfile.width(8);
		myfile << left << '$' << num1(actual_payment) + decimal(principle) << endl;
	}
	//
	myfile << '\n';
	double balance = loan_amount;
	double interest_amount;
	double principle_amount = 0;
	int day = 1;
	myfile.width(25);
	myfile << left << "";
	myfile.width(28);
	myfile << left << "Principal";
	myfile.width(27);
	myfile << "Interest";
	myfile.width(22);
	myfile << "Balance" << endl;
	//Calculation
	while (balance > 0) {
		myfile << fixed << setprecision(2) << showpoint;
		if (balance < principle_amount) 
		{
			interest_amount = balance * ((interest_rate / PERCENTAGE) / NUMOFPERIOD);
			principle_amount = balance;
			balance -= balance;
			myfile.width(10);
			myfile << left << day;
			myfile.width(19);
			if (n(principle_amount) > 0) {
				myfile << right << n(principle_amount) << zero(num2(principle_amount)) << num2(principle_amount) << zero(num1(principle_amount)) << num1(principle_amount) + decimal(principle_amount);
			}
			else if (num2(principle_amount) > 0) {
				myfile << right << num2(principle_amount) << zero(num1(principle_amount)) << num1(principle_amount) + decimal(principle_amount);
			}
			else {
				myfile << right << num1(principle_amount) + decimal(principle_amount);
			}
			myfile.width(19);
			if (n(interest_amount) > 0) {
				myfile << right << n(interest_amount) << zero(num2(interest_amount)) << num2(interest_amount) << zero(num1(interest_amount)) << num1(interest_amount) + decimal(interest_amount);
			}
			else if (num2(interest_amount) > 0) {
				myfile << right << num2(interest_amount) << zero(num1(interest_amount)) << num1(interest_amount) + decimal(interest_amount);
			}
			else {
				myfile << right << num1(interest_amount) + decimal(interest_amount);
			}
			myfile.width(24);
			if (n(balance) > 0) {
				myfile << right << n(balance) << zero(num2(balance)) << num2(balance) << zero(num1(balance)) << num1(balance) + decimal(balance) << endl;
			}
			else if (num2(balance) > 0) {
				myfile << right << num2(balance) << zero(num1(balance)) << num1(balance) + decimal(balance) << endl;
			}
			else {
				myfile.width(30);
				myfile << right << num1(balance) + decimal(balance) << endl;
			}
			break;
		}
		interest_amount = balance * ((interest_rate / PERCENTAGE) / NUMOFPERIOD);
		principle_amount = actual_payment - interest_amount;
		balance -= principle_amount;
		if (day == 1) 
			{
			myfile.width(6);
			myfile << left << day << '$';
			myfile.width(18);
			if (n(principle_amount) > 0) {
				myfile << right << n(principle_amount) << zero(num2(principle_amount)) << num2(principle_amount) << zero(num1(principle_amount)) << num1(principle_amount) + decimal(principle_amount);
			}
			else if (num2(principle_amount) > 0) {
				myfile << right << num2(principle_amount) << zero(num1(principle_amount)) << num1(principle_amount) + decimal(principle_amount);
			}
			else {
				myfile << right << num1(principle_amount) + decimal(principle_amount);
			}
			myfile.width(6);
			myfile << right << '$';
			myfile.width(13);
			if (n(interest_amount) > 0) {
				myfile << right << n(interest_amount) << zero(num2(interest_amount)) << num2(interest_amount) << zero(num1(interest_amount)) << num1(interest_amount) + decimal(interest_amount);
			}
			else if (num2(interest_amount) > 0) {
				myfile << right << num2(interest_amount) << zero(num1(interest_amount)) << num1(interest_amount) + decimal(interest_amount);
			}
			else {
				myfile << right << num1(interest_amount) + decimal(interest_amount);
			}
			myfile.width(6);
			myfile << right << '$';
			myfile.width(13);
			if (n(balance) > 0) {
				myfile << right << n(balance) << zero(num2(balance)) << num2(balance) << zero(num1(balance)) << num1(balance) + decimal(balance) << endl;
			}
			else if (num2(balance) > 0) {
				myfile << right << num2(balance) << zero(num1(balance)) << num1(balance) + decimal(balance) << endl;
			}
			else {
				myfile << right << num1(balance) + decimal(balance) << endl;
			}
			day++;
			continue;

		}
		myfile.width(6);
		myfile << left << day;
		myfile.width(19);
		if (n(principle_amount) > 0) {
			myfile << right << n(principle_amount) << zero(num2(principle_amount)) << num2(principle_amount) << zero(num1(principle_amount)) << num1(principle_amount) + decimal(principle_amount);
		}
		else if (num2(principle_amount) > 0) {
			myfile << right << num2(principle_amount) << zero(num1(principle_amount)) << num1(principle_amount) + decimal(principle_amount);
		}
		else {
			myfile << right << num1(principle_amount) + decimal(principle_amount);
		}
		myfile.width(19);
		if (n(interest_amount) > 0) {
			myfile << right << n(interest_amount) << zero(num2(interest_amount)) << num2(interest_amount) << zero(num1(interest_amount)) << num1(interest_amount) + decimal(interest_amount);
		}
		else if (num2(interest_amount) > 0) {
			myfile << right << num2(interest_amount) << zero(num1(interest_amount)) << num1(interest_amount) + decimal(interest_amount);
		}
		else {
			myfile << right << num1(interest_amount) + decimal(interest_amount);
		}
		myfile.width(19);
		if (n(balance) > 0) {
			myfile << right << n(balance) << zero(num2(balance)) << num2(balance) << zero(num1(balance)) << num1(balance) + decimal(balance) << endl;
		}
		else if (num2(balance) > 0) {
			myfile.width(23);
			myfile << right << num2(balance) << zero(num1(balance)) << num1(balance) + decimal(balance) << endl;
		}
		else {
			myfile << left << num1(balance) + decimal(balance) << endl;
		}
		day++;
	}
	myfile.close();
	return 0;
}


int num1(double num) {;
	int n = num;
	int fin = n % 1000;
	return fin;
}
int num2(double num) {
	int n = num;
	int fin = ((n - num1(n)) / 1000) % 1000;
	return fin;
}
int n(double num) {
	int n = num;
	int fin = ((n / 1000 - num2(n)) / 1000) % 1000;
	return fin;
}

string zero(int num) {
	string word = ",";
	int digits = log10(num) + 1;
	if (digits < 0) {
		digits = 1;
	}
	for (int i = 2; i >= digits; i--) {
		word += "0";
	}
	return word;
}

double decimal(double num) {
	int n = num;
	return num - n;
}
