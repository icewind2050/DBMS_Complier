#include"sql.h"

#define DEBUG_ENABLE 0

Database* rootDatabase = NULL;

Database* UsingDatabase = NULL;

 extern char UsingDatabaseName[50];


/*  对数据库进行的操作
 *  1.findDatabase  根据数据库名寻找目标数据库的前置节点
 *  2.createDatabase 
 *  3.dropDatabase
 *  4.showDatabases
 *  5.useDatabase
 */

void initRootDatabase()
{
    rootDatabase = (Database*)malloc(sizeof(Database));
    rootDatabase->tables = NULL;
    rootDatabase->next_Database = NULL;
}



Database* findDatabase(char* DatabaseName)
{
    if(DEBUG_ENABLE)
    {
       printf("%s \n",DatabaseName);
       printf("findDataBase->\n");
    }

    //初始化头节点，头节点为虚节点，实际不使用
    if(rootDatabase == NULL)
    initRootDatabase();
   

    Database* db = rootDatabase;

    while(db->next_Database != NULL && strcmp(db->next_Database->name_Database,DatabaseName) != 0)
        db = db->next_Database;
    
    if(DEBUG_ENABLE)
    {
        printf("findDatabase End->\n");
    }

    return db;
}



void createDatabase(char* DatabaseName)
{

    if(DEBUG_ENABLE)
    {
        printf("DatabaseName: %s\n",DatabaseName);
        printf("createDatabase->\n");
    }
    
    
    //初始化头节点，头节点为虚节点，实际不使用
    if(rootDatabase == NULL)
    initRootDatabase();

    Database* db = findDatabase(DatabaseName);
    if(db->next_Database!=NULL)
    {
        printf("ERROR: The database is exist!\n\n");
        return ;
    }    
    
    Database* newdb = (Database*)malloc(sizeof(Database));
    strcpy(newdb->name_Database,DatabaseName);
    //newdb->tables = NULL;

    //创建数据库时，初始化数据库的根Table，使其成为一个虚Table
    newdb->tables = (struct Table*)malloc(sizeof(struct Table));
    strcpy(newdb->tables->name_Table,"headTable");
    newdb->tables->next_Table = NULL;

    newdb->next_Database = db->next_Database;

    db->next_Database = newdb;
    printf("create Database: %s successfully!\n\n",DatabaseName);

}

void dropDatabase(char* DatabaseName)
{
    if(DEBUG_ENABLE)
    printf("dropDatabase->\n");
  

    Database* db = findDatabase(DatabaseName);
   
    //结束时，1：找到目标节点的上一个节点   2：下一个节点是NULL节点
    if(db->next_Database == NULL)
    {
        printf("ERROR: The database:%s is not exist!\n\n",DatabaseName);
        return ;
    }
    else
    {
        db->next_Database = db->next_Database->next_Database;
        printf("drop successfully!\n\n");
    }
}

void showDatabases()
{
    if(DEBUG_ENABLE)
    printf("showDatabases->\n");
    
    if(rootDatabase == NULL)
    initRootDatabase();

    printf("\nThe databases are:\n");
    Database* db = rootDatabase;
    while(db->next_Database!=NULL)
    {
        printf("|  %s\n",db->next_Database->name_Database);
        db = db->next_Database;
    }

    printf("\n");

    if(DEBUG_ENABLE)
    printf("showDatabases End->\n");

}

void useDatabase(char* DatabaseName)
{  
    if(DEBUG_ENABLE)
    printf("useDatabase is wroking->\n");

    Database* db = findDatabase(DatabaseName);

    if(DEBUG_ENABLE)
    printf("DatabaseName: %s\n",DatabaseName);

    if(db->next_Database == NULL)
    {
        printf("ERROR: The database:%s is not exist!\n\n",DatabaseName);
        return;
    }
    else //切换UsingDatabase
    {
        UsingDatabase = db->next_Database;
        strcpy(UsingDatabaseName,DatabaseName);
        printf("change successfully!\n");
    }
    
    if(DEBUG_ENABLE)
    printf("useDatabase is end->\n");
}



/*  对Table进行的操作
*   1、createTable
*
*
*
*
*/

/* createTalbe
    1.数据库检查
    2.在数据库的tables  末尾  生成表
*/

//找到数据中对应表的位置       //1.如果表存在，那么返回表的上一个指针     //2.如果不存在，返回db的最后一个位置指针
struct Table* findTable(struct Database* db,char* TableName)
{
    struct Table* tb = db->tables;

    while(tb->next_Table!=NULL&&strcmp(tb->next_Table->name_Table,TableName))
        tb = tb->next_Table;
    
    return tb;
}



void createTable(char* TableName,struct Colume_Defination_List* colume_defination_list){
    if(rootDatabase == NULL)
    {
        printf("ERROR:Please create a database firstly!\n");
        return ;
    }
    if(strlen(UsingDatabaseName) == 0)
    {
        printf("ERROR:Please choose a database firstly!\n");
        return ;
    }


   

    //找到数据库
    struct Database* db = UsingDatabase;
    struct Colume_Defination_List* sp_list = colume_defination_list;
    struct Colume_Defination* sp;

    struct Colume* table_colume;
    struct Colume* colume;

    struct Table* db_table;

    if(DEBUG_ENABLE)
    {
        printf("Dabatase: %s\n",db->name_Database);
    }


    //观察表格是否存在，  1：存在，return   2：不存在，那么，那么db_table此时指向db的最后一个表格 
    db_table = findTable(db,TableName);
    if(db_table->next_Table != NULL)
    {
        printf("ERROR: The table is exist!\n");
        return ;
    }


    //创建表格，通过colume_defination_list中的数据进行创建
    struct Table* table = (struct Table*)malloc(sizeof(struct Table));
    strcpy(table->name_Table,TableName);

    table->columes = (struct Colume*)malloc(sizeof(struct Colume));
    strcpy(table->columes->name_Colume,"firstColume");
    table->columes->next_colume = NULL;

    table->count_columes = 0;
    table->count_items = 0;
    table->next_Table = NULL;

    table_colume = table->columes;

        //通过循环，将colume依次加入
    while(sp_list!=NULL)
    {
        sp = sp_list->colume_defination;
        
        //对colume进行赋值，并加入到Table的columes指针中
        colume = (struct Colume*)malloc(sizeof(struct Colume));
        strcpy(colume->name_Colume,sp->name_ID);
        colume->type = sp->colume_defination_type->type_colume;


        if(DEBUG_ENABLE)
        {
            printf("%s ",colume->name_Colume);
            if(colume->type == enum_INT)
            {
                printf("INT\n");
            }
            else if(colume->type == enum_STRING)
            {
                printf("String\n");
            }
            else if(colume->type == enum_FLOAT)
            {
                printf("FLOAT\n");
            }
        }


        colume->next_colume = NULL;

        table_colume->next_colume = colume;
        table_colume = colume;
        table->count_columes++;

        sp_list = sp_list->next_colume_defination;
    }


    db_table->next_Table = table;
    
    

    if(DEBUG_ENABLE)
    {
        table_colume = table->columes;
        while(table_colume->next_colume != NULL)
        {
            printf("colume_name:%s ",table_colume->next_colume->name_Colume);
            if(table_colume->next_colume->type == enum_INT)
            {
                printf("INT\n");
            }
            else if(table_colume->next_colume->type == enum_STRING)
            {
                printf("String\n");
            }
            else if(table_colume->next_colume->type == enum_FLOAT)
            {
                printf("FLOAT\n");
            }

            table_colume = table_colume->next_colume;
        }
        printf("\n");
    }




    printf("create successfully!\n");
}

void showTables()
{
    struct Database* db = UsingDatabase;
    if(db == NULL)
    {
        printf("ERROR: Please choose a database firstly!\n");
        return;
    }

    struct Table* table = db->tables;
    while(table->next_Table != NULL)
    {
        printf("|   %s\n",table->next_Table->name_Table);
        table = table->next_Table;
    }
    printf("\n");
}

void dropTable(char* TableName)
{
    struct Database* db = UsingDatabase;

    struct Table* table = findTable(db,TableName);

    if(table->next_Table == NULL)
    {
        printf("ERROR: The table is not exist!\n");
        return ;
    }

    table->next_Table = table->next_Table->next_Table;

    printf("drop successfully!\n");

}



/*   核心操作
 *  1.inseretTable
 *  2.selectTable
 *  3.deleteTable
 *  4.updataTable
 */


struct Colume* findColume(struct Table* table,char* ColumeName) 
{
    struct Colume* colume = table->columes;
    while(colume->next_colume != NULL && strcmp(colume->next_colume->name_Colume,ColumeName))
        colume = colume->next_colume;
    
    return colume;
}

//如果对应的type和值不匹配，返回-1 ,添加成功，返回1
int addValueToColume(struct Colume* colume,int count_items,enum Type type,union Colume_Value Col_value)
{
    //首先比对type
    if(colume->type != type)
    {
        return -1;
    }

    //插入对应值
    colume->colume_value[count_items] = Col_value;

    return 1;
}


void insertTable(char* TableName,struct Colume_List* colume_list,struct Colume_Value_List* colume_value_list)
{
    if(rootDatabase == NULL)
    {
        printf("ERROR:Please create a database firstly!\n");
        return ;
    }
    if(strlen(UsingDatabaseName) == 0)
    {
        printf("ERROR:Please choose a database firstly!\n");
        return ;
    }


    //找到要插入的表
    struct Table* table = findTable(UsingDatabase,TableName);
    if(table->next_Table == NULL)
    {
        printf("ERROR: The table is not Exist!\n");
        return ;
    }
    else
    {
        //找到目标表
        table = table->next_Table;
    }


    //依次对表中要插入的列进行操作
    //寻找该列  1、找到:插入   2、未找到：报错返回
    //将函数参数2和参数3的指针右移，直到最后


   

    struct Colume_List* type_sp = colume_list;
    struct Colume_Value_List* value_sp = colume_value_list;

    struct Colume* table_colume_sp = table->columes->next_colume;

    struct Colume* colume;
    enum Type type;
    union Colume_Value col_value;

  
    //colume_list 没有输入时，全部匹配
    if(type_sp == NULL)
    {
        while(table_colume_sp != NULL && value_sp != NULL)
        {
            colume = table_colume_sp;
            
            type = value_sp->type;
            col_value = value_sp->colume_value;

            if(addValueToColume(colume,table->count_items,type,col_value) == -1)
            {
                printf("ERROR: Type not match!\n");
                return ;
            }


            table_colume_sp = table_colume_sp->next_colume;
            value_sp = value_sp->next_Colume_Value_List; 
        }

        if(DEBUG_ENABLE)
        {
            if(table_colume_sp != NULL)
            {
                printf("table_colume_sp is not null\n");
            }
            if(value_sp != NULL)
            {
                printf("value_sp is not null\n");
            }
        }
        //如果函数参数2和参数3  数目不一致，报错返回
        if((table_colume_sp != NULL && value_sp == NULL) || (table_colume_sp == NULL && value_sp != NULL))
        {
            printf("ERROR: Number is not match!\n");
            return ;
        }
    }
    else if(type_sp != NULL)
    {
            //type_sp 有值
        while(type_sp != NULL && value_sp != NULL)
        {

            //找到对应列
            colume = findColume(table,type_sp->name_ID);
            if(colume->next_colume == NULL)
            {
                printf("ERROR:The Colume is not exist!\n");
            }
            else 
            {
                colume = colume->next_colume; 
            }



            type = value_sp->type;

            col_value = value_sp->colume_value;

            if(DEBUG_ENABLE)
            {
                printf("Colume_Name: %s  ",colume->name_Colume);
                switch(colume->type)
                {
                    case enum_INT:
                        printf("Colume_Type: enum_INT\n");
                        break;
                    case enum_FLOAT:
                        printf("Colume_Type: enum_FLOAT\n");
                        break;
                    case enum_STRING:
                        printf("Colume_Type: enum_STRING\n");
                        break;
                }

                printf("value_sp->type: ");
                switch(value_sp->type)
                {
                    case enum_INT:
                        printf("Colume_Type: enum_INT\n");
                        break;
                    case enum_FLOAT:
                        printf("Colume_Type: enum_FLOAT\n");
                        break;
                    case enum_STRING:
                        printf("Colume_Type: enum_STRING\n");
                        break;
                }

                
            }

            if(addValueToColume(colume,table->count_items,type,col_value) == -1)
            {
                printf("ERROR: Type not match!\n");
                return ;
            }


            type_sp = type_sp->next_Colume_List;
            
            value_sp = value_sp->next_Colume_Value_List;
        }

        if(DEBUG_ENABLE)
        {
            if(type_sp != NULL)
            {
                printf("type_sp is not null\n");
            }
            if(value_sp != NULL)
            {
                printf("value_sp is not null\n");
            }
        }
        //如果函数参数2和参数3  数目不一致，报错返回
        if((type_sp != NULL && value_sp == NULL) || (type_sp == NULL && value_sp != NULL))
        {
            printf("ERROR: Number is not match!\n");
            return ;
        }
    }

   

    //将表中维护的行数加1
    table->count_items++;
    printf("Insert successfully!\n");
 }
 
 
 
 /*     selectTable
 *
 *
 *
 */

//单表查询
int selectTableSimple(struct Colume_List* colume_list,struct ID_List* ID_List)
{
    //找到要插入的表
    struct Table* table = findTable(UsingDatabase,ID_List->name_ID);
    if(table->next_Table == NULL)
    {
        printf("ERROR: The table is not Exist!\n");
        return -1;
    }
    else
    {
        //找到目标表
        table = table->next_Table;
    }

    struct Colume* colume;
    int rowNumber = table->count_items;
    struct Colume_List* sp = colume_list;


    if(colume_list->type == enum_XING)
    {
        if(DEBUG_ENABLE)
        {
            printf("select all\n");
        }

        //打印名字
        colume= table->columes;
        while(colume->next_colume != NULL)
        {
            printf("|   %-12s",colume->next_colume->name_Colume);
            colume = colume->next_colume;
        }
        printf("\n");

        //依次打印每一行
        for(int i = 0; i < rowNumber;i++)
        {
            colume= table->columes;
            while(colume->next_colume != NULL)
            {
                //printf("|   %-10s ",colume->next_colume->name_Colume);

                switch(colume->next_colume->type)
                {
                    case enum_INT:
                        printf("|   %-12d",colume->next_colume->colume_value[i].Colume_Value_int);
                        break;
                    case enum_FLOAT:
                        printf("|   %-12g",colume->next_colume->colume_value[i].Colume_Value_float);
                        break;
                    case enum_STRING:
                        printf("|   %-12s",colume->next_colume->colume_value[i].Colume_Value_string);
                        break;
                }
                colume = colume->next_colume;
            }
            printf("\n");



        }
    }
    else
    {
        if(DEBUG_ENABLE)
        {
            printf("select part\n");
        }


        //打印表头
        while(sp!=NULL)
        {
            //找到对应列
            colume = findColume(table,sp->name_ID);
            if(colume->next_colume == NULL)
            {
                printf("ERROR:The Colume is not exist!\n");
                return -1;
            }
            else 
            {
                colume = colume->next_colume; 
            }

            printf("|   %-12s",colume->name_Colume);
            sp = sp->next_Colume_List;
        }
        printf("\n");

        //打印每一行
        for(int i = 0;i < rowNumber; i++)
        {
            sp = colume_list;

            while(sp!=NULL)
            {
                //找到对应列
                colume = findColume(table,sp->name_ID);
                if(colume->next_colume == NULL)
                {
                    printf("ERROR:The Colume is not exist!\n");
                    return -1;
                }
                else 
                {
                    colume = colume->next_colume; 
                }

                
                switch(colume->type)
                {
                    case enum_INT:
                        printf("|   %-12d",colume->colume_value[i].Colume_Value_int);
                        break;
                    case enum_FLOAT:
                        printf("|   %-12g",colume->colume_value[i].Colume_Value_float);
                        break;
                    case enum_STRING:
                        printf("|   %-12s",colume->colume_value[i].Colume_Value_string);
                        break;
                }

                sp = sp->next_Colume_List;
            }
            printf("\n");
        }


    }


    return 1;
}




//复制表，而不是通过指针指向表
struct Table* copyTable(const struct Table* sourceTable) {
    // 创建新的Table结构体
    struct Table* newTable = (struct Table*)malloc(sizeof(Table));

    // 复制表名
    strcpy(newTable->name_Table, sourceTable->name_Table);

    // 复制列信息
    newTable->columes = NULL;
    struct Colume* sourceColumn = sourceTable->columes;
    struct Colume* previousColumn = NULL;
    while (sourceColumn != NULL) {
        // 创建新的Colume结构体
        struct Colume* newColumn = (struct Colume*)malloc(sizeof(struct Colume));
        // 复制列名
        strcpy(newColumn->name_Colume, sourceColumn->name_Colume);

        // 复制列类型
        newColumn->type = sourceColumn->type;

        // 复制列值
        memcpy(newColumn->colume_value, sourceColumn->colume_value, sizeof(union Colume_Value) * 100);

        // 设置下一个列为NULL
        newColumn->next_colume = NULL;

        // 连接到新的Table
        if (previousColumn == NULL) {
            newTable->columes = newColumn;
        } else {
            previousColumn->next_colume = newColumn;
        }
        previousColumn = newColumn;

        sourceColumn = sourceColumn->next_colume;
    }

    // 设置列计数和项计数
    newTable->count_columes = sourceTable->count_columes;
    newTable->count_items = sourceTable->count_items;

    // 设置下一个Table为NULL
    newTable->next_Table = NULL;

    return newTable;
}


int equalColumeValue(enum Type type1,enum Type type2,union Colume_Value c1,union Colume_Value c2)
{
    if(DEBUG_ENABLE)
    {
        if(type1 != type2)
        {
            printf("The Colume_Type is not equal!\n");
            printf("The first Colume Type is not equal!\n");
            return -1;
        }
    }

    if(type1 == enum_INT)
    {
        if(DEBUG_ENABLE)
        {
            printf("equalColumeValue->enum_INT\n");
            printf("value:%d\n",c1.Colume_Value_int);
        }
        if(c1.Colume_Value_int == c2.Colume_Value_int)
            return 1;
        else
            return -1; 
    }
    else if(type1 == enum_FLOAT)
    {
         if(DEBUG_ENABLE)
        {
            printf("equalColumeValue->enum_FOLAT\n");
            printf("value:%g\n",c1.Colume_Value_float);
        }
        if(c1.Colume_Value_float == c2.Colume_Value_float)
            return 1;
        else 
            return -1;
    }
    else if(type1 == enum_STRING)
    {
         if(DEBUG_ENABLE)
        {
            printf("equalColumeValue->enum_STRING\n");
            printf("value:%s\n",c1.Colume_Value_string);
        }
        if(strcmp(c1.Colume_Value_string,c2.Colume_Value_string) == 0)
            return 1;
        else 
            return -1;
    }
}

//根据两个表合成为一个表
struct Table* generateTable(const struct Table* Table1,const struct Table* Table2)
{
    //!!!!!!!!!!!!!!!!
    //通过复制而不是指针引用，如果通过指针引用，修改table1之后，Table1也会变化
    struct Table* table1 = copyTable(Table1);
    struct Table* table2 = copyTable(Table2);
    

    struct Table* table = table1;
    //找到table最后的colume指针
    if(DEBUG_ENABLE)
    {
        printf("table1 name: %s\n",table1->name_Table);
        printf("table1 items: %d\n",table1->count_items);

        printf("table2 name: %s\n",table2->name_Table);
        printf("table2 items: %d\n",table2->count_items);

        printf("table name: %s\n",table->name_Table);
        printf("table items: %d\n",table->count_items);
        

        printf("copyTable successfully!\n");
    }
    
    struct Colume* sp = table->columes;
    while(sp->next_colume != NULL)
    {
        sp = sp->next_colume;
    }

    //规定一下，第一列为主码，且只有第一列为主码
    sp->next_colume = table2->columes->next_colume->next_colume;
    
    table->count_columes = table1->count_columes+table2->count_columes-1;

    table->count_items = 0;

    if(DEBUG_ENABLE)
    {
        printf("table1 name: %s\n",table1->name_Table);
        printf("table1 items: %d\n",table1->count_items);

        printf("table2 name: %s\n",table2->name_Table);
        printf("table2 items: %d\n",table2->count_items);

        printf("table name: %s\n",table->name_Table);
        printf("table items: %d\n",table->count_items);
        

        printf("copyTable successfully!\n");
    }


    if(DEBUG_ENABLE)
    {
        printf("generateTable->columeToOne\n");
    }

    struct Colume* colume1 = Table1->columes->next_colume;
    struct Colume* colume2 = Table2->columes->next_colume;

    struct Colume* sp1;
    struct Colume* sp2;
    struct Colume* sp3;
    //笛卡尔乘积
    for(int i = 0; i < Table1->count_items; i++)
    {
        union Colume_Value value1 = colume1->colume_value[i];

        for(int j = 0; j < Table2->count_items; j++)
        {
            union Colume_Value value2 = colume2->colume_value[j];
            //将结果存在新表中
            if(equalColumeValue(colume1->type,colume2->type,value1,value2) == 1)
            {
                if(DEBUG_ENABLE)
                {
                    printf("\n");
                    printf("generateTable->ToCopyValue\n");
                    printf("i: %d j:%d\n",i,j);
                }

                sp1 = Table1->columes->next_colume;
                sp2 = Table2->columes->next_colume;
                sp2 = sp2->next_colume;

                sp3 = table->columes->next_colume;

                while(sp1!=NULL)
                {
                    //分三种情况复制
                    if(sp1->type == enum_INT)
                    {
                        sp3->colume_value[table->count_items].Colume_Value_int = sp1->colume_value[i].Colume_Value_int;
                    
                        if(DEBUG_ENABLE)
                        {
                            printf("i: %d j:%d\n",i,j);
                            printf("sp1 value: %d\n",sp1->colume_value[i].Colume_Value_int);
                            printf("sp3 value: %d\n",sp3->colume_value[table->count_items].Colume_Value_int);
                        }
                    }
                    
                    else if(sp1->type == enum_FLOAT)
                    {
                        if(DEBUG_ENABLE)
                        {
                            printf("i: %d j:%d\n",i,j);
                            printf("sp1 value: %g\n",sp1->colume_value[i].Colume_Value_float);
                            printf("sp3 value: %g\n",sp3->colume_value[table->count_items].Colume_Value_float);
                        }

                        sp3->colume_value[table->count_items].Colume_Value_float = sp1->colume_value[i].Colume_Value_float;
                    }
                    
                    else if(sp1->type == enum_STRING)
                    {
                        strcpy(sp3->colume_value[table->count_items].Colume_Value_string,sp1->colume_value[i].Colume_Value_string);
                       
                        if(DEBUG_ENABLE)
                        {
                            printf("i: %d j:%d\n",i,j);
                            printf("sp1 value: %s\n",sp1->colume_value[i].Colume_Value_string);
                            printf("sp3 value: %s\n",sp3->colume_value[table->count_items].Colume_Value_string);
                        }
                    }

                    sp1 = sp1->next_colume;
                    sp3 = sp3->next_colume;
                }


                while(sp2!=NULL)
                {
                    if(sp2->type == enum_INT)
                    {
                        sp3->colume_value[table->count_items].Colume_Value_int = sp2->colume_value[j].Colume_Value_int;

                        if(DEBUG_ENABLE)
                        {
                            printf("i: %d j:%d\n",i,j);
                            printf("sp2 value: %d\n",sp2->colume_value[j].Colume_Value_int);
                            printf("sp3 value: %d\n",sp3->colume_value[table->count_items].Colume_Value_int);
                        }
                    }
                   
                    else if(sp2->type == enum_FLOAT)
                    {
                        sp3->colume_value[table->count_items].Colume_Value_float = sp2->colume_value[j].Colume_Value_float;
                    
                        if(DEBUG_ENABLE)
                        {
                            printf("i: %d j:%d\n",i,j);
                            printf("sp2 value: %g\n",sp2->colume_value[j].Colume_Value_float);
                            printf("sp3 value: %g\n",sp3->colume_value[table->count_items].Colume_Value_float);
                        }
                    }
                    
                    else if(sp2->type == enum_STRING)
                    {
                        strcpy(sp3->colume_value[table->count_items].Colume_Value_string,sp2->colume_value[j].Colume_Value_string);
                    
                        if(DEBUG_ENABLE)
                        {
                            printf("i: %d j:%d\n",i,j);
                            printf("sp2 value: %s\n",sp2->colume_value[j].Colume_Value_string);
                            printf("sp3 value: %s\n",sp3->colume_value[table->count_items].Colume_Value_string);
                        }
                    }
                   
                    
                    sp2 = sp2->next_colume;
                    sp3 = sp3->next_colume;
                }

                table->count_items++;
            } 
        }
    }

    if(DEBUG_ENABLE)
    {
        printf("\n");
        printf("generateTable->end!\n");
        
        printf("table name: %s\n",table->name_Table);
        printf("table items: %d\n",table->count_items);
    }


    return table;
}

//通过ID_list,依次找到表，将其合成为一个表进行返回,返回的表在  table_for_mix中
struct Table* mixTable(struct ID_List* ID_List)
{
    
    struct Table* table;
    struct Table* tmp_table;


    //将第一个表赋给table
    table = findTable(UsingDatabase,ID_List->name_ID);
    if(table->next_Table == NULL)
    {
        printf("ERROR: The table is not Exist!\n");
        return NULL;
    }
    else
    {
        //找到目标表
        table = table->next_Table;
    }
    if(DEBUG_ENABLE)
    {
        printf("Find the first table: %s\n",table->name_Table);
    }

    //从第二个表开始找
    struct ID_List* sp = ID_List->next_ID;
    while(sp!=NULL)
    {
        tmp_table = findTable(UsingDatabase,sp->name_ID);
        if(tmp_table->next_Table == NULL)
        {
            printf("ERROR: The table is not Exist!\n");
            return NULL;
        }
        else
        {
            tmp_table = tmp_table->next_Table;
        }

        if(DEBUG_ENABLE)
        {
            printf("Find the next table: %s\n",tmp_table->name_Table);
        }

        //找到之后，找到table表中的Colume最后一个指针，将该指针指向tmp_table的第一个   有效colume
        struct Table* generate_Table = generateTable(table,tmp_table);

        table = generate_Table;

        if(DEBUG_ENABLE)
        {
            printf("\n");
            printf("mixTalbe table name is %s\n",table->name_Table);
            printf("mixTable count_items is: %d\n",table->count_items);
        }

        sp = sp->next_ID;
    }

    
    
    if(DEBUG_ENABLE)
    {
        printf("\n");

        printf("mixTalbe->end table name is %s\n",table->name_Table);
        printf("mixTable->end count_items is: %d\n",table->count_items);
        printf("mixTable succussfully!\n");
        printf("mixTable->end\n");
    }

    return table;
}

//多表查询

int selectTableMulti(struct Colume_List* colume_list,struct ID_List* ID_List) 
{
    

    struct Table* table = mixTable(ID_List);
    if(table == NULL)
    {
        if(DEBUG_ENABLE)
        {
            printf("selectTableMulti-> table is NULL\n");
        }
        return -1;
    }

  
    if(DEBUG_ENABLE)
    {   
        printf("\n");
        printf("selectTableMulti->begin\n");
        printf("selectTalbeMulti table name is %s\n",table->name_Table);
        printf("selectTableMulti count_items is: %d\n",table->count_items);

    }

    struct Colume* colume;
    int rowNumber = table->count_items;
    struct Colume_List* sp = colume_list;


    if(colume_list->type == enum_XING)
    {
        if(DEBUG_ENABLE)
        {
            printf("select all\n");
        }

        //打印名字
        colume= table->columes;
        while(colume->next_colume != NULL)
        {
            printf("|   %-12s",colume->next_colume->name_Colume);
            colume = colume->next_colume;
        }
        printf("\n");

        //依次打印每一行
        for(int i = 0; i < rowNumber;i++)
        {
            colume= table->columes;
            while(colume->next_colume != NULL)
            {
                //printf("|   %-10s ",colume->next_colume->name_Colume);

                switch(colume->next_colume->type)
                {
                    case enum_INT:
                        printf("|   %-12d",colume->next_colume->colume_value[i].Colume_Value_int);
                        break;
                    case enum_FLOAT:
                        printf("|   %-12g",colume->next_colume->colume_value[i].Colume_Value_float);
                        break;
                    case enum_STRING:
                        printf("|   %-12s",colume->next_colume->colume_value[i].Colume_Value_string);
                        break;
                }
                colume = colume->next_colume;
            }
            printf("\n");



        }
    }
    else
    {
        if(DEBUG_ENABLE)
        {
            printf("select part\n");
        }


        //打印表头
        while(sp!=NULL)
        {
            //找到对应列
            colume = findColume(table,sp->name_ID);
            if(colume->next_colume == NULL)
            {
                printf("ERROR:The Colume is not exist!\n");
                return -1;
            }
            else 
            {
                colume = colume->next_colume; 
            }

            printf("|   %-12s",colume->name_Colume);
            sp = sp->next_Colume_List;
        }
        printf("\n");

        //打印每一行
        for(int i = 0;i < rowNumber; i++)
        {
            sp = colume_list;

            while(sp!=NULL)
            {
                //找到对应列
                colume = findColume(table,sp->name_ID);
                if(colume->next_colume == NULL)
                {
                    printf("ERROR:The Colume is not exist!\n");
                    return -1;
                }
                else 
                {
                    colume = colume->next_colume; 
                }

                
                switch(colume->type)
                {
                    case enum_INT:
                        printf("|   %-12d",colume->colume_value[i].Colume_Value_int);
                        break;
                    case enum_FLOAT:
                        printf("|   %-12g",colume->colume_value[i].Colume_Value_float);
                        break;
                    case enum_STRING:
                        printf("|   %-12s",colume->colume_value[i].Colume_Value_string);
                        break;
                }

                sp = sp->next_Colume_List;
            }
            printf("\n");
        }


    }


    return 1;
    
}


 void selectTableWithNoChoice(struct Colume_List* colume_list,struct ID_List* ID_List)
 {
    if(rootDatabase == NULL)
    {
        printf("ERROR:Please create a database firstly!\n");
        return ;
    }
    if(strlen(UsingDatabaseName) == 0)
    {
        printf("ERROR:Please choose a database firstly!\n");
        return ;
    }

    //只有一个表的情况下，进行单表查询
    if(ID_List->next_ID == NULL)
    {
        if(DEBUG_ENABLE)
        {
            printf("simple table select\n");
        }
       /* if(selectTableSimple(colume_list,ID_List) == -1)
       {
            return ;
       } */

        //多表查询方式，将多表产生一个表，之后进行查找
        //多表查询方式，包含了单表查询
        if(selectTableMulti(colume_list,ID_List) == -1)
        {
            return ;
        }

    }
    else
    {
        if(DEBUG_ENABLE)
        {
            printf("multi table select\n");
        }

        //多表查询方式，将多表产生一个表，之后进行查找
        //多表查询方式，包含了单表查询
        if(selectTableMulti(colume_list,ID_List) == -1)
        {
            return ;
        }

        
    }



    printf("select successfully!\n");
 }




//用于判断改行是否输出  1，可以输出， 0，不能输出  -2,打印错误信息
int flag_option_choice(struct Table* table,int i,struct Option_Choices* option_choices)
{
    int flag1 = 1;
    int flag2 = 1;
    enum LinkType linktype = enum_NO;

    struct Option_Choices* sp = option_choices;
    struct Choice* choice;
    struct Colume_Value_List* colume_value;

    //根据Table和option_choices中的name_ID找到对应列
    struct Colume* colume;

     while(sp!=NULL)
        {
            choice = sp->choice;

            if(DEBUG_ENABLE)
            {
                printf("flag_option_choice-> choiceColumeName:%s ",choice->name_ID);
            }

            //找到对应列
            colume = findColume(table,choice->name_ID);
            if(colume->next_colume == NULL)
            {
                printf("ERROR:The Colume is not exist!\n");
                return -2;
            }
            else 
            {
                colume = colume->next_colume; 
            }
            //找到具体的值
            union Colume_Value value = colume->colume_value[i];




            if(DEBUG_ENABLE)
            {
                printf("\n");
                printf("flag_option_choice-> colume_value in choice : ");
                colume_value = choice->choice_colume_value_list;
                switch(colume_value->type)
                {
                    case enum_INT:
                        printf("enum_INT %d  \n",colume_value->colume_value.Colume_Value_int);
                        break;
                    case enum_FLOAT:
                        printf("enum_FLOAT %g  \n",colume_value->colume_value.Colume_Value_float);
                        break;
                    case enum_STRING:
                        printf("enum_STRING %s  \n",colume_value->colume_value.Colume_Value_string);
                        break;
                }
            }
            

            switch(choice->optype)
            {
                case enum_Bigger:
                    {
                        if(DEBUG_ENABLE)
                        {
                            printf("enum_Bigger \n");
                        }

                        colume_value = choice->choice_colume_value_list;
                        switch(colume_value->type)
                        {
                            case enum_INT:
                                {
                                    if(value.Colume_Value_int <= colume_value->colume_value.Colume_Value_int)
                                    {
                                        flag2 = 0;
                                    }
                                }
                                break;
                            case enum_FLOAT:
                                {
                                    if(value.Colume_Value_float <= colume_value->colume_value.Colume_Value_float)
                                    {
                                        flag2 = 0;
                                    }
                                }
                                break;
                            case enum_STRING:
                                {
                                    printf("ERROR: Type is not match!\n");
                                    return -2;
                                }
                                break;
                        }

                    }
                    break;
                case enum_Less:
                    {
                        if(DEBUG_ENABLE)
                        {
                            printf("enum_Less\n");
                        }

                        colume_value = choice->choice_colume_value_list;
                        switch(colume_value->type)
                        {
                            case enum_INT:
                                {
                                    if(value.Colume_Value_int >= colume_value->colume_value.Colume_Value_int)
                                    {
                                        flag2 = 0;
                                    }
                                }
                                break;
                            case enum_FLOAT:
                                {
                                    if(value.Colume_Value_float >= colume_value->colume_value.Colume_Value_float)
                                    {
                                        flag2 = 0;
                                    }
                                }
                                break;
                            case enum_STRING:
                                {
                                    printf("ERROR: Type is not match!\n");
                                    return -2;
                                }
                                break;
                        }
                    }
                    break;
                case enum_Equal:
                    {
                        if(DEBUG_ENABLE)
                        {
                            printf("enum_Equal\n");
                        }
                        colume_value = choice->choice_colume_value_list;
                        switch(colume_value->type)
                        {
                            case enum_INT:
                                {
                                    if(value.Colume_Value_int != colume_value->colume_value.Colume_Value_int)
                                    {
                                        flag2 = 0;
                                    }
                                }
                                break;
                            case enum_FLOAT:
                                {
                                    if(value.Colume_Value_float != colume_value->colume_value.Colume_Value_float)
                                    {
                                        flag2 = 0;
                                    }
                                }
                                break;
                            case enum_STRING:
                                {
                                    if(strcmp(value.Colume_Value_string,colume_value->colume_value.Colume_Value_string) != 0)
                                    {
                                        flag2 = 0;
                                    }
                                }
                                break;
                        }
                    }
                    break;
                case enum_notBigger:
                    {
                        if(DEBUG_ENABLE)
                        {
                            printf("enum_notBigger \n");
                        }
                        colume_value = choice->choice_colume_value_list;
                        switch(colume_value->type)
                        {
                            case enum_INT:
                                {
                                    if(value.Colume_Value_int > colume_value->colume_value.Colume_Value_int)
                                    {
                                        flag2 = 0;
                                    }
                                }
                                break;
                            case enum_FLOAT:
                                {
                                    if(value.Colume_Value_float > colume_value->colume_value.Colume_Value_float)
                                    {
                                        flag2 = 0;
                                    }
                                }
                                break;
                            case enum_STRING:
                                {
                                    printf("ERROR: Type is not match!\n");
                                    return -2;
                                }
                                break;
                        }
                    }
                    break;
                case enum_notLess:
                    {
                        if(DEBUG_ENABLE)
                        {
                            printf("enum_notLess \n");
                        }
                        colume_value = choice->choice_colume_value_list;
                        switch(colume_value->type)
                        {
                            case enum_INT:
                                {
                                    if(value.Colume_Value_int < colume_value->colume_value.Colume_Value_int)
                                    {
                                        flag2 = 0;
                                    }
                                }
                                break;
                            case enum_FLOAT:
                                {
                                    if(value.Colume_Value_float < colume_value->colume_value.Colume_Value_float)
                                    {
                                        flag2 = 0;
                                    }
                                }
                                break;
                            case enum_STRING:
                                {
                                    printf("ERROR: Type is not match!\n");
                                    return -2;
                                }
                                break;
                        }
                    }
                    break;
                case enum_notEqual:
                    {
                        if(DEBUG_ENABLE)
                        {
                            printf("enum_notEqual \n");
                        }
                        colume_value = choice->choice_colume_value_list;
                        switch(colume_value->type)
                        {
                            case enum_INT:
                                {
                                    if(value.Colume_Value_int == colume_value->colume_value.Colume_Value_int)
                                    {
                                        flag2 = 0;
                                    }
                                }
                                break;
                            case enum_FLOAT:
                                {
                                    if(value.Colume_Value_float == colume_value->colume_value.Colume_Value_float)
                                    {
                                        flag2 = 0;
                                    }
                                }
                                break;
                            case enum_STRING:
                                {
                                    if(strcmp(value.Colume_Value_string,colume_value->colume_value.Colume_Value_string) == 0)
                                    {
                                        flag2 = 0;
                                    }
                                }
                                break;
                        }
                    }
                    break;

            }







            switch(linktype)
            {
                case enum_NO:
                    {
                        flag1 = flag2;
                        flag2 = 1;
                    }
                    break;
                case enum_AND:
                    {
                        flag1 = flag1*flag2;
                        flag2 = 1;
                    }
                    break;
                case enum_OR:
                    {
                        flag1 = ((flag1+flag2)>0)?1:0;
                        flag2 = 1;
                    }
                    break;
            }


            switch(sp->LinkType)
            {
                case enum_NO:
                    linktype = enum_NO;
                    break;
                case enum_AND:
                    linktype = enum_AND;
                    break;
                case enum_OR:
                    linktype = enum_OR;
                    break;
            }






            sp = sp->next_Option_Choices;

        }

    return flag1;
}





int selectTableChoice(struct Colume_List* colume_list,struct ID_List* ID_List,struct Option_Choices* option_choices) 
{
    /* //找到要插入的表
    struct Table* table = findTable(UsingDatabase,ID_List->name_ID);
    if(table->next_Table == NULL)
    {
        printf("ERROR: The table is not Exist!\n");
        return -1;
    }
    else
    {
        //找到目标表
        table = table->next_Table;
    } */

    struct Table* table = mixTable(ID_List);
    if(table == NULL)
    {
        if(DEBUG_ENABLE)
        {
            printf("selectTableMulti-> table is NULL\n");
        }
        return -1;
    }

  
    if(DEBUG_ENABLE)
    {   
        printf("\n");
        printf("selectTableMulti->begin\n");
        printf("selectTalbeMulti table name is %s\n",table->name_Table);
        printf("selectTableMulti count_items is: %d\n",table->count_items);

    }

    struct Colume* colume;
    int rowNumber = table->count_items;
    struct Colume_List* sp = colume_list;


    if(colume_list->type == enum_XING)
    {
        if(DEBUG_ENABLE)
        {
            printf("select all\n");
        }

        //打印名字
        colume= table->columes;
        while(colume->next_colume != NULL)
        {
            printf("|   %-12s",colume->next_colume->name_Colume);
            colume = colume->next_colume;
        }
        printf("\n");

        //依次打印每一行
        for(int i = 0; i < rowNumber;i++)
        {

            //flag_option_choice 返回值为1：可以输出， 返回值为-2：报错信息， 返回值为-1 不输出
            //
            if(flag_option_choice(table,i,option_choices) == -2)
            {
                return -1;
            }
            else if(flag_option_choice(table,i,option_choices) == 1)  //值为1，可以打印
            {
                colume= table->columes;
                while(colume->next_colume != NULL)
                {
                    //printf("|   %-10s ",colume->next_colume->name_Colume);

                    switch(colume->next_colume->type)
                    {
                        case enum_INT:
                            printf("|   %-12d",colume->next_colume->colume_value[i].Colume_Value_int);
                            break;
                        case enum_FLOAT:
                            printf("|   %-12g",colume->next_colume->colume_value[i].Colume_Value_float);
                            break;
                        case enum_STRING:
                            printf("|   %-12s",colume->next_colume->colume_value[i].Colume_Value_string);
                            break;
                    }
                    colume = colume->next_colume;
                }
                printf("\n");
            }

        }
    }
    else
    {
        if(DEBUG_ENABLE)
        {
            printf("select part\n");
        }


        //打印表头
        while(sp!=NULL)
        {
            //找到对应列
            colume = findColume(table,sp->name_ID);
            if(colume->next_colume == NULL)
            {
                printf("ERROR:The Colume is not exist!\n");
                return -1;
            }
            else 
            {
                colume = colume->next_colume; 
            }

            printf("|   %-12s",colume->name_Colume);
            sp = sp->next_Colume_List;
        }
        printf("\n");

        //打印每一行
        for(int i = 0;i < rowNumber; i++)
        {
            //flag_option_choice 返回值为1：可以输出， 返回值为-2：报错信息， 返回值为-1 不输出
            if(flag_option_choice(table,i,option_choices) == -2)
                return -1;
            else if(flag_option_choice(table,i,option_choices) == 1)
            {
                sp = colume_list;

                while(sp!=NULL)
                {
                    //找到对应列
                    colume = findColume(table,sp->name_ID);
                    if(colume->next_colume == NULL)
                    {
                        printf("ERROR:The Colume is not exist!\n");
                        return -1;
                    }
                    else 
                    {
                        colume = colume->next_colume; 
                    }

                    
                    switch(colume->type)
                    {
                        case enum_INT:
                            printf("|   %-12d",colume->colume_value[i].Colume_Value_int);
                            break;
                        case enum_FLOAT:
                            printf("|   %-12g",colume->colume_value[i].Colume_Value_float);
                            break;
                        case enum_STRING:
                            printf("|   %-12s",colume->colume_value[i].Colume_Value_string);
                            break;
                    }

                    sp = sp->next_Colume_List;
                }
                printf("\n");
            }
        }


    }


    return 1;
    
}


 void selectTableWithChoice(struct Colume_List* colume_list,struct ID_List* ID_List,struct Option_Choices* option_choices)
 {
    if(rootDatabase == NULL)
    {
        printf("ERROR:Please create a database firstly!\n");
        return ;
    }
    if(strlen(UsingDatabaseName) == 0)
    {
        printf("ERROR:Please choose a database firstly!\n");
        return ;
    }


    if(selectTableChoice(colume_list,ID_List,option_choices) == -1)
    {
        return ;
    }


    printf("select successfully!\n");
 }




 void deleteTable(char* TableName,struct Option_Choices* option_choices)
 {
    //找到要删除的表
    struct Table* table = findTable(UsingDatabase,TableName);
    if(table->next_Table == NULL)
    {
        printf("ERROR: The table is not Exist!\n");
        return ;
    }
    else
    {
        //找到目标表
        table = table->next_Table;
    }


    
    struct Colume* colume;
    int rowNumber = table->count_items;


    if(DEBUG_ENABLE)
    {
        printf("deletetable \n");
    }

    //打印名字
    /* colume= table->columes;
    while(colume->next_colume != NULL)
    {
        printf("|   %-12s",colume->next_colume->name_Colume);
        colume = colume->next_colume;
    }
    printf("\n"); */

    //依次遍历每一行
    for(int i = 0; i < rowNumber;i++)
    {

        //flag_option_choice 返回值为1：可以删除， 返回值为-2：报错信息， 返回值为-1 不做变化
        //
        if(flag_option_choice(table,i,option_choices) == -2)
        {
            return ;
        }
        else if(flag_option_choice(table,i,option_choices) == 1)  //值为1，可以删除
        {
            colume= table->columes;
            while(colume->next_colume != NULL)
            {


                switch(colume->next_colume->type)
                {
                    case enum_INT:
                        {
                            for(int j = i; j < rowNumber-1; j++)
                            {
                                colume->next_colume->colume_value[j].Colume_Value_int = 
                                colume->next_colume->colume_value[j+1].Colume_Value_int;
                            }
                           
                        }
                        break;
                    case enum_FLOAT:
                        {
                            for(int j = i; j < rowNumber-1; j++)
                            {
                                colume->next_colume->colume_value[j].Colume_Value_float = 
                                colume->next_colume->colume_value[j+1].Colume_Value_float;
                            }
                            
                        }
                        break;
                    case enum_STRING:
                        {
                            for(int j = i; j < rowNumber-1; j++)
                            {
                                strcpy(colume->next_colume->colume_value[j].Colume_Value_string,
                                colume->next_colume->colume_value[j+1].Colume_Value_string);
                            }
                        }
                        break;
                }

                colume = colume->next_colume;
            }
            
            //最后一行清零
            rowNumber--;
            table->count_items--;

        }

    }
    
    printf("delete successfully!\n");
 }



void updateTableALL(char* TableName,struct Choice_List* choice_list)
{
    //找到要更新的表
    struct Table* table = findTable(UsingDatabase,TableName);
    if(table->next_Table == NULL)
    {
        printf("ERROR: The table is not Exist!\n");
        return ;
    }
    else
    {
        //找到目标表
        table = table->next_Table;
    }


    struct Colume* colume;
    int rowNumber = table->count_items;

    struct Choice_List* sp;

    if(DEBUG_ENABLE)
    {
        printf("updateTableALL \n");
    }



    //依次遍历每一行
    for(int i = 0; i < rowNumber;i++)
    {

        //依次对choice_list中的列进行更改

        sp = choice_list;
        while(sp!=NULL)
        {
            //找到对应的列
            
            colume = findColume(table,sp->choice->name_ID);
            if(colume->next_colume == NULL)
            {
                printf("ERROR:The Colume is not exist!\n");
                return ;
            }
            else 
            {
                colume = colume->next_colume; 
            }

            //对列中对应行进行更新
            switch(sp->choice->choice_colume_value_list->type)
            {
                case enum_INT:
                    {
                        colume->colume_value[i].Colume_Value_int = 
                        sp->choice->choice_colume_value_list->colume_value.Colume_Value_int;
                    }
                    break;
                case enum_FLOAT:
                    {
                        colume->colume_value[i].Colume_Value_float = 
                        sp->choice->choice_colume_value_list->colume_value.Colume_Value_float;
                    }
                    break;
                case enum_STRING:
                    {
                        strcpy(colume->colume_value[i].Colume_Value_string,
                        sp->choice->choice_colume_value_list->colume_value.Colume_Value_string);
                    }
                    break;
            }
            

            sp = sp->next_Choice;
        }


    }
    printf("update successfully!\n");

}



void updateTable(char* TableName,struct Choice_List* choice_list,struct Option_Choices* option_choices)
{
    //找到要更新的表
    struct Table* table = findTable(UsingDatabase,TableName);
    if(table->next_Table == NULL)
    {
        printf("ERROR: The table is not Exist!\n");
        return ;
    }
    else
    {
        //找到目标表
        table = table->next_Table;
    }


    struct Colume* colume;
    int rowNumber = table->count_items;

    struct Choice_List* sp;

    if(DEBUG_ENABLE)
    {
        printf("updateTable \n");
    }

    

    //依次遍历每一行
    for(int i = 0; i < rowNumber;i++)
    {

        //flag_option_choice 返回值为1：可以更新， 返回值为-2：报错信息， 返回值为-1 不做变化
        //
        if(flag_option_choice(table,i,option_choices) == -2)
        {
            return ;
        }
        else if(flag_option_choice(table,i,option_choices) == 1)  //值为1，可以更新
        {


            //依次对choice_list中的列进行更改

            sp = choice_list;
            while(sp!=NULL)
            {
                //找到对应的列
                
                colume = findColume(table,sp->choice->name_ID);
                if(colume->next_colume == NULL)
                {
                    printf("ERROR:The Colume is not exist!\n");
                    return ;
                }
                else 
                {
                    colume = colume->next_colume; 
                }

                //对列中对应行进行更新
                switch(sp->choice->choice_colume_value_list->type)
                {
                    case enum_INT:
                        {
                            colume->colume_value[i].Colume_Value_int = 
                            sp->choice->choice_colume_value_list->colume_value.Colume_Value_int;
                        }
                        break;
                    case enum_FLOAT:
                        {
                            colume->colume_value[i].Colume_Value_float = 
                            sp->choice->choice_colume_value_list->colume_value.Colume_Value_float;
                        }
                        break;
                    case enum_STRING:
                        {
                            strcpy(colume->colume_value[i].Colume_Value_string,
                            sp->choice->choice_colume_value_list->colume_value.Colume_Value_string);
                        }
                        break;
                }
                



                sp = sp->next_Choice;
            }

        }

    }


    printf("update successfully!\n");
}
