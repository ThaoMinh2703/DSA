#include <iostream>
#include <limits.h>
using namespace std;

int minLength(int a[], int n, int target) {
	int left = 0;
	int sum = 0;
	int minLength = INT_MAX;
	for (int right = 0; right < n; right++) {
		sum += a[right];
		while (sum >= target) {
			int currentLength = right - left + 1;
			if (currentLength < minLength)
				minLength = currentLength;
			
			sum -= a[left];
			left++;
		}
	}
	return (minLength == INT_MAX) ? 0 : minLength;

}

int main() {
	int a[1000];
	int n;
	cin >> n;
	cout << "nums = ";
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int target;
	cout << "target = ";
	cin >> target;
	cout << minLength(a, n, target);
	return 0;

}