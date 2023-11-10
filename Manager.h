#pragma once
#include "SelectionTree.h"
#include "BpTree.h"

class Manager
{
private:
	char *cmd;
	BpTree *bptree;
	SelectionTree *stree;

public:
	ifstream fin;
	ofstream flog;

	// constructor
	Manager(int bpOrder)
	{
		cmd = NULL;
		bptree = new BpTree(&flog, bpOrder);
		stree = new SelectionTree(&flog);
	}

	// destructor
	~Manager()
	{
		delete bptree;
		delete stree;
	}

	void run(const char *command);
	bool LOAD();
	bool ADD(string& data);

	bool Parser(string& data);
	bool Insert(string& name, int code, string& author, int year, int loan_count);

	bool SEARCH_BP_BOOK(string& book);
	bool SEARCH_BP_RANGE(string start, string end);

	bool PRINT_BP();
	bool PRINT_ST();

	bool DELETE();

	void printErrorCode(int n);
	void printSuccessCode(string cmd);
};
