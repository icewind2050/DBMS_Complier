%{
    #include<stdio.h>
    int yylex(void);
    void yyerror(char *s){
        printf("ERROR '%s'\n",s);
    }
%}
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
%token ID
%token CHAR
%token NUMBER
%token INT
%token STRING
%token DELETE
%token LEFT_PARENTHESIS //"("
%token RIGHT_PARENTHESIS//")"
%token SEMICOLON //";"
%token COMMA //","
%token STAR //"*"
%token DOT //"."
%token GREATER_THAN //">"
%token LESS_THAN   //"<"
%token EQUAL //"="
%token EXCLA //"!"

%left OR
%left AND//终结符定义,生成的头文件会在词法分析器中用到

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
         | DBSQL        //数据库操作
         ;

createSQL: CREATE TABLE table LEFT_PARENTHESIS field_definition RIGHT_PARENTHESIS SEMICOLON
         ;

table: ID
     ;

field_definition: field_type
                | field_definition COMMA field_type
                ;

field_type: field type
          ;

field:ID
     ;

type: CHAR LEFT_PARENTHESIS NUMBER RIGHT_PARENTHESIS
    | INT
    ;

selectSQL: SELECT field_star FROM tables SEMICOLON
         | SELECT field_star FROM tables WHERE conditions SEMICOLON
         ;

field_star: table_fields
          | STAR
          ;

table_fields: table_field
            | table_field COMMA table_fields
            ;

table_field: field
           | table DOT field
           ;

tables: table
      | table COMMA tables
      ;

conditions: comp_left comp_op comp_right
          ;

comp_left: table_field
         ;

comp_op: GREATER_THAN
       | LESS_THAN
       | EQUAL
       | EXCLA EQUAL
       ;

comp_right: table_field
          | NUMBER
          | STRING
          ;

insertSQL: INSERT INTO table VALUES LEFT_PARENTHESIS values RIGHT_PARENTHESIS SEMICOLON
         | INSERT INTO table LEFT_PARENTHESIS field RIGHT_PARENTHESIS VALUES LEFT_PARENTHESIS values RIGHT_PARENTHESIS SEMICOLON
         ; 
%%
int main(){
    printf("\nSQL>");
    while(1){
        yyparse();
    }
}

