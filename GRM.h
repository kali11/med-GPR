#pragma once
#include "Node.h"
#include "Datastore.h"
#include <set>
#include <vector>
#include "AbstractDatastore.h"
#include "GRMUtils.h"
#include <memory>

class GRM
{
private:
	set<vector<bool>> FG;
    shared_ptr<Node> root;
	AbstractDatastore& datastore;
public:
	GRM();
	~GRM(void);
	void GRMAlgoritm(unsigned minSup);
    void GARM(shared_ptr<Node>, unsigned);
	void GarmProperty(shared_ptr<Node> n, shared_ptr<Node> ln, shared_ptr<Node> rn);
};

