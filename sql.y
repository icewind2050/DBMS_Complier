%{
    int yylex(void);
    void yyerror(char *)
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
%left OR
%left AND