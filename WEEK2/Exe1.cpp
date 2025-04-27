#include <iostream>
using namespace std;

int linearSearch(int a[], int n, int key) {
	for (int i = 0; i < n; i++) {
		if (a[i] == key)
			return i;
	}
	return -1;
}

int main() {
	int a[1000];
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;

	int key;
	cin >> key;
	cout << linearSearch(a, n, key);
	return 0;
}