#include "GRMUtils.h"


GRMUtils::GRMUtils(void)
{
}


GRMUtils::~GRMUtils(void)
{
}

bool GRMUtils::isSubsetOfItems(vector<bool> items1, vector<bool> items2)
{
	if(items1.size() != items2.size())
	{
		cout << "Zla wielkosc wektorow items" << endl;
		return false;
	}
	for(unsigned i = 0; i < items1.size(); i++)
	{
		if(items1[i] > items2[i]) return false;
	}
	return true;
}

bool GRMUtils::isTransactionListsEqual(set<int> list1, set<int> list2)
{
	return list1 == list2;
}

bool GRMUtils::isSubsetOfTransactionList(set<int> list1, set<int> list2)
{
	if(list1 == list2) return false;

	bool list1Inlist2 = true;
	for(auto it = list1.begin(); it != list1.end(); ++it)
	{
		if(list2.find(*it) == list2.end()) list1Inlist2 = false;
	}

	bool list2Inlist1 = true;
	for(auto it = list2.begin(); it != list2.end(); ++it)
	{
		if(list1.find(*it) == list1.end()) list2Inlist1 = false;
	}
	return list1Inlist2 || list2Inlist1;
}
