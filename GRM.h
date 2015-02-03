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
	set<vector<pair<unsigned int, unsigned int>>> FG;
	set<shared_ptr<Node>> preds;
    shared_ptr<Node> root;
	AbstractDatastore* datastore;
	unsigned int ncol;
public:
	string fileName;
	GRM(string fileName);
	~GRM(void);
	void GRMAlgoritm(unsigned minSup);
    void GARM(shared_ptr<Node>, unsigned);
	void GarmProperty(shared_ptr<Node> n, shared_ptr<Node> ln, shared_ptr<Node> rn);
	void fillMetadata(shared_ptr<Node>);
	set<shared_ptr<Node>> getPreds(void) { return preds; }
};

