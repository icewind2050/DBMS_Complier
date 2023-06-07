%{
    
    int yylex(void);
    void yyerror(char *s){
        printf("ERROR '%s'\n",s);
    }
    #include<stdio.h>
    #include"include/DBCORE.hh"
    #include"include/DBSHELL.hh"
    
%}
%union{
    int val_int;
    float val_float;
    double val_double;
    char* val_string;
    enum OpType* val_opType;

    struct Colume_Defination_Type* val_colume_defination_type;
    struct Colume_Defination* val_colume_defination;
    struct Colume_Defination_List* val_colume_defination_list;

    union Colume_Value* val_colume_value;
    struct Colume_Value_List* val_colume_value_list;
    struct Colume_List* val_colume_list;

    struct Choice* val_choice;
    struct Option_Choices* val_option_choices;

    struct ID_List* val_ID_list;
    struct Choice_List* val_choices_list;
}
%token CREATE
%token DATABASE
%token SHOW
%token DATABASES
%token DROP
%token USE
%token TABLE
%token TABLES
%token INSERT
%token INTO
%token VALUES
%token SELECT
%token FROM
%token WHERE
%token UPDATE
%token SET
%token CHAR
%token DELETE
%token LEFT_PARENTHESIS //"("
%token RIGHT_PARENTHESIS//")"
%token SEMICOLON //";"
%token COMMA //","
%token STAR //"*"
%token DOT //"."
%token GREATER_THAN //">"
%token LESS_THAN   //"<"
%token NOT_LESS_THAN//">="
%token NOT_GREATER_THAN//"<="
%token EQUAL //"="
%token NOT_EQUAL //"!="


%token<val_int>INT 
%token<val_float>FLOAT
%token<val_string>STRING
%token<val_string> ID 

%type<val_colume_defination_type> columes_defination_type
%type<val_colume_defination> columes_defination
%type<val_colume_defination_list> columes_defination_list

%type<val_colume_value_list> columes_value
%type<val_colume_value_list> columes_value_list
%type<val_colume_list> columes_list


%type<val_choice> choice
%type<val_option_choices> option_choices
%type<val_ID_list> ID_list
%type<val_choices_list> choices_list  

%left OR
%left AND//终结符定义,生成的头文件会在词法分析器中用到
%nonassoc UNINUMS

%%
//TODO:从这里开始先定义语句，生成代码后面在写
statements: statements statement {printf("\nSQL> ");}
          | statement {printf("\nSQL> ");}
          ; //这里定义了语句的开始符号statements,后面每次用户每次输入语句都从这里开始


statement: createSQL    //建表语句
         | selectSQL    //查询语句
         | insertSQL    //插入语句
         | updateSQL    //更新语句
         | deleteSQL    //删除
         | dropSQL      //删掉整个表
         | DBSQL        //数据库操作
         ;

createSQL:CREATE TABLE table LEFT_PARENTHESIS colume_defination_list RIGHT_PARENTHESIS SEMICOLON{
            createTable($3,$5);
            printf("SQL>>");
         }
         ;

columes_defination_list:colume_defination{
                            $$ = (struct Colume_Defination_List*)malloc(sizeof(struct Colume_Defination_List));
                            $$->colume_defination = $1;
                            $$->next_colume_defination = NULL;
                        }
                       |columes_defination_list COMMA colume_defination{
                            $$ = $1;
                            struct Colume_Defination_List* sp = $$;
                            while(sp->next_colume_defination != NULL)
                                sp = sp->next_colume_defination;
                            sp->next_colume_defination = (struct Colume_Defination_List*)malloc(sizeof(struct Colume_Defination_List));
                            sp->next_colume_defination->colume_defination = $3;
                            sp->next_colume_defination->next_colume_defination = NULL;
                       }
                       ;

columes_defination:ID colume_defination_type{
                        $$ = (struct Colume_Defination*)malloc(sizeof(struct Colume_Defination));
                        strcpy($$->name_ID,$1);
                        $$->colume_defination_type= $2;
                   }
                   ;

colume_defination_type:INT
                      {
                        $$ = (struct Colume_Defination_Type*)malloc(sizeof(struct Colume_Defination_Type));
                        $$->type_colume = enum_INT;
                      }
                      |CHAR LEFT_PARENTHESIS INT RIGHT_PARENTHESIS{
                        $$ = (struct Colume_Defination_Type*)malloc(sizeof(struct Colume_Defination_Type));
                        $$->type_colume = enum_STRING; 
                      }
                      |FLOAT{
                        $$ = (struct Colume_Defination_Type*)malloc(sizeof(struct Colume_Defination_Type));
                        $$->type_colume = enum_FLOAT; 
                      }
                      ;

table:ID;
insertSQL:INSERT INTO table LEFT_PARENTHESIS colume_list RIGHT_PARENTHESIS VALUES LEFT_PARENTHESIS columes_value_list RIGHT_PARENTHESIS SEMICOLON{
            insertTable($3,$5,$9);
            printf("SQL>>");
         }
         |INSERT INTO table VALUES LEFT_PARENTHESIS columes_value_list RIGHT_PARENTHESIS SEMICOLON{
            insertTable($3,NULL,$6);
            printf("SQL>>");
         }

colume_list:STAR{
                $$ = (struct Colume_List*)malloc(sizeof(struct Colume_List));
                $$->type = enum_XING;
                strcpy($$->name_ID,"*");
                $$->next_Colume_List = NULL
           }
           |colume{
                $$ = (struct Colume_List*)malloc(sizeof(struct Colume_List));
                $$->type = enum_STRING;
                strcpy($$->name_ID,$1);
                $$->next_Colume_List = NULL;
           }
           |colume_list COMMA colume{
                $$ = $1;
                struct Colume_List* sp = $$;
                while(sp->next_Colume_List!=NULL){
                    sp = sp->next_Colume_List;
                }
                sp->next_Colume_List = (struct Colume_List*)malloc(sizeof(struct Colume_List));
                sp->next_Colume_List->type = enum_STRING;
                strcpy(sp->next_Colume_List->name_ID,$3);
                sp->next_Colume_List->next_Colume_List = NULL;
           }
           |LEFT_PARENTHESIS colume_list RIGHT_PARENTHESIS %prec UNINUM{
            $$ = $2;
           }
           ;

colume:ID;
columes_value_list: colume_value{
                        $$ = $1;
                    }
                  | columes_value_list COMMA colume_value{
                        $$ = $1;
                        struct Colume_Value_List* sp = $$;
                        while(sp->next_Colume_Value_List != NULL)
                            sp = sp->next_Colume_Value_List;
                        
                        sp->next_Colume_Value_List = (struct Colume_Value_List*)malloc(sizeof(struct Colume_Value_List));
                        sp->next_Colume_Value_List = $3;
                    }
                    ;

colume_value:   STRING{
                    $$ = (struct Colume_Value_List*)malloc(sizeof(struct Colume_Value_List));
                    $$->type = enum_STRING;
                    strcpy($$->colume_value.Colume_Value_string,$1);
                    $$->next_Colume_Value_List = NULL;
            }
            |   INT{
                    $$ = (struct Colume_Value_List*)malloc(sizeof(struct Colume_Value_List));
                    $$->type = enum_INT;
                    $$->colume_value.Colume_Value_int = $1;
                    $$->next_Colume_Value_List= NULL;
            }
            |   FLOAT{
                    $$ = (struct Colume_Value_List*)malloc(sizeof(struct Colume_Value_List));
                    $$->type = enum_FLOAT;
                    $$->colume_value.Colume_Value_float = $1;
                    $$->next_Colume_Value_List = NULL;
            }
            ;


selectSQL:SELECT colume_list FROM ID_list SEMICOLON{
            selectTableWithNoChoice($2,$4);
            printf("SQL>>");
         }
         |SELECT colume_list FROM ID_list WHERE option_choices SEMICOLON{
            selectTableWithChoice($2,$4,$6);
            printf("SQL>>");
         }
        ;
ID_list:ID{
            $$ = (struct ID_List*)malloc(sizeof(struct ID_List));
            strcpy($$->name_ID,$1);
            $$->next_ID = NULL;
        }
        |ID_list COMMA ID{
            $$ = $1;
            struct ID_List* sp = $$;
            while(sp->next_ID != NULL)
            {
                sp = sp->next_ID;
            }

            sp->next_ID = (struct ID_List*)malloc(sizeof(struct ID_List));
            strcpy(sp->next_ID->name_ID,$3);
            sp->next_ID->next_ID = NULL;
        }
        ;

option_choices: choice{
                   $$ = (struct Option_Choices*)malloc(sizeof(struct Option_Choices));
                    $$->choice = $1;
                    $$->LinkType = enum_NO;
                    $$->next_Option_Choices = NULL; 
                }
                |LEFT_PARENTHESIS option_choices RIGHT_PARENTHESIS %prec UNINUMS{
                    $$ = $2;
                }
                |option_choices AND option_choices{
                    $$ = $1;
                    struct Option_Choices* sp = $$;
                    while(sp->next_Option_Choices != NULL){
                        sp = sp->next_Option_Choices;
                    }
                    sp->LinkType = enum_AND;
                    sp->next_Option_Choices = $3;
                }
                |option_choices OR option_choices{
                    $$ = $1;
                    struct Option_Choices* sp = $$;
                    while(sp->next_Option_Choices != NULL){
                        sp = sp->next_Option_Choices;
                    }
                    sp->LinkType = enum_OR;
                    sp->next_Option_Choices = $3
                }
                ;


choice: colume LESS_THAN colume_value{
            $$ = (struct Choice*)malloc(sizeof(struct Choice));
            strcpy($$->name_ID,$1);
            $$->optype = enum_Less;
            $$->choice_colume_value_list = $3;
        }
        |colume GREATER_THAN colume_value{
            $$ = (struct Choice*)malloc(sizeof(struct Choice));
            strcpy($$->name_ID,$1);
            $$->optype = enum_Bigger;
            $$->choice_colume_value_list = $3;
        }
        |colume EQUAL colume_value{
            $$ = (struct Choice*)malloc(sizeof(struct Choice));
            strcpy($$->name_ID,$1);
            $$->optype = enum_Equal;
            $$->choice_colume_value_list = $3;
        }
        |colume NOT_GREATER_THAN colume_value{
            $$ = (struct Choice*)malloc(sizeof(struct Choice));
            strcpy($$->name_ID,$1);
            $$->optype = enum_notBigger;
            $$->choice_colume_value_list = $3;
        }
        |colume NOT_LESS_THAN colume_value{
            $$ = (struct Choice*)malloc(sizeof(struct Choice));
            strcpy($$->name_ID,$1);
            $$->optype = enum_notLess;
            $$->choice_colume_value_list = $3;
        }
        |colume NOT_EQUAL colume_value{
            $$ = (struct Choice*)malloc(sizeof(struct Choice));
            strcpy($$->name_ID,$1);
            $$->optype = enum_notEqual;
            $$->choice_colume_value_list = $3;
        }
        ;

choices_list:choice{
                $$ = (struct Choice_List*)malloc(sizeof(struct Choice_List));
                $$->choice = $1;
                $$->next_Choice = NULL;
            }
            |choices_list COMMA choice{
                $$ = $1;
                struct Choice_List* sp = $$;
                while(sp->next_Choice != NULL){
                    sp = sp->next_Choice;
                }
                sp->next_Choice = (struct Choice_List*)malloc(sizeof(struct Choice_List));
                sp->next_Choice->choice = $3;
                sp->next_Choice->next_Choice = NULL;
            }
            ;
dropSQL:DROP TABLE table SEMICOLON{
            dropTable($3);
            printf("SQL>>");
        }
        ;

deleteSQL:DELETE FROM table WHERE option_choices SEMICOLON{
            deleteTable($3,$5);
            printf("SQL>>");
        }


updateSQL:UPDATE table SET choices_list SEMICOLON{
            updateTableALL($2,$4);
            printf("SQL>>");
        }
        | UPDATE table SET choices_list WHERE option_choices SEMICOLON{
            updateTable($2,$4,$6);
            printf("SQL>>");
        }
        ;

showSQL:SHOW TABLES SEMICOLON{
        showTables();
        printf("SQL>>");
    }
    ;

DBSQL: CREATE DATABASE database SEMICOLON{createDatabase($3;)}
     | DROP DATABASE database SEMICOLON{dropDatabase($3)}
     | DROP TABLE table SEMICOLON{showDatabases($3)}
     | USE database SEMICOLON{useDatabase($3)}
     ;
database: ID
        ;
%%
int main(){
    printf("\nSQL>");
    while(1){
        yyparse();
    }
}

