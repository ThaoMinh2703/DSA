#ifndef _FUNCTION_H
#define _FUNCTION_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>


using namespace std;

const int p = 31;
const int m = 2000;
const int TABLE_SIZE = 2000;


struct Company {
	string name;
	string profit_tax;
	string address;
};

struct Node {
	Company data;
	Node* pNext;
};

struct HashTable {
	Node* table[TABLE_SIZE];
};

vector <Company> readCompanyList(string file_name);
long long hashString(string company_name);
HashTable* createHashTable(vector <Company>list_company);
void insert(HashTable* hash_table, Company company);
Company* search(HashTable* hash_table, string company_name);
void processFile(const string& inputFile, const string& outputFile, HashTable* hash_table);

#endif
