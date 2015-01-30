#include "Transaction.h"


Transaction::Transaction()
{
}


Transaction::~Transaction(void)
{
}

void Transaction::display()
{
	cout << id << "| ";
	for(int i = 0; i < items.size(); i++)
	{
		cout << items[i] << "|";
	}
	cout << "|" << group << endl;
}
