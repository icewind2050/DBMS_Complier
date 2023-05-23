#include"include/DBCORE.hh"
#include "DBCORE.hh"

Table::Table(const vector<vector<recordUnit>> &another)
{
}

shared_ptr<vector<vector<string, string>>> Table::select(const selectConditions &con)
{
    return shared_ptr<vector<vector<string, string>>>();
}

bool Table::insert(const vector<recordUnit> &value)
{
    return false;
}

bool Table::update(const vector<recordUnit> &value)
{
    return false;
}

bool Table::deleteSQL(const map<string, selectCondition> &con)
{
    return false;
}
