#pragma once
#include <set>
#include <vector>
#include <iostream>

using namespace std;
class GRMUtils
{
public:
	// czy zbior atrybutow items1 jest podzbiorem atrybutow items2
	bool static isSubsetOfItems(vector<bool> items1, vector<bool> items2);
	// czy zbior id transakcji jest podzbiorem drugiego lub na odwrot
	bool static isSubsetOfTransactionList(set<int> list1, set<int> list2);
	// czy listy id transakcji sa rowne
	bool static isTransactionListsEqual(set<int> list1, set<int> list2);
	// zwraca czesc wspolna list id transakcji
	set<int> static getListProduct(set<int> list1, set<int> list2);

	vector<bool> static joinItems(vector<bool> items1, vector<bool> items2);
	GRMUtils(void);
	~GRMUtils(void);
};

