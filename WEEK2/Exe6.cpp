#include <iostream>
using namespace std;

bool equalToTarget(int arr[], int n, int target) {
	int left = 0;
	int right = n - 1;

	while (left < right) {
		int sum = arr[left] + arr[right];

		if (sum == target)
			return true;
		else if (sum < target)
			left++;
		else right--;
	}
	return false;
}

int main() {
	int arr[1000];
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	int target;
	cin >> target;
	if (equalToTarget(arr, n, target)) cout << "YES";
	else cout << "NO";
}