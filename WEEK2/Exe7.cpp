#include <iostream>
using namespace std;

void Sort(int a[], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (a[j] < a[i]) {
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}

void tripletSum(int a[], int n) {
	Sort(a, n);
	for (int i = 0; i < n - 2; i++) {
		if (i > 0 && a[i] == a[i - 1]) continue;
		int left = i + 1;
		int right = n - 1;
		while (left < right) {
			int sum = a[i] + a[left] + a[right];

			if (sum == 0) {
				cout << a[i] << " " << a[left] << " " << a[right] << endl;

				while (left < right && a[left] == a[left + 1])left++;
				while (left < right && a[right - 1] == a[right]) right--;


				left++;
				right--;
			}

			else if (sum < 0) left++;
			else right--;
		}
		
	}
}

int main() {
	int n;
	int a[1000];
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;

	tripletSum(a, n);
	return 0;
}