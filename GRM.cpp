#include "GRM.h"
#include "GRMUtils.h"
#include <algorithm>

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
    vector<Transaction>& transactions = tictacDatastore.transactions;
    vector<bool> temp;
    set<int> tl;
    unsigned int sup;

	this->datastore = tictacDatastore;

	if(transactions.size() > minSup)
	{
        root->items.clear();
        
        for (int i = 0; i < Datastore::ITEMS_SIZE; ++i) {
            sup = 0;
            temp.clear();
            temp.resize(Datastore::ITEMS_SIZE, false);
            tl.clear();

            for (int j = 0; j < transactions.size(); ++j) {
                if (transactions[j].items[i]) {
                    ++sup;
                    tl.insert(j);
                }
            }

            if (sup > minSup && sup < transactions.size()) {
                shared_ptr<Node> N(new Node);
                temp[i] = true;
                N->items.insert(temp);
                N->transactionList = tl;
                root.children.push_back(N);
            }

            GARM(root, minSup);
        }
    }
}

void GRM::GARM(shared_ptr<Node> n, unsigned minSup)
{
    set<vector<bool>> temp;

    for (int i = 0; i < n->children.size() - 1; ++i) {
        for (int j = i + 1; j < n->children.size(); ++j) {
            GarmProperty(n, n->children[i], n->children[j]);
        }

        temp.clear();
        temp = n->items;
        n->items.clear();
        set_union(temp.begin(), temp.end(), n->children[i]->items.begin(), n->children[i]->items.end(), inserter(n->items, n->items.begin()));

        for (int j = 0; j < n->children[i]->children.size(); ++j) {
            if (n->children[i]->children[j]->transactionList.size() <= minSup) {
                temp.clear();
                temp = n->children[i]->children[j]->items;
                n->children[i]->children[j]->items.clear();
                set_union(temp.begin(), temp.end(), n->children[i]->items.begin(), n->children[i]->items.end(), inserter(n->children[i]->children[j]->items, n->children[i]->children[j]->items.begin()));
                n->children[i]->children.erase(n->children[i]->children.begin() + j);
                --j;
            }
        }
        GARM(n->children[i], minSup);
    }
}

void GRM::GarmProperty(shared_ptr<Node> n, shared_ptr<Node> ln, shared_ptr<Node> rn)
{
	if(GRMUtils::isTransactionListsEqual((*ln).transactionList, (*rn).transactionList))
	{
		(*n).removeChild(rn);
	}
}

void GRM::fillMetadata(shared_ptr<Node> n)
{
    for (auto i = n->items.begin(); i != n->items.end(); ++i) {
        for (auto j = datastore.transactions,begin(); j != datastore.transactions.end(); ++j) {
            GRMUtils::isSubsetOfItems(*i, *j)
        }
    }
}
