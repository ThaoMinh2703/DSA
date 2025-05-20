#include <iostream>
#include <cmath>
#include <vector>

#define LH -1
#define EH 0
#define RH 1

using namespace std;

struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
	int height;
};

NODE* createNode(int data) {
	NODE* newNode = new NODE;
	newNode->key = data;
	newNode->height = EH;
	newNode->p_left = newNode->p_right = nullptr;
	return newNode;
}

int height(NODE* pRoot) {
	if (!pRoot)return 0;
	return pRoot->height;
}

int getBalance(NODE* pRoot) {
	if (!pRoot)return 0;
	return height(pRoot->p_left) - height(pRoot->p_right);
}

NODE* leftRotation(NODE* x) {
	NODE* y = x->p_right;
	NODE* z = y->p_left;

	y->p_left = x;
	x->p_right = z;

	x->height = max(height(x->p_left), height(x->p_right)) + 1;
	y->height = max(height(y->p_left), height(y->p_right)) + 1;

	return y;
}

NODE* rightRotation(NODE* x) {
	NODE* y = x->p_left;
	NODE* z = y->p_right;

	y->p_right = x;
	x->p_left = z;

	y->height = max(height(y->p_left), height(y->p_right)) + 1;
	x->height = max(height(x->p_left), height(x->p_right)) + 1;
	
	return y;
}

void Insert(NODE*& pRoot, int x) {
	if (!pRoot) {
		pRoot = createNode(x);
		return;
	}

	if (x < pRoot->key)
		Insert(pRoot->p_left, x);
	else if (x > pRoot->key)
		Insert(pRoot->p_right, x);
	else return;

	pRoot->height = 1 + max(height(pRoot->p_left), height(pRoot->p_right));

	int balance = getBalance(pRoot);

	if (balance > 1 && x < pRoot->p_left->key)
		pRoot = rightRotation(pRoot);

	else if (balance<-1 && x>pRoot->p_right->key)
		pRoot = leftRotation(pRoot);

	else if (balance > 1 && x > pRoot->p_left->key) {
		pRoot->p_left = leftRotation(pRoot->p_left);
		pRoot = rightRotation(pRoot);
	}

	else if (balance < -1 && x < pRoot->p_right->key) {
		pRoot->p_right = rightRotation(pRoot->p_right);
		pRoot = leftRotation(pRoot);
	}
}

NODE* minValueNode(NODE* p) {
	NODE* curr = p;
	while (curr->p_left) {
		curr = curr->p_left;
	}
	return curr;
}

void Remove(NODE*& pRoot, int x) {
	if (!pRoot)return;

	if (x < pRoot->key)
		Remove(pRoot->p_left, x);
	else if (x > pRoot->key)
		Remove(pRoot->p_right, x);

	else {
		if (!pRoot->p_left || !pRoot->p_right) {
			NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
			if (!temp) {
				temp = pRoot;
				pRoot = nullptr;
			}
			else {
				*pRoot = *temp;
			}
			delete temp;
		}
		else {
			NODE* temp = minValueNode(pRoot->p_right);
			pRoot->key = temp->key;
			Remove(pRoot->p_right, temp->key);
		}
	}
	if (!pRoot) return;

	pRoot->height = 1 + max(height(pRoot->p_left), height(pRoot->p_right));

	int balance = getBalance(pRoot);

	if (balance > 1 && getBalance(pRoot->p_left) >= 0)
		pRoot = rightRotation(pRoot);

	else if (balance < -1 && getBalance(pRoot->p_right) <= 0)
		pRoot = leftRotation(pRoot);

	else if (balance > 1 && getBalance(pRoot->p_left) < 0) {
		pRoot->p_left = leftRotation(pRoot->p_left);
		pRoot = rightRotation(pRoot);
	}

	else if (balance < -1 && getBalance(pRoot->p_right) > 0) {
		pRoot->p_right = rightRotation(pRoot->p_right);
		pRoot = leftRotation(pRoot);
	}
}

bool isAVL(NODE* pRoot) {
	if (!pRoot)return true;

	int balance = getBalance(pRoot);
	if (balance > 1 || balance < -1)
		return false;

	return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}