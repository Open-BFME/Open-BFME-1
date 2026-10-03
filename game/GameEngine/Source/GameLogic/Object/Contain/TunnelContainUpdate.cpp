// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// TunnelContain::update (retail 0x0022F570, 164 B).
//
// ZH body verbatim. The five BFME-only facts are TU-local views, not shared
// header edits: Player::m_tunnelSystem at +0x22C, the module data's
// m_framesForFullHeal at +0x168, Object's body module pointer at +0x200, the
// BodyModuleInterface slots getLastDamageInfo/getLastDamageTimestamp at 15/16
// (ZH 18/19), and five logic frames per second.
#include "PreRTS.h"
#include "GameLogic/Module/TunnelContain.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "Common/Player.h"
#include "Common/TunnelTracker.h"

struct Rva0022F570Player
{
	char m_bfmeHead[0x22C];
	TunnelTracker *m_tunnelSystem;
	TunnelTracker *getTunnelSystem( void ) const { return m_tunnelSystem; }
};

struct Rva0022F570ModuleData
{
	char m_bfmeHead[0x168];
	Real m_framesForFullHeal;	// BFME stores the heal rate as a Real
};

struct Rva0022F570Object
{
	char m_bfmeHead[0x200];
	class Rva0022F570Body *m_body;
};

class Rva0022F570Body
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void s13() = 0;
	virtual void s14() = 0;
	virtual const DamageInfo *getLastDamageInfo() const = 0;
	virtual UnsignedInt getLastDamageTimestamp() const = 0;
};

#include <hash_map>

// Retail's GameLogic::findObjectByID is the out-of-line hash lookup at
// 0x0009A510 (hash_map at this+0xB0, buckets at +0xB4); the ZH header's inline m_objVector body is
// not retail's, and the sweep GameLogic.h only declares it. Its body stays
// visible here (as in ObjectEnterUncontrollableCowerState.cpp) so MSVC knows the
// out-of-line call writes no memory and keeps TheGameLogic in a register.
typedef _STL::hash_map<int, Object *, _STL::hash<int>, _STL::equal_to<int> > Rva0022F570ObjectHash;

inline Object *GameLogic::findObjectByID( ObjectID id )
{
	if( id == INVALID_ID )
		return NULL;
	Rva0022F570ObjectHash &hash = *(Rva0022F570ObjectHash *)((char *)this + 0xB0);
	Rva0022F570ObjectHash::iterator it = hash.find( id );
	if( it == hash.end() )
		return NULL;
	return (*it).second;
}

enum { BFME_LOGICFRAMES_PER_SECOND = 5 };

class Rva0022F570TunnelContain : public OpenContain
{
public:
	virtual UpdateSleepTime update( void );	// ?update@TunnelContain@@UAE?AW4UpdateSleepTime@@XZ
};

// ?update@TunnelContain@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime Rva0022F570TunnelContain::update( void )
{
	OpenContain::update();
	const Rva0022F570ModuleData *modData = (const Rva0022F570ModuleData *)getModuleData();
	Object *obj = getObject();
	Player *controllingPlayer = NULL;
	if (obj)
	{
		controllingPlayer = obj->getControllingPlayer();
	}
	if (controllingPlayer)
	{
		TunnelTracker *tunnelSystem = ((Rva0022F570Player *)controllingPlayer)->getTunnelSystem();
		if (tunnelSystem)
		{
			tunnelSystem->healObjects(modData->m_framesForFullHeal);
		}
		Rva0022F570Body *body = ((Rva0022F570Object *)obj)->m_body;
		if (body) {
			const DamageInfo *info = body->getLastDamageInfo();
			if (info) {
				if (body->getLastDamageTimestamp() + BFME_LOGICFRAMES_PER_SECOND > TheGameLogic->getFrame()) {
					ObjectID attackerID = info->in.m_sourceID;
					Object *attacker = TheGameLogic->findObjectByID(attackerID);
					if( attacker )
					{
						if (obj->getRelationship(attacker) == ENEMIES) {
							tunnelSystem->updateNemesis(attacker);
						}
					}
				}
			}
		}
	}
	return UPDATE_SLEEP_NONE;
}
