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
	unsigned int width;

	//header
	file >> sep >> width;
	getline(file, line);

	//default values?

	constants.resize(width + 1);

	Transaction t(width);

	cout << sep << endl;
	while(getline(file, line))
	{
		cout << line << endl;;
		t = createTransactionFromLine(line, sep, width);
		t.id = id++;
		cout << ")) ";
		for (auto i : t.items)
			cout << i.first << "=" << i.second << ", ";
		cout << "-> " << t.group << endl;
		transactions.push_back(t);
	}
	cout << endl;

	file.close();

	return width;
}

Transaction Datastore::createTransactionFromLine(string line, char separator, unsigned int ncol)
{
	Transaction t(ncol);
	auto start = 0U;
	auto end = line.find(separator);
	string element;

	line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());

	for(unsigned int i = 0; i < ncol; ++i)
	{
		element = line.substr(start, end - start);
		start = end + 1;
		end = line.find(separator, start);

		auto it = find(constants[i].begin(), constants[i].end(), element);
		unsigned int index;
		if (it == constants[i].end()) {
			constants[i].push_back(element);
			index = constants[i].size() - 1;
			cout << "new constant " << i << "=" << element << ", index: " << index << endl;
		} else {
			index = distance(constants[i].begin(), it);
			cout << "old constant " << i << "=" << element << ", index: " << index << endl;
		}
		t.items[i].first = i;
		t.items[i].second = index;
	}

	auto it = find(constants[ncol].begin(), constants[ncol].end(), line.substr(start, end));
	unsigned int index;
	if (it == constants[ncol].end()) {
		constants[ncol].push_back(line.substr(start, end));
		index = constants[ncol].size() - 1;
		cout << "new constant group=" << line.substr(start, end) << ", index: " << index << endl;
	} else {
		index = distance(constants[ncol].begin(), it);
		cout << "old constant group=" << line.substr(start, end) << ", index: " << index << endl;
	}

	t.group = index;

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
