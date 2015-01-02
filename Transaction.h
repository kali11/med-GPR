#pragma once
#include <vector>

using namespace std;
/**
* Klasa pojedynczej transakcji
* 
*/
class Transaction
{
public:
	int id;
	bool items [27];
	int group; // klasa do ktorej nalezy dana transakcja
	Transaction(void);
	~Transaction(void);
};

