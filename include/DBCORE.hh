#ifndef SQL_DB_H
#define SQL_DB_H
#include<string>
#include<cinttypes>
#include<vector>
#include<map>
#include<memory>
#include<unordered_map>
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

struct selectConditions
{
    map<string,selectCondition> con;
}

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
    Table();
    Table(const vector<vector<recordUnit>>& another);


    shared_ptr<vector<vector<string,string>>> select(const selectConditions& con);
    bool insert(const vector<recordUnit> & value);
    bool update(const vector<recordUnit> & value);
    bool deleteSQL(const map<string,selectCondition>& con);

    ~Table();
};

class DataBase
{
private:
    string name;
    unordered_map<string,Table> Tables;
public:
    DataBase();
    DataBase(string n);
    ~DataBase();
};


#endif 