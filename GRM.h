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
	set<vector<bool>> GBD;
	AbstractDatastore* datastore;
public:
	GRM(void);
	~GRM(void);
	void GRMAlgoritm(unsigned minSup);
	void GarmProperty(shared_ptr<Node> n, shared_ptr<Node> ln, shared_ptr<Node> rn);
};

