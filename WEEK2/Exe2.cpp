#include <iostream>
using namespace std;

int sentinelLinearSearch(int a[], int n, int key) {
	int last = a[n - 1];//store the last element
	a[n - 1] = key;

	int i = 0;
	while (a[i] != key) {
		i++;
	}
	a[n - 1] = last;//restore the last element
	if (i < n - 1 || a[i] == key)
		return i;
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
	cout << sentinelLinearSearch(a, n, key);
	return 0;
}