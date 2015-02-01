#pragma once
#include "AbstractDatastore.h"
#include "Transaction.h"

using namespace std;

class TestDatastore : public AbstractDatastore
{
public:
	const static int ITEMS_SIZE = 8;

	void loadData();
	TestDatastore(void);
	~TestDatastore(void);
};

