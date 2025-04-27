#include <iostream>
using namespace std;

bool canShip(int arr[], int n, int days, int capicity) {
	int currentWeight = 0;
	int requireDays = 1;

	for (int i = 0; i < n; i++) {
		if (currentWeight + arr[i] > capicity) {
			requireDays++;
			currentWeight = 0;
		}
		currentWeight += arr[i];
	}
	return requireDays <= days;
}

int leastWeight(int arr[], int n, int days) {
	int high = 0;
	int low = 0;

	for (int i = 0; i < n; i++) {
		if (arr[i] > low)
			low = arr[i];
		high += arr[i];
	}

	while (low < high) {
		int mid = (high + low) / 2;

		if (canShip(arr, n, days, mid))
			high = mid;
		else low = mid + 1;
	}
	return low;
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
	int days;
	cin >> days;
	cout << leastWeight(a, n, days);
	return 0;
}