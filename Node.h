#pragma once
#include <memory>
#include <vector>
#include "Transaction.h"

using namespace std;

class Node
{
private:
	shared_ptr<Node> parent;
	vector<shared_ptr<Node>> children;
	vector<int> supportingSet; // zbior id transakcji
public:
	Node(void);
	~Node(void);
};

