#pragma once
#include <vector>
#include <set>
#include "Transaction.h"
#include "GRMUtils.h"

using namespace std;

class AbstractDatastore
{
protected:
	
public:
	vector<Transaction> transactions;
	AbstractDatastore(void);
	~AbstractDatastore(void);
	virtual unsigned int loadData(string)=0;
	int getSupport(vector<pair<unsigned int, unsigned int>> items); //zwraca wsparcie dla zbioru
	set<int> getSupportingSet(vector<pair<unsigned int, unsigned int>> items); //zwraca wektor id transakcji
	void display();
};

