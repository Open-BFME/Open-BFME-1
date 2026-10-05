// cl: /DNDEBUG /MD /EHsc -D_OPERATOR_NEW_DEFINED_ -D_STLP_USE_STATIC_LIB -D_STLP_NO_EXCEPTIONS -Iinputs/reference/shims/ini_bfme -Iinputs/reference/shims/sweep -Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include -Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Include
// stlport
// Four more INI field-parse builders, found by re-running the proven bodies of
// WideBuildFieldParse.cpp and WideBuildFieldParsePair.cpp as a GRAMMAR rather
// than as byte strings: `push esi / mov esi,[esp+8]`, then any sequence of
// either a base-class block (`push esi / call REL32 / add esp,4`) or an
// append block (`push EXTRA / push offset TABLE / mov ecx,esi / call
// 0x00850920`), then `pop esi / ret`.  Opcode-structure grouping cannot see
// these: it keys on the exact block sequence, so a builder with three tables,
// or with the base call last, or with an extra offset too large for an imm8,
// falls out as a singleton.
//
// WHAT THE BYTES SHOW, per member:
//   0x0013E170  two tables, extras 0 and 224 -- 224 needs a `push imm32`
//   0x00212CD0  base call, then two tables, extras 92 and 0
//   0x00378170  three tables, all extra 0, no base call
//   0x00753A80  one table then the base call LAST, which fixes the source
//               order of the two statements and is not recoverable any other
//               way
//
// Builder names remain address-derived. Recovered tables use the verified
// FieldParse declarations below; the remaining tables are unresolved externs.
//
// The receiver stays spelled WideMulti because every member body here is
// matched under a name carrying it; respelling the parameter type would rename
// the enclosing bodies and unmatch those rows. The appender they call is
// retail's MultiIniFieldParse::add at 0x00850920, so the call goes through the
// defining class, taken from the real Common/INI.h.

#include "Common/INI.h"

class WideFieldParse
{
public:
	const char *m_token;
	void (*m_parse)();
	const void *m_userData;
	unsigned int m_offset;
};

class WideMulti
{
};

// Every body below appends through this one spelling of retail's appender.
#define WIDE_MULTI_APPEND( P, TBL, EXTRA ) \
	reinterpret_cast<MultiIniFieldParse &>( P ).add( \
		reinterpret_cast<const FieldParse *>( TBL ), EXTRA )

class Gen00012355
{
public:
	static void buildFieldParse( WideMulti &p );
};

class Gen00022584
{
public:
	static void buildFieldParse( WideMulti &p );
};

extern "C" const FieldParse __identifier("?s_objectFieldParseTable@ThingTemplate@@0QBUFieldParse@@B")[];
extern const FieldParse g_voiceFieldParse[];

class Rva0013E170
{
public:
	static void buildFieldParse( WideMulti &p );
};

void Rva0013E170::buildFieldParse( WideMulti &p )
{
	WIDE_MULTI_APPEND( p, __identifier("?s_objectFieldParseTable@ThingTemplate@@0QBUFieldParse@@B"), 0 );
	WIDE_MULTI_APPEND( p, g_voiceFieldParse, 224 );
}

extern const WideFieldParse WideTblA00212CD0[];
extern const WideFieldParse WideTblB00212CD0[];

class Rva00212CD0
{
public:
	static void buildFieldParse( WideMulti &p );
};

void Rva00212CD0::buildFieldParse( WideMulti &p )
{
	Gen00012355::buildFieldParse( p );
	WIDE_MULTI_APPEND( p, WideTblA00212CD0, 92 );
	WIDE_MULTI_APPEND( p, WideTblB00212CD0, 0 );
}

extern const FieldParse g_table_00122E10[];
extern const WideFieldParse WideTblB00378170[];
extern const WideFieldParse WideTblC00378170[];

class Rva00378170
{
public:
	static void buildFieldParse( WideMulti &p );
};

void Rva00378170::buildFieldParse( WideMulti &p )
{
	WIDE_MULTI_APPEND( p, g_table_00122E10, 0 );
	WIDE_MULTI_APPEND( p, WideTblB00378170, 0 );
	WIDE_MULTI_APPEND( p, WideTblC00378170, 0 );
}

extern const WideFieldParse WideTblA00753A80[];

class Rva00753A80
{
public:
	static void buildFieldParse( WideMulti &p );
};

void Rva00753A80::buildFieldParse( WideMulti &p )
{
	WIDE_MULTI_APPEND( p, WideTblA00753A80, 0 );
	Gen00022584::buildFieldParse( p );
}
