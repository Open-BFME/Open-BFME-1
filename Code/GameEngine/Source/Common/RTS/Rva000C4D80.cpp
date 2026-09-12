// Open-BFME: neutral reconstruction of the 195-byte body at 0x000C4D80.
//
// The boundary is FUN_004c4d80 (Ghidra, 195 bytes).  Its matched callers and
// adjacent BFME ActionManager bodies establish the thiscall ABI and the
// Object/ActionObject helper slots.  The final shroud call is to the already
// matched static helper at 0x000C3F80; its retail body uses EDI=source,
// ESI=target and one stack command-source argument.  Keeping that helper
// visible in this TU is what lets MSVC 7.1 reproduce the compiler-private register ABI.
// The owning class/function name remains address-neutral pending a named
// caller or vtable proof.
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;
typedef unsigned char UnsignedByte;

enum Relationship
{
	ENEMIES = 2
};

enum KindOfType
{
	KINDOF_INVALID = -1
};

enum CommandSourceType
{
	CMD_FROM_SCRIPT = 1
};

enum ObjectShroudStatus
{
	OBJECTSHROUD_FOGGED = 3
};

class Player
{
public:
	Int getPlayerIndex() const;
};

class Thing
{
public:
	Bool isAboveTerrainOrWater() const;
};

class Object
{
public:
	Relationship getRelationship( const Object *other ) const;
	Player *getControllingPlayer() const;
	ObjectShroudStatus getShroudedStatus( Int playerIndex ) const;

	char m_unreconstructed00[ 0x90 ];
	UnsignedByte m_status;
	char m_unreconstructed91[ 0x200 - 0x91 ];
	class Rva000C4D80Module *m_module200;
	char m_unreconstructed204[ 0x344 - 0x204 ];
	UnsignedByte m_privateStatus;
};

class BFMEActionObject
{
public:
	Bool testStatus( Int status ) const;
};

class BFMEActionThing
{
public:
	Bool isKindOf( Int kind ) const;
};

class Rva000C4D80Module
{
public:
	virtual void slot0( void );
	virtual void slot1( void );
	virtual void slot2( void );
	virtual void slot3( void );
	virtual float getCurrent( void );
	virtual void slot5( void );
	virtual float getMaximum( void );
};

// This is the same file-static helper shape as the matched body in
// Code/GameEngine/Source/Common/RTS/ActionManager.cpp.  Retail's optimized
// internal-call ABI is visible in its body at 0x000C3F80.
static Bool isObjectShroudedForAction( const Object *source, const Object *target,
	CommandSourceType commandSource )
{
	if (target)
	{
		Int targetID = *reinterpret_cast<const Int *>(reinterpret_cast<const char *>(target) + 0x74);
		if (targetID >= 0x05f5e0fc && targetID <= 0x05f5e0ff)
			return false;
	}

	if (source && target && source->getControllingPlayer())
	{
		if (*reinterpret_cast<const Int *>(reinterpret_cast<const char *>(source->getControllingPlayer()) + 0x2c) == 0 &&
				commandSource != CMD_FROM_SCRIPT &&
				target->getShroudedStatus(source->getControllingPlayer()->getPlayerIndex()) >= OBJECTSHROUD_FOGGED)
			return true;
	}

	return false;
}

class Rva000C4D80Manager
{
public:
	Bool evaluate( Object *obj, const Object *target, Int commandSource );
};

// ?evaluate@Rva000C4D80Manager@@QAE_NPAVObject@@PBV2@H@Z
Bool Rva000C4D80Manager::evaluate( Object *obj, const Object *target, Int commandSource )
{
	if( !obj || !target )
		return false;
	if( obj->getRelationship( target ) != ENEMIES )
		return false;
	if( obj->m_privateStatus & 1 )
		return false;
	if( obj->m_status & 4 )
		return false;
	if( ((const BFMEActionObject *)target)->testStatus( 2 ) )
		return false;
	if( ((const BFMEActionObject *)target)->testStatus( 0x13 ) )
		return false;
	if( ((const BFMEActionThing *)obj)->isKindOf( 0xC ) )
	{
		if( !((const Thing *)obj)->isAboveTerrainOrWater() )
			return false;
		if( !((const BFMEActionThing *)target)->isKindOf( 0x23 ) )
			return false;
	}
	else
	{
		if( !((const BFMEActionThing *)target)->isKindOf( 0x1F ) )
			return false;
	}

	Rva000C4D80Module *module = obj->m_module200;
	float current = module->getCurrent();
	if( current == module->getMaximum() )
		return false;
	if( isObjectShroudedForAction( obj, target, (CommandSourceType)commandSource ) )
		return false;
	return true;
}
