#pragma once
#include <memory>
#include <vector>
#include "Transaction.h"
#include <set>
#include "GRMUtils.h"

using namespace std;

class Node
{
private:

public:
	set<vector<pair<unsigned int, unsigned int>>> items;
	shared_ptr<Node> parent;
	vector<shared_ptr<Node>> children;
	set<int> transactionList; // zbior id transakcjii

    int groupId;
    bool oneClassOnly;

	Node(void);
	Node(const Node&);
	~Node(void);
	void cartesianProduct(set<vector<pair<unsigned int, unsigned int>>> itemsToAdd);
	void removeChild(shared_ptr<Node> toRemove);
};
