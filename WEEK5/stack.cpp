#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>

using namespace std;

struct NODE {
	int key;
	NODE* p_next;
};


struct Stack {
	NODE* top;
};

Stack* initializeStack() {
	Stack* s = new Stack;
	s->top = nullptr;
	return s;
}

NODE* createNode(int key) {
	NODE* newNode = new NODE;
	newNode->key = key;
	newNode->p_next = NULL;
	return newNode;
}
bool isEmpty(Stack s) {
	return s.top == nullptr;
}

void push(Stack& s, int key) {
	NODE* newNode = createNode(key);
	newNode->p_next = s.top;
	s.top = newNode;
}

int pop(Stack& s) {
	if (isEmpty(s))
		return -1;

	NODE* temp = s.top;
	int value = temp->key;
	s.top = s.top->p_next;
	delete temp;
	return value;
}

int size(Stack s) {
	if (isEmpty(s))
		return 0;

	int cnt = 0;
	NODE* p = s.top;
	while (p != NULL) {
		cnt++;
		p = p->p_next;
	}
	return cnt;

}

void printStack(Stack s, ofstream& fout) {
	if (isEmpty(s)) {
		fout << "EMPTY\n";
		return;
	}

	int n = size(s);
	int* arr = new int[n];
	NODE* curr = s.top;
	int i = n - 1;
	while (curr != nullptr) {
		arr[i] = curr->key;
		curr = curr->p_next;
		i--;
	}

	for (int j = 0; j < n; j++) {
		fout << arr[j];
		if (j != n - 1)fout << " ";

	}
	fout << "\n";
	delete[]arr;
}
int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	Stack* s = nullptr;

	char command[20];

	while (fin >> command) {
		if (strcmp(command, "init") == 0) {
			s = initializeStack();
			fout << "EMPTY\n";
		}
		else if (strcmp(command, "push") == 0) {
			int key;
			fin >> key;
			push(*s, key);
			printStack(*s, fout);
		}
		else if (strcmp(command, "pop") == 0) {
			int value = pop(*s);
			if (value == -1) {
				fout << "EMPTY\n";
			}
			else {
				printStack(*s, fout);
			}
		}
	}
	fin.close();
	fout.close();
	return 0;

}







