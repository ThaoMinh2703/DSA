#include <iostream>
using namespace std;

//Function to check an array is sorted using recursion
bool isSorted(int arr[], int n) {
	if (n == 1 || n == 0) return true;//if there is only one or zero elements, it is sorted

	if (arr[0] > arr[1]) return false;

	return isSorted(arr + 1, n - 1);// check the rest of array
}

int main() {
	int arr[100];
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	if (isSorted(arr, n)) {
		cout << "\nThe array is Sorted" << endl;
	}
	else cout << "\nThe array is Not Sorted" << endl;
	
	return 0;
}