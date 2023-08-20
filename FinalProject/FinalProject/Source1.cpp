#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;
const int COLUMN_WIDTH = 60;
bool isAcceptable(char c)
{
	return (((c >= 48) && (c <= 57)) || ((c >= 65) && (c <= 90)) || ((c >=
		97) && (c <= 122)));
}
class MyString {
private:
	string str;
	int frequency;
public:
	MyString() {
		str = "";
		frequency = 0;
	}
	MyString(string s) {
		str = s;
		frequency = 1;
	}
	bool operator==(string rhs) const
	{
		return (str == rhs);
	}
	bool operator >(MyString s) const
	{
		if (frequency == s.frequency) {
			return str < s.str;
		}
		return frequency > s.frequency;
	}
	bool operator <(MyString s) const
	{
		return frequency < s.frequency;
	}
	MyString operator ++(int)
	{
		MyString temp = *this;
		frequency++;
		return temp;
	}
	friend ofstream& operator<<(ofstream& o, const MyString& obj);
};
// output to file
ofstream& operator<<(ofstream& o, const MyString& obj) {
	o.width(COLUMN_WIDTH);
	o << left << obj.str << obj.frequency << endl;
	return o;
}

bool freqcompare(const MyString& val1, const MyString& val2) {
	return val1 > val2;
}