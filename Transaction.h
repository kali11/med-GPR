#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Transaction
{
public:
	int id;
	vector<pair<unsigned int, unsigned int>> items;
	int group;
	Transaction(unsigned int ncol);
	~Transaction(void);
	void display();

};

