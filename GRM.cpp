#include "GRM.h"
#include "TestDatastore.h"
#include "GRMUtils.h"
#include <algorithm>
#include <time.h>
#include <sys\timeb.h> 

GRM::GRM(string fileName)
{
	this->fileName = fileName;
	datastore = NULL;
	root = shared_ptr<Node>(new Node());

	//fill root with empty set (important!)
	root->items.insert(vector<pair<unsigned int, unsigned int>>());
}


GRM::~GRM(void)
{
	delete datastore;
}

void GRM::GRMAlgoritm(unsigned minSup)
{
	struct timeb start, end;

	ftime(&start);
	Datastore* tictacDatastore = new Datastore();
	ncol = tictacDatastore->loadData(this->fileName);
	ftime(&end);
	tLoad = (unsigned int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));

    vector<Transaction>& transactions = tictacDatastore->transactions;
    vector<pair<unsigned int, unsigned int>> temp;
	vector<set<int>> ruleIndices;
    set<int> tl, ts;
	vector<int> vs;
    unsigned int sup;

	this->datastore = tictacDatastore;

	if(transactions.size() > minSup)
	{   
		ftime(&start);
        for (unsigned int i = 0; i < this->ncol; ++i) {

			for (unsigned int k = 0; k < tictacDatastore->constants[i].size(); ++k) {
				sup = 0;
				temp.clear();
				tl.clear();

				for (unsigned int j = 0; j < transactions.size(); ++j) {
					if (transactions[j].items[i].second == k) {
						++sup;
						tl.insert(j);
					}
				}
	
				if (sup > minSup) {
	                shared_ptr<Node> N(new Node);
	                temp.push_back(make_pair(i, k));
					N->items.insert(vector<pair<unsigned int, unsigned int>>(temp));
					N->transactionList = tl;
					root->children.push_back(N);
				}
			}
        }
		GARM(root, minSup);
		ftime(&end);
		tGRM = (unsigned int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));


		ftime(&start);
		fillMetadata(root);
		ftime(&end);

		tMeta = (unsigned int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));

		ftime(&start);
		for (auto i : getPreds()) {
			for (auto j : i->items) {
				rPreds.push_back(make_pair(j, i->groupId));
			}
		}
		sort(rPreds.begin(), rPreds.end(), [](pair<vector<pair<unsigned int, unsigned int>>, unsigned int> x, pair<vector<pair<unsigned int, unsigned int>>, unsigned int> y){ return x.first.size() < y.first.size(); });

		for (unsigned int i = 0; i < rPreds.size(); ++i) {
			ruleIndices.clear();
			for (auto j : rPreds[i].first) {
				ruleIndices.push_back(set<int>());
				for (unsigned int l = 0; l < rPreds.size(); ++l) {
					if (find(rPreds[l].first.begin(), rPreds[l].first.end(), j) != rPreds[l].first.end())
						ruleIndices[ruleIndices.size() - 1].insert(l);
				}
			}

			ts = ruleIndices[0];
			for (auto s : ruleIndices)
				ts = GRMUtils::getListProduct(ts, s);
			
			vs = vector<int>(ts.begin(), ts.end());
			
			sort(vs.begin(), vs.end(), [this](int x, int y){ return rPreds[x].first.size() < rPreds[y].first.size(); });

			int psize = rPreds[vs[0]].first.size();
			for (auto k = vs.begin(); k != vs.end(); ++k) {
				if (rPreds[*k].first.size() == psize) {
					k = vs.erase(k);
					if (k == vs.end()) break;
				}
				else
					break;
			}

			sort (vs.begin(), vs.end());

			for (auto k = vs.end(); k != vs.begin(); --k)
				rPreds.erase(rPreds.begin() + *(k - 1));
		}
		ftime(&end);
		
		tRules = (unsigned int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
    }
}

void GRM::GARM(shared_ptr<Node> n, unsigned minSup)
{
    for (int i = 0; i < ((int)n->children.size()) - 1; ++i) {
        for (unsigned int j = i + 1; j < n->children.size(); ++j) {
            GarmProperty(n, n->children[i], n->children[j]);
        }

		n->children[i]->cartesianProduct(n->items);		

        for (unsigned int j = 0; j < n->children[i]->children.size(); ++j) {
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
	if (GRMUtils::isTransactionListsEqual((*ln).transactionList, (*rn).transactionList))
	{
		for(auto it = (*rn).items.begin(); it != (*rn).items.end(); ++it)
		{
			(*ln).items.insert(*it);
		}
		(*n).removeChild(rn);
		return;
	}

	if (!GRMUtils::isSubsetOfTransactionList((*ln).transactionList, (*rn).transactionList))
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

	if (n->groupId != -1 && n->oneClassOnly) {
		preds.insert(n);
		for (auto c : n->children)
			c.reset();
		return;
	}

	for (auto c : n->children)
		fillMetadata(c);
}

vector<vector<string>>* GRM::getDictionary(void) {
	return &datastore->constants;
}

unsigned int GRM::getNCol(void) {
	return ncol;
}
	