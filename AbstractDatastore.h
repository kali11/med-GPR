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
	virtual void loadData()=0;
	int getSupport(vector<bool> items); //zwraca wsparcie dla zbioru
	set<int> getSupportingSet(vector<bool> items); //zwraca wektor id transakcji
	void display();
};

