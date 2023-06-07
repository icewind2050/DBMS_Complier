#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Type 用于表示Column的种类
enum Type{
    enum_INT,
    enum_FLOAT,
    enum_CHAR_INT,
    enum_STRING,

    enum_XING,   //用于select * 
    enum_NULL    //用于insert into stu(没写，按顺序插入) values();
};

//OpType用于表示Operator的种类
enum OpType{
    enum_Bigger,
    enum_Less,
    enum_Equal,
    enum_notBigger,
    enum_notLess,
    enum_notEqual
};

enum LinkType{
    enum_NO,
    enum_AND,
    enum_OR,
    enum_SET
};

typedef union Colume_Value{
    int Colume_Value_int;
    float Colume_Value_float;
    char Colume_Value_string[20];
}Colume_Value;

typedef struct Colume{
    char name_Colume[20];
    enum Type type;
    union Colume_Value colume_value[100];  //这一列一共可以存储100个值
    struct Colume* next_colume;
}Colume;

typedef struct Table{
    char name_Table[20];
    Colume* columes;
    int count_columes;
    int count_items;
    struct Table* next_Table;
}Table;

typedef struct Database{
    char name_Database[20];
    Table* tables;
    struct Database* next_Database;
}Database;


/* 下面三种结构体用于createSql
 *
 */

typedef struct Colume_Defination_Type{
    enum Type type_colume;
}Colume_Defination_Type;

typedef struct Colume_Defination{
    char name_ID[20];
    struct Colume_Defination_Type*  colume_defination_type;
}Colume_Defination;

typedef struct Colume_Defination_List{
    struct Colume_Defination* colume_defination;
    struct Colume_Defination_List* next_colume_defination;
}Colume_Defination_List;






 typedef struct Colume_Type_Value{
    enum Type type;
    union Colume_Value* colume_value;
 }Colume_Type_Value;

 //Colume_Value_List  是值的集合
typedef struct Colume_Value_List{  
    enum Type type;//三种类型，用于标志colume_value
    union Colume_Value colume_value;        //在插入时，通过比对表格中 列的元素类型进行判断
    struct Colume_Value_List* next_Colume_Value_List;
}Colume_Value_List;



//用于columes_list
//columes_list只有   1、列名  2、类型  用于区分 '*' 、'ID'
typedef struct Colume_List{
    enum Type type;  // type 用于在select语句中识别 1、*  2、ID
    char name_ID[20];
    struct Colume_List* next_Colume_List;
}Colume_List;




//ID_list
//Select语句中的 单表、多表查询
typedef struct ID_List{
    char name_ID[20];
    struct ID_List* next_ID;
}ID_List;


typedef struct Choice{
    char name_ID[20];
    enum OpType optype;
    //union Colume_Value choice_value;
    struct Colume_Value_List* choice_colume_value_list;
}Choice;

//用于SELECT
typedef struct Option_Choices{
    struct Choice* choice;
    enum LinkType LinkType;
    struct  Option_Choices* next_Option_Choices;
}Option_Choices;


//用于SET
typedef struct Choice_List{
    struct Choice* choice;
    struct Choice_List* next_Choice;
}Choice_List;





//对数据库进行操作
void createDatabase(char* DatabaseName);
void dropDatabase(char* DatabaseName);
void showDatabases();
void useDatabase();

//对数据库中的表进行操作
void createTable(char* TableName,struct Colume_Defination_List* colume_defination_list);
void showTables();
void dropTable(char* TableName);

void insertTable(char* TableName,struct Colume_List* colume_list,struct Colume_Value_List* colume_value_list);
void selectTableWithNoChoice(struct Colume_List* colume_list,struct ID_List* ID_List);
void selectTableWithChoice(struct Colume_List* colume_list,struct ID_List* ID_List,struct Option_Choices* option_choices);
void deleteTable(char* TableName,struct Option_Choices* option_choices);
void updateTableALL(char* TableName,struct Choice_List* choice_list);
void updateTable(char* TableName,struct Choice_List* choice_list,struct Option_Choices* option_choices);