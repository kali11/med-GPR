#include "Transaction.h"


Transaction::Transaction(unsigned int ncol)
{
	items.resize(ncol, pair<unsigned int, unsigned int>(numeric_limits<unsigned int>::max(), numeric_limits<unsigned int>::max()));
}


Transaction::~Transaction(void)
{
}

void Transaction::display()
{
	cout << id << "| ";
	for(int i = 0; i < items.size(); i++)
	{
		cout << items[i].second << "|";
	}
	cout << "|" << group << endl;
}
