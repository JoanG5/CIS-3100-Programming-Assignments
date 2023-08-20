#include <iostream>
#include "HEADER.h"
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	string filein, fileout;
	int wordcount = 0;
	vector <string> speech;
	vector <MyString> words;
	string word;
	string newword = "";
	bool add;

	cout << "Enter the source data file name: ";
	cin >> filein;
	fstream file(filein);

	while (wordcount < 1 || wordcount > 5) {
		cout << "How many Adjacent words in a phrase, enter 1-5: ";
		cin >> wordcount;
	}

	cout << "Enter the phrase frequency file name: ";
	cin >> fileout;
	ofstream outfile(fileout);

	while (file >> word) {
		int ind = 0;
		int sind;
		for (int i = 0; i < word.length(); i++) {
			if (!isAcceptable(word[i])) {
				ind++;
				continue;
			}
			break;
		}
		for (int i = word.length(); i > 0; i--) {
			if (!isAcceptable(word[i])) {
				sind = i;
				continue;
			}
			break;
		}
		for (int x = ind; x < sind; x++) {
			if (isAcceptable(word[x]) || word[x] == '-') {
				newword += word[x];
			}
		}
		if (newword.size() == 0) { // if blank space
			continue;
		}
		transform(newword.begin(), newword.end(), newword.begin(), ::toupper);
		speech.push_back(newword);
		newword = "";
	}

	for (int ind = 0; ind <= (speech.size() - wordcount); ind++) {
		add = true;
		newword = speech[ind];
		for (int j = 1; j < wordcount; j++) {
			if (speech.size() >= (ind + wordcount)) {
				newword += " " + speech[ind + j];
			}
		}
		if (!words.empty()) { // if the vector is NOT empty
			for (int x = 0; x < (words.size() - 1); x++) {
				if (words[x] == newword) {
					words[x]++;
					add = false;
					break;
				}
			}
		}
		if (add) {
			words.push_back(MyString(newword));
		}
		newword = "";
	}

	sort(words.begin(), words.end(), freqcompare); // Need to make it alpha order as well
	outfile << "The file: " << fileout << " contains " << speech.size() << " words, and " << words.size() << " phrases." << endl;
	for (int x = 0; x < words.size(); x++) {
		outfile << words[x];
	}
}
