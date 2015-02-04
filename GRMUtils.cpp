#include "GRMUtils.h"
#include <algorithm>
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
	for (unsigned i = 0; i < items1.size(); i++)
	{
		if (find(items2.begin(), items2.end(), items1[i]) == items2.end()) return false;
	}
	return true;
}

bool GRMUtils::isTransactionListsEqual(set<int> list1, set<int> list2)
{
	return list1 == list2;
}

//checks whether A is a proper subset of B or vice versa
bool GRMUtils::isSubsetOfTransactionList(set<int> list1, set<int> list2)
{
	if (list1 == list2) return false;

	bool list1Inlist2 = true;
	for (auto it = list1.begin(); it != list1.end(); ++it)
	{
		if (list2.find(*it) == list2.end()) list1Inlist2 = false;
	}

	if (list1Inlist2) return true;

	for (auto it = list2.begin(); it != list2.end(); ++it)
	{
		if (list1.find(*it) == list1.end()) return false;
	}

	return true;
}

//calculates set intersection
set<int> GRMUtils::getListProduct(set<int> list1, set<int> list2)
{
	if (list1 == list2) return list1;

	set<int> result;
	for (auto it = list1.begin(); it != list1.end(); ++it)
	{
		if (list2.find(*it) != list2.end()) result.insert(*it);
	}

	return result;
}

vector<pair<unsigned int, unsigned int>> GRMUtils::joinItems(vector<pair<unsigned int, unsigned int>> items1, vector<pair<unsigned int, unsigned int>> items2)
{
	vector<pair<unsigned int, unsigned int>> vec(items1);
	set<pair<unsigned int, unsigned int>> s;
	vec.insert(vec.end(), items2.begin(), items2.end());
	unsigned size = vec.size();
	for (unsigned i = 0; i < size; ++i) s.insert(vec[i]);
	vec.assign( s.begin(), s.end() );

	return vec;
}

set<vector<pair<unsigned int, unsigned int>>> GRMUtils::addList2ToList1(set<vector<pair<unsigned int, unsigned int>>> list1, set<vector<pair<unsigned int, unsigned int>>> list2)
{
	set<vector<pair<unsigned int, unsigned int>>> result;

	for (auto it = list1.begin(); it != list1.end(); ++it)
	{
		result.insert(vector<pair<unsigned int, unsigned int>>(*it));
	}

	for (auto it = list2.begin(); it != list2.end(); ++it)
	{
		result.insert(vector<pair<unsigned int, unsigned int>>(*it));
	}

	return result;
}
