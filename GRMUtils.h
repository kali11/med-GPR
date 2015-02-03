#pragma once
#include <set>
#include <vector>
#include <iostream>

using namespace std;
class GRMUtils
{
public:
	// czy zbior atrybutow items1 jest podzbiorem atrybutow items2
	bool static isSubsetOfItems(vector<pair<unsigned int, unsigned int>> items1, vector<pair<unsigned int, unsigned int>> items2);
	// czy zbior id transakcji jest podzbiorem drugiego lub na odwrot
	bool static isSubsetOfTransactionList(set<int> list1, set<int> list2);
	// czy listy id transakcji sa rowne
	bool static isTransactionListsEqual(set<int> list1, set<int> list2);
	// zwraca czesc wspolna list id transakcji
	set<int> static getListProduct(set<int> list1, set<int> list2);

	vector<pair<unsigned int, unsigned int>> static joinItems(vector<pair<unsigned int, unsigned int>> items1, vector<pair<unsigned int, unsigned int>> items2);

	set<vector<pair<unsigned int, unsigned int>>> static addList2ToList1(set<vector<pair<unsigned int, unsigned int>>> list1, set<vector<pair<unsigned int, unsigned int>>> list2);
	GRMUtils(void);
	~GRMUtils(void);
};

