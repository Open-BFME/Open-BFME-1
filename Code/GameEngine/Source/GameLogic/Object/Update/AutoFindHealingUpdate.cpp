// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoFindHealingUpdate.h
class AutoFindHealingUpdateModuleData
{
	friend class AutoFindHealingUpdate;

	virtual void virtualAnchor( void ) = 0;
	unsigned int m_padding;
	unsigned int m_first;
	unsigned int m_second;
	float m_searchDelay;
	float m_searchRange;

public:
	AutoFindHealingUpdateModuleData( void );
};

AutoFindHealingUpdateModuleData::AutoFindHealingUpdateModuleData( void )
{
	m_first = 0;
	m_second = 0;
	m_searchDelay = 0.95f;
	m_searchRange = 0.25f;
}

//-------------------------------------------------------------------------------------------------
// update() (0x002817B0). Local, offset-driven replica of the retail layout -- see the
// packet notes: fields are read through raw pointer offsets rather than modeled as real
// C++ base classes, since update() is reached through a secondary (non-primary) vtable
// slot and the compiler bakes negative-offset field reads directly into the function body.
//-------------------------------------------------------------------------------------------------

class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer( void ) const;
};

// AICommandInterface subobject reached at ai+0x20; aiGetHealed is a direct (non-virtual)
// call at a fixed retail address.
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI			= 2,
	CMD_FROM_DOZER	= 3
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiGetHealed( Object *obj, CommandSourceType cmdSource );
};

// Vtable-shape-only stubs: only the slot COUNT before the real method matters, not the
// interfaces' true contents, since we never construct or size these -- only call through
// pointers already held by the object.
class BodyModuleInterface_VT
{
public:
	virtual void _pad0( void ) = 0;
	virtual void _pad1( void ) = 0;
	virtual void _pad2( void ) = 0;
	virtual void _pad3( void ) = 0;
	virtual float getHealth( void ) = 0;			// slot 4 -> vtable+0x10
	virtual void _pad5( void ) = 0;
	virtual float getMaxHealth( void ) = 0;	// slot 6 -> vtable+0x18
};

class AIUpdateInterface_VT
{
public:
	virtual void _pad0( void ) = 0;
	virtual void _pad1( void ) = 0;
	virtual void _pad2( void ) = 0;
	virtual void _pad3( void ) = 0;
	virtual void _pad4( void ) = 0;
	virtual void _pad5( void ) = 0;
	virtual void _pad6( void ) = 0;
	virtual void _pad7( void ) = 0;
	virtual void _pad8( void ) = 0;
	virtual void _pad9( void ) = 0;
	virtual void _pad10( void ) = 0;
	virtual void _pad11( void ) = 0;
	virtual void _pad12( void ) = 0;
	virtual void _pad13( void ) = 0;
	virtual void _pad14( void ) = 0;
	virtual void _pad15( void ) = 0;
	virtual void _pad16( void ) = 0;
	virtual void _pad17( void ) = 0;
	virtual void _pad18( void ) = 0;
	virtual void _pad19( void ) = 0;
	virtual void _pad20( void ) = 0;
	virtual void _pad21( void ) = 0;
	virtual void _pad22( void ) = 0;
	virtual void _pad23( void ) = 0;
	virtual void _pad24( void ) = 0;
	virtual void _pad25( void ) = 0;
	virtual void _pad26( void ) = 0;
	virtual void _pad27( void ) = 0;
	virtual void _pad28( void ) = 0;
	virtual void _pad29( void ) = 0;
	virtual void _pad30( void ) = 0;
	virtual void _pad31( void ) = 0;
	virtual void _pad32( void ) = 0;
	virtual void _pad33( void ) = 0;
	virtual void _pad34( void ) = 0;
	virtual void _pad35( void ) = 0;
	virtual void _pad36( void ) = 0;
	virtual void _pad37( void ) = 0;
	virtual void _pad38( void ) = 0;
	virtual void _pad39( void ) = 0;
	virtual void _pad40( void ) = 0;
	virtual void _pad41( void ) = 0;
	virtual void _pad42( void ) = 0;
	virtual void _pad43( void ) = 0;
	virtual void _pad44( void ) = 0;
	virtual void _pad45( void ) = 0;
	virtual void _pad46( void ) = 0;
	virtual void _pad47( void ) = 0;
	virtual void _pad48( void ) = 0;
	virtual void _pad49( void ) = 0;
	virtual void _pad50( void ) = 0;
	virtual void _pad51( void ) = 0;
	virtual void _pad52( void ) = 0;
	virtual void _pad53( void ) = 0;
	virtual void _pad54( void ) = 0;
	virtual void _pad55( void ) = 0;
	virtual void _pad56( void ) = 0;
	virtual void _pad57( void ) = 0;
	virtual void _pad58( void ) = 0;
	virtual void _pad59( void ) = 0;
	virtual void _pad60( void ) = 0;
	virtual void _pad61( void ) = 0;
	virtual void _pad62( void ) = 0;
	virtual void _pad63( void ) = 0;
	virtual void _pad64( void ) = 0;
	virtual void _pad65( void ) = 0;
	virtual void _pad66( void ) = 0;
	virtual void _pad67( void ) = 0;
	virtual void _pad68( void ) = 0;
	virtual void _pad69( void ) = 0;
	virtual void _pad70( void ) = 0;
	virtual void _pad71( void ) = 0;
	virtual void _pad72( void ) = 0;
	virtual void _pad73( void ) = 0;
	virtual void _pad74( void ) = 0;
	virtual void _pad75( void ) = 0;
	virtual void _pad76( void ) = 0;
	virtual void _pad77( void ) = 0;
	virtual void _pad78( void ) = 0;
	virtual void _pad79( void ) = 0;
	virtual void _pad80( void ) = 0;
	virtual void _pad81( void ) = 0;
	virtual void _pad82( void ) = 0;
	virtual void _pad83( void ) = 0;
	virtual void _pad84( void ) = 0;
	virtual void _pad85( void ) = 0;
	virtual void _pad86( void ) = 0;
	virtual void _pad87( void ) = 0;
	virtual void _pad88( void ) = 0;
	virtual void _pad89( void ) = 0;
	virtual void _pad90( void ) = 0;
	virtual void _pad91( void ) = 0;
	virtual void _pad92( void ) = 0;
	virtual void _pad93( void ) = 0;
	virtual void _pad94( void ) = 0;
	virtual void _pad95( void ) = 0;
	virtual bool isIdle( void ) = 0;					// slot 96 -> vtable+0x180
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoFindHealingUpdate.h
class AutoFindHealingUpdate
{
public:
	virtual UpdateSleepTime update( void );
	Object *scanClosestTarget( void );	// present-unmatched elsewhere; pinned at 0x36787
};

UpdateSleepTime AutoFindHealingUpdate::update( void )
{
	char *rawThis = reinterpret_cast<char *>( this );

	// this-0x8: owning Object*, cached by the caller's Module base before the
	// secondary (UpdateModuleInterface) vtable slot that 'this' points at.
	Object *obj = *reinterpret_cast<Object **>( rawThis - 0x8 );

	// obj->getControllingPlayer()->getPlayerType(): getPlayerType() is a plain field
	// read of the enum at Player+0x2c; PLAYER_HUMAN == 0.
	Player *controller = obj->getControllingPlayer();
	int playerType = *reinterpret_cast<int *>( reinterpret_cast<char *>( controller ) + 0x2c );
	if( playerType == 0 )
	{
		return UPDATE_SLEEP_NONE;
	}

	// this-0xc: cached ModuleData*.
	AutoFindHealingUpdateModuleData *data =
		*reinterpret_cast<AutoFindHealingUpdateModuleData **>( rawThis - 0xc );

	int *nextScanFrames = reinterpret_cast<int *>( rawThis + 0x10 );
	if( *nextScanFrames > 0 )
	{
		( *nextScanFrames )--;
		return UPDATE_SLEEP_NONE;
	}
	*nextScanFrames = data->m_first;

	AIUpdateInterface_VT *ai =
		*reinterpret_cast<AIUpdateInterface_VT **>( reinterpret_cast<char *>( obj ) + 0x204 );
	if( ai == 0 )
	{
		return UPDATE_SLEEP_NONE;
	}

	BodyModuleInterface_VT *body =
		*reinterpret_cast<BodyModuleInterface_VT **>( reinterpret_cast<char *>( obj ) + 0x200 );
	if( body == 0 )
	{
		return UPDATE_SLEEP_NONE;
	}

	if( body->getHealth() > body->getMaxHealth() * data->m_searchDelay )
	{
		return UPDATE_SLEEP_NONE;
	}

	if( !ai->isIdle() )
	{
		return UPDATE_SLEEP_NONE;
	}

	// scanClosestTarget() is reached at the primary (this-0x10) representation of the
	// object, not the UpdateModuleInterface slot 'this' points at here.
	AutoFindHealingUpdate *primaryThis =
		reinterpret_cast<AutoFindHealingUpdate *>( rawThis - 0x10 );
	Object *healUnit = primaryThis->scanClosestTarget();
	if( healUnit != 0 )
	{
		AICommandInterface *cmd =
			reinterpret_cast<AICommandInterface *>( reinterpret_cast<char *>( ai ) + 0x20 );
		cmd->aiGetHealed( healUnit, CMD_FROM_AI );
	}

	return UPDATE_SLEEP_NONE;
}
