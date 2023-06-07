%{
    int yywrap(void);
    int yylex(void);
    #include<string.h>
    #include"sql.tab.hh"
    int yyline =1;
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
STRING '\'[^\']*\''
NUMBERFLOAT -?(([0-9]*\.[0-9]+)([Ee][+-]?[0-9]+)?)
NAME [a-zA-Z][a-zA-Z0-9_]*

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
{NUMBER} {yylval.intval = atoi(yytext); return INT;}
{NUMBERFLOAT} {yylval.val_float = atof(yytext); return FLOAT;}
{NAME}    {yylval.val_string = strdup(yytext); return ID;}

"("  { return LEFT_PARENTHESIS; }
")"  { return RIGHT_PARENTHESIS; }
";"  { return SEMICOLON; }
","  { return COMMA; }
"*"  { return STAR; }
"."  { return DOT; }
"<"  { return LESS_THAN; }
">"  { return GREATER_THAN; }
"<=" { return NOT_GREATER_THAN}
">=" { return NOT_LESS_THAN}
"="  { return EQUAL; }
"!="  { return NOT_EQUAL; }

\n   { line++; }
{STRING} {*(yytext+strlen(yytext)-1) = '\0'; yylval.chval = strdup(yytext+1);  return STRING;}
[ \t]+                {;}//忽视空白
"//".*                {;}//跳过注释
%%

int yywrap(void){
    return 1;
}
