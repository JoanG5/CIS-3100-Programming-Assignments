#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

const int CLASSSIZE = 35;
const int BAR = 60;

const int DGRADE = 70;
const int CMINUSGRADE = 73;
const int CGRADE = 77;
const int CPLUSGRADE = 80;
const int BMINUSGRADE = 83;
const int BGRADE = 87;
const int BPLUSGRADE = 90;
const int AMINUSGRADE = 93;

const int FPERCENT = 5;
const int DPERCENT = 10;
const int CMINUSPERCENT = 15;
const int CPERCENT = 25;
const int CPLUSPERCENT = 35;
const int BMINUSPERCENT = 45;
const int BPERCENT = 60;
const int BPLUSPERCENT = 75;
const int AMINUSPERCENT = 90;

enum Grade { F, D, CMINUS, C, CPLUS, BMINUS, B, BPLUS, AMINUS, A };

struct StudentData
{
	string lastName;
	string firstName;
	double score;
	double percentage;
	Grade pointGrade;
	Grade curveGrade;
	Grade finalGrade;
};

bool insert(StudentData** studentarr, StudentData student, int& currentsize, int& capacity);
void newArray(StudentData*& arr, int size, int sizeadd);
void percentile(StudentData*& arr, int total_size);
Grade gradeCheck(double grade);
Grade percentCheck(double grade);
string letterGrade(Grade g);
void outputGradeBook(string ofileName, StudentData s[], int size);

bool scoreCompare(const StudentData& val1, const StudentData& val2) {
	return val1.score < val2.score;
}
bool nameCompare(const StudentData& val1, const StudentData& val2) {
	if (val1.lastName != val2.lastName) {
		return val1.lastName < val2.lastName;
	}
	return val1.firstName < val2.firstName;
}
// To visualize data easier
void ShowArray(StudentData arr[], int size);

int main() {
	int count = 0;
	int index = 0;
	int size = CLASSSIZE;
	StudentData* student = new StudentData[CLASSSIZE];
	string filename;
	string outputfilename;
	string text;

	cout << "Enter the student grade data file: ";
	cin >> filename;
	cout << "Enter the gradebook file name: ";
	cin >> outputfilename;
	cout << "Initial Class size = " << CLASSSIZE << " students." << endl;

	StudentData NewStudent;
	fstream file(filename);
	while (file >> text) {
		if (count == 0) {
			NewStudent.lastName = text;
			count++;
		}
		else if (count == 1) {
			NewStudent.firstName = text;
			count++;
		}
		else {
			NewStudent.score = stod(text);
			NewStudent.pointGrade = gradeCheck(NewStudent.score);
			if (!insert(&student, NewStudent, index, size)) {
				newArray(student, size, CLASSSIZE);
				size += size;
				cout << "The Class size has been increased to " << size << " students." << endl;
				insert(&student, NewStudent, index, size);
			}
			count = 0;
			index++;
		}
	}
	cout << "The total enrollment = " << index << " students." << endl;

	sort(student, student + index, scoreCompare);
	percentile(student, index);
	sort(student, student + index, nameCompare);
	outputGradeBook(outputfilename, student, index);
}

bool insert(StudentData** studentarr, StudentData student, int& currentsize, int& capacity) {
	if (currentsize >= capacity) {
		return false;
	}
	(*studentarr)[currentsize] = student;
	return true;
}

void newArray(StudentData*& arr, int size, int sizeadd) {
	StudentData* NewArr = new StudentData[size + sizeadd];
	for (int i = 0; i < size; i++) {
		NewArr[i] = arr[i];
	}
	delete[] arr;
	arr = NewArr;
}

void percentile(StudentData*& arr, int total_size) {
	double val = -1;
	int ind = 1;
	for (int i = 0; i < total_size; i++) {
		if (arr[i].score == val) {
			arr[i].percentage = ((ind + 2) / (double) total_size) * 100.0;
			arr[i - 1].percentage = ((ind + 2) / (double) total_size) * 100.0;
		}
		else {
			arr[i].percentage = ((i + 1) / (double) total_size) * 100.0;
			ind = i;
		}

		val = arr[i].score;
		arr[i].curveGrade = percentCheck(arr[i].percentage);

		if (arr[i].score < BAR) {
			arr[i].finalGrade = F;
		}
		else if (arr[i].pointGrade > arr[i].curveGrade){
			arr[i].finalGrade = arr[i].pointGrade;
		}
		else {
			arr[i].finalGrade = arr[i].curveGrade;
		}
	}
}

Grade gradeCheck(double grade) {
	if (grade < BAR) {
		return F;
	}
	else if (grade < DGRADE) {
		return D;
	}
	else if (grade < CMINUSGRADE) {
		return CMINUS;
	}
	else if (grade < CGRADE) {
		return C;
	}
	else if (grade < CPLUSGRADE) {
		return CPLUS;
	}
	else if (grade < BMINUSGRADE) {
		return BMINUS;
	}
	else if (grade < BGRADE) {
		return B;
	}
	else if (grade < BPLUSGRADE) {
		return BPLUS;
	}
	else if (grade < AMINUSGRADE) {
		return AMINUS;
	}
	else {
		return A;
	}
}

Grade percentCheck(double grade) {
	if (grade < FPERCENT) {
		return F;
	}
	else if (grade < DPERCENT) {
		return D;
	}
	else if (grade < CMINUSPERCENT) {
		return CMINUS;
	}
	else if (grade < CPERCENT) {
		return C;
	}
	else if (grade < CPLUSPERCENT) {
		return CPLUS;
	}
	else if (grade < BMINUSPERCENT) {
		return BMINUS;
	}
	else if (grade < BPERCENT) {
		return B;
	}
	else if (grade < BPLUSPERCENT) {
		return BPLUS;
	}
	else if (grade < AMINUSPERCENT) {
		return AMINUS;
	}
	else {
		return A;
	}
}

string letterGrade(Grade g)
{
	string s;
	switch (g)
	{
	case F: return "F";
		break;
	case D: return "D";
		break;
	case CMINUS: return "C-";
		break;
	case C: return "C";
		break;
	case CPLUS: return "C+";
		break;
	case BMINUS: return "B-";
		break;
	case B: return "B";
		break;
	case BPLUS: return "B+";
		break;
	case AMINUS: return "A-";
		break;
	case A: return "A";
		break;
	default: return "Error";
	}
}

void ShowArray(StudentData arr[], int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i].lastName << "      " << arr[i].firstName << "      " << arr[i].score << "      " <<arr[i].percentage << "      " << letterGrade(arr[i].pointGrade) << "      " << letterGrade(arr[i].curveGrade) << "      " << letterGrade(arr[i].finalGrade) << endl;
		cout << ' ' << endl;
	}
}

void outputGradeBook(string ofileName, StudentData s[], int size) {
	ofstream outputfile(ofileName);
	outputfile << fixed << setprecision(2) << showpoint;
	outputfile << setw(16) << left << "Last Name" << setw(16) << left << "First Name" << "" << setw(5) << right << "Points" << setw(10) << left << "" << setw(10) << left << "Grade" << setw(5) << left << "" << setw(5) << right << "Percent" << setw(10) << left << "" << setw(10) << left << "Grade" << setw(10) << left << "Final" << endl;

	for (int i = 0; i < size; i++) {
		outputfile << setw(16) << left << s[i].lastName << setw(16) << left << s[i].firstName << " " << setw(5) << right << s[i].score << setw(10) << left << "" << setw(10) << left << letterGrade(s[i].pointGrade) << setw(6) << left << "" << setw(6) << right << s[i].percentage << setw(10) << left << "" << setw(10) << left << letterGrade(s[i].curveGrade) << setw(10) << left << letterGrade(s[i].finalGrade) << endl;
	}

	outputfile.close();
}
