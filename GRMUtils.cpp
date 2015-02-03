#include "GRMUtils.h"
#include <cassert>


GRMUtils::GRMUtils(void)
{
}


GRMUtils::~GRMUtils(void)
{
}

//if items1 is a subset of items2
bool GRMUtils::isSubsetOfItems(vector<pair<unsigned int, unsigned int>> items1, vector<pair<unsigned int, unsigned int>> items2)
{
	for(unsigned i = 0; i < items1.size(); i++)
	{
		if(find(items2.begin(), items2.end(), items1[i]) == items2.end()) return false;
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

vector<pair<unsigned int, unsigned int>> GRMUtils::joinItems(vector<pair<unsigned int, unsigned int>> items1, vector<pair<unsigned int, unsigned int>> items2)
{
	vector<pair<unsigned int, unsigned int>> x(items1);
	x.insert(x.end(), items2.begin(), items2.end());
	return x;
}

set<vector<pair<unsigned int, unsigned int>>> GRMUtils::addList2ToList1(set<vector<pair<unsigned int, unsigned int>>> list1, set<vector<pair<unsigned int, unsigned int>>> list2)
{
	set<vector<pair<unsigned int, unsigned int>>> result;

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
