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
#line 1 "src/tpc.y"

/* tpc.y */
#include <stdio.h>
#include <unistd.h>
#include "tree.h"
#include "tpc.h"
#include "symbol_table.h"
#include <string.h>
#include <getopt.h>
void translate(Node* tree, FILE* f);
extern FILE *yyin;

int yylex();
void yyerror(char *);
int lineno = 1;
extern int current_column;
Node *root = NULL;
Symbol *tableGlobale[TAILLE_TABLE];
LocalTableNode* localTables = NULL;

static struct option option_complete[] = {
    {"tree",  no_argument, 0, 't'},
    {"help",  no_argument, 0, 'h'},
    {"symtabs",  no_argument, 0, 's'},
    {0, 0, 0, 0}
};

#line 99 "obj/tpc.c"

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

#include "tpc.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CHARACTER = 3,                  /* CHARACTER  */
  YYSYMBOL_ADDSUB = 4,                     /* ADDSUB  */
  YYSYMBOL_DIVSTAR = 5,                    /* DIVSTAR  */
  YYSYMBOL_NUM = 6,                        /* NUM  */
  YYSYMBOL_IDENT = 7,                      /* IDENT  */
  YYSYMBOL_ORDER = 8,                      /* ORDER  */
  YYSYMBOL_EQ = 9,                         /* EQ  */
  YYSYMBOL_OR = 10,                        /* OR  */
  YYSYMBOL_AND = 11,                       /* AND  */
  YYSYMBOL_TYPE = 12,                      /* TYPE  */
  YYSYMBOL_STRUCT = 13,                    /* STRUCT  */
  YYSYMBOL_VOID = 14,                      /* VOID  */
  YYSYMBOL_IF = 15,                        /* IF  */
  YYSYMBOL_ELSE = 16,                      /* ELSE  */
  YYSYMBOL_WHILE = 17,                     /* WHILE  */
  YYSYMBOL_RETURN = 18,                    /* RETURN  */
  YYSYMBOL_19_ = 19,                       /* ';'  */
  YYSYMBOL_20_ = 20,                       /* '{'  */
  YYSYMBOL_21_ = 21,                       /* '}'  */
  YYSYMBOL_22_ = 22,                       /* ','  */
  YYSYMBOL_23_ = 23,                       /* '('  */
  YYSYMBOL_24_ = 24,                       /* ')'  */
  YYSYMBOL_25_ = 25,                       /* '='  */
  YYSYMBOL_26_ = 26,                       /* '!'  */
  YYSYMBOL_27_ = 27,                       /* '.'  */
  YYSYMBOL_YYACCEPT = 28,                  /* $accept  */
  YYSYMBOL_Prog = 29,                      /* Prog  */
  YYSYMBOL_DeclVars = 30,                  /* DeclVars  */
  YYSYMBOL_DeclStruct = 31,                /* DeclStruct  */
  YYSYMBOL_ContenuStruct = 32,             /* ContenuStruct  */
  YYSYMBOL_Declarateurs = 33,              /* Declarateurs  */
  YYSYMBOL_DeclFoncts = 34,                /* DeclFoncts  */
  YYSYMBOL_DeclFonct = 35,                 /* DeclFonct  */
  YYSYMBOL_EnTeteFonct = 36,               /* EnTeteFonct  */
  YYSYMBOL_Parametres = 37,                /* Parametres  */
  YYSYMBOL_ListTypVar = 38,                /* ListTypVar  */
  YYSYMBOL_Corps = 39,                     /* Corps  */
  YYSYMBOL_SuiteInstr = 40,                /* SuiteInstr  */
  YYSYMBOL_Instr = 41,                     /* Instr  */
  YYSYMBOL_Exp = 42,                       /* Exp  */
  YYSYMBOL_TB = 43,                        /* TB  */
  YYSYMBOL_FB = 44,                        /* FB  */
  YYSYMBOL_M = 45,                         /* M  */
  YYSYMBOL_E = 46,                         /* E  */
  YYSYMBOL_T = 47,                         /* T  */
  YYSYMBOL_F = 48,                         /* F  */
  YYSYMBOL_FieldPathDot = 49,              /* FieldPathDot  */
  YYSYMBOL_Arguments = 50,                 /* Arguments  */
  YYSYMBOL_ListExp = 51                    /* ListExp  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   158

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  144

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   273


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
       2,     2,     2,    26,     2,     2,     2,     2,     2,     2,
      23,    24,     2,     2,    22,     2,    27,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    19,
       2,    25,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    20,     2,    21,     2,     2,     2,     2,
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
      15,    16,    17,    18
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    56,    56,    67,    81,    97,   109,   114,   127,   140,
     148,   166,   180,   185,   192,   202,   209,   217,   229,   244,
     258,   262,   268,   276,   285,   296,   309,   318,   324,   329,
     336,   345,   359,   369,   377,   383,   389,   393,   398,   405,
     410,   417,   422,   429,   431,   438,   443,   456,   461,   471,
     476,   487,   493,   497,   503,   512,   521,   527,   532,   542,
     547,   552,   558
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
  "\"end of file\"", "error", "\"invalid token\"", "CHARACTER", "ADDSUB",
  "DIVSTAR", "NUM", "IDENT", "ORDER", "EQ", "OR", "AND", "TYPE", "STRUCT",
  "VOID", "IF", "ELSE", "WHILE", "RETURN", "';'", "'{'", "'}'", "','",
  "'('", "')'", "'='", "'!'", "'.'", "$accept", "Prog", "DeclVars",
  "DeclStruct", "ContenuStruct", "Declarateurs", "DeclFoncts", "DeclFonct",
  "EnTeteFonct", "Parametres", "ListTypVar", "Corps", "SuiteInstr",
  "Instr", "Exp", "TB", "FB", "M", "E", "T", "F", "FieldPathDot",
  "Arguments", "ListExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-112)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -112,     4,    86,  -112,     5,    19,    33,  -112,    89,  -112,
      -1,    87,    38,    22,    88,   102,   105,  -112,  -112,  -112,
      92,  -112,   106,    91,    61,    40,    92,    87,   108,    82,
     109,   110,  -112,    94,    97,  -112,    92,   113,   114,    71,
    -112,    98,    91,   113,   116,    34,  -112,   117,  -112,    95,
     101,  -112,    67,   113,   113,   119,   111,  -112,    25,   104,
     112,   115,     2,  -112,  -112,  -112,  -112,    36,  -112,   121,
     122,  -112,  -112,    68,    69,   113,  -112,     7,     7,     7,
    -112,     7,  -112,   118,  -112,     7,     7,    28,   120,   123,
     125,   130,   131,  -112,   124,    51,     7,   132,  -112,   133,
    -112,  -112,    74,   127,   126,   134,    10,    12,  -112,     7,
      13,  -112,     7,  -112,     7,     7,     7,     7,     7,  -112,
      66,  -112,  -112,  -112,   128,     7,    60,    60,   129,  -112,
     120,   123,   125,   130,   131,  -112,  -112,  -112,   127,   136,
    -112,  -112,    60,  -112
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       6,     0,     0,     1,     0,     0,     0,     5,     2,    15,
       0,    13,     0,     0,     0,     0,     0,    14,     6,    16,
       0,     3,     0,    13,     0,     0,     0,     0,     0,    28,
       0,     0,    20,     0,    21,    12,     0,     0,     0,     0,
       4,     0,     0,     0,     0,     0,    23,     0,    17,     0,
       0,    13,     0,     0,     0,     0,     0,    19,     0,    57,
       0,     0,     0,    37,    28,    26,    27,     0,    25,     0,
       0,    18,     9,     0,     0,     0,     7,    60,     0,     0,
      54,     0,    53,    57,    35,     0,     0,     0,    39,    41,
      43,    45,    47,    49,    56,     0,     0,     0,    22,     0,
      11,     8,     0,    62,     0,    59,     0,     0,    50,    60,
       0,    51,     0,    34,     0,     0,     0,     0,     0,    36,
       0,    58,    24,    10,     0,     0,     0,     0,     0,    52,
      38,    40,    42,    44,    46,    48,    29,    33,    61,    30,
      32,    55,     0,    31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -112,  -112,   137,  -112,  -112,   -10,  -112,   135,  -112,    20,
    -112,  -112,    78,  -111,   -61,    32,    31,    39,    30,    41,
     -79,   -45,    48,  -112
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     7,    39,    12,     8,     9,    10,    33,
      34,    19,    45,    66,   103,    88,    89,    90,    91,    92,
      93,    94,   104,   105
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      67,    87,   108,    25,     3,    80,    81,   111,    82,    83,
      80,    81,    11,    82,    83,   139,   140,   106,   107,    18,
     112,    84,   112,   112,   110,    85,    13,    52,    86,    23,
      85,   143,    51,    86,   126,   120,   127,   129,   112,   135,
      14,    59,    24,    73,    74,    24,    41,   113,    25,    60,
      67,    61,    62,    63,    64,    65,    50,    21,    59,    40,
      22,    96,    22,    97,   138,   102,    60,    59,    61,    62,
      63,    64,   119,    37,    38,    60,   112,    61,    62,    63,
      64,    67,    67,    54,    55,   136,    72,   100,   101,    22,
      22,    22,    56,   123,    43,    44,    22,    67,     4,     5,
       6,    15,    16,     6,    30,    31,    32,    69,    70,    27,
      20,    26,    28,    35,    36,    42,    46,    47,    48,    49,
      51,    53,    57,    58,    68,    71,    75,    77,    98,    99,
      76,   114,   115,   116,   117,    78,   118,   112,    79,   121,
     122,   109,    95,    17,   130,   131,   133,   137,     0,     0,
     124,    97,   142,   141,   132,    29,   125,   128,   134
};

static const yytype_int16 yycheck[] =
{
      45,    62,    81,    13,     0,     3,     4,    86,     6,     7,
       3,     4,     7,     6,     7,   126,   127,    78,    79,    20,
      10,    19,    10,    10,    85,    23,     7,    37,    26,     7,
      23,   142,     7,    26,    24,    96,    24,    24,    10,   118,
       7,     7,    20,    53,    54,    20,    26,    19,    58,    15,
      95,    17,    18,    19,    20,    21,    36,    19,     7,    19,
      22,    25,    22,    27,   125,    75,    15,     7,    17,    18,
      19,    20,    21,    12,    13,    15,    10,    17,    18,    19,
      20,   126,   127,    12,    13,    19,    19,    19,    19,    22,
      22,    22,    21,    19,    12,    13,    22,   142,    12,    13,
      14,    12,    13,    14,    12,    13,    14,    12,    13,     7,
      23,    23,     7,     7,    23,     7,     7,     7,    24,    22,
       7,     7,    24,     7,     7,    24,     7,    23,     7,     7,
      19,    11,     9,     8,     4,    23,     5,    10,    23,     7,
       7,    23,    64,     8,   112,   114,   116,    19,    -1,    -1,
      24,    27,    16,    24,   115,    18,    22,   109,   117
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    29,    30,     0,    12,    13,    14,    31,    34,    35,
      36,     7,    33,     7,     7,    12,    13,    35,    20,    39,
      23,    19,    22,     7,    20,    33,    23,     7,     7,    30,
      12,    13,    14,    37,    38,     7,    23,    12,    13,    32,
      19,    37,     7,    12,    13,    40,     7,     7,    24,    22,
      37,     7,    33,     7,    12,    13,    21,    24,     7,     7,
      15,    17,    18,    19,    20,    21,    41,    49,     7,    12,
      13,    24,    19,    33,    33,     7,    19,    23,    23,    23,
       3,     4,     6,     7,    19,    23,    26,    42,    43,    44,
      45,    46,    47,    48,    49,    40,    25,    27,     7,     7,
      19,    19,    33,    42,    50,    51,    42,    42,    48,    23,
      42,    48,    10,    19,    11,     9,     8,     4,     5,    21,
      42,     7,     7,    19,    24,    22,    24,    24,    50,    24,
      43,    44,    45,    46,    47,    48,    19,    19,    42,    41,
      41,    24,    16,    41
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    28,    29,    30,    30,    30,    30,    31,    32,    32,
      32,    32,    33,    33,    34,    34,    35,    36,    36,    36,
      37,    37,    38,    38,    38,    38,    39,    40,    40,    41,
      41,    41,    41,    41,    41,    41,    41,    41,    42,    42,
      43,    43,    44,    44,    45,    45,    46,    46,    47,    47,
      48,    48,    48,    48,    48,    48,    48,    49,    49,    50,
      50,    51,    51
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     4,     5,     2,     0,     6,     4,     3,
       5,     4,     3,     1,     2,     1,     2,     5,     6,     5,
       1,     1,     4,     2,     5,     3,     4,     2,     0,     4,
       5,     7,     5,     5,     3,     2,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       2,     2,     3,     1,     1,     4,     1,     1,     3,     1,
       0,     3,     1
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
  case 2: /* Prog: DeclVars DeclFoncts  */
#line 57 "src/tpc.y"
    {
        (yyval.node) = makeNode(program);
        addChild((yyval.node),(yyvsp[-1].node));
        addChild((yyval.node),(yyvsp[0].node));
        root = (yyval.node);
    }
#line 1230 "obj/tpc.c"
    break;

  case 3: /* DeclVars: DeclVars TYPE Declarateurs ';'  */
#line 68 "src/tpc.y"
      {
        if ((yyvsp[-3].node) == NULL){
            (yyval.node) = makeNode(declarations);
        }else {
            (yyval.node) = (yyvsp[-3].node);
        }
        Node * d = makeNode(declaration);
        Node *t = makeNodeString(type, (yyvsp[-2].ident));
        addChild(t,(yyvsp[-1].node));
        addChild(d,t);
        addChild((yyval.node),d);

      }
#line 1248 "obj/tpc.c"
    break;

  case 4: /* DeclVars: DeclVars STRUCT IDENT Declarateurs ';'  */
#line 82 "src/tpc.y"
    {
       if ((yyvsp[-4].node) == NULL){
            (yyval.node) = makeNode(declarations);
        }else {
            (yyval.node) = (yyvsp[-4].node);
        }
        Node *d = makeNode(declaration);
        Node *s = makeNode(structure);
        Node * i = makeNodeString(id,(yyvsp[-2].ident));
        
        addChild(s,i);
        addChild(s,(yyvsp[-1].node));
        addChild(d,s);
        addChild((yyval.node),d);
    }
#line 1268 "obj/tpc.c"
    break;

  case 5: /* DeclVars: DeclVars DeclStruct  */
#line 99 "src/tpc.y"
    {
        if ((yyvsp[-1].node) == NULL){
            (yyval.node) = makeNode(declarations);
        }else {
            (yyval.node) = (yyvsp[-1].node);
        }
        addChild((yyval.node),(yyvsp[0].node));

    }
#line 1282 "obj/tpc.c"
    break;

  case 6: /* DeclVars: %empty  */
#line 109 "src/tpc.y"
    {
        (yyval.node) = NULL;
    }
#line 1290 "obj/tpc.c"
    break;

  case 7: /* DeclStruct: STRUCT IDENT '{' ContenuStruct '}' ';'  */
#line 115 "src/tpc.y"
       {
        Node *d = makeNode(declaration);
        Node *s = makeNode(structure);
        Node *i = makeNodeString(id,(yyvsp[-4].ident));
        
        addChild(s,i);
        addChild(s,(yyvsp[-2].node));
        addChild(d,s);
        (yyval.node) = d;
       }
#line 1305 "obj/tpc.c"
    break;

  case 8: /* ContenuStruct: ContenuStruct TYPE Declarateurs ';'  */
#line 128 "src/tpc.y"
        {
            Node *c;
            if ((yyvsp[-3].node) == NULL){
                c = makeNode(contenustruct);
            }else {
                c = (yyvsp[-3].node) ;
            }
            Node *t = makeNodeString(type, (yyvsp[-2].ident));
            addChild(t,(yyvsp[-1].node));
            addChild(c,t);
            (yyval.node) = c;
        }
#line 1322 "obj/tpc.c"
    break;

  case 9: /* ContenuStruct: TYPE Declarateurs ';'  */
#line 141 "src/tpc.y"
    {
        Node *c = makeNode(contenustruct);
        Node *t = makeNodeString(type, (yyvsp[-2].ident));
        addChild(t,(yyvsp[-1].node));
        addChild(c,t);
        (yyval.node) = c;
    }
#line 1334 "obj/tpc.c"
    break;

  case 10: /* ContenuStruct: ContenuStruct STRUCT IDENT Declarateurs ';'  */
#line 149 "src/tpc.y"
    {
        Node *c;
        if ((yyvsp[-4].node) == NULL){
            c = makeNode(contenustruct);
        } else {
            c = (yyvsp[-4].node);
        }

        Node *s = makeNode(structure);
        Node *i = makeNodeString(id, (yyvsp[-2].ident));

        addChild(s, i);
        addChild(s, (yyvsp[-1].node));
        addChild(c, s);

        (yyval.node) = c;
    }
#line 1356 "obj/tpc.c"
    break;

  case 11: /* ContenuStruct: STRUCT IDENT Declarateurs ';'  */
#line 167 "src/tpc.y"
    {
        Node *c = makeNode(contenustruct);
        Node *s = makeNode(structure);
        Node *i = makeNodeString(id, (yyvsp[-2].ident));

        addChild(s, i);
        addChild(s, (yyvsp[-1].node));
        addChild(c, s);

        (yyval.node) = c;
    }
#line 1372 "obj/tpc.c"
    break;

  case 12: /* Declarateurs: Declarateurs ',' IDENT  */
#line 181 "src/tpc.y"
       {
        (yyval.node) = (yyvsp[-2].node);
        addSibling((yyval.node),makeNodeString(id,(yyvsp[0].ident)));
       }
#line 1381 "obj/tpc.c"
    break;

  case 13: /* Declarateurs: IDENT  */
#line 186 "src/tpc.y"
    {

        (yyval.node) = makeNodeString(id,(yyvsp[0].ident));
    }
#line 1390 "obj/tpc.c"
    break;

  case 14: /* DeclFoncts: DeclFoncts DeclFonct  */
#line 193 "src/tpc.y"
       {
        if ((yyvsp[-1].node)==NULL){
            (yyval.node) = makeNode(functions);
        }else {
            (yyval.node) = (yyvsp[-1].node);
        }
        addChild((yyval.node),(yyvsp[0].node));

       }
#line 1404 "obj/tpc.c"
    break;

  case 15: /* DeclFoncts: DeclFonct  */
#line 203 "src/tpc.y"
    {
        (yyval.node) = makeNode(functions);
        addChild((yyval.node),(yyvsp[0].node));
    }
#line 1413 "obj/tpc.c"
    break;

  case 16: /* DeclFonct: EnTeteFonct Corps  */
#line 210 "src/tpc.y"
       {
        (yyval.node) = makeNode(function);
        addChild((yyval.node),(yyvsp[-1].node));
        addChild((yyval.node),(yyvsp[0].node));
       }
#line 1423 "obj/tpc.c"
    break;

  case 17: /* EnTeteFonct: TYPE IDENT '(' Parametres ')'  */
#line 218 "src/tpc.y"
       {
        Node * h = makeNode(heading);
        Node * t = makeNodeString(type,(yyvsp[-4].ident));
        Node * i = makeNodeString(id,(yyvsp[-3].ident));
        
        addChild(h,i);
        addChild(h,t);
        addChild(h,(yyvsp[-1].node));
        (yyval.node) = h;

       }
#line 1439 "obj/tpc.c"
    break;

  case 18: /* EnTeteFonct: STRUCT IDENT IDENT '(' Parametres ')'  */
#line 230 "src/tpc.y"
    {
        Node * h = makeNode(heading);
        Node * s = makeNode(structure);
        Node * t = makeNode(type);
        Node * id_structure = makeNodeString(id,(yyvsp[-4].ident));
        Node * id_function = makeNodeString(id,(yyvsp[-3].ident));
        addChild(s,id_structure);
        addChild(t,s);
        addChild(h,t);
        addChild(h,id_function);
        addChild(h,(yyvsp[-1].node));
        (yyval.node) = h ;

    }
#line 1458 "obj/tpc.c"
    break;

  case 19: /* EnTeteFonct: VOID IDENT '(' Parametres ')'  */
#line 245 "src/tpc.y"
    {
        Node * h  = makeNode(heading);
        Node * t = makeNode(type);
        Node * v = makeNodeString(type,"void");
        Node * i = makeNodeString(id,(yyvsp[-3].ident));
        addChild(t,v);
        addChild(h,t);
        addChild(h,i);
        addChild(h,(yyvsp[-1].node));
        (yyval.node) = h;
    }
#line 1474 "obj/tpc.c"
    break;

  case 20: /* Parametres: VOID  */
#line 259 "src/tpc.y"
       {
        (yyval.node) = makeNode(parameters);
       }
#line 1482 "obj/tpc.c"
    break;

  case 21: /* Parametres: ListTypVar  */
#line 263 "src/tpc.y"
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1490 "obj/tpc.c"
    break;

  case 22: /* ListTypVar: ListTypVar ',' TYPE IDENT  */
#line 269 "src/tpc.y"
       {
        (yyval.node) = (yyvsp[-3].node);
        Node * t = makeNodeString(type,(yyvsp[-1].ident));
        Node * i = makeNodeString(id,(yyvsp[0].ident));
        addChild(t,i);
        addChild((yyval.node),t);
       }
#line 1502 "obj/tpc.c"
    break;

  case 23: /* ListTypVar: TYPE IDENT  */
#line 277 "src/tpc.y"
    {
        Node * p = makeNode(parameters);
        Node * t = makeNodeString(type,(yyvsp[-1].ident));
        Node * i = makeNodeString(id,(yyvsp[0].ident));
        addChild(t,i);
        addChild(p,t);
        (yyval.node) = p;
    }
#line 1515 "obj/tpc.c"
    break;

  case 24: /* ListTypVar: ListTypVar ',' STRUCT IDENT IDENT  */
#line 286 "src/tpc.y"
    {
        (yyval.node)  = (yyvsp[-4].node);
        Node *t = makeNode(type);
        Node * s = makeNode(structure);
        addChild(s,makeNodeString(id,(yyvsp[-1].ident)));
        addChild(t,s);
        Node *i = makeNodeString(id,(yyvsp[0].ident));
        addChild(t,i);
        addChild((yyval.node),t);
    }
#line 1530 "obj/tpc.c"
    break;

  case 25: /* ListTypVar: STRUCT IDENT IDENT  */
#line 297 "src/tpc.y"
    {
        Node * p = makeNode(parameters);
        Node *t = makeNode(type);
        Node * s = makeNode(structure);
        addChild(s,makeNodeString(id,(yyvsp[-1].ident)));
        addChild(t,s);
        Node *i = makeNodeString(id,(yyvsp[0].ident));
        addChild(t,i);
        addChild(p,t);
        (yyval.node) = p;
    }
#line 1546 "obj/tpc.c"
    break;

  case 26: /* Corps: '{' DeclVars SuiteInstr '}'  */
#line 310 "src/tpc.y"
    {
        Node *b = makeNode(body);
        addChild(b,(yyvsp[-2].node));
        addChild(b,(yyvsp[-1].node));
        (yyval.node) = b;
    }
#line 1557 "obj/tpc.c"
    break;

  case 27: /* SuiteInstr: SuiteInstr Instr  */
#line 319 "src/tpc.y"
       {
        (yyval.node) = (yyvsp[-1].node);
        addChild((yyval.node),(yyvsp[0].node));
       }
#line 1566 "obj/tpc.c"
    break;

  case 28: /* SuiteInstr: %empty  */
#line 324 "src/tpc.y"
    {
        (yyval.node) = makeNode(instructions);
    }
#line 1574 "obj/tpc.c"
    break;

  case 29: /* Instr: FieldPathDot '=' Exp ';'  */
#line 330 "src/tpc.y"
    {
        Node *a = makeNode(assign);
        addChild(a,(yyvsp[-3].node));
        addChild(a,(yyvsp[-1].node));
        (yyval.node) = a;
    }
#line 1585 "obj/tpc.c"
    break;

  case 30: /* Instr: IF '(' Exp ')' Instr  */
#line 337 "src/tpc.y"
    {
        Node * ifc = makeNode(if_);
        Node * c = makeNode(condition);
        addChild(c,(yyvsp[-2].node));
        addChild(ifc,c);
        addChild(ifc,(yyvsp[0].node));
        (yyval.node) = ifc;
    }
#line 1598 "obj/tpc.c"
    break;

  case 31: /* Instr: IF '(' Exp ')' Instr ELSE Instr  */
#line 346 "src/tpc.y"
        {
        Node * ifc = makeNode(if_);
       
        Node * c = makeNode(condition);
        addChild(c,(yyvsp[-4].node));
        
        addChild(ifc,c);
        addChild(ifc,(yyvsp[-2].node));
        addChild(ifc,(yyvsp[0].node));
        (yyval.node) = ifc;
        

    }
#line 1616 "obj/tpc.c"
    break;

  case 32: /* Instr: WHILE '(' Exp ')' Instr  */
#line 360 "src/tpc.y"
        {
        Node * whilec  = makeNode(while_);
        Node * c = makeNode(condition);
        addChild(c,(yyvsp[-2].node));
        addChild(whilec,c);
        addChild(whilec,(yyvsp[0].node));
        (yyval.node) = whilec;

    }
#line 1630 "obj/tpc.c"
    break;

  case 33: /* Instr: IDENT '(' Arguments ')' ';'  */
#line 370 "src/tpc.y"
    {
        Node *  cf = makeNode(call_function);
        Node * i = makeNodeString(id,(yyvsp[-4].ident));
        addChild(cf,i);
        addChild(cf,(yyvsp[-2].node));
        (yyval.node) = cf;
    }
#line 1642 "obj/tpc.c"
    break;

  case 34: /* Instr: RETURN Exp ';'  */
#line 378 "src/tpc.y"
    {
        Node *r = makeNode(return_);
        addChild(r,(yyvsp[-1].node));
        (yyval.node) = r;
    }
#line 1652 "obj/tpc.c"
    break;

  case 35: /* Instr: RETURN ';'  */
#line 384 "src/tpc.y"
    {
        Node *r = makeNode(return_);
  
        (yyval.node) = r;
    }
#line 1662 "obj/tpc.c"
    break;

  case 36: /* Instr: '{' SuiteInstr '}'  */
#line 390 "src/tpc.y"
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1670 "obj/tpc.c"
    break;

  case 37: /* Instr: ';'  */
#line 394 "src/tpc.y"
    {
        (yyval.node) = makeNode(instructions);
    }
#line 1678 "obj/tpc.c"
    break;

  case 38: /* Exp: Exp OR TB  */
#line 399 "src/tpc.y"
    {
        Node * o = makeNode(or_);
        addChild(o,(yyvsp[-2].node));
        addChild(o,(yyvsp[0].node));
        (yyval.node) = o;
    }
#line 1689 "obj/tpc.c"
    break;

  case 39: /* Exp: TB  */
#line 406 "src/tpc.y"
    {
        (yyval.node) =  (yyvsp[0].node);
    }
#line 1697 "obj/tpc.c"
    break;

  case 40: /* TB: TB AND FB  */
#line 411 "src/tpc.y"
    {
        Node * a = makeNode(and_);
        addChild(a,(yyvsp[-2].node));
        addChild(a,(yyvsp[0].node));
        (yyval.node) = a;
    }
#line 1708 "obj/tpc.c"
    break;

  case 41: /* TB: FB  */
#line 418 "src/tpc.y"
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1716 "obj/tpc.c"
    break;

  case 42: /* FB: FB EQ M  */
#line 423 "src/tpc.y"
    {
        Node *e = makeNodeString(compare,(yyvsp[-1].comp));
        addChild(e,(yyvsp[-2].node));
        addChild(e,(yyvsp[0].node));
        (yyval.node) = e;
    }
#line 1727 "obj/tpc.c"
    break;

  case 44: /* M: M ORDER E  */
#line 432 "src/tpc.y"
    {
        Node *o = makeNodeString(order,(yyvsp[-1].comp));
        addChild(o,(yyvsp[-2].node));
        addChild(o,(yyvsp[0].node));
        (yyval.node) = o;
    }
#line 1738 "obj/tpc.c"
    break;

  case 45: /* M: E  */
#line 439 "src/tpc.y"
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1746 "obj/tpc.c"
    break;

  case 46: /* E: E ADDSUB T  */
#line 444 "src/tpc.y"
    {
        Node *o;
        if ((yyvsp[-1].byte)=='+'){ 
            o = makeNode(add);

        }else{
            o = makeNode(sub);
        }
        addChild(o,(yyvsp[-2].node));
        addChild(o,(yyvsp[0].node));
        (yyval.node) = o;
    }
#line 1763 "obj/tpc.c"
    break;

  case 47: /* E: T  */
#line 457 "src/tpc.y"
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1771 "obj/tpc.c"
    break;

  case 48: /* T: T DIVSTAR F  */
#line 462 "src/tpc.y"
    {
        char buffer[2];
        buffer[0] = (yyvsp[-1].byte);
        buffer[1] = '\0';
        Node * d = makeNodeString(divstar,buffer);
        addChild(d,(yyvsp[-2].node));
        addChild(d,(yyvsp[0].node));
        (yyval.node) = d;
    }
#line 1785 "obj/tpc.c"
    break;

  case 49: /* T: F  */
#line 472 "src/tpc.y"
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1793 "obj/tpc.c"
    break;

  case 50: /* F: ADDSUB F  */
#line 477 "src/tpc.y"
    {
        Node *o;
        if ((yyvsp[-1].byte)=='-'){
            o = makeNode(negatif);
        }else {
            o = makeNode(positif);
        }
        addChild(o,(yyvsp[0].node));
        (yyval.node) = o;
    }
#line 1808 "obj/tpc.c"
    break;

  case 51: /* F: '!' F  */
#line 488 "src/tpc.y"
    {
        Node * n = makeNode(not_);
        addChild(n,(yyvsp[0].node));
        (yyval.node) = n;
    }
#line 1818 "obj/tpc.c"
    break;

  case 52: /* F: '(' Exp ')'  */
#line 494 "src/tpc.y"
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1826 "obj/tpc.c"
    break;

  case 53: /* F: NUM  */
#line 498 "src/tpc.y"
    {
        char buffer[64];
        sprintf(buffer,"%d",(yyvsp[0].num));
        (yyval.node) = makeNodeString(num,buffer);
    }
#line 1836 "obj/tpc.c"
    break;

  case 54: /* F: CHARACTER  */
#line 504 "src/tpc.y"
    {   
        char buffer[2];
        buffer[0] = (yyvsp[0].byte);
        buffer[1] = '\0';
        (yyval.node) = makeNodeString(character,buffer);
    }
#line 1847 "obj/tpc.c"
    break;

  case 55: /* F: IDENT '(' Arguments ')'  */
#line 513 "src/tpc.y"
    {
        Node * cf = makeNode(call_function);
        Node * i = makeNodeString(id,(yyvsp[-3].ident));
        addChild(cf,i);
        addChild(cf,(yyvsp[-1].node));

        (yyval.node) = cf;
    }
#line 1860 "obj/tpc.c"
    break;

  case 56: /* F: FieldPathDot  */
#line 522 "src/tpc.y"
    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1868 "obj/tpc.c"
    break;

  case 57: /* FieldPathDot: IDENT  */
#line 528 "src/tpc.y"
      {
        Node *i = makeNodeString(id,(yyvsp[0].ident));
        (yyval.node) = i;
      }
#line 1877 "obj/tpc.c"
    break;

  case 58: /* FieldPathDot: FieldPathDot '.' IDENT  */
#line 533 "src/tpc.y"
    {
        Node *f =makeNode(field_dot);
        addChild(f,(yyvsp[-2].node));
        Node * i = makeNodeString(id,(yyvsp[0].ident));
        addChild(f,i);
        (yyval.node) = f;
    }
#line 1889 "obj/tpc.c"
    break;

  case 59: /* Arguments: ListExp  */
#line 543 "src/tpc.y"
       {
        (yyval.node) = (yyvsp[0].node);
       }
#line 1897 "obj/tpc.c"
    break;

  case 60: /* Arguments: %empty  */
#line 547 "src/tpc.y"
    {
        (yyval.node) = makeNode(arguments);
    }
#line 1905 "obj/tpc.c"
    break;

  case 61: /* ListExp: ListExp ',' Exp  */
#line 553 "src/tpc.y"
       {

        (yyval.node) = (yyvsp[-2].node);
        addChild((yyval.node),(yyvsp[0].node));
       }
#line 1915 "obj/tpc.c"
    break;

  case 62: /* ListExp: Exp  */
#line 559 "src/tpc.y"
    {
        Node *a = makeNode(arguments);
        addChild(a,(yyvsp[0].node));
        (yyval.node) = a;
    }
#line 1925 "obj/tpc.c"
    break;


#line 1929 "obj/tpc.c"

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

#line 565 "src/tpc.y"

void yyerror(char *s) {
    fprintf(stderr, "Erreur syntaxique : %s a la ligne %d colonne %d\n",s,lineno,current_column);
}

void h_print(const char *arg){
    fprintf(stderr,"utilisation : %s  option fichier\n Options :\n -t | --tree :affiche l’arbre abstrait sur la sortie standard\n -h | --help : affiche une description de l’interface utilisateur et termine l’exécution\n -s | --symtabs : affiche les tables de symboles\n",arg);
}
int main(int argc, char **argv) {
    int canShow =0;
    int option;
    int showtabl = 0;
    while((option = getopt_long(argc,argv,"ths",option_complete,NULL)) != -1){
        switch(option){
            case 't':
                canShow =1;
                break;
            case 'h':
                h_print(argv[0]);
                return 0;
            case 's':
                showtabl = 1;
                break;
            default : 
                    fprintf(stderr,"Option inconnu");
                    return 3;
        }
    }
    
    if (optind<argc){
        yyin = fopen(argv[optind],"r");
        if (yyin == NULL){
            fprintf(stderr,"erreur d'ouverture");
            return 3;
        }
    }
    int r = yyparse();

    if (root != NULL) {
    
        //Symbol *tableGlobale[TAILLE_TABLE];
        init_table(tableGlobale);
        ajout_fonction(tableGlobale, "putint", TYPE_VOID);
        ajout_fonction(tableGlobale, "putchar", TYPE_VOID);
        ajout_fonction(tableGlobale, "getint", TYPE_INT);
        ajout_fonction(tableGlobale, "getchar", TYPE_CHAR);
        deplct = 0;
        //parcours_struct_def(root);
        ajout_globalTPC(root->firstChild, tableGlobale);
        parcours_fonctions(root);
        
        verif_existence_main(root);
        verif_return_fonctions(root);
        if (showtabl) {
        printf("Table globale :\n");
        afficher_table(tableGlobale);
        afficher_table_locale();
        }
        FILE* f = fopen("_anonymous.asm", "w");
        if (f == NULL){
            fprintf(stderr,"erreur de creation\n");
            return 3;
        }
        translate(root,f);
        fclose(f);
    }

    if (root!=NULL && canShow == 1){
        printTree(root);

    }
    return r;

}
