#include "GRM.h"
#include "TestDatastore.h"
#include "GRMUtils.h"
#include <algorithm>

GRM::GRM(string fileName)
{
	this->fileName = fileName;
	datastore = NULL;
	root = shared_ptr<Node>(new Node());
}


GRM::~GRM(void)
{
	delete datastore;
}

void GRM::GRMAlgoritm(unsigned minSup)
{
	Datastore* tictacDatastore = new Datastore();
	ncol = tictacDatastore->loadData(this->fileName);
	root->items.insert(vector<pair<unsigned int, unsigned int>>(this->ncol));
    vector<Transaction>& transactions = tictacDatastore->transactions;
    vector<pair<unsigned int, unsigned int>> temp;
    set<int> tl;
    unsigned int sup;

	this->datastore = tictacDatastore;

	if(transactions.size() > minSup)
	{   
        for (int i = 0; i < this->ncol; ++i) {
            temp.clear();
            tl.clear();

			for (int k = 0; k < tictacDatastore->constants[i].size(); ++k) {
				sup = 0;

				for (int j = 0; j < transactions.size(); ++j) {
					if (transactions[j].items[i].second == k) {
						++sup;
						tl.insert(j);
					}
				}
	
				if (sup > minSup) {
	                shared_ptr<Node> N(new Node);
	                temp.push_back(pair<unsigned int, unsigned int>(i, k));
					N->items.insert(temp);
					N->transactionList = tl;
					root->children.push_back(N);
				}
			}
        }
		GARM(root, minSup);
    }
	fillMetadata(root);
}

void GRM::GARM(shared_ptr<Node> n, unsigned minSup)
{
    for (int i = 0; i < ((int)n->children.size()) - 1; ++i) {
        for (int j = i + 1; j < n->children.size(); ++j) {
            GarmProperty(n, n->children[i], n->children[j]);
        }

		n->children[i]->cartesianProduct(n->items);

        for (int j = 0; j < n->children[i]->children.size(); ++j) {
            if (n->children[i]->children[j]->transactionList.size() <= minSup) {
				n->children[i]->children[j]->cartesianProduct(n->children[i]->items);
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
		for(auto it = (*rn).items.begin(); it != (*rn).items.end(); ++it)
		{
			(*ln).items.insert(*it);
		}
		(*n).removeChild(rn);
		return;
	}
	if(!GRMUtils::isSubsetOfTransactionList((*ln).transactionList, (*rn).transactionList))
	{
		Node* node = new Node(*rn);
		node->transactionList = GRMUtils::getListProduct((*ln).transactionList, (*rn).transactionList);
		shared_ptr<Node> node_ptr(node);
		(*ln).children.push_back(node_ptr);

	}
}

void GRM::fillMetadata(shared_ptr<Node> n)
{
	if (n->items.size() > 0) {
		for (auto t : datastore->transactions) {
			if (GRMUtils::isSubsetOfItems(*(n->items.begin()), t.items)) {
				if (n->groupId == -1)
					n->groupId = t.group;
				else if (n->groupId != t.group) {
					n->oneClassOnly = false;
					break;
				}
			}
		}
	}

	if (n->groupId != -1 && n->oneClassOnly)
		preds.insert(n);

	for (auto c : n->children)
		fillMetadata(c);
}
