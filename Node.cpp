#include "Node.h"


Node::Node(void)
{
    oneClassOnly = true;
    groupId = -1;
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
		}
	}
}
