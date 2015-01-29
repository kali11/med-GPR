#pragma once
#include <vector>
#include "Transaction.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
class Datastore
{
private:
	vector<Transaction> transactions;
	ifstream openDataFile();
	Transaction createTransactionFromLine(string line);
public:
	Datastore(void);
	~Datastore(void);
	void loadData();
	int getSupport(bool items [27]); //zwraca wsparcie dla zbioru
	vector<int> getSupportingSet(bool items [27]); //zwraca wektor id transakcji
	void display();
};

