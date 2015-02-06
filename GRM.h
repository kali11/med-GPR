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
	vector<pair<vector<pair<unsigned int, unsigned int>>, pair<unsigned int, unsigned int>>> rPreds;
    shared_ptr<Node> root;
	AbstractDatastore* datastore;
	unsigned int ncol;
public:
	string fileName;
	unsigned int tLoad, tGRM, tMeta, tRules;

	GRM(string fileName);
	~GRM(void);
	void GRMAlgoritm(unsigned minSup);
    void GARM(shared_ptr<Node>, unsigned);
	void GarmProperty(shared_ptr<Node> n, shared_ptr<Node> ln, shared_ptr<Node> rn);
	void fillMetadata(shared_ptr<Node>);
	vector<vector<string>>* getDictionary(void);
	unsigned int getNCol(void);
	set<shared_ptr<Node>> getPreds(void) { return preds; }
	vector<pair<vector<pair<unsigned int, unsigned int>>, pair<unsigned int, unsigned int>>> getRPreds(void) { return rPreds; }
	unsigned int getDecix(void) { return datastore->decix; }
};

