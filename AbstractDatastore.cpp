#include "AbstractDatastore.h"


AbstractDatastore::AbstractDatastore(void)
{
}


AbstractDatastore::~AbstractDatastore(void)
{
}

set<int> AbstractDatastore::getSupportingSet(vector<pair<unsigned int, unsigned int>> items)
{
	set<int> result;
	for(Transaction t : transactions)
	{
		if(GRMUtils::isSubsetOfItems(items, t.items))
			result.insert(t.id);
	}
	return result;
}

int AbstractDatastore::getSupport(vector<pair<unsigned int, unsigned int>> items)
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
