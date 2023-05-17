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
%token ASTERISK //"*"
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
         | deleteSQL    //删除表
         | DB           //数据库操作语句
         ;


%%
int main(){
    printf("\nSQL>");
    while(1){
        yyparse();
    }
}

