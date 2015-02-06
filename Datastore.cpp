#include "Datastore.h"
#include <algorithm>

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
	unsigned int width, decix;

	//header
	file >> sep >> width >> decix;
	getline(file, line);

	constants.resize(width + 1);

	Transaction t(width);

	while(getline(file, line))
	{
		t = createTransactionFromLine(line, sep, width, decix);
		t.id = id++;
		transactions.push_back(t);
	}

	file.close();

	this->decix = decix;

	return width;
}

Transaction Datastore::createTransactionFromLine(string line, char separator, unsigned int ncol, unsigned int decix)
{
	Transaction t(ncol);
	auto start = 0U;
	auto end = line.find(separator);
	string element;

	line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());

	for(unsigned int i = 0, j = 0; i < ncol + 1; ++i, ++j)
	{
		element = line.substr(start, end - start);
		start = end + 1;
		end = line.find(separator, start);

		auto it = find(constants[i].begin(), constants[i].end(), element);
		unsigned int index;
		if (it == constants[i].end()) {
			constants[i].push_back(element);
			index = constants[i].size() - 1;
		} else {
			index = distance(constants[i].begin(), it);
		}

		if (!(i ^ decix)) {
			t.group = index;
			--j;
			continue;
		}
		
		t.items[j].first = i;
		t.items[j].second = index;
	}

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
