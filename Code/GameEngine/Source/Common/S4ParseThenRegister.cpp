// Four 111-byte bodies of SAGE's INI definition-parsing shape:
//
//     void parse( INI *ini, Sink *sink )
//     {
//         T *t = new T;
//         ini->initFromINI( t, &table );
//         t->m_storage[ 1 ] = t->m_storage[ 5 ];
//         sink->m( (int)t );
//     }
//
// WHAT THE BYTES SHOW, AND WHICH NAMES ARE RECOVERED.  The third call is
// 0x008520A0 in all four, already a matched row:
// `?initFromINI@INI@@QAEXPAXPBUFieldParse@@@Z`.  It is __thiscall on the
// function's FIRST argument and takes the freshly allocated object plus a fixed
// data address -- so the second pushed dword is a parse table, one per row
// (0x0110C6CC, 0x0110C9BC, 0x0110CA40, 0x0110CBA0 as virtual addresses).  The
// fourth call is 0x00489270 in all four, also already a matched row:
// `?m@Gen_00489270@@QAEXH@Z`, __thiscall with one dword.  Its `this` is read
// from [esp+0x1C] with five dwords pushed -- the SECOND argument slot, not the
// first -- so this function takes TWO parameters and the two member calls are
// made on DIFFERENT objects.  That is the one fact about the signature that a
// caller could not have told us and the callee bytes do.
//
// BETWEEN THE TWO CALLS, ONE DWORD IS COPIED WITHIN THE NEW OBJECT: `mov
// eax,[esi+0x14] / mov [esi+4],eax`.  Both offsets are inside the allocation in
// every row, and nothing else touches the object, so the stand-in below is a
// plain dword array and the copy is spelled by index.  What those two fields
// are is not observable.
//
// THE `new` IS THE ORDINARY MSVC SEQUENCE with a default constructor and an EH
// state driven to 0 across it and back to -1 before `initFromINI` -- the
// allocation is the only thing under the unwind.  The null-allocation arm sets
// esi to zero and REJOINS the main path, so a failed allocation still runs both
// calls; the source has no null check.
//
// THE AXES ARE THE ALLOCATION SIZE, THE CONSTRUCTOR AND THE TABLE.  Retail's
// sizes are 64, 72, 80 and 64 bytes -- all imm8, which is why all four bodies
// are the same length.  Two rows allocate 64 bytes but have different
// constructors and different tables, so they stay separate types.
//
// IDENTITY IS NOT RECOVERED for the parsed classes or the tables: each is named
// after the body that uses it, the constructors are DECLARED and pinned to the
// addresses their REL32s resolve to, and the tables are extern objects of an
// INCOMPLETE type -- only their addresses are ever used, and the bytes show
// nothing about their contents.

struct FieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI( void *what, const FieldParse *table );
};

struct Gen_00489270
{
	void m( int a );
};

class Rva00489210
{
public:
	Rva00489210();
	int *volatile m_00;
	int m_04;
	char m_08, m_09, m_0A;
	volatile int m_0C;
};

#define S4_PARSE_THEN_REGISTER( NAME, DWORDS )                                 \
	extern int g_s4Head##NAME;                                                 \
	struct S4Parsed##NAME : public Rva00489210                                 \
	{                                                                          \
		volatile int m_storage[ DWORDS - 4 ];                                  \
		S4Parsed##NAME();                                                      \
	};                                                                         \
	extern const FieldParse s4Table##NAME;                                     \
	void s4parse##NAME( INI *ini, Gen_00489270 *sink )                         \
	{                                                                          \
		S4Parsed##NAME *t = new S4Parsed##NAME;                                \
		ini->initFromINI( t, &s4Table##NAME );                                 \
		t->m_04 = t->m_storage[ 1 ];                                           \
		sink->m( (int)t );                                                     \
	}

S4_PARSE_THEN_REGISTER( 0059BDE0, 16 )
S4_PARSE_THEN_REGISTER( 0059E290, 18 )
S4_PARSE_THEN_REGISTER( 0059E860, 20 )
S4_PARSE_THEN_REGISTER( 0059F980, 16 )

S4Parsed0059BDE0::S4Parsed0059BDE0()
{
	m_storage[ 0 ] = 0;
	m_storage[ 1 ] = 30;
	m_00 = &g_s4Head0059BDE0;
	m_storage[ 2 ] = 0;
	m_storage[ 3 ] = 0;
	m_storage[ 4 ] = 0;
	m_storage[ 5 ] = 0;
	m_storage[ 6 ] = -1;
	m_storage[ 7 ] = 0;
	m_storage[ 8 ] = 0;
	m_04 = m_storage[ 1 ];
	m_storage[ 9 ] = 0;
	m_storage[ 10 ] = 0;
	m_storage[ 11 ] = 0;
	m_0C = 0;
	m_09 = 1;
}

S4Parsed0059E290::S4Parsed0059E290()
{
	m_storage[ 0 ] = 0;
	m_storage[ 1 ] = 3;
	m_00 = &g_s4Head0059E290;
	m_storage[ 2 ] = 0;
	m_storage[ 3 ] = 0;
	m_storage[ 4 ] = 0;
	m_storage[ 5 ] = 0;
	m_storage[ 6 ] = -1;
	m_storage[ 7 ] = 0;
	m_storage[ 8 ] = 0;
	m_storage[ 9 ] = 0;
	m_storage[ 10 ] = 0;
	m_storage[ 11 ] = 0;
	m_storage[ 12 ] = 0;
	m_04 = m_storage[ 1 ];
	m_storage[ 13 ] = 0;
	m_0C = 0;
	m_09 = 1;
}

S4Parsed0059E860::S4Parsed0059E860()
{
	m_storage[ 0 ] = 0;
	m_storage[ 1 ] = 5;
	m_00 = &g_s4Head0059E860;
	m_storage[ 2 ] = 0;
	m_storage[ 3 ] = 0;
	m_storage[ 4 ] = 0;
	m_storage[ 5 ] = 0;
	m_storage[ 6 ] = -1;
	m_storage[ 7 ] = 0;
	m_storage[ 8 ] = 0;
	m_storage[ 9 ] = 0;
	m_storage[ 10 ] = 0;
	m_storage[ 11 ] = 0;
	m_storage[ 12 ] = 0;
	m_storage[ 13 ] = 0;
	m_storage[ 14 ] = 0;
	m_04 = m_storage[ 1 ];
	m_storage[ 15 ] = 0;
	m_0C = 0;
	m_09 = 1;
}
