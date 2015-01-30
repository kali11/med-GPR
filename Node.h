#pragma once
#include <memory>
#include <vector>
#include "Transaction.h"
#include <set>

using namespace std;

class Node
{
private:

public:
	set<vector<bool>> items;
	shared_ptr<Node> parent;
	vector<shared_ptr<Node>> children;
	set<int> transactionList; // zbior id transakcjii

    unsigned int groupId;
    bool seenBefore;

	Node(void);
	~Node(void);
	void addToItems(vector<bool> itemsToAdd);
	void removeChild(shared_ptr<Node> toRemove);
};
