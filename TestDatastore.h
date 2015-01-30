#pragma once
#include "AbstractDatastore.h"
#include "Transaction.h"

using namespace std;

class TestDatastore : public AbstractDatastore
{
public:
	void loadData();
	TestDatastore(void);
	~TestDatastore(void);
};

