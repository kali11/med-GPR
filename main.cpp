#include <iostream>
#include <fstream>
#include <sstream>
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
	string confFileName;
	ifstream confFile;

	string fileName, outFileName, outReducedFileName, temp;
	stringstream outLine;
	unsigned int minSup;

	//load config
	if (argc == 2)
		confFileName = string(argv[1]);
	else
		confFileName = "medconf.ini";
		
	confFile.open(confFileName, ios_base::in);
	if (confFile.is_open())
		confFile >> fileName >> outFileName >> outReducedFileName >> minSup;
	else {
		cout << "Podaj nazwê pliku z danymi: ";
		cin >> fileName;
		cout << "Podaj nazwê pliku wynikowego dla wszystkich regu³: ";
		cin >> outFileName;
		cout << "Podaj nazwê pliku wynikowego dla zredukowanego zbioru regu³: ";
		cin >> outReducedFileName;
		cout << "Podaj minimalne wymagane wsparcie dla potencjalnych czêstych generatorów: ";
		cin >> minSup;
	}

	ofstream of(outFileName, ios_base::out);
	ofstream orf(outReducedFileName, ios_base::out);

	GRM grm(fileName);
	grm.GRMAlgoritm(minSup);

	of << "Zbiór regu³ decyzyjnych wygenerowanych ze zbioru " << fileName << ":" << endl;
	orf << "Zredukowany zbiór regu³ decyzyjnych wygenerowanych ze zbioru " << fileName << ":" << endl;

	for (auto n : grm.getPreds()) {
		for (auto v : n->items) {
			outLine.str("");
			for (unsigned int i = 0; i < v.size(); ++i)
				outLine << v[i].first + 1 << " = " << grm.getDictionary()->at(v[i].first)[v[i].second] << ", ";
			temp = outLine.str().substr(0, outLine.str().length() - 2);
			outLine.str("");
			outLine << temp << " -> " << grm.getDictionary()->at(grm.getDecix())[n->groupId] << " (" << n->support << ")";
			of << outLine.str() << endl;
		}
	}

	for (auto r : grm.getRPreds()) {
		outLine.str("");
		for (unsigned int i = 0; i < r.first.size(); ++i)
			outLine << r.first[i].first + 1 << " = " << grm.getDictionary()->at(r.first[i].first)[r.first[i].second] << ", ";
		temp = outLine.str().substr(0, outLine.str().length() - 2);
		outLine.str("");
		outLine << temp << " -> " << grm.getDictionary()->at(grm.getDecix())[r.second.first] << " (" << r.second.second << ")";
		orf << outLine.str() << endl;
	}

	orf << endl;
	orf << "Czas wczytywania danych: " << grm.tLoad << "ms." << endl;
	orf << "Czas tworzenia drzewa potencjalnych generatorów: " << grm.tGRM << "ms." << endl;
	orf << "Czas uzupe³niania informacji o rozró¿nialnoœci klas wzglêdem generatorów: " << grm.tMeta << "ms." << endl;
	orf << "Czas wyodrêbniania i redukowania zbioru regu³ decyzyjnych: " << grm.tRules << "ms." << endl;

	of.close();
	orf.close();
	return 0;
}