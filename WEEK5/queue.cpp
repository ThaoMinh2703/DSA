#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct NODE {
	int key;
	NODE* p_next;
};


struct Queue {
	NODE* head;
	NODE* tail;
};

Queue* initializeQueue() {
	Queue* q = new Queue;
	q->head = nullptr;
	q->tail = nullptr;
	return q;
}

bool isEmpty(Queue q) {
	return q.head == nullptr;
}
NODE* createNode(int key) {
	NODE* newNode = new NODE;
	newNode->key = key;
	newNode->p_next = NULL;
	return newNode;
}

void enqueue(Queue& q, int key) {
	NODE* newNode = createNode(key);

	if (q.tail) q.tail->p_next = newNode;
	else q.head = newNode;
	q.tail = newNode;
}

int dequeue(Queue& q) {
	if (isEmpty(q))
		return 0;

	NODE* temp = q.head;
	int value = temp->key;
	q.head = q.head->p_next;

	if (!q.head)
		q.tail = nullptr;

	delete temp;
	return value;
}

int size(Queue q) {
	if (isEmpty(q))
		return 0;

	int cnt = 0;
	NODE* p = q.head;
	while (p != NULL) {
		cnt++;
		p = p->p_next;
	}
	return cnt;
}

void printQueue(Queue q, ofstream& fout) {
	if (isEmpty(q)) {
		fout << "EMPTY\n";
		return;
	}

	int n = size(q);
	int* arr = new int[n];
	NODE* curr = q.head;
	int i = 0;
	while (curr != nullptr) {
		arr[i] = curr->key;
		curr = curr->p_next;
		i++;
	}

	for (int j = 0; j < n; j++) {
		fout << arr[j];
		if (j != 1)fout << " ";

	}
	fout << "\n";
	delete[]arr;
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	Queue* q = nullptr;

	char command[20];

	while (fin >> command) {
		if (strcmp(command, "init") == 0) {
			q = initializeQueue();
			fout << "EMPTY\n";
		}
		else if (strcmp(command, "enqueue") == 0) {
			int key;
			fin >> key;
			enqueue(*q, key);
			printQueue(*q, fout);
		}
		else if (strcmp(command, "dequeue") == 0) {
			int value = dequeue(*q);
			if (value == 0) {
				fout << "EMPTY\n";
			}
			else {
				printQueue(*q, fout);
			}
		}
	}
	fin.close();
	fout.close();
	return 0;
}