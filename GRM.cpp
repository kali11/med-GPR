#include "GRM.h"


GRM::GRM(void)
{
}


GRM::~GRM(void)
{
}

void GRM::GRMAlgoritm(unsigned minSup)
{
	Datastore tictacDatastore;
	tictacDatastore.loadData();
	this->datastore = tictacDatastore;

	if(datastore.transactions.size() < minSup)
	{
		vector<bool> empty;
		empty.resize(0, tictacDatastore.ITEMS_SIZE);
		FG.insert(empty);
		return;
	}


}

void GRM::GarmProperty(shared_ptr<Node> n, shared_ptr<Node> ln, shared_ptr<Node> rn)
{
	if(GRMUtils::isTransactionListsEqual((*ln).transactionList, (*rn).transactionList))
	{

		(*n).removeChild(rn);
	}
}