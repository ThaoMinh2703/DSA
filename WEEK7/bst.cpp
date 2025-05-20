#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};

NODE* Search(NODE* pRoot, int x) {
	if (pRoot) {
		if (pRoot->key == x)
			return pRoot;
		if (pRoot->key > x)
			return Search(pRoot->p_left, x);
		return Search(pRoot->p_right, x);
	}
	return nullptr;
}

void Insert(NODE*& pRoot, int x) {
	if (pRoot == nullptr) {
		pRoot = new NODE;
		pRoot->key = x;
		pRoot->p_left = pRoot->p_right = nullptr;
		return;
	}
	if (pRoot->key == x)
		return;

	if (pRoot->key > x)
		Insert(pRoot->p_left, x);
	else
		Insert(pRoot->p_right, x);
}

void Remove(NODE*& pRoot, int x) {
	if (pRoot == nullptr)return;

	if (x < pRoot->key) {
		Remove(pRoot->p_left, x);
	}
	else if (x > pRoot->key) {
		Remove(pRoot->p_right, x);
	}
	else {
		if (pRoot->p_left == nullptr && pRoot->p_right == nullptr)
		{
			delete pRoot;
			pRoot = nullptr;
		}
		else if (pRoot->p_left == nullptr) {
			NODE* temp = pRoot;
			pRoot = pRoot->p_right;
			delete temp;
		}
		else if (pRoot->p_right == nullptr) {
			NODE* temp = pRoot;
			pRoot = pRoot->p_left;
			delete temp;
		}
		else {
			NODE* minNodeParent = pRoot;
			NODE* minNode = pRoot->p_right;
			while (minNode->p_left != nullptr) {
				minNodeParent = minNode;
				minNode = minNode->p_left;
			}
			pRoot->key = minNode->key;
			
			if (minNodeParent == pRoot) {
				minNodeParent->p_right = minNode->p_right;
			}
			else {
				minNodeParent->p_left = minNode->p_right;
			}
			delete minNode;
		}
	}
}

NODE* createTree(int a[], int n) {
	NODE* pRoot = nullptr;
	for (int i = 0; i < n; i++) {
		Insert(pRoot, a[i]);
	}
	return pRoot;
}

void removeTree(NODE*& pRoot) {
	if (pRoot == nullptr)return;
	
	removeTree(pRoot->p_left);
	removeTree(pRoot->p_right);

	delete pRoot;
	pRoot = nullptr;
}

int Height(NODE* pRoot) {
	if (pRoot == nullptr)return -1;

	int leftHeight = Height(pRoot->p_left);
	int rightHeight = Height(pRoot->p_right);

	return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int countLess(NODE* pRoot, int x) {
	if (pRoot == nullptr)return 0;

	if (pRoot->key >= x) {
		return countLess(pRoot->p_left, x);
	}
	else {
		return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
	}
}

int countGreater(NODE* pRoot, int x) {
	if (pRoot == nullptr)return 0;

	if (pRoot->key <= x) {
		return countGreater(pRoot->p_right, x);
	}
	else {
		return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
	}
}

bool isBST(NODE* pRoot) {
	NODE* stack[1000];
	int top = -1;
	NODE* curr = pRoot;
	NODE* prev = nullptr;

	while (curr != nullptr || top != -1) {
		while (curr != nullptr) {
			stack[++top] = curr;
			curr = curr->p_left;
		}
		curr = stack[top--];

		if (prev != nullptr && curr->key <= prev->key)
			return false;

		prev = curr;
		curr = curr->p_right;
	}
	return true;
}

bool isFullBST(NODE* pRoot) {
	if (pRoot == nullptr)return true;

	if ((pRoot->p_left == nullptr) && (pRoot->p_right == nullptr))return true;

	if (pRoot->p_left != nullptr && pRoot->p_right != nullptr)
		return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);
	return false;
}

