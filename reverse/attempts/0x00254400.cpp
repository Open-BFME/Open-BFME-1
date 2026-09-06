// ?d_00254400@@YAXXZ
// partial score=0.68 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// stlport

#include <list>

class Thing;
class ModuleData;

template <int NUMBITS> class BitFlags
{
public:
	unsigned int m_bits[6];
	bool testSetAndClear( const BitFlags &mustBeSet, const BitFlags &mustBeClear ) const;
	bool anySet( void ) const
	{
		for( int i = 0; i < 6; ++i )
			if( m_bits[i] != 0 )
				return true;
		return false;
	}
};

typedef BitFlags<116> KindOfMaskType;

extern KindOfMaskType KINDOFMASK_NONE;

// The template's inline kind-of test is the one used by CreateCrateDie.  Only
// the override link and mask offset are needed here; the remaining template
// fields stay opaque.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride( void ) const;

	void *m_vptr;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed_008[0xC0];
	KindOfMaskType m_kindOf;

	bool isKindOfMulti( const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear ) const
	{
		return m_kindOf.testSetAndClear( mustBeSet, mustBeClear );
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	void *m_vptr;
	ThingTemplate *m_template;

	const ThingTemplate *getTemplate( void ) const
	{
		const Overridable *tmpl = (const Overridable *)m_template;
		if( tmpl != 0 && tmpl->m_nextOverride != 0 )
			tmpl = tmpl->m_nextOverride->getFinalOverride();
		return (const ThingTemplate *)tmpl;
	}
};

enum ScienceType { SCIENCE_INVALID = -1 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	bool hasScience( ScienceType t ) const;			///< ILT 0x0000943F -> 0x000CE340

	void *getDefaultTeam( void ) const
	{
		return *(void *const *)( (const unsigned char *)this + 0x230 );
	}

	int getPlayerType( void ) const
	{
		return *(const int *)( (const unsigned char *)this + 0x2C );
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const AsciiString &that ) throw();
	~AsciiString() throw();

private:
	void *m_data;
};

typedef std::list<AsciiString> AsciiStringList;
typedef std::list<AsciiString>::const_iterator AsciiStringListConstIterator;

class CreateCrateDieModuleData;
class AIUpdateInterface;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfo
{
	public:
	unsigned char m_unreconstructed_00[8];
	struct In
	{
		int m_sourceID;
	} in;
};

enum Relationship
{
	ALLIES = 2
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Player *getControllingPlayer( void ) const;		///< ILT 0x00020824 -> 0x001BE3F0
	Relationship getRelationship( const Object *that ) const;

	AIUpdateInterface *getAIUpdateInterface( void ) const
	{
		return *(AIUpdateInterface *const *)( (const unsigned char *)this + 0x204 );
	}

	int getID( void ) const
	{
		return *(const int *)( (const unsigned char *)this + 0x74 );
	}

	void setTeam( void *team )
	{
		struct SetTeamVTable
		{
			virtual void slot00(); virtual void slot04(); virtual void slot08();
			virtual void slot0C(); virtual void slot10(); virtual void slot14();
			virtual void slot18(); virtual void slot1C(); virtual void slot20();
			virtual void slot24(); virtual void slot28(); virtual void slot2C();
			virtual void slot30(); virtual void slot34(); virtual void slot38();
			virtual void slot3C(); virtual void slot40(); virtual void slot44();
			virtual void slot48(); virtual void slot4C(); virtual void slot50( void * );
		};
		((SetTeamVTable *)this)->slot50( team );
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void notifyCrate( int id )
	{
		*(int *)( (unsigned char *)this + 0x218 ) = id;
	}
};

// Only the one field this function reads is reconstructed. m_killerScience is
// at +0x30 because that is the offset the caller-side load uses -- the template
// pointer arrives as the first argument and is dereferenced there directly.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/CrateSystem.h
class CrateTemplate
{
public:
	void *m_baseVptr;
	unsigned char m_baseData[8];
	AsciiString m_name;
	float m_creationChance;
	int m_veterancyLevel;
	KindOfMaskType m_killedByTypeKindof;
	ScienceType m_killerScience;					///< retail this+0x30
	AsciiStringList m_possibleCrates;
	unsigned char m_isOwnedByMaker;				///< retail this+0x38
};

class DieMuxData
{
public:
	bool isDieApplicable( const Object *object, const DamageInfo *damageInfo ) const;

private:
	unsigned char m_unreconstructed[1];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleData
{
public:
	unsigned char m_unreconstructed_00[8];
	DieMuxData m_dieMuxData;
	unsigned char m_unreconstructed_09[0x2B];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateCrateDie.h
class CreateCrateDieModuleData : public DieModuleData
{
public:
	AsciiStringList m_crateNameList;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID( int id );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/CrateSystem.h
class CrateSystem
{
public:
	const CrateTemplate *findCrateTemplate( AsciiString name ) const throw();
};

extern GameLogic *TheGameLogic;
extern CrateSystem *TheCrateSystem;

extern float GetGameLogicRandomValueReal( float min, float max, char *file, int line );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor();
	ObjectModule( Thing *thing, const ModuleData *moduleData );

protected:
	Object *getObject( void ) const { return m_obj; }
	const ModuleData *getModuleData( void ) const { return m_moduleData; }

private:
	const ModuleData *m_moduleData;
	Object *m_obj;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class BehaviorModule : public ObjectModule,
	public BehaviorModuleInterface
{
public:
	BehaviorModule( Thing *thing, const ModuleData *moduleData )
		: ObjectModule( thing, moduleData )
	{
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleInterface
{
public:
	virtual void onDie( const DamageInfo *damageInfo ) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModule : public BehaviorModule,
	public DieModuleInterface
{
public:
	const DieModuleData *getDieModuleData( void ) const
	{
		return (const DieModuleData *)getModuleData();
	}

	bool isDieApplicable( const DamageInfo *damageInfo ) const
	{
		return getDieModuleData()->m_dieMuxData.isDieApplicable( getObject(), damageInfo );
	}

	DieModule( Thing *thing, const ModuleData *moduleData )
		: BehaviorModule( thing, moduleData )
	{
	}

	virtual void onDie( const DamageInfo *damageInfo ) = 0;

};

class CreateCrateDiePrimary : public ObjectModule
{
public:
	bool testKillerType( CrateTemplate const *currentCrateData, Object *killer );
	Object *createCrate( CrateTemplate const *currentCrateData );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateCrateDie.h
class CreateCrateDie : public DieModule
{
public:
	CreateCrateDie( Thing *thing, const ModuleData *moduleData );
	virtual void onDie( const DamageInfo *damageInfo );

	const CreateCrateDieModuleData *getCreateCrateDieModuleData( void ) const
	{
		return (const CreateCrateDieModuleData *)getModuleData();
	}

private:
	bool testCreationChance( CrateTemplate const *currentCrateData )
	{
		float testAgainst = currentCrateData->m_creationChance;
		return GetGameLogicRandomValueReal( 0.0f, 1.0f,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Die\\CreateCrateDie.cpp",
			112 ) < testAgainst;
	}

	Object *createCrate( CrateTemplate const *currentCrateData );
	__declspec(noinline) bool testKillerType( CrateTemplate const *currentCrateData, Object *killer );
	bool testKillerScience( CrateTemplate const *currentCrateData, Object *killer );
};

CreateCrateDie::CreateCrateDie( Thing *thing, const ModuleData *moduleData )
	: DieModule( thing, moduleData )
{
}

// ?onDie@CreateCrateDie@@UAEXPBUDamageInfo@@@Z
// Retail 0x00254400. The implementation enters through the DieModuleInterface
// subobject, so the object and module-data pointers sit at this-0x08 and
// this-0x0c respectively.
void CreateCrateDie::onDie( const DamageInfo *damageInfo )
{
	if( !isDieApplicable( damageInfo ) )
		return;

	CrateTemplate const *currentCrateData = 0;
	Object *killer = TheGameLogic->findObjectByID( damageInfo->in.m_sourceID );
	Object *me = getObject();

	if( killer && killer->getRelationship( me ) == ALLIES )
		return;

	for( AsciiStringListConstIterator iter =
			getCreateCrateDieModuleData()->m_crateNameList.begin();
		iter != getCreateCrateDieModuleData()->m_crateNameList.end(); ++iter )
	{
		currentCrateData = TheCrateSystem->findCrateTemplate( *iter );
		if( currentCrateData == 0 )
			continue;

		float testAgainst = currentCrateData->m_creationChance;
		if( !(GetGameLogicRandomValueReal( 0.0f, 1.0f,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Die\\CreateCrateDie.cpp",
			112 ) < testAgainst) )
			continue;

		if( currentCrateData->m_killedByTypeKindof.anySet() &&
			!((CreateCrateDiePrimary *)this)
				->testKillerType( currentCrateData, killer ) )
			continue;

		if( currentCrateData->m_killerScience != SCIENCE_INVALID &&
			!testKillerScience( currentCrateData, killer ) )
			continue;

		Object *crate = ((CreateCrateDiePrimary *)this)
			->createCrate( currentCrateData );
		if( crate == 0 )
			continue;

		if( currentCrateData->m_isOwnedByMaker )
			crate->setTeam( me->getControllingPlayer()->getDefaultTeam() );

		if( killer )
		{
			Player *killerPlayer = killer->getControllingPlayer();
			if( killerPlayer && killerPlayer->getPlayerType() == 1 )
			{
				AIUpdateInterface *ai = killer->getAIUpdateInterface();
				if( ai )
					ai->notifyCrate( crate->getID() );
			}
		}

	}
}

class CreateCrateDieOnDieProbe : public ObjectModule,
	public BehaviorModuleInterface,
	public DieModuleInterface
{
public:
	virtual void onDie( const DamageInfo *damageInfo );
};

void CreateCrateDieOnDieProbe::onDie( const DamageInfo *damageInfo )
{
	if( !(*(const DieModuleData **)((const unsigned char *)this - 0xc))
			->m_dieMuxData.isDieApplicable(
				*(const Object **)((const unsigned char *)this - 8), damageInfo ) )
		return;

	CrateTemplate const *currentCrateData = 0;
	Object *killer = TheGameLogic->findObjectByID( damageInfo->in.m_sourceID );
	Object *me = *(Object **)((unsigned char *)this - 8);
	if( killer && killer->getRelationship( me ) == ALLIES )
		return;

	for( AsciiStringListConstIterator iter =
			((AsciiStringList *)((unsigned char *)*(const void **)(
				(const unsigned char *)this - 0xc) + 0x34))->begin();
			iter != ((AsciiStringList *)((unsigned char *)*(const void **)(
				(const unsigned char *)this - 0xc) + 0x34))->end(); iter++ )
	{
		currentCrateData = TheCrateSystem->findCrateTemplate( *iter );
		if( currentCrateData == 0 )
			continue;
		float testAgainst = currentCrateData->m_creationChance;
		if( !(GetGameLogicRandomValueReal( 0.0f, 1.0f,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Die\\CreateCrateDie.cpp",
			112 ) < testAgainst) )
			continue;
		if( currentCrateData->m_killedByTypeKindof.anySet() &&
			!((CreateCrateDiePrimary *)((unsigned char *)this - 0x10))->testKillerType(
				currentCrateData, killer ) )
			continue;
		if( currentCrateData->m_killerScience != SCIENCE_INVALID &&
			(!killer || !killer->getControllingPlayer() ||
				!killer->getControllingPlayer()->hasScience( currentCrateData->m_killerScience )) )
			continue;
		Object *crate = ((CreateCrateDiePrimary *)((unsigned char *)this - 0x10))->createCrate(
			currentCrateData );
		if( crate == 0 )
			continue;
		if( currentCrateData->m_isOwnedByMaker )
			crate->setTeam( me->getControllingPlayer()->getDefaultTeam() );
		if( killer )
		{
			Player *killerPlayer = killer->getControllingPlayer();
			if( killerPlayer && killerPlayer->getPlayerType() == 1 )
			{
				AIUpdateInterface *ai = killer->getAIUpdateInterface();
				if( ai )
					ai->notifyCrate( crate->getID() );
			}
		}
	}
}

// ?testKillerType@CreateCrateDie@@AAE_NPBVCrateTemplate@@PAVObject@@@Z
// Retail 0x002543B0.  The kind-of mask is six dwords at template+0x18;
// ThingTemplate's inline test forwards it to the landed BitFlags helper.
bool CreateCrateDie::testKillerType( CrateTemplate const *currentCrateData, Object *killer )
{
	if( killer == 0 )
		return false;

	if( ! killer->getTemplate()->isKindOfMulti(
			currentCrateData->m_killedByTypeKindof,
			KINDOFMASK_NONE ) )
		return false;

	return true;
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
