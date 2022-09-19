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
    ID = 258,                      /* ID  */
    NUMCONST = 259,                /* NUMCONST  */
    CHARCONST = 260,               /* CHARCONST  */
    STRINGCONST = 261,             /* STRINGCONST  */
    BOOLCONST = 262,               /* BOOLCONST  */
    ytlesser = 263,                /* ytlesser  */
    ytgreater = 264,               /* ytgreater  */
    ytequals = 265,                /* ytequals  */
    ytadd = 266,                   /* ytadd  */
    ytsub = 267,                   /* ytsub  */
    ytmul = 268,                   /* ytmul  */
    ytdiv = 269,                   /* ytdiv  */
    ytlbracket = 270,              /* ytlbracket  */
    ytrbracket = 271,              /* ytrbracket  */
    ytquestion = 272,              /* ytquestion  */
    ytcomma = 273,                 /* ytcomma  */
    ytsemicolon = 274,             /* ytsemicolon  */
    ytcolon = 275,                 /* ytcolon  */
    ytlbrace = 276,                /* ytlbrace  */
    ytrbrace = 277,                /* ytrbrace  */
    ytlparen = 278,                /* ytlparen  */
    ytrparen = 279,                /* ytrparen  */
    ytmod = 280,                   /* ytmod  */
    ytand = 281,                   /* ytand  */
    ytor = 282,                    /* ytor  */
    yteq = 283,                    /* yteq  */
    ytnoteq = 284,                 /* ytnoteq  */
    yteqlesser = 285,              /* yteqlesser  */
    yteqgreater = 286,             /* yteqgreater  */
    ytassadd = 287,                /* ytassadd  */
    ytasssub = 288,                /* ytasssub  */
    ytassmul = 289,                /* ytassmul  */
    ytassdiv = 290,                /* ytassdiv  */
    ytinc = 291,                   /* ytinc  */
    ytdec = 292,                   /* ytdec  */
    ytnot = 293,                   /* ytnot  */
    ytint = 294,                   /* ytint  */
    ytif = 295,                    /* ytif  */
    ytfor = 296,                   /* ytfor  */
    ytto = 297,                    /* ytto  */
    ytby = 298,                    /* ytby  */
    ytdo = 299,                    /* ytdo  */
    ytthen = 300,                  /* ytthen  */
    ytbreak = 301,                 /* ytbreak  */
    ytelse = 302,                  /* ytelse  */
    ytwhile = 303,                 /* ytwhile  */
    ytreturn = 304,                /* ytreturn  */
    ytbool = 305,                  /* ytbool  */
    ytchar = 306,                  /* ytchar  */
    ytstatic = 307                 /* ytstatic  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 9 "parser.y"

    struct TokenData *tokenPtr;

#line 120 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
