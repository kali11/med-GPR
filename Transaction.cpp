#include "Transaction.h"


Transaction::Transaction(unsigned int ncol)
{
	items.resize(ncol);
	group = -1;
	id = -1;
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
