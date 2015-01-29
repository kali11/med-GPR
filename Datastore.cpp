#include "Datastore.h"


Datastore::Datastore(void)
{
}


Datastore::~Datastore(void)
{
	for(Transaction t : transactions)
	{
		delete[] t.items;
	}
}

vector<int> Datastore::getSupportingSet(bool items[27])
{
	vector<int> result;
	for(Transaction t : transactions)
	{
		if(Transaction::isSubset(items, t.items))
			result.push_back(t.id);
	}
	return result;
}

int Datastore::getSupport(bool items[27])
{
	return getSupportingSet(items).size();
}

void Datastore::loadData()
{
	ifstream file = this->openDataFile();
	string line;
	Transaction t(27);
	int id = 1;
	while(getline(file, line))
	{
		t = createTransactionFromLine(line);
		t.id = id;
		transactions.push_back(t);
		id++;
	}
	file.close();
}

void Datastore::display()
{
	for(Transaction t : transactions)
	{
		t.display();
	}
}

Transaction Datastore::createTransactionFromLine(string line)
{
	Transaction t(27);
	auto start = 0U;
	auto end = line.find(",");
	string element;
	for(int i = 0; i < 10; i++)
	{
		element = line.substr(start, end - start);
		start = end + 1;
		end = line.find(",", start);
		if(element == "x")
			t.items[3*i] = true;
		else if(element == "o")
			t.items[3*i+1] = true;
		else if(element == "b")
			t.items[3*i+2] = true;

		if(line.substr(start, end) == "positive")
			t.group = 1;
		else
			t.group = 0;
	}
	return t;
}

ifstream Datastore::openDataFile()
{
	ifstream file;
	file.open("data.csv");
	if(!file.is_open())
	{
		cout << "Nie mozna otworzyc pliku z danymi" << endl;
		file.close();
		exit(1);
	}
	return file;
}
