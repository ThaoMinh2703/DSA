#include <iostream>
using namespace std;

int binarySearchMinimum(int a[], int n) {
	int left = 0;
	int right = n - 1;
	int mid = (left + right) / 2;

	while (left < right) {
		mid = (left + right) / 2;
		if (a[mid] > a[right]) left = mid + 1;
		if (a[mid] < a[right])right = mid;
	}
	return a[left];
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
	cout << binarySearchMinimum(a, n);
	return 0;
}