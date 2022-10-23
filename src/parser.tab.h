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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
    ytint = 258,                   /* ytint  */
    ytbool = 259,                  /* ytbool  */
    ytchar = 260,                  /* ytchar  */
    ytstatic = 261,                /* ytstatic  */
    ID = 262,                      /* ID  */
    NUMCONST = 263,                /* NUMCONST  */
    CHARCONST = 264,               /* CHARCONST  */
    STRINGCONST = 265,             /* STRINGCONST  */
    BOOLCONST = 266,               /* BOOLCONST  */
    ytequals = 267,                /* ytequals  */
    ytadd = 268,                   /* ytadd  */
    ytsub = 269,                   /* ytsub  */
    ytmul = 270,                   /* ytmul  */
    ytdiv = 271,                   /* ytdiv  */
    ytmod = 272,                   /* ytmod  */
    ytassadd = 273,                /* ytassadd  */
    ytasssub = 274,                /* ytasssub  */
    ytassmul = 275,                /* ytassmul  */
    ytassdiv = 276,                /* ytassdiv  */
    ytinc = 277,                   /* ytinc  */
    ytdec = 278,                   /* ytdec  */
    ytquestion = 279,              /* ytquestion  */
    ytlesser = 280,                /* ytlesser  */
    ytgreater = 281,               /* ytgreater  */
    yteq = 282,                    /* yteq  */
    ytnoteq = 283,                 /* ytnoteq  */
    yteqlesser = 284,              /* yteqlesser  */
    yteqgreater = 285,             /* yteqgreater  */
    ytif = 286,                    /* ytif  */
    ytelse = 287,                  /* ytelse  */
    ytwhile = 288,                 /* ytwhile  */
    ytdo = 289,                    /* ytdo  */
    ytthen = 290,                  /* ytthen  */
    ytnot = 291,                   /* ytnot  */
    ytand = 292,                   /* ytand  */
    ytor = 293,                    /* ytor  */
    ytfor = 294,                   /* ytfor  */
    ytto = 295,                    /* ytto  */
    ytby = 296,                    /* ytby  */
    ytbreak = 297,                 /* ytbreak  */
    ytreturn = 298,                /* ytreturn  */
    ytcompound = 299,              /* ytcompound  */
    ytarr = 300                    /* ytarr  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "parser.y"

    Token token;
    Node * nodePtr;
    char * literal;

#line 115 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
