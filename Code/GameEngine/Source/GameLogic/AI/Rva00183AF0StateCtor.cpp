// ??0Rva00183C10@@QAE@PAVStateMachine@@@Z
// Neutral RVA identity for the constructor at retail 0x00183AF0.
//
// Identity evidence: AIStateMachine's AI_ATTACK_MOVE_TO construction at its
// source line 807 calls ILT 0x000268C8, which jumps here.  Retail vtable
// 0x0109B190 has 18 slots and the nearby runtime name is
// "AIAttackMoveToState".  The separate 0x00183990 body installs vtable
// 0x01099C08, so this source keeps an address-derived class spelling rather
// than conflating the two constructors.  The base-name literal in this body
// is the proven retail string "AIMoveToState".
// cl: /DNDEBUG /MD /EHsc

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class AsciiString
{
public:
	AsciiString( const char *text ) : m_data( text ) {}

	StringBase<char> m_data;
};

class StateMachine;
class Object;

// The base constructor uses the existing AIInternalMoveToState ILT pin. The
// complete virtual-slot shape keeps this neutral state ABI-compatible with
// the 18-slot retail vtable installed by the constructor.
class AIInternalMoveToState
{
public:
	AIInternalMoveToState( void *machine, AsciiString name );

	virtual ~AIInternalMoveToState();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();

protected:
	char m_baseGap04[ 0x18 ];
	void *m_machine;
	char m_baseTail20[ 0x50 - 0x20 ];
};

// Retail slot 0 is ILT 0x0004103D -> scalar deleting dtor 0x001873E0.
// That helper calls ILT 0x0001C215, whose target is the existing complete
// destructor at 0x00183C10.  The complete dtor owns the raw submachine at
// +0x58, so the derived declaration is part of this class's real lifetime ABI.

// The 0x00181F60 callee is retained as an address-derived neutral
// sub-machine.  Seven virtual slots after the destructor place
// initDefaultState at +0x1c, matching the retail indirect call.
class Rva00581F60SubMachine
{
public:
	Rva00581F60SubMachine( Object *owner, AsciiString name );
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
	Object *m_owner;

	Object *getOwner() { return m_owner; }
};

class Rva00183C10 : public AIInternalMoveToState
{
public:
	Rva00183C10( StateMachine *machine );
	virtual ~Rva00183C10();

private:
	unsigned char m_byte50;
	char m_gap51[ 3 ];
	int m_int54;
	Rva00581F60SubMachine *m_subMachine;
	int m_int5c;
	int m_retryCount;
	int m_tail64;
	int m_tail68;
	int m_tail6c;
	int m_tail70;
};

// The existing complete destructor at 0x00183C10 is defined below with
// this full class layout, so its vtable has the same 18 slots as the constructor.

Rva00183C10::Rva00183C10( StateMachine *machine )
	: AIInternalMoveToState( machine,
		AsciiString( "AIMoveToState" ) )
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

Rva00183C10::~Rva00183C10()
{
	delete m_subMachine;
	m_subMachine = 0;
}
