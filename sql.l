%{
    #include<string.h>
    #include"sql.tab.h"
    int line =1;
%}
CREATE CREATE|create
SHOW SHOW|show
DROP DROP|drop
USE USE|use
DATABASE DATABASE|database
DATABASES DATABASES|databases
TABLE TABLE|table
TABLES TABLES|tables
CHAR CHAR|char
INT INT|int
FROM from|FROM
SELECT SELECT|select
WHERE WHERE|where
AND AND|and
OR OR|or
INSERT INSERT|insert
INTO INTO|into
VALUES VALUES|VALUES
DELETE DELETE|delete
UPDATE UPDATE|update
SET SET|set
ID [a-zA-Z][a-zA-Z_0-9]*
NUMBER [-+]?[0-9][0-9]*
STRING '.*'

%%
{CHAR} {yylval.typeval = CHAR; return CHAR; }
{INT} {yylval.typeval = INT; return INT;}

{CREATE} { return CREATE;}
{SHOW} {return SHOW; }
{DROP} {return DROP; }
{USE} {return USE;}
{TABLE} {return TABLE;}
{TABLES} { return TABLES;}
{DATABASE} { return DATABASE;}
{DATABASES} { return DATABASES;}


{SELECT} {return SELECT;}
{FROM} {return FROM;}
{WHERE} {return WHERE;}
{AND} {return AND;}
{OR} {return OR;}

{INSERT} {return INSERT;}
{INTO} {return INTO;}
{VALUES} {return VALUES;}

{DELETE} {return DELETE;}
{UPDATE} {return UPDATE;}
{SET} {return SET;}

{ID} { yylval.chval = strdup(yytext); return ID;}
{NUMBER} {yylval.intval = atoi(yytext); return NUMBER;}
"("  { return LEFT_PARENTHESIS; }
")"  { return RIGHT_PARENTHESIS; }
";"  { return SEMICOLON; }
","  { return COMMA; }
"*"  { return ASTERISK; }
"."  { return DOT; }
"<"  { return GREATER_THAN; }
">"  { return LESS_THAN; }
"="  { return EQUAL; }
"!"  { return EXCLA; }

\n   { line++; }
{STRING} {*(yytext+strlen(yytext)-1) = '\0'; yylval.chval = strdup(yytext+1);  return STRING;}
[ \t]+                {;}//忽视空白
"//".*                {;}//跳过注释
%%