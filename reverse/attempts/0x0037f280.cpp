// ?call@Gen0002B7F6@@QAEXPAVExperienceLevelData@@PAVObject@@_N@Z
// partial score=0.78 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc
// stlport
// BFME ExperienceLevelSystem::update, retail 0x0037F4C0.  The pending list at
// +0x1C holds ObjectID, level-data pointer and effect flag records.  Phase 5
// resolves each live object, applies the record, then clears the list.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>
#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned int ObjectID;
typedef unsigned int NameKeyType;

class AsciiString
{
public:
	void set( const AsciiString &that );

private:
	void *m_data;
};

class ExperienceLevelData;
class ExperienceTracker;
class Module;
class UpgradeTemplate;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;

class ExperienceLevelSystem;

extern void j_00038843();

class BfmeItemRY
{
public:
	void bfmeDoRY( void *first, void *second );
};

class Gen_00283790
{
public:
	void bfmeDispatch( void *key );
};

class BfmeThingVKP
{
public:
	void bfmeSetVKP( Int first, Int second );
};

struct ModelConditionFlags
{
	unsigned int m_bits[ 10 ];
};

class ExperienceLevelData
{
public:
	char m_base[ 0x0c ];
	AsciiString m_name;
	Int m_requiredExperience;
	Int m_experienceAward;
	Int m_experienceAwardOwnGuysDie;
	_STL::vector<AsciiString> m_targetNames;
	_STL::vector<AsciiString> m_attributeModifiers;
	_STL::vector<AsciiString> m_levelUpFx;
	Int m_levelUpOCL;
	_STL::vector<UpgradeTemplate *> m_upgrades;
	ModelConditionFlags m_modelConditionState;
	char m_unmodelledSelectionDecal[ 0x30 ];
	Bool m_showLevelUpTint;
	char m_unmodelledTint[ 0x23 ];
	Int m_rank;
	Bool m_informUpdateModule;
	Bool m_singlePlayerOnly;
	Bool m_multiPlayerOnly;
	Int m_emotionType;
};

typedef char ExperienceLevelDataSizeMustBeD8[
	sizeof( ExperienceLevelData ) == 0xd8 ? 1 : -1];

class ExperienceTracker
{
public:
	void bfmeSetScalarIndex( Int index );

	char m_base[ 8 ];
	AsciiString m_name;
	Int m_unmodelled0c;
	Int m_experience;
	Int m_experienceAwardOwnGuysDie;
	char m_unmodelled18[ 8 ];
	Int m_scalarIndex;
};

class Object
{
public:
	Bool applyAttributeModifier( const AsciiString &name, Int duration );
	void giveUpgrade( const UpgradeTemplate *upgrade );
	Module *findModule( NameKeyType key );
	void bfmeApplySpecialModelCondition( Int condition,
		const void *animation, Int frames );

	char m_pad000[ 0x210 ];
	ExperienceTracker *m_experienceTracker;
	char m_pad214[ 0x344 - 0x214 ];
	unsigned char m_flags344;
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	__forceinline Object *findObjectByID( ObjectID id )
	{
		if ( id == 0 )
			return 0;
		ObjectPtrHash::iterator it = m_objectHash.find( id );
		if ( it == m_objectHash.end() )
			return 0;
		return (*it).second;
	}

	char m_pad000[ 0x3c ];
	unsigned int m_frame;
	char m_pad040[ 0x70 ];
	ObjectPtrHash m_objectHash;
};

extern GameLogic *TheBfmeGameLogic;

struct PendingExperienceLevel
{
	ObjectID m_objectID;
	ExperienceLevelData *m_level;
	Bool m_showEffect;
};

class ExperienceLevelSystem
{
public:
	virtual void update();

	char m_pad[ 0x18 ];
	_STL::list<PendingExperienceLevel> m_pending;
};

typedef void (ExperienceLevelSystem::*ExperienceLevelEffectCall)(
	ExperienceLevelData *, Object *);

union ExperienceLevelEffectCallValue
{
	void (*freeFunction)();
	ExperienceLevelEffectCall memberFunction;
};

class Gen0002B7F6
{
public:
	void call( ExperienceLevelData *level, Object *object, Bool showEffect );
};

void Gen0002B7F6::call( ExperienceLevelData *level, Object *object,
	Bool showEffect )
{
	for ( unsigned int index = 0;
		index < static_cast<unsigned int>(
			level->m_attributeModifiers.end() -
			level->m_attributeModifiers.begin() ); ++index )
	{
		object->applyAttributeModifier(
			level->m_attributeModifiers.begin()[ index ], -1 );
	}

	for ( unsigned int index = 0;
		index < static_cast<unsigned int>(
			level->m_upgrades.end() - level->m_upgrades.begin() ); ++index )
	{
		object->giveUpgrade( level->m_upgrades.begin()[ index ] );
	}

	if ( showEffect && TheBfmeGameLogic->m_frame >= 10 )
	{
		ExperienceLevelEffectCallValue effectCall;
		effectCall.freeFunction = j_00038843;
		(reinterpret_cast<ExperienceLevelSystem *>( this )
			->*effectCall.memberFunction)( level, object );
	}

	((BfmeItemRY *)object)->bfmeDoRY( (void *)0xc7, (void *)0xf );

	ExperienceTracker *tracker = object->m_experienceTracker;
	tracker->m_name.set( level->m_name );
	tracker->m_experience = level->m_experienceAward;
	tracker->m_experienceAwardOwnGuysDie = level->m_experienceAwardOwnGuysDie;
	++tracker->m_scalarIndex;
	tracker->bfmeSetScalarIndex( level->m_rank );

	unsigned int nonzero = 0;
	for ( unsigned int index = 0; index < 10; ++index )
	{
		if ( level->m_modelConditionState.m_bits[ index ] != 0 )
		{
			nonzero = 1;
			break;
		}
	}
	if ( nonzero != 0 )
	{
		ModelConditionFlags clear = {};
		((BfmeThingVKP *)object)->bfmeSetVKP(
			reinterpret_cast<Int>( &clear ),
			reinterpret_cast<Int>( level->m_modelConditionState.m_bits ) );
	}

	Int trueValue = 1;
	if ( level->m_informUpdateModule )
	{
		if ( (*reinterpret_cast<unsigned char *>( 0x012f0894 ) & trueValue) == 0 )
		{
			*reinterpret_cast<unsigned int *>( 0x012f0894 ) |= trueValue;
			NameKeyType key = TheNameKeyGenerator->nameToKey(
				reinterpret_cast<const char *>( 0x010904a4 ) );
			*reinterpret_cast<NameKeyType *>( 0x012f0890 ) = key;
		}

		Module *module = object->findModule(
			*reinterpret_cast<NameKeyType *>( 0x012f0890 ) );
		if ( module != 0 )
			((Gen_00283790 *)module)->bfmeDispatch(
				reinterpret_cast<void *>( level->m_rank ) );
	}

	if ( level->m_emotionType != -1 )
		object->bfmeApplySpecialModelCondition( level->m_emotionType, 0, trueValue );
}

void ExperienceLevelSystem::update()
{
	for ( _STL::list<PendingExperienceLevel>::iterator it = m_pending.begin();
		it != m_pending.end(); ++it )
	{
		Object *object = TheBfmeGameLogic->findObjectByID( (*it).m_objectID );
		if ( object && !(object->m_flags344 & 1) )
			((Gen0002B7F6 *)this)->call(
				(*it).m_level, object, (*it).m_showEffect );
	}

	m_pending.clear();
}
