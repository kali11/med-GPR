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

set<int> GRMUtils::getListProduct(set<int> list1, set<int> list2)
{
	if(list1 == list2) return list1;

	set<int> result;
	for(auto it = list1.begin(); it != list1.end(); ++it)
	{
		if(list2.find(*it) != list2.end()) result.insert(*it);
	}
	for(auto it = list2.begin(); it != list2.end(); ++it)
	{
		if(list1.find(*it) != list1.end()) result.insert(*it);
	}
	return result;
}

vector<bool> GRMUtils::joinItems(vector<bool> items1, vector<bool> items2)
{
	vector<bool> result;
	if(items1.size() != items2.size())
	{
		cout << "wektory nie sa rownej dlugosci" << endl;
		return result;
	}
	for(int i = 0; i < items1.size(); ++i)
	{
		result.push_back(items1[i] || items2[i]);
	}
	return result;
}

set<vector<bool>> GRMUtils::addList2ToList1(set<vector<bool>> list1, set<vector<bool>> list2)
{
	set<vector<bool>> result;
	for(auto it = list1.begin(); it != list1.end(); ++it)
	{
		result.insert(*it);
	}
	for(auto it = list2.begin(); it != list2.end(); ++it)
	{
		result.insert(*it);
	}
	return result;
}
