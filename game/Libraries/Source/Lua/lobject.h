/* ALTERED SOURCE VERSION -- this header differs from upstream Lua 4.0.1.
   See PROVENANCE.txt for what changed and why; marking the alteration is a
   condition of the licence at lua.h:215. */
/*
** $Id: lobject.h,v 1.82 2000/10/30 17:49:19 roberto Exp $
** Type definitions for Lua objects
** See Copyright Notice in lua.h
*/

#ifndef lobject_h
#define lobject_h


#include "llimits.h"
#include "lua.h"


#ifdef LUA_DEBUG
#undef NDEBUG
#include <assert.h>
#define LUA_INTERNALERROR(s)	assert(((void)s,0))
#define LUA_ASSERT(c,s)		assert(((void)s,(c)))
#else
#define LUA_INTERNALERROR(s)	/* empty */
#define LUA_ASSERT(c,s)		/* empty */
#endif


#ifdef LUA_DEBUG
/* to avoid warnings, and make sure value is really unused */
#define UNUSED(x)	(x=0, (void)(x))
#else
#define UNUSED(x)	((void)(x))	/* to avoid warnings */
#endif


/* mark for closures active in the stack */
/* BFME's Lua carries one more type tag than upstream 4.0.1: retail luaD_call
   stores 7 for LUA_TMARK where stock Lua stores 6.  Bumping both constants is
   what makes ldebug/ltm/ldo byte-exact; the extra tag itself is never named in
   the image, only counted. */
#define LUA_TMARK	7


/* tags for values visible from Lua == first user-created tag */
#define NUM_TAGS	7


/* check whether `t' is a mark */
#define is_T_MARK(t)	((t) == LUA_TMARK)


typedef union {
  struct TString *ts;	/* LUA_TSTRING, LUA_TUSERDATA */
  struct Closure *cl;	/* LUA_TFUNCTION */
  struct Hash *a;	/* LUA_TTABLE */
  struct CallInfo *i;	/* LUA_TLMARK */
  Number n;		/* LUA_TNUMBER */
  int b;		/* EA's added tag 6, LUA_TBOOLEAN -- no macro named for the
			   tag itself in retail, just switched on as literal 6 */
} Value;


/* Macros to access values */
#define ttype(o)        ((o)->ttype)
#define nvalue(o)       ((o)->value.n)
#define tsvalue(o)      ((o)->value.ts)
#define clvalue(o)      ((o)->value.cl)
#define hvalue(o)       ((o)->value.a)
#define infovalue(o)	((o)->value.i)
#define bvalue(o)	((o)->value.b)
#define svalue(o)       (tsvalue(o)->str)


typedef struct lua_TObject {
  int ttype;
  Value value;
} TObject;


/*
** String headers for string table
*/

/*
** most `malloc' libraries allocate memory in blocks of 8 bytes. TSPACK
** tries to make sizeof(TString) a multiple of this granularity, to reduce
** waste of space.
*/
#define TSPACK	((int)sizeof(int))

typedef struct TString {
  union {
    struct {  /* for strings */
      unsigned long hash;
      int constindex;  /* hint to reuse constants */
    } s;
    struct {  /* for userdata */
      int tag;
      void *value;
    } d;
  } u;
  size_t len;
  struct TString *nexthash;  /* chain for hash table */
  int marked;
  char str[TSPACK];   /* variable length string!! must be the last field! */
} TString;


/*
** Function Prototypes
*/
typedef struct Proto {
  Number *knum;  /* Number numbers used by the function */
  int nknum;  /* size of `knum' */
  struct TString **kstr;  /* strings used by the function */
  int nkstr;  /* size of `kstr' */
  struct Proto **kproto;  /* functions defined inside the function */
  int nkproto;  /* size of `kproto' */
  Instruction *code;
  int ncode;  /* size of `code'; when 0 means an incomplete `Proto' */
  short numparams;
  short is_vararg;
  short maxstacksize;
  short marked;
  struct Proto *next;
  /* debug information */
  int *lineinfo;  /* map from opcodes to source lines */
  int nlineinfo;  /* size of `lineinfo' */
  int nlocvars;
  struct LocVar *locvars;  /* information about local variables */
  int lineDefined;
  TString  *source;
} Proto;


typedef struct LocVar {
  TString *varname;
  int startpc;  /* first point where variable is active */
  int endpc;    /* first point where variable is dead */
} LocVar;


/*
** Closures
*/
typedef struct Closure {
  union {
    lua_CFunction c;  /* C functions */
    struct Proto *l;  /* Lua functions */
  } f;
  struct Closure *next;
  struct Closure *mark;  /* marked closures (point to itself when not marked) */
  short isC;  /* 0 for Lua functions, 1 for C functions */
  short nupvalues;
  TObject upvalue[1];
} Closure;


#define iscfunction(o)	(ttype(o) == LUA_TFUNCTION && clvalue(o)->isC)


typedef struct Node {
  TObject key;
  TObject val;
  struct Node *next;  /* for chaining */
} Node;

typedef struct Hash {
  Node *node;
  int htag;
  int size;
  /* BFME's luaH_new takes an extra caller-requested size argument (the
     pre-power-of-2 value) and stores it raw here, one slot before where a
     stock node/htag/size/firstfree layout would put firstfree. */
  int reqsize;
  Node *firstfree;  /* this position is free; all positions after it are full */
  struct Hash *next;
  struct Hash *mark;  /* marked tables (point to itself when not marked) */
} Hash;


/* unmarked tables and closures are represented by pointing `mark' to
** themselves
*/
#define ismarked(x)	((x)->mark != (x))


/*
** informations about a call (for debugging)
*/
typedef struct CallInfo {
  struct Closure *func;  /* function being called */
  const Instruction **pc;  /* current pc of called function */
  int lastpc;  /* last pc traced */
  int line;  /* current line */
  int refi;  /* current index in `lineinfo' */
} CallInfo;


extern const TObject luaO_nilobject;
extern const char *const luaO_typenames[];


#define luaO_typename(o)	(luaO_typenames[ttype(o)])


lint32 luaO_power2 (lint32 n);
char *luaO_openspace (lua_State *L, size_t n);

int luaO_equalObj (const TObject *t1, const TObject *t2);
int luaO_str2d (const char *s, Number *result);

void luaO_verror (lua_State *L, const char *fmt, ...);
void luaO_chunkid (char *out, const char *source, int len);


#endif
