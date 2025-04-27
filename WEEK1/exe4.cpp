#include <iostream>
using namespace std;

//recursive function to solve Tower of Hanoi
void TowerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) {
	if (n == 1) {
		cout << "Move disk 1 from " << from_rod << " to " << to_rod << endl;
		return;
	}
	TowerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
	cout << "Move disk " << n << " from " << from_rod << " to " << to_rod << endl;
	TowerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main() {
	int n = 3;
	TowerOfHanoi(n, 'A', 'B', 'C');
	return 0;
}