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
	set<vector<bool>> items;
	shared_ptr<Node> parent;
	vector<shared_ptr<Node>> children;
	set<int> transactionList; // zbior id transakcjii

    int groupId;
    bool oneClassOnly;

	Node(void);
	~Node(void);
	void cartesianProduct(set<vector<bool>> itemsToAdd);
	void removeChild(shared_ptr<Node> toRemove);
};
