#include "Datastore.h"


Datastore::Datastore(void)
{
}


Datastore::~Datastore(void)
{
}

void Datastore::loadData()
{
	ifstream file = this->openDataFile();
	string line;
	Transaction t;
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

Transaction Datastore::createTransactionFromLine(string line)
{
	Transaction t;
	t.items.resize(ITEMS_SIZE, false);
	auto start = 0U;
	auto end = line.find(",");
	string element;
	for(int i = 0; i < ITEMS_SIZE / 2; i++)
	{
		element = line.substr(start, end - start);
		start = end + 1;
		end = line.find(",", start);
		if(element == "0")
			t.items[2*i] = true;
		else if(element == "1")
			t.items[2*i+1] = true;

		if(line.substr(start, end) == "win")
			t.group = 1;
		else if (line.substr(start, end) == "loss")
			t.group = 0;
		else t.group = 2;
	}
	return t;
}

ifstream Datastore::openDataFile()
{
	ifstream file;
	file.open(fileName);
	if(!file.is_open())
	{
		cout << "Nie mozna otworzyc pliku z danymi" << endl;
		file.close();
		exit(1);
	}
	return file;
}
