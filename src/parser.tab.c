/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include "Token.h"
#include "ASTNode.h"
#include "parser.tab.h"
#include <stdio.h>
#include <string.h>

extern int yylex();

extern Node * AST;

int yyerror (char *s) { //does nothing?
    printf("%s\n", s);
    return 0;
}


#line 89 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ytint = 3,                      /* ytint  */
  YYSYMBOL_ytbool = 4,                     /* ytbool  */
  YYSYMBOL_ytchar = 5,                     /* ytchar  */
  YYSYMBOL_ytstatic = 6,                   /* ytstatic  */
  YYSYMBOL_ID = 7,                         /* ID  */
  YYSYMBOL_NUMCONST = 8,                   /* NUMCONST  */
  YYSYMBOL_CHARCONST = 9,                  /* CHARCONST  */
  YYSYMBOL_STRINGCONST = 10,               /* STRINGCONST  */
  YYSYMBOL_BOOLCONST = 11,                 /* BOOLCONST  */
  YYSYMBOL_ytequals = 12,                  /* ytequals  */
  YYSYMBOL_ytadd = 13,                     /* ytadd  */
  YYSYMBOL_ytsub = 14,                     /* ytsub  */
  YYSYMBOL_ytmul = 15,                     /* ytmul  */
  YYSYMBOL_ytdiv = 16,                     /* ytdiv  */
  YYSYMBOL_ytmod = 17,                     /* ytmod  */
  YYSYMBOL_ytassadd = 18,                  /* ytassadd  */
  YYSYMBOL_ytasssub = 19,                  /* ytasssub  */
  YYSYMBOL_ytassmul = 20,                  /* ytassmul  */
  YYSYMBOL_ytassdiv = 21,                  /* ytassdiv  */
  YYSYMBOL_ytinc = 22,                     /* ytinc  */
  YYSYMBOL_ytdec = 23,                     /* ytdec  */
  YYSYMBOL_ytquestion = 24,                /* ytquestion  */
  YYSYMBOL_ytlesser = 25,                  /* ytlesser  */
  YYSYMBOL_ytgreater = 26,                 /* ytgreater  */
  YYSYMBOL_yteq = 27,                      /* yteq  */
  YYSYMBOL_ytnoteq = 28,                   /* ytnoteq  */
  YYSYMBOL_yteqlesser = 29,                /* yteqlesser  */
  YYSYMBOL_yteqgreater = 30,               /* yteqgreater  */
  YYSYMBOL_ytif = 31,                      /* ytif  */
  YYSYMBOL_ytelse = 32,                    /* ytelse  */
  YYSYMBOL_ytwhile = 33,                   /* ytwhile  */
  YYSYMBOL_ytdo = 34,                      /* ytdo  */
  YYSYMBOL_ytthen = 35,                    /* ytthen  */
  YYSYMBOL_ytnot = 36,                     /* ytnot  */
  YYSYMBOL_ytand = 37,                     /* ytand  */
  YYSYMBOL_ytor = 38,                      /* ytor  */
  YYSYMBOL_ytfor = 39,                     /* ytfor  */
  YYSYMBOL_ytto = 40,                      /* ytto  */
  YYSYMBOL_ytby = 41,                      /* ytby  */
  YYSYMBOL_ytbreak = 42,                   /* ytbreak  */
  YYSYMBOL_ytreturn = 43,                  /* ytreturn  */
  YYSYMBOL_ytcompound = 44,                /* ytcompound  */
  YYSYMBOL_ytarr = 45,                     /* ytarr  */
  YYSYMBOL_46_ = 46,                       /* ';'  */
  YYSYMBOL_47_ = 47,                       /* ','  */
  YYSYMBOL_48_ = 48,                       /* ':'  */
  YYSYMBOL_49_ = 49,                       /* ']'  */
  YYSYMBOL_50_ = 50,                       /* '('  */
  YYSYMBOL_51_ = 51,                       /* ')'  */
  YYSYMBOL_52_ = 52,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_program = 54,                   /* program  */
  YYSYMBOL_declList = 55,                  /* declList  */
  YYSYMBOL_decl = 56,                      /* decl  */
  YYSYMBOL_varDecl = 57,                   /* varDecl  */
  YYSYMBOL_scopedVarDecl = 58,             /* scopedVarDecl  */
  YYSYMBOL_varDeclList = 59,               /* varDeclList  */
  YYSYMBOL_varDeclInit = 60,               /* varDeclInit  */
  YYSYMBOL_varDeclId = 61,                 /* varDeclId  */
  YYSYMBOL_typeSpec = 62,                  /* typeSpec  */
  YYSYMBOL_funDecl = 63,                   /* funDecl  */
  YYSYMBOL_parms = 64,                     /* parms  */
  YYSYMBOL_parmList = 65,                  /* parmList  */
  YYSYMBOL_parmTypeList = 66,              /* parmTypeList  */
  YYSYMBOL_parmIdList = 67,                /* parmIdList  */
  YYSYMBOL_parmId = 68,                    /* parmId  */
  YYSYMBOL_stmt = 69,                      /* stmt  */
  YYSYMBOL_matched = 70,                   /* matched  */
  YYSYMBOL_unmatched = 71,                 /* unmatched  */
  YYSYMBOL_expStmt = 72,                   /* expStmt  */
  YYSYMBOL_compoundStmt = 73,              /* compoundStmt  */
  YYSYMBOL_localDecls = 74,                /* localDecls  */
  YYSYMBOL_stmtList = 75,                  /* stmtList  */
  YYSYMBOL_matchedSelectStmt = 76,         /* matchedSelectStmt  */
  YYSYMBOL_unmatchedSelectStmt = 77,       /* unmatchedSelectStmt  */
  YYSYMBOL_matchedIterStmt = 78,           /* matchedIterStmt  */
  YYSYMBOL_unmatchedIterStmt = 79,         /* unmatchedIterStmt  */
  YYSYMBOL_iterRange = 80,                 /* iterRange  */
  YYSYMBOL_returnStmt = 81,                /* returnStmt  */
  YYSYMBOL_breakStmt = 82,                 /* breakStmt  */
  YYSYMBOL_exp = 83,                       /* exp  */
  YYSYMBOL_assignop = 84,                  /* assignop  */
  YYSYMBOL_simpleExp = 85,                 /* simpleExp  */
  YYSYMBOL_andExp = 86,                    /* andExp  */
  YYSYMBOL_unaryRelExp = 87,               /* unaryRelExp  */
  YYSYMBOL_relExp = 88,                    /* relExp  */
  YYSYMBOL_relop = 89,                     /* relop  */
  YYSYMBOL_sumExp = 90,                    /* sumExp  */
  YYSYMBOL_sumop = 91,                     /* sumop  */
  YYSYMBOL_mulExp = 92,                    /* mulExp  */
  YYSYMBOL_mulop = 93,                     /* mulop  */
  YYSYMBOL_unaryExp = 94,                  /* unaryExp  */
  YYSYMBOL_unaryop = 95,                   /* unaryop  */
  YYSYMBOL_factor = 96,                    /* factor  */
  YYSYMBOL_mutable = 97,                   /* mutable  */
  YYSYMBOL_immutable = 98,                 /* immutable  */
  YYSYMBOL_call = 99,                      /* call  */
  YYSYMBOL_args = 100,                     /* args  */
  YYSYMBOL_argList = 101,                  /* argList  */
  YYSYMBOL_constant = 102                  /* constant  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   217

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  111
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  171

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   300


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      50,    51,     2,     2,    47,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    46,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    52,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    37,    37,    41,    48,    52,    55,    59,    72,    85,
      98,   105,   109,   112,   123,   127,   133,   136,   139,   143,
     152,   162,   165,   169,   175,   179,   193,   200,   204,   208,
     214,   217,   222,   225,   227,   230,   233,   236,   240,   243,
     247,   250,   254,   260,   267,   271,   278,   282,   289,   294,
     301,   307,   320,   326,   339,   344,   351,   354,   359,   363,
     368,   372,   376,   380,   383,   386,   389,   392,   396,   401,
     405,   410,   414,   418,   422,   427,   431,   434,   437,   440,
     443,   446,   450,   455,   459,   462,   466,   471,   475,   478,
     481,   485,   488,   492,   495,   498,   502,   505,   509,   512,
     520,   523,   526,   530,   537,   540,   544,   551,   555,   560,
     565,   570
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ytint", "ytbool",
  "ytchar", "ytstatic", "ID", "NUMCONST", "CHARCONST", "STRINGCONST",
  "BOOLCONST", "ytequals", "ytadd", "ytsub", "ytmul", "ytdiv", "ytmod",
  "ytassadd", "ytasssub", "ytassmul", "ytassdiv", "ytinc", "ytdec",
  "ytquestion", "ytlesser", "ytgreater", "yteq", "ytnoteq", "yteqlesser",
  "yteqgreater", "ytif", "ytelse", "ytwhile", "ytdo", "ytthen", "ytnot",
  "ytand", "ytor", "ytfor", "ytto", "ytby", "ytbreak", "ytreturn",
  "ytcompound", "ytarr", "';'", "','", "':'", "']'", "'('", "')'", "'}'",
  "$accept", "program", "declList", "decl", "varDecl", "scopedVarDecl",
  "varDeclList", "varDeclInit", "varDeclId", "typeSpec", "funDecl",
  "parms", "parmList", "parmTypeList", "parmIdList", "parmId", "stmt",
  "matched", "unmatched", "expStmt", "compoundStmt", "localDecls",
  "stmtList", "matchedSelectStmt", "unmatchedSelectStmt",
  "matchedIterStmt", "unmatchedIterStmt", "iterRange", "returnStmt",
  "breakStmt", "exp", "assignop", "simpleExp", "andExp", "unaryRelExp",
  "relExp", "relop", "sumExp", "sumop", "mulExp", "mulop", "unaryExp",
  "unaryop", "factor", "mutable", "immutable", "call", "args", "argList",
  "constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-133)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      73,  -133,  -133,  -133,   -43,    33,    73,  -133,  -133,    30,
    -133,    85,  -133,  -133,   -29,    -3,  -133,     0,    67,     1,
      36,  -133,    71,    85,  -133,    87,   148,    61,    65,  -133,
      72,    85,    66,    68,    75,  -133,   -19,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,   148,   148,    84,    88,  -133,  -133,
     140,    94,  -133,   167,  -133,  -133,  -133,  -133,  -133,    79,
      67,  -133,  -133,  -133,  -133,    72,   148,   148,  -133,    80,
      84,    46,   148,   148,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,   167,   167,  -133,  -133,  -133,   167,  -133,  -133,
    -133,    81,  -133,    86,  -133,    91,    77,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,   148,    88,  -133,    58,    94,
    -133,    85,  -133,    87,     3,  -133,  -133,   148,  -133,    87,
      45,   148,   148,   123,    92,   137,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,    93,
    -133,    56,  -133,    19,    -6,   129,  -133,  -133,   103,  -133,
    -133,    90,    90,   148,  -133,  -133,   118,  -133,  -133,   126,
      22,    90,    90,   148,  -133,  -133,  -133,  -133,    18,   148,
      84
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    18,    16,    17,     0,     0,     2,     4,     5,     0,
       6,    22,     1,     3,    14,     0,    11,    12,     0,     0,
      21,    24,     0,    22,     7,     0,     0,    28,    25,    27,
       0,     0,     0,     0,    14,    10,    98,   108,   109,   110,
     111,    93,    94,    95,     0,     0,    13,    69,    71,    73,
      75,    83,    87,     0,    92,    96,    97,   101,   102,     0,
       0,    44,    20,    23,    15,     0,     0,   105,    72,     0,
      62,    96,     0,     0,    84,    85,    76,    78,    80,    81,
      77,    79,     0,     0,    88,    89,    90,     0,    91,    29,
      26,    46,    19,     0,   107,     0,   104,   100,    63,    64,
      65,    66,    67,    60,    61,     0,    68,    70,    74,    82,
      86,     0,    43,     0,     0,    99,   103,     0,    59,     0,
       0,     0,     0,     0,     0,     0,    41,    42,    45,    30,
      31,    32,    33,    34,    38,    35,    39,    36,    37,     0,
     106,     0,     9,     0,     0,     0,    58,    56,     0,    40,
       8,     0,     0,     0,    57,    48,    30,    50,    52,     0,
       0,     0,     0,     0,    47,    49,    51,    53,    54,     0,
      55
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -133,  -133,  -133,   158,  -133,  -133,  -104,   146,  -133,     2,
    -133,   156,  -133,   149,  -133,   125,    35,  -132,  -111,  -133,
     -25,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
     -42,  -133,   -26,   116,   -38,  -133,  -133,   107,  -133,   109,
    -133,   -49,  -133,  -133,   -44,  -133,  -133,  -133,  -133,  -133
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,     8,   112,    15,    16,    17,    18,
      10,    19,    20,    21,    28,    29,   128,   129,   130,   131,
     132,    91,   114,   133,   134,   135,   136,   159,   137,   138,
     139,   105,    70,    47,    48,    49,    82,    50,    83,    51,
      87,    52,    53,    54,    55,    56,    57,    95,    96,    58
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      46,    71,     9,    69,    88,    62,    68,    11,     9,   120,
      36,    37,    38,    39,    40,   141,    22,    41,    42,   156,
     157,    23,    71,    71,    93,    94,    66,    43,   152,   164,
     166,    67,    72,    12,   121,   107,   122,    14,   110,    44,
      92,   158,   123,    24,    25,   124,   125,    61,    26,   126,
     165,   167,    30,    45,   151,   127,    72,    72,    98,   169,
      72,    71,   163,   118,    99,   100,   101,   102,   103,   104,
      71,    74,    75,    71,    27,   140,     1,     2,     3,    32,
       4,    71,    31,   148,     1,     2,     3,   111,     1,     2,
       3,   142,    25,   113,    34,   143,   144,    36,    37,    38,
      39,    40,   150,    25,    41,    42,    59,    71,    71,    84,
      85,    86,    60,   119,    43,    64,    61,    71,    71,    65,
      22,   121,    72,   122,   117,    73,    44,   160,    89,   123,
     145,    97,   124,   125,    61,   115,   126,   168,   146,   149,
      45,   153,   116,   170,    36,    37,    38,    39,    40,   154,
     161,    41,    42,    74,    75,    36,    37,    38,    39,    40,
     162,    43,    41,    42,    13,    76,    77,    78,    79,    80,
      81,    35,    43,    44,    36,    37,    38,    39,    40,    33,
      63,    41,    42,   147,    44,    90,   155,    45,   106,   108,
       0,    43,   109,     0,     0,     0,     0,     0,    45,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    45
};

static const yytype_int16 yycheck[] =
{
      26,    45,     0,    45,    53,    30,    44,    50,     6,   113,
       7,     8,     9,    10,    11,   119,    45,    14,    15,   151,
     152,    50,    66,    67,    66,    67,    45,    24,    34,   161,
     162,    50,    38,     0,    31,    73,    33,     7,    87,    36,
      65,   152,    39,    46,    47,    42,    43,    44,    48,    46,
     161,   162,    51,    50,    35,    52,    38,    38,    12,    41,
      38,   105,    40,   105,    18,    19,    20,    21,    22,    23,
     114,    13,    14,   117,     7,   117,     3,     4,     5,     8,
       7,   125,    46,   125,     3,     4,     5,     6,     3,     4,
       5,    46,    47,    91,     7,   121,   122,     7,     8,     9,
      10,    11,    46,    47,    14,    15,    45,   151,   152,    15,
      16,    17,    47,   111,    24,    49,    44,   161,   162,    51,
      45,    31,    38,    33,    47,    37,    36,   153,    49,    39,
       7,    51,    42,    43,    44,    49,    46,   163,    46,    46,
      50,    12,    51,   169,     7,     8,     9,    10,    11,    46,
      32,    14,    15,    13,    14,     7,     8,     9,    10,    11,
      34,    24,    14,    15,     6,    25,    26,    27,    28,    29,
      30,    25,    24,    36,     7,     8,     9,    10,    11,    23,
      31,    14,    15,    46,    36,    60,   151,    50,    72,    82,
      -1,    24,    83,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     7,    54,    55,    56,    57,    62,
      63,    50,     0,    56,     7,    59,    60,    61,    62,    64,
      65,    66,    45,    50,    46,    47,    48,     7,    67,    68,
      51,    46,     8,    64,     7,    60,     7,     8,     9,    10,
      11,    14,    15,    24,    36,    50,    85,    86,    87,    88,
      90,    92,    94,    95,    96,    97,    98,    99,   102,    45,
      47,    44,    73,    66,    49,    51,    45,    50,    87,    83,
      85,    97,    38,    37,    13,    14,    25,    26,    27,    28,
      29,    30,    89,    91,    15,    16,    17,    93,    94,    49,
      68,    74,    73,    83,    83,   100,   101,    51,    12,    18,
      19,    20,    21,    22,    23,    84,    86,    87,    90,    92,
      94,     6,    58,    62,    75,    49,    51,    47,    83,    62,
      59,    31,    33,    39,    42,    43,    46,    52,    69,    70,
      71,    72,    73,    76,    77,    78,    79,    81,    82,    83,
      83,    59,    46,    85,    85,     7,    46,    46,    83,    46,
      46,    35,    34,    12,    46,    69,    70,    70,    71,    80,
      85,    32,    34,    40,    70,    71,    70,    71,    85,    41,
      85
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    57,    58,    58,
      59,    59,    60,    60,    61,    61,    62,    62,    62,    63,
      63,    64,    64,    65,    65,    66,    67,    67,    68,    68,
      69,    69,    70,    70,    70,    70,    70,    70,    71,    71,
      72,    72,    73,    74,    74,    75,    75,    76,    77,    77,
      78,    78,    79,    79,    80,    80,    81,    81,    82,    83,
      83,    83,    83,    84,    84,    84,    84,    84,    85,    85,
      86,    86,    87,    87,    88,    88,    89,    89,    89,    89,
      89,    89,    90,    90,    91,    91,    92,    92,    93,    93,
      93,    94,    94,    95,    95,    95,    96,    96,    97,    97,
      98,    98,    98,    99,   100,   100,   101,   101,   102,   102,
     102,   102
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     4,     3,
       3,     1,     1,     3,     1,     4,     1,     1,     1,     6,
       5,     1,     0,     3,     1,     2,     3,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     4,     2,     0,     2,     0,     6,     4,     6,
       4,     6,     4,     6,     3,     5,     2,     3,     2,     3,
       2,     2,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     1,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     4,
       3,     1,     1,     4,     1,     0,     3,     1,     1,     1,
       1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: declList  */
#line 37 "parser.y"
             {
        AST = (yyvsp[0].nodePtr);
    }
#line 1321 "parser.tab.c"
    break;

  case 3: /* declList: declList decl  */
#line 41 "parser.y"
                  {
        if((yyvsp[-1].nodePtr) != NULL) {
            (yyval.nodePtr) = AddSibling((yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        } else {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
    }
#line 1333 "parser.tab.c"
    break;

  case 4: /* declList: decl  */
#line 48 "parser.y"
         {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1341 "parser.tab.c"
    break;

  case 5: /* decl: varDecl  */
#line 52 "parser.y"
            {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1349 "parser.tab.c"
    break;

  case 6: /* decl: funDecl  */
#line 55 "parser.y"
            {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1357 "parser.tab.c"
    break;

  case 7: /* varDecl: typeSpec varDeclList ';'  */
#line 59 "parser.y"
                             {
        Node * cur = (yyvsp[-1].nodePtr);
        while(cur != NULL) {
            SetDataType((yyvsp[-2].literal), cur);
            if(cur->sibling != NULL) {
                cur = cur->sibling;
            } else {
                cur = NULL;
            }
        }
        (yyval.nodePtr) = (yyvsp[-1].nodePtr);
    }
#line 1374 "parser.tab.c"
    break;

  case 8: /* scopedVarDecl: ytstatic typeSpec varDeclList ';'  */
#line 72 "parser.y"
                                      {
        (yyvsp[-1].nodePtr)->nodeType = ntStaticVar;
        Node * cur = (yyvsp[-1].nodePtr);
        while(cur != NULL) {
            SetDataType((yyvsp[-2].literal), cur);
            if(cur->sibling != NULL) {
                cur = cur->sibling;
            } else {
                cur = NULL;
            }
        }
        (yyval.nodePtr) = (yyvsp[-1].nodePtr);
    }
#line 1392 "parser.tab.c"
    break;

  case 9: /* scopedVarDecl: typeSpec varDeclList ';'  */
#line 85 "parser.y"
                             {
        Node * cur = (yyvsp[-1].nodePtr);
        while(cur != NULL) {
            SetDataType((yyvsp[-2].literal), cur);
            if(cur->sibling != NULL) {
                cur = cur->sibling;
            } else {
                cur = NULL;
            }
        }
        (yyval.nodePtr) = (yyvsp[-1].nodePtr);
    }
#line 1409 "parser.tab.c"
    break;

  case 10: /* varDeclList: varDeclList ',' varDeclInit  */
#line 98 "parser.y"
                                {
        if((yyvsp[-2].nodePtr) != NULL) {
            (yyval.nodePtr) = AddSibling((yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
        } else {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
    }
#line 1421 "parser.tab.c"
    break;

  case 11: /* varDeclList: varDeclInit  */
#line 105 "parser.y"
                {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1429 "parser.tab.c"
    break;

  case 12: /* varDeclInit: varDeclId  */
#line 109 "parser.y"
              {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1437 "parser.tab.c"
    break;

  case 13: /* varDeclInit: varDeclId ':' simpleExp  */
#line 112 "parser.y"
                            {
        if((yyvsp[-2].nodePtr) != NULL) {
            if((yyvsp[0].nodePtr) != NULL) {
                (yyval.nodePtr) = AddChild((yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
                (yyvsp[-2].nodePtr)->isInitialized = 1;
            }
        } else {
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
        }
    }
#line 1452 "parser.tab.c"
    break;

  case 14: /* varDeclId: ID  */
#line 123 "parser.y"
       {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntVar);
        (yyval.nodePtr)->isDecl = 1;
    }
#line 1461 "parser.tab.c"
    break;

  case 15: /* varDeclId: ID ytarr NUMCONST ']'  */
#line 127 "parser.y"
                          {
        (yyval.nodePtr) = NewNode((yyvsp[-3].token), ntVarArray); // doesn't clean ytarr
        (yyval.nodePtr)->isDecl = 1;
        (yyval.nodePtr)->isArray = 1;
    }
#line 1471 "parser.tab.c"
    break;

  case 16: /* typeSpec: ytbool  */
#line 133 "parser.y"
           {
        (yyval.literal) = "bool";
    }
#line 1479 "parser.tab.c"
    break;

  case 17: /* typeSpec: ytchar  */
#line 136 "parser.y"
           {
        (yyval.literal) = "char";
    }
#line 1487 "parser.tab.c"
    break;

  case 18: /* typeSpec: ytint  */
#line 139 "parser.y"
          {
        (yyval.literal) = "int";
    }
#line 1495 "parser.tab.c"
    break;

  case 19: /* funDecl: typeSpec ID '(' parms ')' compoundStmt  */
#line 143 "parser.y"
                                           {
        (yyval.nodePtr) = NewNode((yyvsp[-4].token), ntFunc);
        (yyval.nodePtr)->isDecl = 1;
        (yyval.nodePtr)->isInitialized = 1;
        SetDataType((yyvsp[-5].literal), (yyval.nodePtr));
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-2].nodePtr)); //might be empty
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[0].nodePtr));
        (yyvsp[0].nodePtr)->nodeType = ntCompoundwFunc;
    }
#line 1509 "parser.tab.c"
    break;

  case 20: /* funDecl: ID '(' parms ')' compoundStmt  */
#line 152 "parser.y"
                                  {
        (yyval.nodePtr) = NewNode((yyvsp[-4].token), ntFunc);
        (yyval.nodePtr)->isDecl = 1;
        (yyval.nodePtr)->isInitialized = 1;
        SetDataType(strdup("void"), (yyval.nodePtr));
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-2].nodePtr)); //might be empty
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[0].nodePtr));
        (yyvsp[0].nodePtr)->nodeType = ntCompoundwFunc;
    }
#line 1523 "parser.tab.c"
    break;

  case 21: /* parms: parmList  */
#line 162 "parser.y"
             {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1531 "parser.tab.c"
    break;

  case 22: /* parms: %empty  */
#line 165 "parser.y"
           {
        (yyval.nodePtr) = NULL;
    }
#line 1539 "parser.tab.c"
    break;

  case 23: /* parmList: parmList ';' parmTypeList  */
#line 169 "parser.y"
                              {
        (yyval.nodePtr) = (yyvsp[-2].nodePtr);
        if((yyvsp[0].nodePtr) != NULL) {
            (yyval.nodePtr) = AddSibling((yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
        }
    }
#line 1550 "parser.tab.c"
    break;

  case 24: /* parmList: parmTypeList  */
#line 175 "parser.y"
                 {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1558 "parser.tab.c"
    break;

  case 25: /* parmTypeList: typeSpec parmIdList  */
#line 179 "parser.y"
                        {
        Node * cur = (yyvsp[0].nodePtr);
        while(cur != NULL) {
            SetDataType((yyvsp[-1].literal), cur);
            cur->isInitialized = 1;
            if(cur->sibling != NULL) {
                cur = cur->sibling;
            } else {
                cur = NULL;
            }
        }
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1576 "parser.tab.c"
    break;

  case 26: /* parmIdList: parmIdList ',' parmId  */
#line 193 "parser.y"
                          {
        if((yyvsp[-2].nodePtr) != NULL) {
            (yyval.nodePtr) = AddSibling((yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
        } else {
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
        }
    }
#line 1588 "parser.tab.c"
    break;

  case 27: /* parmIdList: parmId  */
#line 200 "parser.y"
           {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1596 "parser.tab.c"
    break;

  case 28: /* parmId: ID  */
#line 204 "parser.y"
       {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntParm);
        (yyval.nodePtr)->isDecl = 1;
    }
#line 1605 "parser.tab.c"
    break;

  case 29: /* parmId: ID ytarr ']'  */
#line 208 "parser.y"
                 {
        (yyval.nodePtr) = NewNode((yyvsp[-2].token), ntParmArray); // doesn't clean ytarr
        (yyval.nodePtr)->isDecl = 1;
        (yyval.nodePtr)->isArray = 1;
    }
#line 1615 "parser.tab.c"
    break;

  case 30: /* stmt: matched  */
#line 214 "parser.y"
            {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1623 "parser.tab.c"
    break;

  case 31: /* stmt: unmatched  */
#line 217 "parser.y"
              {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1631 "parser.tab.c"
    break;

  case 32: /* matched: expStmt  */
#line 222 "parser.y"
            {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1639 "parser.tab.c"
    break;

  case 33: /* matched: compoundStmt  */
#line 225 "parser.y"
                 {
    }
#line 1646 "parser.tab.c"
    break;

  case 34: /* matched: matchedSelectStmt  */
#line 227 "parser.y"
                      {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1654 "parser.tab.c"
    break;

  case 35: /* matched: matchedIterStmt  */
#line 230 "parser.y"
                    {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1662 "parser.tab.c"
    break;

  case 36: /* matched: returnStmt  */
#line 233 "parser.y"
               {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1670 "parser.tab.c"
    break;

  case 37: /* matched: breakStmt  */
#line 236 "parser.y"
              {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1678 "parser.tab.c"
    break;

  case 38: /* unmatched: unmatchedSelectStmt  */
#line 240 "parser.y"
                        {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1686 "parser.tab.c"
    break;

  case 39: /* unmatched: unmatchedIterStmt  */
#line 243 "parser.y"
                      {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1694 "parser.tab.c"
    break;

  case 40: /* expStmt: exp ';'  */
#line 247 "parser.y"
            {
        (yyval.nodePtr) = (yyvsp[-1].nodePtr);
    }
#line 1702 "parser.tab.c"
    break;

  case 41: /* expStmt: ';'  */
#line 250 "parser.y"
        {
        (yyval.nodePtr) = NULL;
    }
#line 1710 "parser.tab.c"
    break;

  case 42: /* compoundStmt: ytcompound localDecls stmtList '}'  */
#line 254 "parser.y"
                                       {
        (yyval.nodePtr) = NewNode((yyvsp[-3].token), ntCompound);
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-2].nodePtr)); //might be empty
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-1].nodePtr));
    }
#line 1720 "parser.tab.c"
    break;

  case 43: /* localDecls: localDecls scopedVarDecl  */
#line 260 "parser.y"
                             {
        if((yyvsp[-1].nodePtr) != NULL) {
            (yyval.nodePtr) = AddSibling((yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        } else {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
    }
#line 1732 "parser.tab.c"
    break;

  case 44: /* localDecls: %empty  */
#line 267 "parser.y"
           {
        (yyval.nodePtr) = NULL;
    }
#line 1740 "parser.tab.c"
    break;

  case 45: /* stmtList: stmtList stmt  */
#line 271 "parser.y"
                  {
        if((yyvsp[-1].nodePtr) != NULL) {
            (yyval.nodePtr) = AddSibling((yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        } else {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
    }
#line 1752 "parser.tab.c"
    break;

  case 46: /* stmtList: %empty  */
#line 278 "parser.y"
           {
        (yyval.nodePtr) = NULL;
    }
#line 1760 "parser.tab.c"
    break;

  case 47: /* matchedSelectStmt: ytif simpleExp ytthen matched ytelse matched  */
#line 282 "parser.y"
                                                 {
        (yyval.nodePtr) = NewNode((yyvsp[-5].token), ntIf);
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-4].nodePtr));
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-2].nodePtr));
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[0].nodePtr));
    }
#line 1771 "parser.tab.c"
    break;

  case 48: /* unmatchedSelectStmt: ytif simpleExp ytthen stmt  */
#line 289 "parser.y"
                               {
        (yyval.nodePtr) = NewNode((yyvsp[-3].token), ntIf);
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-2].nodePtr));
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[0].nodePtr));
    }
#line 1781 "parser.tab.c"
    break;

  case 49: /* unmatchedSelectStmt: ytif simpleExp ytthen matched ytelse unmatched  */
#line 294 "parser.y"
                                                   {
        (yyval.nodePtr) = NewNode((yyvsp[-5].token), ntIf);
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-4].nodePtr));
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-2].nodePtr));
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[0].nodePtr));
    }
#line 1792 "parser.tab.c"
    break;

  case 50: /* matchedIterStmt: ytwhile simpleExp ytdo matched  */
#line 301 "parser.y"
                                   {
        (yyval.nodePtr) = NewNode((yyvsp[-3].token), ntIter);
        (yyval.nodePtr)->isLoop = 1;
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-2].nodePtr));
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[0].nodePtr));
    }
#line 1803 "parser.tab.c"
    break;

  case 51: /* matchedIterStmt: ytfor ID ytequals iterRange ytdo matched  */
#line 307 "parser.y"
                                             {
        (yyval.nodePtr) = NewNode((yyvsp[-5].token), ntTo);
        (yyval.nodePtr)->isLoop = 1;
        Node * id;
        id = NewNode((yyvsp[-4].token), ntVar);
        id->isDecl = 1;
        id->isInitialized = 1;
        SetDataType(strdup("int"), id); //is this fine? assumes always int
        (yyval.nodePtr) = AddChild((yyval.nodePtr), id);
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-2].nodePtr));
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[0].nodePtr));
    }
#line 1820 "parser.tab.c"
    break;

  case 52: /* unmatchedIterStmt: ytwhile simpleExp ytdo unmatched  */
#line 320 "parser.y"
                                     {
        (yyval.nodePtr) = NewNode((yyvsp[-3].token), ntIter);
        (yyval.nodePtr)->isLoop = 1;
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-2].nodePtr));
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[0].nodePtr));
    }
#line 1831 "parser.tab.c"
    break;

  case 53: /* unmatchedIterStmt: ytfor ID ytequals iterRange ytdo unmatched  */
#line 326 "parser.y"
                                               {
        (yyval.nodePtr) = NewNode((yyvsp[-5].token), ntTo);
        (yyval.nodePtr)->isLoop = 1;
        Node * id;
        id = NewNode((yyvsp[-4].token), ntVar);
        id->isDecl = 1;
        id->isInitialized = 1;
        SetDataType(strdup("int"), id); //is this fine? assumes always int
        (yyval.nodePtr) = AddChild((yyval.nodePtr), id);
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-2].nodePtr));
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[0].nodePtr));
    }
#line 1848 "parser.tab.c"
    break;

  case 54: /* iterRange: simpleExp ytto simpleExp  */
#line 339 "parser.y"
                             {
        (yyval.nodePtr) = NewNode((yyvsp[-1].token), ntRange);
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-2].nodePtr));
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[0].nodePtr));
    }
#line 1858 "parser.tab.c"
    break;

  case 55: /* iterRange: simpleExp ytto simpleExp ytby simpleExp  */
#line 344 "parser.y"
                                            {
        (yyval.nodePtr) = NewNode((yyvsp[-3].token), ntRange);
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-4].nodePtr));
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-2].nodePtr));
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[0].nodePtr));
    }
#line 1869 "parser.tab.c"
    break;

  case 56: /* returnStmt: ytreturn ';'  */
#line 351 "parser.y"
                 {
        (yyval.nodePtr) = NewNode((yyvsp[-1].token), ntReturn);
    }
#line 1877 "parser.tab.c"
    break;

  case 57: /* returnStmt: ytreturn exp ';'  */
#line 354 "parser.y"
                     {
        (yyval.nodePtr) = NewNode((yyvsp[-2].token), ntReturn);
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-1].nodePtr));
    }
#line 1886 "parser.tab.c"
    break;

  case 58: /* breakStmt: ytbreak ';'  */
#line 359 "parser.y"
                {
        (yyval.nodePtr) = NewNode((yyvsp[-1].token), ntBreak);
    }
#line 1894 "parser.tab.c"
    break;

  case 59: /* exp: mutable assignop exp  */
#line 363 "parser.y"
                         {
        (yyvsp[-1].nodePtr) = AddChild((yyvsp[-1].nodePtr), (yyvsp[-2].nodePtr));
        (yyvsp[-1].nodePtr) = AddChild((yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        (yyval.nodePtr) = (yyvsp[-1].nodePtr);
    }
#line 1904 "parser.tab.c"
    break;

  case 60: /* exp: mutable ytinc  */
#line 368 "parser.y"
                  {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntAssign);
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-1].nodePtr));
    }
#line 1913 "parser.tab.c"
    break;

  case 61: /* exp: mutable ytdec  */
#line 372 "parser.y"
                  {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntAssign);
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-1].nodePtr));
    }
#line 1922 "parser.tab.c"
    break;

  case 62: /* exp: simpleExp  */
#line 376 "parser.y"
              {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1930 "parser.tab.c"
    break;

  case 63: /* assignop: ytequals  */
#line 380 "parser.y"
             {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntTrueAssign);
    }
#line 1938 "parser.tab.c"
    break;

  case 64: /* assignop: ytassadd  */
#line 383 "parser.y"
             {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntTrueAssign);
    }
#line 1946 "parser.tab.c"
    break;

  case 65: /* assignop: ytasssub  */
#line 386 "parser.y"
             {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntTrueAssign);
    }
#line 1954 "parser.tab.c"
    break;

  case 66: /* assignop: ytassmul  */
#line 389 "parser.y"
             {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntTrueAssign);
    }
#line 1962 "parser.tab.c"
    break;

  case 67: /* assignop: ytassdiv  */
#line 392 "parser.y"
             {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntTrueAssign);
    }
#line 1970 "parser.tab.c"
    break;

  case 68: /* simpleExp: simpleExp ytor andExp  */
#line 396 "parser.y"
                          {
        (yyval.nodePtr) = NewNode((yyvsp[-1].token), ntOrOp);
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-2].nodePtr));
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[0].nodePtr));
    }
#line 1980 "parser.tab.c"
    break;

  case 69: /* simpleExp: andExp  */
#line 401 "parser.y"
           {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 1988 "parser.tab.c"
    break;

  case 70: /* andExp: andExp ytand unaryRelExp  */
#line 405 "parser.y"
                             {
        (yyval.nodePtr) = NewNode((yyvsp[-1].token), ntAndOp);
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-2].nodePtr));
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[0].nodePtr));
    }
#line 1998 "parser.tab.c"
    break;

  case 71: /* andExp: unaryRelExp  */
#line 410 "parser.y"
                {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 2006 "parser.tab.c"
    break;

  case 72: /* unaryRelExp: ytnot unaryRelExp  */
#line 414 "parser.y"
                      {
        (yyval.nodePtr) = NewNode((yyvsp[-1].token), ntNotOp);
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[0].nodePtr));
    }
#line 2015 "parser.tab.c"
    break;

  case 73: /* unaryRelExp: relExp  */
#line 418 "parser.y"
           {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 2023 "parser.tab.c"
    break;

  case 74: /* relExp: sumExp relop sumExp  */
#line 422 "parser.y"
                        {
        (yyvsp[-1].nodePtr) = AddChild((yyvsp[-1].nodePtr), (yyvsp[-2].nodePtr));
        (yyvsp[-1].nodePtr) = AddChild((yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        (yyval.nodePtr) = (yyvsp[-1].nodePtr);
    }
#line 2033 "parser.tab.c"
    break;

  case 75: /* relExp: sumExp  */
#line 427 "parser.y"
           {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 2041 "parser.tab.c"
    break;

  case 76: /* relop: ytlesser  */
#line 431 "parser.y"
             {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntRelOp);
    }
#line 2049 "parser.tab.c"
    break;

  case 77: /* relop: yteqlesser  */
#line 434 "parser.y"
               {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntRelOp);
    }
#line 2057 "parser.tab.c"
    break;

  case 78: /* relop: ytgreater  */
#line 437 "parser.y"
              {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntRelOp);
    }
#line 2065 "parser.tab.c"
    break;

  case 79: /* relop: yteqgreater  */
#line 440 "parser.y"
                {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntRelOp);
    }
#line 2073 "parser.tab.c"
    break;

  case 80: /* relop: yteq  */
#line 443 "parser.y"
         {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntRelOp);
    }
#line 2081 "parser.tab.c"
    break;

  case 81: /* relop: ytnoteq  */
#line 446 "parser.y"
            {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntRelOp);
    }
#line 2089 "parser.tab.c"
    break;

  case 82: /* sumExp: sumExp sumop mulExp  */
#line 450 "parser.y"
                        {
        (yyvsp[-1].nodePtr) = AddChild((yyvsp[-1].nodePtr), (yyvsp[-2].nodePtr));
        (yyvsp[-1].nodePtr) = AddChild((yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        (yyval.nodePtr) = (yyvsp[-1].nodePtr);
    }
#line 2099 "parser.tab.c"
    break;

  case 83: /* sumExp: mulExp  */
#line 455 "parser.y"
           {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 2107 "parser.tab.c"
    break;

  case 84: /* sumop: ytadd  */
#line 459 "parser.y"
          {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntOp);
    }
#line 2115 "parser.tab.c"
    break;

  case 85: /* sumop: ytsub  */
#line 462 "parser.y"
          {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntOp);
    }
#line 2123 "parser.tab.c"
    break;

  case 86: /* mulExp: mulExp mulop unaryExp  */
#line 466 "parser.y"
                          {
        (yyvsp[-1].nodePtr) = AddChild((yyvsp[-1].nodePtr), (yyvsp[-2].nodePtr));
        (yyvsp[-1].nodePtr) = AddChild((yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        (yyval.nodePtr) = (yyvsp[-1].nodePtr);
    }
#line 2133 "parser.tab.c"
    break;

  case 87: /* mulExp: unaryExp  */
#line 471 "parser.y"
             {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 2141 "parser.tab.c"
    break;

  case 88: /* mulop: ytmul  */
#line 475 "parser.y"
          {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntOp);
    }
#line 2149 "parser.tab.c"
    break;

  case 89: /* mulop: ytdiv  */
#line 478 "parser.y"
          {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntOp);
    }
#line 2157 "parser.tab.c"
    break;

  case 90: /* mulop: ytmod  */
#line 481 "parser.y"
          {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntOp);
    }
#line 2165 "parser.tab.c"
    break;

  case 91: /* unaryExp: unaryop unaryExp  */
#line 485 "parser.y"
                     {
        (yyval.nodePtr) = AddChild((yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
    }
#line 2173 "parser.tab.c"
    break;

  case 92: /* unaryExp: factor  */
#line 488 "parser.y"
           {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 2181 "parser.tab.c"
    break;

  case 93: /* unaryop: ytsub  */
#line 492 "parser.y"
          {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntSignOp);
    }
#line 2189 "parser.tab.c"
    break;

  case 94: /* unaryop: ytmul  */
#line 495 "parser.y"
          {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntSizeofOp);
    }
#line 2197 "parser.tab.c"
    break;

  case 95: /* unaryop: ytquestion  */
#line 498 "parser.y"
               {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntQuestOp);
    }
#line 2205 "parser.tab.c"
    break;

  case 96: /* factor: mutable  */
#line 502 "parser.y"
            {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 2213 "parser.tab.c"
    break;

  case 97: /* factor: immutable  */
#line 505 "parser.y"
              {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 2221 "parser.tab.c"
    break;

  case 98: /* mutable: ID  */
#line 509 "parser.y"
       {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntID);
    }
#line 2229 "parser.tab.c"
    break;

  case 99: /* mutable: ID ytarr exp ']'  */
#line 512 "parser.y"
                     {
        (yyval.nodePtr) = NewNode((yyvsp[-2].token), ntArrAd);
        Node * firstChild;
        firstChild = NewNode((yyvsp[-3].token), ntID);
        (yyval.nodePtr) = AddChild((yyval.nodePtr), firstChild);
        (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-1].nodePtr));
    }
#line 2241 "parser.tab.c"
    break;

  case 100: /* immutable: '(' exp ')'  */
#line 520 "parser.y"
                {
        (yyval.nodePtr) = (yyvsp[-1].nodePtr);
    }
#line 2249 "parser.tab.c"
    break;

  case 101: /* immutable: call  */
#line 523 "parser.y"
         {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 2257 "parser.tab.c"
    break;

  case 102: /* immutable: constant  */
#line 526 "parser.y"
             {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 2265 "parser.tab.c"
    break;

  case 103: /* call: ID '(' args ')'  */
#line 530 "parser.y"
                    {
        (yyval.nodePtr) = NewNode((yyvsp[-3].token), ntCall);
        if((yyvsp[-1].nodePtr) != NULL) {
            (yyval.nodePtr) = AddChild((yyval.nodePtr), (yyvsp[-1].nodePtr));
        }
    }
#line 2276 "parser.tab.c"
    break;

  case 104: /* args: argList  */
#line 537 "parser.y"
            {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 2284 "parser.tab.c"
    break;

  case 105: /* args: %empty  */
#line 540 "parser.y"
           {
        (yyval.nodePtr) = NULL;
    }
#line 2292 "parser.tab.c"
    break;

  case 106: /* argList: argList ',' exp  */
#line 544 "parser.y"
                    {
        if((yyvsp[-2].nodePtr) != NULL) {
            (yyval.nodePtr) = AddSibling((yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
        } else {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
    }
#line 2304 "parser.tab.c"
    break;

  case 107: /* argList: exp  */
#line 551 "parser.y"
        {
        (yyval.nodePtr) = (yyvsp[0].nodePtr);
    }
#line 2312 "parser.tab.c"
    break;

  case 108: /* constant: NUMCONST  */
#line 555 "parser.y"
             {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntNumConst);
        (yyval.nodePtr)->isInitialized = 1;
        (yyval.nodePtr)->isConst = 1;
    }
#line 2322 "parser.tab.c"
    break;

  case 109: /* constant: CHARCONST  */
#line 560 "parser.y"
              {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntCharConst);
        (yyval.nodePtr)->isInitialized = 1;
        (yyval.nodePtr)->isConst = 1;
    }
#line 2332 "parser.tab.c"
    break;

  case 110: /* constant: STRINGCONST  */
#line 565 "parser.y"
                {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntStringConst);
        (yyval.nodePtr)->isInitialized = 1;
        (yyval.nodePtr)->isConst = 1;
    }
#line 2342 "parser.tab.c"
    break;

  case 111: /* constant: BOOLCONST  */
#line 570 "parser.y"
              {
        (yyval.nodePtr) = NewNode((yyvsp[0].token), ntBoolConst);
        (yyval.nodePtr)->isInitialized = 1;
        (yyval.nodePtr)->isConst = 1;
    }
#line 2352 "parser.tab.c"
    break;


#line 2356 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 576 "parser.y"
