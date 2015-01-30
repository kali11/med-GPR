#include <iostream>
#include "Datastore.h"
#include "AbstractDatastore.h"
#include "TestDatastore.h"
#include <vector>
#include <set>

using namespace std;

void tests();

int main(int argc, char *argv[])
{
	cout << "main" << endl;

	tests();
	system("PAUSE");
	return 0;
}

void tests()
{
	cout << "testy" << endl;

	// test wczytywania danych i zamiany do postaci transakcyjnej
	Datastore datastore;
	datastore.loadData();

	// test TestDatastore
	TestDatastore testDatastore;
	testDatastore.loadData();
	testDatastore.display();

	vector<bool> testItems;
	testItems.resize(8, false);
	testItems[7] = true;
	if(testDatastore.getSupport(testItems) != 2)
		cout << "getSupport() for testDatabase ERROR" << endl;

	// testy liczenia wsparcia
	vector<bool> items;// {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,  0,1};
	items.resize(27, false);
	items[26] = true;
	if(datastore.getSupport(items) != 205) cout << "getSupport() ERROR" << endl;

	// testy getSupportingSet
	vector<bool> example; //{1,0,0, 1,0,0, 1,0,0, 1,0,0, 0,1,0, 0,1,0, 1,0,0, 0,1,0, 0,1,0};
	example.resize(27, false);
	example[0] = example[3] = example[6] = example[9] = example[13] = example[16] = example[18] = example[22] = example[25] = true;
	if(datastore.getSupportingSet(example).size() != 1) cout << "getSupportingSet() ERROR" << endl;

	// testy isSubset()
	vector<bool> bigset;
	bigset.resize(27, false);
	bigset[0] = bigset[1] = bigset[2] = bigset[26] = true;
	if(!GRMUtils::isSubsetOfItems(items, bigset)) cout << "isSubset() ERROR" << endl;
	bigset[26] = false;
	if(GRMUtils::isSubsetOfItems(items, bigset)) cout << "isSubset() ERROR" << endl;

	// testy isTransactionListsEqual
	set<int> set1;
	set1.insert(1);
	set1.insert(2);
	if(!GRMUtils::isTransactionListsEqual(set1, set1)) cout << "isTransactionListsEqual ERROR" << endl;

	// testy isSubsetOfTransactionList
	if(GRMUtils::isSubsetOfTransactionList(set1, set1)) cout << "isSubsetOfTransactionList ERROR" << endl;
	set<int> set2;
	set2.insert(1);
	if(!GRMUtils::isSubsetOfTransactionList(set1, set2)) cout << "isSubsetOfTransactionList ERROR" << endl;
	if(!GRMUtils::isSubsetOfTransactionList(set2, set1)) cout << "isSubsetOfTransactionList ERROR" << endl;
	set2.insert(3);
	if(GRMUtils::isSubsetOfTransactionList(set1, set2)) cout << "isSubsetOfTransactionList ERROR" << endl;
	if(GRMUtils::isSubsetOfTransactionList(set2, set1)) cout << "isSubsetOfTransactionList ERROR" << endl;
	cout << "koniec testow" << endl;

}