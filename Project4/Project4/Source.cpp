// Author: John Doe
// CIS 3100 BMWA Spring 2021
//Assignment Grade:

#include <iostream>
#include <ctime>
#include <random>

using namespace std;

const int WHITEBALLS = 69;
const int WHITEPICKS = 5;
const int REDBALLS = 26;

int* arrayinit(int size);
int pop(int index, int arr[], int size);
void showarray(int arr[], int size);
void selectionsort(int arr[], int size);

int main() {
	srand(time(0));
	int games, index, num = 0;
	int balls[WHITEPICKS];

	cout << "How many games would you like to play? ";
	cin >> games;
	cout << "\n\n";
	for (int play = 0; play < games; play++) {
		int* arr = arrayinit(WHITEBALLS);
		int* redarr = arrayinit(REDBALLS);
		for (int i = 0; i < WHITEPICKS; i++) {
			index = rand() % (WHITEBALLS - num);
			balls[num] = arr[index];
			pop(index, arr, WHITEBALLS - num);
			num++;
		}
		selectionsort(balls, WHITEPICKS);
		cout << "White Balls is: ";
		showarray(balls, WHITEPICKS);
		cout << "Power Ball is: " << redarr[rand() % REDBALLS] << endl;
		delete[] arr;
		delete[] redarr;
		num = 0;
		cout << endl;
	}
}

int* arrayinit(int size) {
	int* arr = new int[size];
	for (int i = 0; i < size; i++) {
		arr[i] = i + 1;
	}
	return arr;
}

int pop(int index, int arr[], int size) {
	int val = arr[index];
	for (int i = index; i < size - 1; i++) {
		arr[i] = arr[i + 1];
	}
	return val;
}

void showarray(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
}

void selectionsort(int arr[], int size) {
	int minIndex, minValue;

	for (int start = 0; start < (size - 1); start++) {
		minIndex = start;
		minValue = arr[start];
		for (int index = start + 1; index < size; index++) {
			if (arr[index] < minValue) {
				minValue = arr[index];
				minIndex = index;
			}
		}
		swap(arr[minIndex], arr[start]);
	}
}
