#include <iostream>
using namespace std;

int fibonacci(int n) {
	if (n <= 2) return (n - 1);
	return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cout << fibonacci(i) << " ";
	}
	return 0;
}