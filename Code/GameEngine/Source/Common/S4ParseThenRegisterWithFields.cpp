// Four 142-byte bodies: the same INI definition-parsing shape as
// S4ParseThenRegister.cpp, but the allocated object's constructor is INLINED
// here rather than called, and it sets five fields:
//
//     void parse( INI *ini, Sink *sink )
//     {
//         D *t = new D;          // D::D() base ctor, then five stores
//         ini->initFromINI( t, &table );
//         sink->m( (int)t );
//     }
//
// WHAT THE BYTES SHOW.  Inside the `if (allocation)` arm, a __thiscall call on
// `this` UNADJUSTED is followed by five stores at +0, +4, +0xC, +0x20 and a
// BYTE at +9.  A call on an unadjusted `this` puts the callee's object at offset
// zero, and stores that follow it in the same arm are the rest of a constructor
// the compiler chose to inline -- MSVC's order is base constructors, then own
// vptr, then members, and the +0 store sits exactly where either of the last two
// would.
//
// THE CALLEE IS ALREADY RECOVERED, and it decides the base's layout for us:
// 0x00489210 is the matched row `??0Rva00489210@@QAE@XZ` in
// R3ScalarFieldConstructors2.cpp, a 31-byte constructor that writes a pointer at
// +0 and fields at +4, +8, +9, +0xA and +0xC.  Its class declaration is repeated
// here verbatim.  Every field this family re-writes -- +0, +4, +9, +0xC -- is a
// field that constructor already wrote, so what these four bodies do is override
// the base's defaults; +0x20 is the only store outside it.
//
// WHY +0 IS SPELLED AS A POINTER FIELD AND NOT AS A vptr.  Both compile to the
// same 142 bytes: a polymorphic base with the derived class storing its own
// vftable is byte-identical to a plain pointer member assigned in the
// constructor body.  The pointer-member spelling is used because it asserts
// less -- no vtable, no virtual function, no inheritance of one -- and because
// it is the reading R3 already landed for this same field of this same base.
//
// STORE ORDER IS SOURCE ORDER, NOT DECLARATION ORDER.  The byte at +9 is written
// LAST, after +0x20.  A member-initialiser list would have emitted it between +4
// and +0xC; a constructor BODY emits statements as written.  That is why the
// bodies below are constructor bodies.
//
// THE AXES ARE FOUR ADDRESSES AND ONE CONSTANT.  Retail's four +4 values are 10,
// 8, 6 and 6; its four +0 pointers and four parse tables are eight distinct data
// addresses; its allocation sizes are 36, 36, 52 and 52 bytes.  The constants at
// +0xC (0), +0x20 (-1) and +9 (1) are the same in all four.  Both callees --
// `INI::initFromINI` at 0x008520A0 and `Gen_00489270::m` at 0x00489270 -- are
// matched rows and are shared by all four, as they are by the sibling file.
//
// IDENTITY IS NOT RECOVERED for the four derived classes, their +0 pointers or
// their tables: each is named after the body that builds it, and the two data
// objects are extern declarations whose ADDRESSES are all the bytes show.

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
	int *m_00;
	int m_04;
	char m_08, m_09, m_0A;
	int m_0C;
};

#define S4_NO_TAIL
#define S4_TAIL_16 int m_tail[ 4 ];

#define S4_PARSE_WITH_FIELDS( NAME, AT4, TAIL )                                \
	extern int g_s4Head##NAME;                                                 \
	extern const FieldParse s4Table##NAME;                                     \
	struct S4Built##NAME : public Rva00489210                                  \
	{                                                                          \
		int m_10, m_14, m_18, m_1C, m_20;                                      \
		TAIL                                                                   \
		S4Built##NAME()                                                        \
		{                                                                      \
			m_00 = &g_s4Head##NAME;                                            \
			m_04 = ( AT4 );                                                    \
			m_0C = 0;                                                          \
			m_20 = -1;                                                         \
			m_09 = 1;                                                          \
		}                                                                      \
	};                                                                         \
	void s4parseFields##NAME( INI *ini, Gen_00489270 *sink )                   \
	{                                                                          \
		S4Built##NAME *t = new S4Built##NAME;                                  \
		ini->initFromINI( t, &s4Table##NAME );                                 \
		sink->m( (int)t );                                                     \
	}

S4_PARSE_WITH_FIELDS( 0059C4C0, 10, S4_NO_TAIL )
S4_PARSE_WITH_FIELDS( 0059CB30, 8, S4_NO_TAIL )
S4_PARSE_WITH_FIELDS( 0059F280, 6, S4_TAIL_16 )
S4_PARSE_WITH_FIELDS( 0059F630, 6, S4_TAIL_16 )
