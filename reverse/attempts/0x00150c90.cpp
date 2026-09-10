// ?groupDoSpecialPowerAtLocation@AIGroup@@QAEXIPBUCoord3D@@MPBVObject@@I@Z
// partial score=0.88 date=2026-09-09
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::groupDoSpecialPowerAtLocation, retail 0x00150C90, 187 bytes.
//
// The BFME implementation keeps the member-list walk in place, records the
// command options in the member AI interface at +0x48, and dispatches the
// waypoint form of the special power after the ActionManager check.  The
// dispatcher at GameLogic::logicMessageDispatcher names this AIGroup caller.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef float Real;

struct Coord3D;
class Object;
class SpecialPowerTemplate;
class Waypoint;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplateByID( UnsignedInt id );
};

class ActionManager
{
public:
	Bool canDoSpecialPowerAtLocation( const Object *object,
		const Coord3D *location, CommandSourceType commandSource,
		const SpecialPowerTemplate *power, const Object *objectInWay,
		UnsignedInt commandOptions, Bool checkSourceRequirements );
};

class AIUpdateInterface
{
public:
	unsigned char m_beforeField48[0x48];
	UnsignedInt m_field48;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void bfmeAbortActiveSpecialAbilities( void ) const;
	void doSpecialPowerUsingWaypoints( const SpecialPowerTemplate *power,
		const Waypoint *way, UnsignedInt commandOptions, Bool forced );
	void friend_setUndetectedDefector( Bool status );

	unsigned char m_beforeAI[0x204];
	AIUpdateInterface *m_ai;
};

extern SpecialPowerStore *TheSpecialPowerStore;
extern ActionManager *TheActionManager;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void groupDoSpecialPowerAtLocation( UnsignedInt specialPowerID,
		const Coord3D *location, Real angle, const Object *objectInWay,
		UnsignedInt commandOptions );

private:
	virtual ~AIGroup();
	_STL::list<Object *> m_memberList;
};

void AIGroup::groupDoSpecialPowerAtLocation( UnsignedInt specialPowerID,
	const Coord3D *location, Real angle, const Object *objectInWay,
	UnsignedInt commandOptions )
{
	_STL::list<Object *>::iterator i = m_memberList.begin();
	Object *object;
	for( ; i != m_memberList.end(); ++i )
	{
		object = (*i);
		AIUpdateInterface *ai = object->m_ai;
		if( !ai )
			continue;

		ai->m_field48 = commandOptions;
		if( *reinterpret_cast<volatile UnsignedInt *>( &commandOptions ) == 0 )
			object->bfmeAbortActiveSpecialAbilities();

		const SpecialPowerTemplate *spTemplate =
			TheSpecialPowerStore->findSpecialPowerTemplateByID( specialPowerID );
		if( !spTemplate )
			continue;

		if( !TheActionManager->canDoSpecialPowerAtLocation(
			object, location, CMD_FROM_PLAYER, spTemplate,
			reinterpret_cast<const Object *>(
				*reinterpret_cast<const UnsignedInt *>( &angle )),
			reinterpret_cast<UnsignedInt>( objectInWay ), true ) )
			continue;

		object->doSpecialPowerUsingWaypoints( spTemplate,
			reinterpret_cast<const Waypoint *>( location ),
			reinterpret_cast<UnsignedInt>( objectInWay ), false );
		object->friend_setUndetectedDefector( false );
	}
}
