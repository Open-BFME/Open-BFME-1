// ?groupDoSpecialPowerAtLocation@Rva00150C90AIGroup@@QAEXIPBUCoord3D@@MPBVObject@@I@Z
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: special-power-at-location group dispatch, retail RVA 0x00150C90
// (187 B, ret 0x14), reached from GameLogic::logicMessageDispatcher. The walk
// matches Zero Hour's AIGroup::groupDoSpecialPowerAtLocation over the member
// list at this+0x04, but BFME records the last argument in each member's AI
// interface at +0x48 (when it has one), cancels active abilities when it is
// zero, and issues the waypoint form of the power. The ILT window contradicts
// AIGroup as the owner name, so the class keeps the address token, as at
// 0x00152110.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

#include "../../../Include/Common/ScalarTypes.h"



struct Coord3D;
class Object;
class SpecialPowerTemplate;
class Waypoint;

#include "../command_source_type.h"




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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class Rva00150C90AIGroup
{
public:
	void groupDoSpecialPowerAtLocation( UnsignedInt specialPowerID,
		const Coord3D *location, Real angle, const Object *objectInWay,
		UnsignedInt commandOptions );

private:
	virtual ~Rva00150C90AIGroup();
	_STL::list<Object *> m_memberList;
};

void Rva00150C90AIGroup::groupDoSpecialPowerAtLocation( UnsignedInt specialPowerID,
	const Coord3D *location, Real angle, const Object *objectInWay,
	UnsignedInt commandOptions )
{
	_STL::list<Object *>::iterator i;
	for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
	{
		Object *object = (*i);
		AIUpdateInterface *ai = object->m_ai;
		if( ai )
			ai->m_field48 = commandOptions;
		if( commandOptions == 0 )
			object->bfmeAbortActiveSpecialAbilities();

		const SpecialPowerTemplate *spTemplate =
			TheSpecialPowerStore->findSpecialPowerTemplateByID( specialPowerID );
		if( spTemplate )
		{
			if( TheActionManager->canDoSpecialPowerAtLocation(
				object, location, CMD_FROM_PLAYER, spTemplate,
				reinterpret_cast<const Object *>(
					*reinterpret_cast<const UnsignedInt *>( &angle )),
				reinterpret_cast<UnsignedInt>( objectInWay ), true ) )
			{
				object->doSpecialPowerUsingWaypoints( spTemplate,
					reinterpret_cast<const Waypoint *>( location ),
					reinterpret_cast<UnsignedInt>( objectInWay ), false );
				object->friend_setUndetectedDefector( false );
			}
		}
	}
}
