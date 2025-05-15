#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "function.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 4) {
		cout << "Error arguments" << endl;
		return 1;
	}

	string mstFile = argv[1];
	string inputFile = argv[2];
	string outputFile = argv[3];

	ifstream inFile(inputFile);
	if (!inFile.is_open()) {
		return 1;
	}

	vector <Company>list_company = readCompanyList(mstFile);
	if (list_company.empty()) {
		cout << "No company data loaded" << endl;
		return 1;
	}
	HashTable* ht = createHashTable(list_company);
	processFile(inputFile, outputFile, ht);


	return 0;
}


