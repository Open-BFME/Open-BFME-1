// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

template <int NUMBITS> class BitFlags
{
public:
	unsigned int m_bits[6];
	bool testSetAndClear( const BitFlags &mustBeSet, const BitFlags &mustBeClear ) const;
};

typedef BitFlags<116> KindOfMaskType;

extern KindOfMaskType KINDOFMASK_NONE;

// The template's inline kind-of test is the one used by CreateCrateDie.  Only
// the override link and mask offset are needed here; the remaining template
// fields stay opaque.
class Overridable
{
public:
	const Overridable *getFinalOverride( void ) const;

	void *m_vptr;
	Overridable *m_nextOverride;
};

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

class AsciiString
{
public:
	AsciiString( const AsciiString &that ) throw();
	~AsciiString() throw();

private:
	void *m_data;
};

struct AsciiStringListNode
{
	AsciiStringListNode *m_next;
	AsciiStringListNode *m_prev;
	AsciiString m_value;
};

class AsciiStringList
{
public:
	AsciiStringListNode *m_node;
};

class CreateCrateDieModuleData;
class AIUpdateInterface;

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

class DieModuleData
{
public:
	unsigned char m_unreconstructed_00[8];
	DieMuxData m_dieMuxData;
	unsigned char m_unreconstructed_09[0x2B];
};

class CreateCrateDieModuleData : public DieModuleData
{
public:
	AsciiStringList m_crateNameList;
};

class GameLogic
{
public:
	Object *findObjectByID( int id );
};

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
	virtual void onDie( const DamageInfo *damageInfo ) = 0;
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
	virtual void onDie( const DamageInfo *damageInfo );

private:
	__declspec(noinline) bool testKillerType( CrateTemplate const *currentCrateData, Object *killer );
	bool testKillerScience( CrateTemplate const *currentCrateData, Object *killer );
};

CreateCrateDie::CreateCrateDie( Thing *thing, const ModuleData *moduleData )
	: DieModule( thing, moduleData )
{
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
