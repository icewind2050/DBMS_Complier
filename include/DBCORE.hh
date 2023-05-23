#ifndef SQL_DB_H
#define SQL_DB_H
#include<string>
#include<cinttypes>
#include<vector>
#include<map>
#include<memory>
using std::shared_ptr;
using std::string;
using std::vector;
using std::map;

enum TYPE{STRING,INT,FLOAT};
enum OP{GREAT,LESS,EQUAL,NOEQUAL};
struct selectCondition
{   
    TYPE datatype;
    OP operator;
    string value;
};


struct recordUnit
{
    TYPE datatype;
    string charval;

};


class Table
{
private:
    vector<vector<recordUnit>> table;
public:
    Table(/* args */);
    shared_ptr<vector<vector<string,string>>> select(const map<string,selectCondition>& con);
    bool insert(const vector<recordUnit> & value);
    bool update(const vector<recordUnit> & value);
    bool 

    ~Table();
};


#endif 