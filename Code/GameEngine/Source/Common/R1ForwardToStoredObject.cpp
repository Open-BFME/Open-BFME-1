// Eleven bodies whose mnemonic sequence is "load, load, push, call" -- one
// argument handed to one call, and then straight out.  Grouping by mnemonics
// alone put them together, but the operands split them into six shapes, and one
// of the six is not address-derived at all.
//
// WHAT THE BYTES SHOW.  Every one of these ends in `call` + `ret`, never `jmp`,
// which is what a __thiscall callee taking a stack argument forces: the callee
// pops the argument, so this function cannot hand its own frame over.  Whatever
// the callee leaves in eax is what these functions return; where the callee is
// unknown that is spelled `void`, which asserts the least.
//
// FIVE ROWS ARE IDENTIFIED, not guessed.  They read the global at 0x012F0898 --
// which the ledger already pins as TheGameLogic -- and call the body at
// 0x0009A510, which the ledger already names GameLogic::findObjectByID(int).
// So those five are `TheGameLogic->findObjectByID( <member> )`, and the member
// they pass is an object id.  The declarations of GameLogic and Object here are
// the minimum needed to reproduce those two decorated names; they are not a
// claim about the real classes.
//
// The rest keep address-derived names: `GloXXXXXXXX` for a global's type,
// `GenXXXXXXXX` for a callee's class, `hXXXXXXXX` for a member whose only
// evidence is the address it reaches.  TheAudio is the exception in the other
// direction -- the ledger pins the global, and the pinned name fixes the class
// name to AudioManager, but the vtable slot it calls (0xA8) is not identified
// and the pad virtuals exist only to place it.
//
// TWO GLOBALS ARE SHARED WITH OTHER FILES.  0x012F19E8 is also read by
// 0x00584E20 in R1GuardedPointerTailCalls.cpp; the type declared here and there
// must agree, and does.

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID( int id );
};
extern GameLogic *TheGameLogic;

#define BFME_FIND_OBJECT_BY_ID( NAME, OFFSET )                            \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		Object *get() const;                                              \
		char m_lead[ OFFSET ];                                            \
		int m_id;                                                         \
	};                                                                    \
	Object *NAME::get() const                                             \
	{                                                                     \
		return TheGameLogic->findObjectByID( m_id );                      \
	}

BFME_FIND_OBJECT_BY_ID( Rva000A14D0, 0x30 )
BFME_FIND_OBJECT_BY_ID( Rva000A14F0, 0x30 )
BFME_FIND_OBJECT_BY_ID( Rva0015C260, 0x44 )
BFME_FIND_OBJECT_BY_ID( Rva00238AC0, 0xd8 )
BFME_FIND_OBJECT_BY_ID( Rva002BA1E0, 0x74 )

// -------------------------------------------------- other globals, same shape

class Glo00EED810
{
public:
	void h000EF060( int value );
};
extern Glo00EED810 *g_Glo00EED810;

class Rva0015B750
{
public:
	void go() const;
	char m_lead[ 0x48 ];
	int m_value;
};
void Rva0015B750::go() const { g_Glo00EED810->h000EF060( m_value ); }

class Glo00EF19E8
{
public:
	void h0046B2B0( int value );
};
extern Glo00EF19E8 *g_Glo00EF19E8;

class Rva0046B3B0
{
public:
	void go() const;
	char m_lead[ 0x1c0 ];
	int m_value;
};
void Rva0046B3B0::go() const { g_Glo00EF19E8->h0046B2B0( m_value ); }

// -------------------------------------------------- receiver off the stack

class Gen0021CE60
{
public:
	void handle( int value );
};
void Rva0021A2D0( int value, Gen0021CE60 *target ) { target->handle( value ); }

// -------------------------------------------------- clear a field, then call

class Gen001C9AC0
{
public:
	void handle( int value );
};

class Rva0025FA60
{
public:
	void go();
	char m_lead[ 8 ];
	Gen001C9AC0 *m_target;
	char m_mid[ 0x2c - 0x0c ];
	int m_value;
};
void Rva0025FA60::go()
{
	m_value = 0;
	m_target->handle( 27 );
}

// -------------------------------------------------- virtual through a global

#define BFME_VSLOT4( P )                                                  \
	virtual void P##_0();                                                 \
	virtual void P##_1();                                                 \
	virtual void P##_2();                                                 \
	virtual void P##_3();

#define BFME_VSLOT16( P )                                                 \
	BFME_VSLOT4( P##a )                                                   \
	BFME_VSLOT4( P##b )                                                   \
	BFME_VSLOT4( P##c )                                                   \
	BFME_VSLOT4( P##d )

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	BFME_VSLOT16( a ) BFME_VSLOT16( b ) BFME_VSLOT4( c ) BFME_VSLOT4( d )
	virtual void e_0();
	virtual void e_1();
	virtual void slot( int value );
};
extern AudioManager *TheAudio;

void Rva002EFF00() { TheAudio->slot( 0 ); }

class Glo00EF7048
{
public:
	BFME_VSLOT4( a )
	virtual void slot( int value );
};
extern Glo00EF7048 *g_Glo00EF7048;

void Rva002F0930() { g_Glo00EF7048->slot( 1 ); }
