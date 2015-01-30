#include "TestDatastore.h"


TestDatastore::TestDatastore(void)
{
}


TestDatastore::~TestDatastore(void)
{
}

void TestDatastore::loadData()
{
	Transaction t;
	t.group = 1;
	t.id = 1;
	vector<bool> items;
	items.resize(8,true);
	items[5] = items[6] = items[7] = false;
	t.items = items;
	transactions.push_back(t);

	t.id = 2;
	items[5] = true;
	t.items = items;
	transactions.push_back(t);

	t.id = 3;
	t.group = 2;
	items[5] = false;
	items[6] = items[7] = true;
	t.items = items;
	transactions.push_back(t);

	t.id = 4;
	t.group = 3;
	items[2] = items[3] = items[6] = items[7] = false;
	t.items = items;
	transactions.push_back(t);

	t.id = 5;
	t.group = 2;
	items[0] = false;
	items[2] = items[3] = items[4] = items[6] = items[7] = true;
	t.items = items;
	transactions.push_back(t);
}
