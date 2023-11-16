#include "Manager.h"

void Manager::run(const char* command)
{
	fin.open(command);

	if (fin.fail())
	{
		flog << "File Open Error" << endl;
		return;
	}

	flog.open("log.txt", std::ios::app);

	string input;

	// parse string into command and data
	while (getline(fin, input))
	{
		stringstream ss(input);
		string cmd;
		getline(ss, cmd, '	');

		if (cmd == "LOAD")
		{
			LOAD();
		}
		else if (cmd == "ADD")
		{
			string data;
			getline(ss, data, '\r');
			ADD(data);
		}
		else if (cmd == "SEARCH_BP")
		{
			string obj1, obj2;
			getline(ss, obj1, '	');
			if (obj1 == "")
			{
				// no obj1
				printErrorCode(400);
			}
			else if (ss.eof())
			{
				// no obj2
				SEARCH_BP_BOOK(obj1);
			}
			else
			{
				// obj1 and obj2
				getline(ss, obj2, '	');
				SEARCH_BP_RANGE(obj1, obj2);
			}
		}
		else if (cmd == "PRINT_BP")
		{
			PRINT_BP();
		}
		else if (cmd == "PRINT_ST")
		{
			string scode;
			getline(ss, scode, '	');
			if (scode == "")
				printErrorCode(500); // no code
			else 
				PRINT_ST(stoi(scode));
		}
		else if (cmd == "DELETE")
		{
			DELETE();
		}
		else if (cmd == "EXIT")
		{
			printSuccessCode("EXIT");
			exit(0);
		}
		else
		{
			printErrorCode(700);
		}
	}
	input.clear();

	fin.close();
	flog.close();
	return;
}

// load bookdata from data.txt
bool Manager::LOAD()
{
	try
	{
		ifstream fin("loan_book.txt");

		if (fin.fail())
			throw "bool Manager::LOAD() - failed to read loan_book.txt";

		bool succ = true;

		string line;
		while (getline(fin, line))
			succ = succ && ParseLOAD(line);

		if (succ == true)
		{
			printSuccessCode("LOAD");
			return true;
		}
		else
		{
			printErrorCode(100);
			return false;
		}
	}
	catch (const char *err)
	{
		cout << err << endl;
		printErrorCode(100);
	}

	return false;
}

// add bookdata into B+tree with logging
bool Manager::ADD(string &data)
{
	try
	{
		if (ParseADD(data))
			return true;
		else
			printErrorCode(200);
	}
	catch (const char *err)
	{
		cout << err << endl;
		printErrorCode(200);
		return false;
	}

	return false;
}

// parse string data into name, code, author, year, loan_count.
bool Manager::ParseLOAD(string &data)
{
	string cmd, sname, scode, sauthor, syear, slcount;
	stringstream ss(data);

	// parse book data
	if (getline(ss, sname, '	'));
	else
	{
		throw "void Manager::parser(string& data)";
		return false;
	}
	if (getline(ss, scode, '	'));
	else
	{
		throw "void Manager::parser(string& data)";
		return false;
	}
	if (getline(ss, sauthor, '	'));
	else
	{
		throw "void Manager::parser(string& data)";
		return false;
	}
	if (getline(ss, syear, '	'));
	else
	{
		throw "void Manager::parser(string& data)";
		return false;
	}
	if (getline(ss, slcount, '	'));
	else
	{
		throw "void Manager::parser(string& data)";
		return false;
	}

	// insert parsed bookdata into B+ tree
	LoanBookData* node = new LoanBookData;
	node->setBookData(sname, stoi(scode), sauthor, stoi(syear));
	node->setCount(stoi(slcount));

	return bptree->Insert(node);
}

bool Manager::ParseADD(string& data)
{
	string cmd, sname, scode, sauthor, syear;
	stringstream ss(data);

	// parse book data
	if (getline(ss, sname, '	'));
	else
	{
		throw "void Manager::parser(string& data)";
		return false;
	}
	if (getline(ss, scode, '	'));
	else
	{
		throw "void Manager::parser(string& data)";
		return false;
	}
	if (getline(ss, sauthor, '	'));
	else
	{
		throw "void Manager::parser(string& data)";
		return false;
	}
	if (getline(ss, syear, '	'));
	else
	{
		throw "void Manager::parser(string& data)";
		return false;
	}

	// insert parsed data into B+ tree
	LoanBookData* node = new LoanBookData;
	node->setBookData(sname, stoi(scode), sauthor, stoi(syear));
	return bptree->Insert(node);
}

bool Manager::SEARCH_BP_BOOK(string &book)
{
	try
	{
		if (bptree->searchBook(book))
			return true;
		else
			printErrorCode(300);
	}
	catch (const char *err)
	{
		cout << err << endl;
		printErrorCode(300);
	}

	return false;
}

bool Manager::SEARCH_BP_RANGE(string s, string e)
{
	try
	{
		if (bptree->searchRange(s, e))
			return true;
		else
			printErrorCode(300);
	}
	catch (const char *err)
	{
		cout << err << endl;
		printErrorCode(300);
	}

	return false;
}

bool Manager::PRINT_BP()
{
	try
	{
		if (bptree->linearPrint())
			return true;
		else
			printErrorCode(400);	
	}
	catch (const char *err)
	{
		cout << err << endl;
		printErrorCode(400);
	}

	return false;
}

bool Manager::PRINT_ST(int code)
{
	try
	{
		if (stree->printBookData(code))
			return true;
		else
			printErrorCode(500);
	}
	catch (const char *err)
	{
		cout << err << endl;
		printErrorCode(500);
	}

	return false;
}

bool Manager::DELETE()
{
	try
	{
		if (stree->Delete())
			return true;
		else
			printErrorCode(600);
	}
	catch (const char *err)
	{
		cout << err << endl;
		printErrorCode(600);
	}

	return false;
}

void Manager::printErrorCode(int n)
{
	// ERROR CODE PRINT
	flog << "=======================" << endl;
	flog << "ERROR " << n << endl;
	flog << "=======================" << endl
		 << endl;
}

void Manager::printSuccessCode(string cmd)
{
	// SUCCESS CODE PRINT
	flog << "=======" << cmd << "========" << endl;
	flog << "Success" << endl;
	flog << "=======================" << endl
		 << endl;
}
