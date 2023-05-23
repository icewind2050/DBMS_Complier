#ifndef _SHELL_H
#define _SHELL_H
#include"DBCORE.hh"
class DBSHELL
{
public:

    void printColumn(recordUnits);
    void printResult(vector<recordUnits>);
    void insert(shared_ptr<Table> table ,const recordUnits & value);
    void update(shared_ptr<Table> table ,const recordUnits & value);
    void deleteSQL(shared_ptr<Table> table ,const map<string,Condition>& con,const recordUnits & value);
    
    

    DBSHELL(/* args */);
    ~DBSHELL();
};



#endif