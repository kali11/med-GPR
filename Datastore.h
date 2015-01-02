#pragma once
#include <vector>
#include "Transaction.h"

using namespace std;
class Datastore
{
private:
	vector<Transaction> transactions;
public:
	Datastore(void);
	~Datastore(void);
	float getSupport(bool items [27]); //zwraca wsparcie dla zbioru
	vector<int> getSupportingSet(bool items [27]); //zwraca zbiór wspierajacy
};

