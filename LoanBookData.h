#pragma once

#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

class LoanBookData
{
private:
    string name;
    int code;
    string author;
    int year;
    int loan_count;

public:
    LoanBookData()
    {
        name = "";
        code = -1;
        author = "";
        year = 0;
        loan_count = 0;
    }

    ~LoanBookData() {};

    void setBookData(string& name, int code, string& author, int year)
    {
        this->name = name;
        this->code = code;
        this->author = author;
        this->year = year;
    }

    void setName(string name) { this->name = name; }
    void setCode(int code) { this->code = code; }
    void setAuthor(string author) { this->author = author; }
    void setYear(int year) { this->year = year; }
    void setCount(int loan_count) { this->loan_count = loan_count; }
    void updateCount() { this->loan_count += 1; }

    string getName() { return name; }
    int getCode() { return code; }
    string getAuthor() { return author; }
    int getYear() { return year; }
    int getLoanCount() { return loan_count; }

    // check loan count for delete from bptree
    bool check()
    {
        // true = book have to insert into stree
        // false = no need to move. remain in bptree
        switch (code)
        {
        case 0:
            if (loan_count >= 3) return true;
            else return false;
        case 100:
            if (loan_count >= 3) return true;
            else return false;
        case 200:
            if (loan_count >= 3) return true;
            else return false;
        case 300:
            if (loan_count >= 4) return true;
            else return false;
        case 400:
            if (loan_count >= 4) return true;
            else return false;
        case 500:
            if (loan_count >= 2) return true;
            else return false;
        case 600:
            if (loan_count >= 2) return true;
            else return false;
        case 700:
            if (loan_count >= 2) return true;
            else return false;

        default:
            return false;
        }
    }

    friend ostream& operator<<(ostream& fout, const LoanBookData& obj)
    {
        fout << obj.name << '/' << obj.code << '/' << obj.author << '/' << obj.year << '/' << obj.loan_count << endl;
        return fout;
    }
};