// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

class Thing;
class ModuleData;

template <int NUMBITS> class BitFlags
{
public:
	unsigned int m_bits[6];
	bool testSetAndClear( const BitFlags &mustBeSet, const BitFlags &mustBeClear ) const;
	bool any( void ) const
	{
		for( unsigned int i = 0; i < 6; ++i )
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
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride( void ) const;

	void *m_vptr;
	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
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

	void setOrientation( float angle );
};

enum ScienceType { SCIENCE_INVALID = -1 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
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

#include "ascii_string.h"

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
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

	float getMajorRadius( void ) const
	{
		volatile const float *radius =
			(volatile const float *)( (const unsigned char *)this + 0xBC );
		return *radius;
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
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
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/CrateSystem.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleData
{
public:
	unsigned char m_unreconstructed_00[8];
	DieMuxData m_dieMuxData;
	unsigned char m_unreconstructed_09[0x2B];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateCrateDie.h
class CreateCrateDieModuleData : public DieModuleData
{
public:
	AsciiStringList m_crateNameList;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID( int id );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/CrateSystem.h
class CrateSystem
{
public:
	const CrateTemplate *findCrateTemplate( AsciiString name ) const throw();
};

extern GameLogic *TheGameLogic;
extern CrateSystem *TheCrateSystem;

extern float GetGameLogicRandomValueReal( float min, float max, char *file, int line );

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor();
	ObjectModule( Thing *thing, const ModuleData *moduleData );

protected:
	const ModuleData *getModuleData( void ) const { return *(const ModuleData *const *)( m_data + 0 ); }
	Object *getObject( void ) const { return *(Object *const *)( m_data + 4 ); }

private:
	unsigned char m_data[8];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleInterface
{
public:
	virtual void onDie( const DamageInfo *damageInfo ) = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModule : public ObjectModule,
	public BehaviorModuleInterface,
	public DieModuleInterface
{
public:
	DieModule( Thing *thing, const ModuleData *moduleData )
		: ObjectModule( thing, moduleData )
	{
	}

	const DieModuleData *getDieModuleData( void ) const { return (const DieModuleData *)getModuleData(); }
	bool isDieApplicable( const DamageInfo *damageInfo ) const { return getDieModuleData()->m_dieMuxData.isDieApplicable( getObject(), damageInfo ); }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateCrateDie.h
class CreateCrateDie : public DieModule
{
public:
	CreateCrateDie( Thing *thing, const ModuleData *moduleData );
	virtual void onDie( const DamageInfo *damageInfo );
	const CreateCrateDieModuleData *getCreateCrateDieModuleData( void ) const { return (const CreateCrateDieModuleData *)getModuleData(); }

private:
	__declspec(noinline) bool testKillerType( CrateTemplate const *currentCrateData, Object *killer );
	bool testKillerScience( CrateTemplate const *currentCrateData, Object *killer );
	Object *createCrate( CrateTemplate const *currentCrateData );
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

// ?onDie@CreateCrateDie@@UAEXPBVDamageInfo@@@Z
// Retail 0x00254400. Entered through the DieModuleInterface subobject at +0x10.
void CreateCrateDie::onDie( const DamageInfo *damageInfo )
{
	if( !isDieApplicable( damageInfo ) )
		return;

	CrateTemplate const *currentCrateData = 0;
	Object *killer = TheGameLogic->findObjectByID( damageInfo->in.m_sourceID );
	Object *me = getObject();

	if( killer && killer->getRelationship( me ) == ALLIES )
		return;

	for( AsciiStringListNode *iter = getCreateCrateDieModuleData()->m_crateNameList.m_node->m_next;
			iter != getCreateCrateDieModuleData()->m_crateNameList.m_node;
			iter = iter->m_next )
	{
		currentCrateData = TheCrateSystem->findCrateTemplate( iter->m_value );
		if( currentCrateData )
		{
			float testAgainst = currentCrateData->m_creationChance;
			if( !( GetGameLogicRandomValueReal( 0.0f, 1.0f, (char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Die\\CreateCrateDie.cpp", 112 ) < testAgainst ) )
				continue;

			if( currentCrateData->m_killedByTypeKindof.any() && !testKillerType( currentCrateData, killer ) )
				continue;

			if( ( currentCrateData->m_killerScience != SCIENCE_INVALID ) && !testKillerScience( currentCrateData, killer ) )
				continue;

			Object *crate = createCrate( currentCrateData );
			if( crate )
			{
				if( currentCrateData->m_isOwnedByMaker )
					crate->setTeam( me->getControllingPlayer()->getDefaultTeam() );

				if( killer )
				{
					if( killer->getControllingPlayer() && killer->getControllingPlayer()->getPlayerType() == 1 )
					{
						AIUpdateInterface *ai = killer->getAIUpdateInterface();
						if( ai )
							ai->notifyCrate( crate->getID() );
					}
				}
			}
		}
	}
}

// The following are the narrow views used by CreateCrateDie::createCrate.  They
// preserve the retail object and STL layouts without introducing a second
// canonical class declaration or a new vtable.
struct Coord3D
{
	float x;
	float y;
	float z;
};

typedef int PathfindLayerEnum;
typedef int Bool;
enum { LAYER_GROUND = 1 };

struct CrateCreationNode
{
	CrateCreationNode *m_next;
	CrateCreationNode *m_prev;
	AsciiString m_crateName;
	float m_crateChance;
};

struct FindPositionOptions
{
	FindPositionOptions()
		: flags( 0 ), minRadius( 0.0f ), maxRadius( 0.0f ),
		  startAngle( -99999.9f ), maxZDelta( 1.0e10f ),
		  ignoreObject( 0 ), sourceToPathToDest( 0 ), relationshipObject( 0 )
	{
	}

	int flags;
	float minRadius;
	float maxRadius;
	float startAngle;
	float maxZDelta;
	Object *ignoreObject;
	void *sourceToPathToDest;
	Object *relationshipObject;
};

enum { FPF_IGNORE_ALLY_OR_NEUTRAL_UNITS = 0x00000008 };

struct ObjectStatusMaskType
{
	unsigned int m_bits[3];
};

class Team;
class ThingFactory
{
};

class Drawable
{
};

class ObjectDrawableView
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual Drawable *getDrawable() const = 0;
};

extern ThingFactory *TheThingFactory;
extern float g_bfmeOffsetDF;
extern const char g_Rva0107301CEmptyString[];
extern void j_0000b848();
extern void j_0001214d();
extern void j_00026c4c();
extern void j_00028560();
extern void j_00035e0e();
extern void j_000399a5();
extern void j_0003a1a7();
extern void j_0003a391();
extern void j_0003bdef();
extern void j_0004494a();

typedef int (Object::*ObjectGetLayerCall)() const;
typedef void (Object::*ObjectSetPositionCall)( const Coord3D * );
typedef void (Object::*ObjectSetLayerCall)( PathfindLayerEnum );
typedef void (Thing::*ThingSetOrientationCall)( float );
typedef const ThingTemplate *(ThingFactory::*ThingFactoryFindTemplateCall)( const AsciiString & );
typedef Object *(ThingFactory::*ThingFactoryNewObjectCall)(
	const ThingTemplate *, Team *, const volatile ObjectStatusMaskType &, void * );
typedef void (Drawable::*DrawableSetDecalCall)( int );
typedef void (Drawable::*DrawableSetDecalSizeCall)( float, float );
typedef void (Drawable::*DrawableSetDecalFadeCall)( float, float );
typedef bool (*FindPositionAroundCall)( const Coord3D *, const FindPositionOptions *, Coord3D * );

static __forceinline PathfindLayerEnum createCrateGetLayer( Object *object )
{
	union { void (*raw)(); ObjectGetLayerCall member; } call;
	call.raw = j_0003a391;
	return (object->*call.member)();
}

static __forceinline Drawable *createCrateGetDrawable( Object *object )
{
	return ( (const ObjectDrawableView *)object )->getDrawable();
}

static __forceinline void createCrateSetPosition( Object *object, const Coord3D *position )
{
	union { void (*raw)(); ObjectSetPositionCall member; } call;
	call.raw = j_0003a1a7;
	(object->*call.member)( position );
}

static __forceinline void createCrateSetOrientation( Object *object, float angle )
{
	union { void (*raw)(); ThingSetOrientationCall member; } call;
	call.raw = j_000399a5;
	( ( (Thing *)object )->*call.member )( angle );
}

static __forceinline void createCrateSetLayer( Object *object, PathfindLayerEnum layer )
{
	union { void (*raw)(); ObjectSetLayerCall member; } call;
	call.raw = j_00035e0e;
	(object->*call.member)( layer );
}

static __forceinline const ThingTemplate *createCrateFindTemplate(
	ThingFactory *factory, const AsciiString &name )
{
	union { void (*raw)(); ThingFactoryFindTemplateCall member; } call;
	call.raw = j_00028560;
	return (factory->*call.member)( name );
}

static __forceinline Object *createCrateNewObject(
	ThingFactory *factory, const ThingTemplate *thingTemplate, Team *team,
	const volatile ObjectStatusMaskType &statusBits = ObjectStatusMaskType(),
	void *extra = 0 )
{
	union { void (*raw)(); ThingFactoryNewObjectCall member; } call;
	call.raw = j_0004494a;
	return (factory->*call.member)( thingTemplate, team, statusBits, extra );
}

static __forceinline bool createCrateFindPositionAround(
	const Coord3D *center, const FindPositionOptions *options, Coord3D *result )
{
	union { void (*raw)(); FindPositionAroundCall call; } target;
	target.raw = j_00026c4c;
	return target.call( center, options, result );
}

static __forceinline void createCrateSetDecal( Drawable *drawable, int decal )
{
	union { void (*raw)(); DrawableSetDecalCall member; } call;
	call.raw = j_0001214d;
	(drawable->*call.member)( decal );
}

static __forceinline void createCrateSetDecalSize( Drawable *drawable, float x, float y )
{
	union { void (*raw)(); DrawableSetDecalSizeCall member; } call;
	call.raw = j_0000b848;
	(drawable->*call.member)( x, y );
}

static __forceinline void createCrateSetDecalFade( Drawable *drawable, float target, float rate )
{
	union { void (*raw)(); DrawableSetDecalFadeCall member; } call;
	call.raw = j_0003bdef;
	(drawable->*call.member)( target, rate );
}

// ?createCrate@CreateCrateDie@@AAEPAVObject@@PBVCrateTemplate@@@Z
// Retail 0x00253FF0.  The source and helper sequence are the original
// CreateCrateDie::createCrate implementation; only ABI-neutral typed views are
// used for the already-bound incremental-link thunks.
Object *CreateCrateDie::createCrate( CrateTemplate const *currentCrateData )
{
	CreateCrateDie *self = this;
	PathfindLayerEnum layer = createCrateGetLayer(
		*(Object **)( (unsigned char *)self + 8 ) );
	float multipleCratePick = GetGameLogicRandomValueReal(
		0.0f, 1.0f,
		(char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Die\\CreateCrateDie.cpp",
		167 );
	float multipleCrateRunningTotal = 0.0f;
	AsciiString crateName( g_Rva0107301CEmptyString );

	CrateCreationNode *sentinel =
		(CrateCreationNode *)currentCrateData->m_possibleCrates.m_node;
	for( CrateCreationNode *iter = sentinel->m_next;
			iter != sentinel;
			iter = iter->m_next )
	{
		multipleCrateRunningTotal += iter->m_crateChance;
		if( multipleCrateRunningTotal > multipleCratePick )
		{
			AsciiString const *crateNameSource = &iter->m_crateName;
			crateName = *crateNameSource;
			break;
		}
	}

	const ThingTemplate *crateType = createCrateFindTemplate( TheThingFactory, crateName );
	if( crateType == 0 )
		return 0;

	Object *object = *(Object **)( (unsigned char *)self + 8 );
	Coord3D centerPoint;
	centerPoint.x = *(float *)( (unsigned char *)object + 0x38 );
	centerPoint.y = *(float *)( (unsigned char *)object + 0x3C );
	centerPoint.z = *(float *)( (unsigned char *)object + 0x40 );
	Bool spotFound = 0;
	Coord3D creationPoint;
	FindPositionOptions fpOptions;
	fpOptions.minRadius = 0.0f;
	fpOptions.maxRadius = 5.0f;
	fpOptions.relationshipObject = object;
	fpOptions.flags = FPF_IGNORE_ALLY_OR_NEUTRAL_UNITS;

	if( layer != LAYER_GROUND )
	{
		creationPoint = centerPoint;
		spotFound = true;
	}
	else if( createCrateFindPositionAround( &centerPoint, &fpOptions, &creationPoint ) )
	{
		spotFound = true;
	}
	else
	{
		fpOptions.minRadius = 0.0f;
		fpOptions.maxRadius = 125.0f;
		fpOptions.relationshipObject = 0;
		fpOptions.flags = 0;
		if( createCrateFindPositionAround( &centerPoint, &fpOptions, &creationPoint ) )
			spotFound = true;
	}

	if( spotFound )
	{
		Object *newCrate = createCrateNewObject(
			TheThingFactory, crateType, (Team *)0 );

		createCrateSetPosition( newCrate, &creationPoint );
		( (Thing *)newCrate )->setOrientation( GetGameLogicRandomValueReal(
			0.0f, 2.0f * 3.14159265359f,
			(char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Die\\CreateCrateDie.cpp",
			226 ) );
		createCrateSetLayer( newCrate, layer );

		Drawable *crateDrawable =
			( (const ObjectDrawableView *)newCrate )->getDrawable();
		if( crateDrawable )
		{
			createCrateSetDecal( crateDrawable, 5 );
			union { void (*raw)(); DrawableSetDecalSizeCall member; } decalSizeCall;
			decalSizeCall.raw = j_0000b848;
			( crateDrawable->*decalSizeCall.member )(
				newCrate->getMajorRadius() * g_bfmeOffsetDF,
				newCrate->getMajorRadius() * g_bfmeOffsetDF );
			createCrateSetDecalFade( crateDrawable, 1.0f, 0.03f );
		}

		return newCrate;
	}

	return 0;
}
