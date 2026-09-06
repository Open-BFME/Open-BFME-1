// ??0Rva00183AF0State@@QAE@PAX@Z
// partial score=0.75 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: fuzzy-twin of GiantBirdAttackMoveToState's constructor
// (GiantBirdAttackMoveToStateCtor.cpp, retail 0x002BF6D0, 183 bytes) and of
// the Rva0014F280StateBase state-ctor family in Rva0017F4F0StateCtor.cpp
// (which documents that this base writes its early zero members out of
// address order -- +0x54, +0x50, +0x5c, then a literal 5 at +0x60 here --
// via ctor-BODY assignments, not an initializer list, to match retail's
// instruction schedule).
//
// Layout recovered from d_00180810.asm @ 0x00183AF0 (198B):
//   base Rva0014F280StateBase(machine, name) call (ILT 0x00032182, pinned)
//   vtable install 0x0109B190
//   +0x50 byte = 0            (early, ctor body)
//   +0x54 int  = 0            (early, ctor body -- written before +0x50)
//   +0x5c int  = 0            (early, ctor body)
//   +0x60 int  = 5            (early, ctor body -- retryCount-equivalent)
//   +0x58 ptr  = new <sub-machine>(((Rva002BF6D0StateMachine*)m_machine)->getOwner(),
//                                   AsciiString("...")); then ->initDefaultState()
//   +0x64/+0x68/+0x6c/+0x70 int = 0   (four zero members, late/body, replacing
//                                      the twin's single m_goalHandle = 0;)
//
// BLOCKED: the sub-machine constructor call (REL32 0x0000DFA8, an
// already-matched anonymous jump thunk "?j_0000dfa8@@YAXXZ" in
// Code/gen_small/thunks_006.cpp -> FUN_00581f60, itself unidentified) needs
// a properly-typed pin (an additive reverse/symbols.csv row mapping a real
// ctor-shaped mangled name to 0x0000DFA8, the way
// "??0AICommandParms@@QAE@W4AICommandType@@W4CommandSourceType@@@Z" pins to
// 0x00030EA4 elsewhere) before a normal C++ constructor call to a
// TU-local sub-machine class will route to that exact address. Editing the
// shared symbols.csv ledger was out of scope for this pass; a sibling with
// ledger-write access can add the row and this file's shape should then
// compile byte-exact -- the base/vtable/array-of-zero-members portion above
// is already probe-verified against retail up to the callee-address
// mismatch.

#include "../../../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class AsciiString
{
public:
	AsciiString( const char *text ) : m_string( text ) {}

	StringBase<char> m_string;
};

class Rva0014F280StateBase
{
public:
	Rva0014F280StateBase( void *machine, AsciiString name );

	virtual ~Rva0014F280StateBase();

protected:
	char m_baseGap04[ 0x18 ];
	void *m_machine;			// +0x1c
	char m_baseTail20[ 0x50 - 0x20 ];	// pad to +0x50
};

// TU-local stand-in for the still-unidentified sub-machine class built at
// FUN_00581f60 (via thunk 0x0000DFA8). Needs a real symbols.csv pin before
// this constructor call will route to the correct retail address.
class Rva00581F60SubMachine
{
public:
	Rva00581F60SubMachine( void *owner, AsciiString name );
	virtual ~Rva00581F60SubMachine();
	virtual void unused04();
	virtual void unused08();
	virtual void unused0c();
	virtual void unused10();
	virtual void unused14();
	virtual void unused18();
	virtual void initDefaultState();

private:
	char m_unreconstructed04[ 0x40 ];
};

class Rva002BF6D0StateMachine
{
private:
	char m_gap00[ 0x10 ];

public:
	void *m_owner;

	void *getOwner() { return m_owner; }
};

class Rva00183AF0State : public Rva0014F280StateBase
{
public:
	Rva00183AF0State( void *machine );

private:
	volatile unsigned char m_byte50;	// +0x50
	char m_gap51[ 3 ];
	volatile int m_int54;			// +0x54
	Rva00581F60SubMachine *m_subMachine;	// +0x58
	volatile int m_int5c;			// +0x5c
	volatile int m_retryCount;		// +0x60
	int m_tail64;				// +0x64
	int m_tail68;				// +0x68
	int m_tail6c;				// +0x6c
	int m_tail70;				// +0x70
};

Rva00183AF0State::Rva00183AF0State( void *machine )
	: Rva0014F280StateBase( machine, AsciiString( "GiantBirdNormalFlightState" ) )
{
	m_int54 = 0;
	m_byte50 = 0;
	m_int5c = 0;
	m_retryCount = 5;
	m_subMachine = new Rva00581F60SubMachine(
		((Rva002BF6D0StateMachine *)m_machine)->getOwner(),
		AsciiString( "AIAttackMoveMachine" ) );
	m_subMachine->initDefaultState();
	m_tail64 = 0;
	m_tail68 = 0;
	m_tail6c = 0;
	m_tail70 = 0;
}
