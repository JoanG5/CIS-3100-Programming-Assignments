#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int NUMOFPERIOD = 12;
const int LOANLOWERBOUND = 0;
const int LOANUPPERBOUND = 9999999;
const float RATELOWERBOUND = 0;
const float RATEUPPERBOUND = 30;
const int YEARUPPERBOUND = 99;
const int YEARLOWERBOUND = 1;
const int PRINCIPLEUPPERBOUND = 9999999;
const int PRINCIPLELOWERBOUND = 0;
const int PERCENTAGE = 100;

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
		cout << "Enter Loan amount (0-9999999), for example 300000.90: ";
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
	monthly_payment = (loan_amount * ((interest_rate / PERCENTAGE) / NUMOFPERIOD)) / (1 - 1 / pow(1 + (interest_rate / PERCENTAGE) / NUMOFPERIOD, (years * NUMOFPERIOD)));
	double actual_payment = monthly_payment + principle;
	//Display
	myfile.width(9);
	myfile << left << " " << "MORTGAGE AMORTIZATION TABLE" << '\n' << endl;

	myfile << fixed << setprecision(2) << showpoint;
	myfile.width(25);
	myfile << left << "Amount:" << '$' << loan_amount << endl;
	myfile.width(25);
	myfile << fixed << setprecision(3) << showpoint;
	myfile << left << "Interest Rate:" << interest_rate << '%' << endl;
	myfile.width(25);
	myfile << fixed << setprecision(2) << showpoint;
	myfile << left << "Term(Years):" << years << endl;
	myfile.width(25);
	myfile << left << "Monthly Payment:" << '$' << monthly_payment << endl;
	myfile.width(25);
	myfile << left << "Additional Principal:" << '$' << principle << endl;
	myfile.width(25);
	myfile << left << "Actual Payment:" << '$' << actual_payment << endl;

	myfile << '\n';

	double balance = loan_amount;
	double interest_amount;
	double principle_amount = 0;
	int day = 1;

	myfile.width(6);
	myfile << right << "";
	myfile.width(20);
	myfile << right << "Principal";
	myfile.width(18);
	myfile << "Interest";
	myfile.width(16);
	myfile << "Balance" << endl;
	//Calculation 
	while (balance > 0) {
		if (balance < principle_amount) {
			interest_amount = balance * ((interest_rate / PERCENTAGE) / NUMOFPERIOD);
			principle_amount = balance;
			balance -= balance;
			myfile.width(6);
			myfile << left << day;
			myfile.width(19);
			myfile << right << principle_amount;
			myfile.width(19);
			myfile << right << interest_amount;
			myfile.width(19);
			myfile << balance << endl;
			break;
		}
		interest_amount = balance * ((interest_rate / PERCENTAGE) / NUMOFPERIOD);
		principle_amount = actual_payment - interest_amount;
		balance -= principle_amount;

		if (day == 1) {
			myfile.width(6);
			myfile << left << day << '$';
			myfile.width(18);
			myfile << right << principle_amount;
			myfile.width(6);
			myfile << right << '$';
			myfile.width(13);
			myfile << right << interest_amount;
			myfile.width(6);
			myfile << right << '$';
			myfile.width(13);
			myfile << balance << endl;
			day++;
			continue;
		}

		myfile.width(6);
		myfile << left << day;
		myfile.width(19);
		myfile << right << principle_amount;
		myfile.width(19);
		myfile << right << interest_amount;
		myfile.width(19);
		myfile << balance << endl;
		day++;
	}
	myfile.close();

	return 0;
}
