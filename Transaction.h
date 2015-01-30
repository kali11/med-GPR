#pragma once
#include <vector>
#include <iostream>

using namespace std;
/**
* Klasa pojedynczej transakcji
* 
* Numeracja pol na planszy:
* 1|2|3
* 4|5|6
* 7|8|9
*/
class Transaction
{
public:
	int id;
	vector<bool> items; //kolejne pola: 1x,1o,1b,2x,2o,2b,3x,3o,3b,4x,4o,4b...
	int group; // klasa do ktorej nalezy dana transakcja 0 - negative, 1 - positive
	Transaction();
	~Transaction(void);
	void display();

};

