// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// InGameUI::createMoveHint (0x00444450): slot 27 (+0x6C) of InGameUI's table
// 0x00CF5B38 (targets/game/reverse/identity_evidence/0043ac80.md). Zero Hour's body, except
// that BFME skips a location two TerrainLogic queries reject and clears every
// hint before adding the new one instead of expiring the old hints of the
// same source.

typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

struct Coord3D
{
	Real x, y, z;

	void set( const Coord3D *a )
	{
		x = a->x;
		y = a->y;
		z = a->z;
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
union GameMessageArgumentType
{
	Coord3D location;
};

class GameMessage
{
public:
	const GameMessageArgumentType *getArgument( Int argIndex ) const;
};

enum KindOfType { BFME_KINDOF_2 = 2 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf( KindOfType t ) const;
};

// Object's mobility test (0x001C9270), under its ledger name.
class ObjectIsMobileBody
{
public:
	Bool isMobile() const;
};

class Object : public Thing
{
};

// Drawable+0xFC is m_object.
struct BfmeMoveHintDrawable
{
	unsigned char m_unmodelled000[0xfc];
	Object *m_object;										///< this+0xFC

	Object *getObject() { return m_object; }
};

#define BFME_MOVE_HINT_SLOT(n) virtual void bfmeMoveHintSlot##n() = 0;

// Two location queries of BFME's TerrainLogic, vtable +0x50 and +0x58.
class BfmeMoveHintTerrainLogic
{
public:
	BFME_MOVE_HINT_SLOT(0) BFME_MOVE_HINT_SLOT(1) BFME_MOVE_HINT_SLOT(2) BFME_MOVE_HINT_SLOT(3)
	BFME_MOVE_HINT_SLOT(4) BFME_MOVE_HINT_SLOT(5) BFME_MOVE_HINT_SLOT(6) BFME_MOVE_HINT_SLOT(7)
	BFME_MOVE_HINT_SLOT(8) BFME_MOVE_HINT_SLOT(9) BFME_MOVE_HINT_SLOT(10) BFME_MOVE_HINT_SLOT(11)
	BFME_MOVE_HINT_SLOT(12) BFME_MOVE_HINT_SLOT(13) BFME_MOVE_HINT_SLOT(14) BFME_MOVE_HINT_SLOT(15)
	BFME_MOVE_HINT_SLOT(16) BFME_MOVE_HINT_SLOT(17) BFME_MOVE_HINT_SLOT(18) BFME_MOVE_HINT_SLOT(19)
	virtual Bool terrainSlot20( Real x, Real y ) = 0;		///< vtable +0x50
	BFME_MOVE_HINT_SLOT(21)
	virtual Bool terrainSlot22( Real x, Real y ) = 0;		///< vtable +0x58
};

extern BfmeMoveHintTerrainLogic *TheTerrainLogic;

// BFME's GameClient hands out its frame through vtable +0x68.
class BfmeMoveHintGameClient
{
public:
	BFME_MOVE_HINT_SLOT(0) BFME_MOVE_HINT_SLOT(1) BFME_MOVE_HINT_SLOT(2) BFME_MOVE_HINT_SLOT(3)
	BFME_MOVE_HINT_SLOT(4) BFME_MOVE_HINT_SLOT(5) BFME_MOVE_HINT_SLOT(6) BFME_MOVE_HINT_SLOT(7)
	BFME_MOVE_HINT_SLOT(8) BFME_MOVE_HINT_SLOT(9) BFME_MOVE_HINT_SLOT(10) BFME_MOVE_HINT_SLOT(11)
	BFME_MOVE_HINT_SLOT(12) BFME_MOVE_HINT_SLOT(13) BFME_MOVE_HINT_SLOT(14) BFME_MOVE_HINT_SLOT(15)
	BFME_MOVE_HINT_SLOT(16) BFME_MOVE_HINT_SLOT(17) BFME_MOVE_HINT_SLOT(18) BFME_MOVE_HINT_SLOT(19)
	BFME_MOVE_HINT_SLOT(20) BFME_MOVE_HINT_SLOT(21) BFME_MOVE_HINT_SLOT(22) BFME_MOVE_HINT_SLOT(23)
	BFME_MOVE_HINT_SLOT(24) BFME_MOVE_HINT_SLOT(25)
	virtual UnsignedInt getFrame() = 0;					///< vtable +0x68
};

extern BfmeMoveHintGameClient *TheGameClient;

struct MoveHintStruct
{
	Coord3D pos;											///< entry+0x00
	UnsignedInt frame;										///< entry+0x0C
	Bool m_flag10;											///< entry+0x10
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	enum { MAX_MOVE_HINTS = 25 };

	BFME_MOVE_HINT_SLOT(0) BFME_MOVE_HINT_SLOT(1) BFME_MOVE_HINT_SLOT(2) BFME_MOVE_HINT_SLOT(3)
	BFME_MOVE_HINT_SLOT(4) BFME_MOVE_HINT_SLOT(5) BFME_MOVE_HINT_SLOT(6) BFME_MOVE_HINT_SLOT(7)
	BFME_MOVE_HINT_SLOT(8) BFME_MOVE_HINT_SLOT(9) BFME_MOVE_HINT_SLOT(10) BFME_MOVE_HINT_SLOT(11)
	BFME_MOVE_HINT_SLOT(12) BFME_MOVE_HINT_SLOT(13) BFME_MOVE_HINT_SLOT(14) BFME_MOVE_HINT_SLOT(15)
	BFME_MOVE_HINT_SLOT(16) BFME_MOVE_HINT_SLOT(17) BFME_MOVE_HINT_SLOT(18) BFME_MOVE_HINT_SLOT(19)
	BFME_MOVE_HINT_SLOT(20) BFME_MOVE_HINT_SLOT(21) BFME_MOVE_HINT_SLOT(22) BFME_MOVE_HINT_SLOT(23)
	BFME_MOVE_HINT_SLOT(24) BFME_MOVE_HINT_SLOT(25) BFME_MOVE_HINT_SLOT(26)
	virtual void createMoveHint( const GameMessage *msg );		///< vtable +0x6C
	BFME_MOVE_HINT_SLOT(28) BFME_MOVE_HINT_SLOT(29) BFME_MOVE_HINT_SLOT(30) BFME_MOVE_HINT_SLOT(31)
	BFME_MOVE_HINT_SLOT(32) BFME_MOVE_HINT_SLOT(33) BFME_MOVE_HINT_SLOT(34) BFME_MOVE_HINT_SLOT(35)
	BFME_MOVE_HINT_SLOT(36) BFME_MOVE_HINT_SLOT(37) BFME_MOVE_HINT_SLOT(38) BFME_MOVE_HINT_SLOT(39)
	BFME_MOVE_HINT_SLOT(40) BFME_MOVE_HINT_SLOT(41) BFME_MOVE_HINT_SLOT(42) BFME_MOVE_HINT_SLOT(43)
	BFME_MOVE_HINT_SLOT(44) BFME_MOVE_HINT_SLOT(45) BFME_MOVE_HINT_SLOT(46) BFME_MOVE_HINT_SLOT(47)
	BFME_MOVE_HINT_SLOT(48) BFME_MOVE_HINT_SLOT(49) BFME_MOVE_HINT_SLOT(50) BFME_MOVE_HINT_SLOT(51)
	BFME_MOVE_HINT_SLOT(52) BFME_MOVE_HINT_SLOT(53) BFME_MOVE_HINT_SLOT(54) BFME_MOVE_HINT_SLOT(55)
	BFME_MOVE_HINT_SLOT(56) BFME_MOVE_HINT_SLOT(57) BFME_MOVE_HINT_SLOT(58) BFME_MOVE_HINT_SLOT(59)
	virtual Int getSelectCount() = 0;						///< vtable +0xF0, returns this+0x554
	BFME_MOVE_HINT_SLOT(61) BFME_MOVE_HINT_SLOT(62) BFME_MOVE_HINT_SLOT(63) BFME_MOVE_HINT_SLOT(64)
	virtual BfmeMoveHintDrawable *getFirstSelectedDrawable() = 0;	///< vtable +0x104

protected:
	// Index-checked: retail tests (unsigned)i < 25 on every pass of the loop.
	void resetMoveHint( Int i )
	{
		if( (UnsignedInt)i < MAX_MOVE_HINTS )
		{
			m_moveHint[i].frame = 0;
			m_moveHint[i].m_flag10 = true;
		}
	}

private:
	unsigned char m_unmodelled004[0x34];
	MoveHintStruct m_moveHint[MAX_MOVE_HINTS];				///< this+0x38
	Int m_nextMoveHint;										///< this+0x22C
};

#undef BFME_MOVE_HINT_SLOT

// ?createMoveHint@InGameUI@@UAEXPBVGameMessage@@@Z
void InGameUI::createMoveHint( const GameMessage *msg )
{
	if( getSelectCount() == 1 )
	{
		BfmeMoveHintDrawable *draw = getFirstSelectedDrawable();
		Object *obj = draw ? draw->getObject() : 0;
		if( obj )
		{
			if( obj->isKindOf( BFME_KINDOF_2 ) )
				return;

			//Don't allow move hints to be created if our selected object can't move!
			if( !((const ObjectIsMobileBody *)obj)->isMobile() )
				return;
		}
	}

	Coord3D loc;
	loc.set( &msg->getArgument( 0 )->location );

	if( TheTerrainLogic->terrainSlot20( loc.x, loc.y ) )
		return;
	if( TheTerrainLogic->terrainSlot22( loc.x, loc.y ) )
		return;

	for( Int i = 0; i < MAX_MOVE_HINTS; i++ )
		resetMoveHint( i );

	m_moveHint[ m_nextMoveHint ].frame = TheGameClient->getFrame();
	m_moveHint[ m_nextMoveHint ].pos = loc;
	m_moveHint[ m_nextMoveHint ].m_flag10 = false;

	m_nextMoveHint++;

	// wrap around
	if( m_nextMoveHint == MAX_MOVE_HINTS )
		m_nextMoveHint = 0;
}
