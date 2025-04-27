#include <iostream>
using namespace std;

const int N = 8;
int board[N][N] = { 0 };
int solutions = 0;//count valid solutions

//function check if the N-Queen can be placed at board[row][col]
bool isSafe(int row, int col) {
	for (int i = 0; i < row; i++) {
		if (board[i][col] == 1) return false;//check column

		if (col - row + i > 0 && board[i][col - row + i] == 1)
			return false;//check left diagonal

		if (col + row - i < N && board[i][col + row - i] == 1)
			return false;//check right diagonal
	}
	return true;
}

//backtracking function to place queens

void solveNQueen(int row) {
	if (row == N) {
		solutions++;//sucessfully
		return;
	}

	for (int col = 0; col < N; col++) {
		if (isSafe(row, col)) {
			board[row][col] = 1;//place queen
			solveNQueen(row + 1);//recursive
			board[row][col] = 0;//backtracking
		}
	}
}

int main() {
	solveNQueen(0);
	cout << solutions << endl;
	return 0;
}