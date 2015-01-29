#include "Transaction.h"


Transaction::Transaction(int itemsSize)
{
	items = new bool[itemsSize];
	this->itemsSize = itemsSize;
	for(int i = 0; i < itemsSize; i++)
	{
		items[i] = false;
	}
}


Transaction::~Transaction(void)
{
}

void Transaction::display()
{
	cout << id << "| ";
	for(int i = 0; i < itemsSize; i++)
	{
		cout << items[i] << "|";
	}
	cout << "|" << group << endl;
}

bool Transaction::isSubset(bool items[27], bool items2[27])
{
	for(int i = 0; i < 27; i++) 
	{
		if(items[i] > items2[i]) return false;
	}
	return true;
}
