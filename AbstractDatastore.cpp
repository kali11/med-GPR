#include "AbstractDatastore.h"


AbstractDatastore::AbstractDatastore(void)
{
}


AbstractDatastore::~AbstractDatastore(void)
{
}

set<int> AbstractDatastore::getSupportingSet(vector<bool> items)
{
	set<int> result;
	for(Transaction t : transactions)
	{
		if(GRMUtils::isSubsetOfItems(items, t.items))
			result.insert(t.id);
	}
	return result;
}

int AbstractDatastore::getSupport(vector<bool> items)
{
	return getSupportingSet(items).size();
}

void AbstractDatastore::display()
{
	for(Transaction t : transactions)
	{
		t.display();
	}
}
