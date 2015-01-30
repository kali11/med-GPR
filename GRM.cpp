#include "GRM.h"


GRM::GRM(void)
{
	datastore = NULL;
}


GRM::~GRM(void)
{
	delete datastore;
}

void GRM::GRMAlgoritm(unsigned minSup)
{
	Datastore* tictacDatastore = new Datastore();
	tictacDatastore->loadData();
	this->datastore = tictacDatastore;

	if(datastore->transactions.size() < minSup)
	{
		vector<bool> empty;
		empty.resize(0, tictacDatastore->ITEMS_SIZE);
		FG.insert(empty);
		return;
	}


}

void GRM::GarmProperty(shared_ptr<Node> n, shared_ptr<Node> ln, shared_ptr<Node> rn)
{
	if(GRMUtils::isTransactionListsEqual((*ln).transactionList, (*rn).transactionList))
	{
		for(auto it = (*rn).items.begin(); it != (*rn).items.end(); ++it)
		{
			(*ln).items.insert(*it);
		}
		(*n).removeChild(rn);
		return;
	}
	if(!GRMUtils::isSubsetOfTransactionList((*ln).transactionList, (*rn).transactionList))
	{
		Node node = *rn;
		node.cartesianProduct((*rn).items);
		shared_ptr<Node> node_ptr(&node);
		(*ln).children.push_back(node_ptr);

	}
}