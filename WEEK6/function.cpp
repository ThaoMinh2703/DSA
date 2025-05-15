#include "function.h"

vector <Company>readCompanyList(string file_name) {
	vector <Company> companies;
	ifstream inFile(file_name);
	if (!inFile.is_open()) {
		cout << "Cannot open MST file" << file_name << endl;
		return companies;
	}

	string line;
	getline(inFile, line);

	while (getline(inFile, line)) {
		size_t pos1 = line.find('|');
		size_t pos2 = line.find('|', pos1 + 1);

		if (pos1 == string::npos || pos2 == string::npos)
			continue;
	
		Company c;
		c.name = line.substr(0, pos1);
		c.profit_tax = line.substr(pos1 + 1, pos2 - pos1 - 1);
		c.address = line.substr(pos2 + 1);

		companies.push_back(c);
	}
	inFile.close();
	return companies;
}

long long hashString(string company_name) {
	int len = company_name.size();
	string s = (len <= 20) ? company_name : company_name.substr(len - 20);
	long long hash = 0;
	long long pow = 1;
	for (int i = 0; i < s.length(); i++) {
		int ascii_val = (int)s[i];
		hash = (hash + ascii_val * pow) % m;
		pow = (pow * p) % m;
	}
	return hash;
}

HashTable* createHashTable(vector <Company>list_company) {
	HashTable* ht = new HashTable;
	for (int i = 0; i < TABLE_SIZE; i++) {
		ht->table[i] = nullptr;
	}

	for (const Company& c : list_company)
		insert(ht, c);
	return ht;
}

void insert(HashTable* hash_table, Company company) {
	Company comp;
	comp.name = company.name;
	comp.address = company.address;
	comp.profit_tax = company.profit_tax;

	long long index = hashString(comp.name);

	Node* newNode = new Node;
	newNode->data = comp;
	newNode->pNext = hash_table->table[index];
	hash_table->table[index] = newNode;
}

Company* search(HashTable* hash_table, string company_name) {
	long long index = hashString(company_name);
	Node* curr = hash_table->table[index];

	while (curr != nullptr) {
		if (curr->data.name == company_name) {
			return &(curr->data);
		}
		curr = curr->pNext;
	}
	return nullptr;
}

void processFile(const string& inputFile, const string& outputFile, HashTable* hash_table) {
	ifstream fin(inputFile);
	ofstream fout(outputFile);

	if (!fin.is_open()) {
		cout << "Cannot open input file" << endl;
		return;
	}

	if (!fout.is_open()) {
		cout << "Cannot open output file" << endl;
		return;
	}

	string line;
	while (getline(fin, line)) {
		Company* res = search(hash_table, line);
		if (res) {
			string result = res->name + "|" + res->profit_tax + "|" + res->address + "\n";
			fout << result;
			cout << result;
		}
		else {
			string notFound = line + "|NOT FOUND\n";
			fout << notFound;
			cout << notFound;
		}
	}
	fin.close();
	fout.close();
}