#include "Node.h"


Node::Node(void)
{
	groupId = -1;
	oneClassOnly = true;
}

Node::Node(const Node& n)
{
	items = n.items;
	parent = n.parent;
	children = n.children;
	transactionList = n.transactionList;

	groupId = n.groupId;
	oneClassOnly = n.oneClassOnly;
}

Node::~Node(void)
{
}

void Node::removeChild(shared_ptr<Node> toRemove)
{
	for(auto it = children.begin(); it != children.end(); ++it)
	{
		if(*it == toRemove)
		{
			children.erase(it);
			break;
		}
	}
}

void Node::cartesianProduct(set<vector<bool>> itemsToAdd)
{
	set<vector<bool>> result;

	for(auto it = items.begin(); it != items.end(); ++it)
	{
		for(auto it2 = itemsToAdd.begin(); it2 != itemsToAdd.end(); ++it2)
		{
			result.insert(GRMUtils::joinItems(*it, *it2));
		}
	}
	items = result;
}