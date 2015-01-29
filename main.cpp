#include <iostream>
#include "Datastore.h"

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

	// testy liczenia wsparcia
	bool items[27] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,  0,1};
	if(datastore.getSupport(items) != 205) cout << "getSupport() ERROR" << endl;

	// testy isSubset()
	bool bigset[27] = {1,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,0,0,0,0,  0,1};
	if(!Transaction::isSubset(items, bigset)) cout << "isSubset() ERROR" << endl;
	bigset[26] = false;
	if(Transaction::isSubset(items, bigset)) cout << "isSubset() ERROR" << endl;

	// testy getSupportingSet
	bool example[27] = {1,0,0, 1,0,0, 1,0,0, 1,0,0, 0,1,0, 0,1,0, 1,0,0, 0,1,0, 0,1,0};
	if(datastore.getSupportingSet(example).size() != 1) cout << "getSupportingSet() ERROR" << endl;

	cout << "koniec testow" << endl;

}