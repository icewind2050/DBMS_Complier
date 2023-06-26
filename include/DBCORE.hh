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
using std::unordered_map;
enum TYPE{STRING,INT,FLOAT};
enum OP{GREAT,LESS,EQUAL,NOEQUAL};

struct Condition//对比条件,可能不一定全部用上,有三个部分,类型名,操作符,需要比较的值的大小,这个值是外面传进去的,和表里的值比较,让它固定在左边,应该会用到where上,
{   
    TYPE datatype;
    OP oper;
    string value; 
};

struct Conditions//加上了列的名字,但是在select的时候不一定要,有的时候好像只要传列名就行,让它只在where出现就好
{
    unordered_map<string,Condition> con;
};


struct recordUnit//表的存储单元,其实应该会全部放到内存中来操作,应该编的能简单一点,还是有三项,数据类型,列名,值
{
    TYPE datatype;
    string colunmName;
    string charval;

};

struct recordUnits//这个其实是行的意思,但是这个行可以不完整,不一定要满,在一些时候可以只要几个列项就行,当然全部填满也行
{
    string table_name;
    vector<recordUnit> Units;
}

struct selectPara{//反正按照列名来,where可能有也可能没有,看着来就行
    //TODO: 查询这里可能要大改,不是很清楚递归的时候能不能把参数加到后面,后面出现递归的时候都可能要重新处理
    vector<string> columns;
    Conditions para;
}
struct insertPara{
    recordUnits para;
};
struct updatePara
{
    Conditions p1;
    recordUnits p2;
};
struct delectPara
{
    Conditions para;
};






class Table
{
private:
    vector<recordUnits> table;
public:
    Table();
    Table(const vector<recordUnits>& another);


    shared_ptr<vector<recordUnits>> select(const Conditions& con);
    bool insert(const recordUnits & value);
    bool update(const map<string,Condition>& con,const recordUnits & value);
    bool deleteSQL(const map<string,Condition>& con);

    ~Table();
};

class DataBase
{
private:
    string name;
    unordered_map<string,Table> Tables;
    
public:
    shared_ptr<Table> getTable(string n);
    DataBase();
    DataBase(string n);
    ~DataBase();
};


#endif 