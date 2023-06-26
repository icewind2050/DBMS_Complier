/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SQL_TAB_H_INCLUDED
# define YY_YY_SQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CREATE = 258,                  /* CREATE  */
    DATABASE = 259,                /* DATABASE  */
    SHOW = 260,                    /* SHOW  */
    DATABASES = 261,               /* DATABASES  */
    DROP = 262,                    /* DROP  */
    USE = 263,                     /* USE  */
    TABLE = 264,                   /* TABLE  */
    TABLES = 265,                  /* TABLES  */
    INSERT = 266,                  /* INSERT  */
    INTO = 267,                    /* INTO  */
    VALUES = 268,                  /* VALUES  */
    SELECT = 269,                  /* SELECT  */
    FROM = 270,                    /* FROM  */
    WHERE = 271,                   /* WHERE  */
    UPDATE = 272,                  /* UPDATE  */
    SET = 273,                     /* SET  */
    CHAR = 274,                    /* CHAR  */
    DELETE = 275,                  /* DELETE  */
    LEFT_PARENTHESIS = 276,        /* LEFT_PARENTHESIS  */
    RIGHT_PARENTHESIS = 277,       /* RIGHT_PARENTHESIS  */
    SEMICOLON = 278,               /* SEMICOLON  */
    COMMA = 279,                   /* COMMA  */
    STAR = 280,                    /* STAR  */
    DOT = 281,                     /* DOT  */
    GREATER_THAN = 282,            /* GREATER_THAN  */
    LESS_THAN = 283,               /* LESS_THAN  */
    NOT_LESS_THAN = 284,           /* NOT_LESS_THAN  */
    NOT_GREATER_THAN = 285,        /* NOT_GREATER_THAN  */
    EQUAL = 286,                   /* EQUAL  */
    NOT_EQUAL = 287,               /* NOT_EQUAL  */
    INT = 288,                     /* INT  */
    FLOAT = 289,                   /* FLOAT  */
    STRING = 290,                  /* STRING  */
    ID = 291,                      /* ID  */
    OR = 292,                      /* OR  */
    AND = 293,                     /* AND  */
    UNINUMS = 294                  /* UNINUMS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 8 "sql.y"

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

#line 125 "sql.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SQL_TAB_H_INCLUDED  */
