#include "Datastore.h"


Datastore::Datastore(void)
{
}


Datastore::~Datastore(void)
{
}

unsigned int Datastore::loadData(string fileName)
{
	ifstream file = this->openDataFile(fileName);
	string line;
	int id = 1;

	char sep;
	unsigned int width;

	//header
	file >> sep >> width;
	getline(file, line);

	constants.resize(width);

	Transaction t(width);

	while(getline(file, line))
	{
		t = createTransactionFromLine(line, sep, width);
		t.id = id++;
		transactions.push_back(t);
	}

	file.close();

	return width;
}

Transaction Datastore::createTransactionFromLine(string line, char separator, unsigned int ncol)
{
	Transaction t(ncol);
	t.items.resize(ncol, pair<unsigned int, unsigned int>(numeric_limits<unsigned int>::max(), numeric_limits<unsigned int>::max()));
	auto start = 0U;
	auto end = line.find(separator);
	string element;

	for(int i = 0; i < ncol; i++)
	{
		element = line.substr(start, end - start);
		start = end + 1;
		end = line.find(separator, start);

		auto it = constants[i].insert(element).first;
		t.items[i] = pair<unsigned int, unsigned int>(i, distance(constants[i].begin(), it));
	}

	auto it = constants[ncol - 1].insert(line.substr(start, end)).first;
	t.group = distance(constants[ncol - 1].begin(), it);

	return t;
}

ifstream Datastore::openDataFile(string fileName)
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
