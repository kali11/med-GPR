#include <iostream>
#include <fstream>
#include "Datastore.h"
#include "AbstractDatastore.h"
#include "TestDatastore.h"
#include <vector>
#include <set>
#include "GRM.h"
#include <time.h>
#include <sys\timeb.h> 

using namespace std;

void tests();

int main(int argc, char *argv[])
{
	string fileName, outFileName;
	unsigned int minSup;
	struct timeb start, end;
	int time_diff;
	cout << "Podaj nazwe pliku z danymi: ";
	cin >> fileName;
	cout << "Podaj nazwe pliku wynikowego: ";
	cin >> outFileName;
	cout << "Podaj minimalne wymagane wsparcie dla potencjalnych czestych generatorow: ";
	cin >> minSup;

	ofstream of(outFileName.c_str(), ios_base::out);

	//tests();
	ftime(&start);
	GRM grm(fileName);
	grm.GRMAlgoritm(minSup);
	ftime(&end);
	time_diff = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
	for (auto n : grm.getPreds()) {
		for (auto v : n->items) {
			of << "; ";
			for (int i = 0; i < v.size(); ++i)
				of << v[i].second << ", ";
		}
		of << " -> " << n->groupId << ";" << endl;
	}
	cout << "Czas dzialania algorytmu w ms: " << time_diff << endl;
	of.close();
	return 0;
}

/*void tests()
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

	// test getListProduct
	if(GRMUtils::getListProduct(set1, set2).size() != 1) cout << "getListProduct ERROR" << endl;

}*/