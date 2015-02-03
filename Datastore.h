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
	
	ifstream openDataFile(string fileName);
	Transaction createTransactionFromLine(string line, char separator, unsigned int ncol);

public:

	vector<set<string>> constants;
	Datastore(void);
	~Datastore(void);
	unsigned int loadData(string fileName);
};

