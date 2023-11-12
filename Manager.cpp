#include "Manager.h"

void Manager::run(const char *command)
{
	fin.open(command);

	if (fin.fail())
	{
		flog << "File Open Error" << endl;
		return;
	}

	flog.open("log.txt");

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
		}
		else if (cmd == "SEARCH_BP")
		{
		}
		else if (cmd == "PRINT_BP")
		{
			PRINT_BP();
		}
		else if (cmd == "PRINT_ST")
		{
		}
		else if (cmd == "DELETE")
		{
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

		string line;
		while (getline(fin, line))
		{
			Parser(line);
		}

		printSuccessCode("LOAD");
	}
	catch (const char *err)
	{
		cout << err << endl;
		printErrorCode(100);
	}

	return true;
}

// add bookdata into B+tree with logging
bool Manager::ADD(string &data)
{
	try
	{
		Parser(data);
		printSuccessCode("ADD");
	}
	catch (const char *err)
	{
		cout << err << endl;
		printErrorCode(200);
		return false;
	}

	return true;
}

// parse string data into name, code, author, year, loan_count.
bool Manager::Parser(string &data)
{
	string sname, scode, sauthor, syear, slcount;
	stringstream ss(data);

	// parse book data
	if (getline(ss, sname, '	'))
		;
	else
	{
		throw "void Manager::parser(string& data)";
		return false;
	}
	if (getline(ss, scode, '	'))
		;
	else
	{
		throw "void Manager::parser(string& data)";
		return false;
	}
	if (getline(ss, sauthor, '	'))
		;
	else
	{
		throw "void Manager::parser(string& data)";
		return false;
	}
	if (getline(ss, syear, '	'))
		;
	else
	{
		throw "void Manager::parser(string& data)";
		return false;
	}
	if (getline(ss, slcount, '	'))
		;
	else
	{
		throw "void Manager::parser(string& data)";
		return false;
	}

	// insert parsed bookdata into B+ tree
	return Insert(sname, stoi(scode), sauthor, stoi(syear), stoi(slcount));
}

// insert bookdata into B+ tree without log
bool Manager::Insert(string &name, int code, string &author, int year, int loan_count)
{
	LoanBookData *temp = new LoanBookData();
	temp->setName(name);
	temp->setCode(code);
	temp->setAuthor(author);
	temp->setYear(year);	

	return bptree->Insert(temp);
}

bool Manager::SEARCH_BP_BOOK(string &book)
{
	try
	{
		// todo: search
		printSuccessCode("SEARCH_BP");
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
		// todo: search
		printSuccessCode("SEARCH_BP");
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
		bptree->linearPrint();
	}
	catch (const char *err)
	{
		cout << err << endl;
		printErrorCode(400);
	}

	return false;
}

bool Manager::PRINT_ST()
{
	try
	{
		// todo: print selection tree
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
		// todo: delete
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
