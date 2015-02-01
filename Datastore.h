#pragma once
#include <set>
#include <vector>
#include "Transaction.h"
#include "GRMUtils.h"
#include <fstream>
#include <iostream>
#include <string>
#include "AbstractDatastore.h"

using namespace std;
class Datastore : public AbstractDatastore
{
private:
	
	ifstream openDataFile();
	Transaction createTransactionFromLine(string line);
public:
	string fileName;
	static const int ITEMS_SIZE = 16;
	Datastore(void);
	~Datastore(void);
	void loadData();
};

