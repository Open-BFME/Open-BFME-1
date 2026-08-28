// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

enum ScienceType { SCIENCE_INVALID = -1 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	bool hasScience( ScienceType t ) const;			///< ILT 0x0000943F -> 0x000CE340
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer( void ) const;		///< ILT 0x00020824 -> 0x001BE3F0
};

// Only the one field this function reads is reconstructed. m_killerScience is
// at +0x30 because that is the offset the caller-side load uses -- the template
// pointer arrives as the first argument and is dereferenced there directly.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/CrateSystem.h
class CrateTemplate
{
public:
	unsigned char m_unreconstructed_00[0x30];
	ScienceType m_killerScience;					///< retail this+0x30
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor();
	ObjectModule( Thing *thing, const ModuleData *moduleData );

private:
	unsigned char m_data[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleInterface
{
public:
	virtual void dieModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModule : public ObjectModule,
	public BehaviorModuleInterface,
	public DieModuleInterface
{
public:
	DieModule( Thing *thing, const ModuleData *moduleData )
		: ObjectModule( thing, moduleData )
	{
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateCrateDie.h
class CreateCrateDie : public DieModule
{
public:
	CreateCrateDie( Thing *thing, const ModuleData *moduleData );

private:
	bool testKillerScience( CrateTemplate const *currentCrateData, Object *killer );
};

CreateCrateDie::CreateCrateDie( Thing *thing, const ModuleData *moduleData )
	: DieModule( thing, moduleData )
{
}

// ?testKillerScience@CreateCrateDie@@AAE_NPBVCrateTemplate@@PAVObject@@@Z
// Retail 0x00253DB0. A member that never touches `this` -- ecx is overwritten
// with the killer on the first instruction -- which is exactly what the Zero
// Hour body is.
bool CreateCrateDie::testKillerScience( CrateTemplate const *currentCrateData, Object *killer )
{
	if( killer == 0 )
		return false;

	// killer's player must have the listed science
	Player *killerPlayer = killer->getControllingPlayer();

	if( killerPlayer == 0 )
		return false;

	if( ! killerPlayer->hasScience( currentCrateData->m_killerScience ) )
		return false;

	return true;
}
