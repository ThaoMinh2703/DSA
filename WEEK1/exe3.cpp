#include <iostream>
#include <string>
using namespace std;

void generateBinaryStrings(int n, string str) {
	if (str.length() == n) {
		cout << str << "\n";
		return;
	}

	generateBinaryStrings(n, str + "0");//add 0 into recursive string
	generateBinaryStrings(n, str + "1");//add 1 into recursive string

}

int main() {
	int n;
	cout << "Enter n: ";
	cin >> n;

	generateBinaryStrings(n, "");
	return 0;
}