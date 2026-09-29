// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/vendor/stlport
// readable body of ??0BridgeBehavior@@QAE@PAVThing@@PBVModuleData@@@Z: game/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp
// BridgeBehavior::BridgeBehavior at 0x001F3390 (379 B): the Zero Hour body
// verbatim, on BFME's layout. The ZH-header TU above cannot hold it: there
// UpdateModule's constructor is out of line and AudioEventRTS is 0x64 bytes,
// while retail inlines UpdateModule (0 / -1 / -1 at +0x14..+0x1C) and builds
// both sound arrays from 0x70-byte elements.
//
// Layout evidence: the six final vtable stores are the recorded
// ??_7BridgeBehavior@@6B{ObjectModule,BehaviorModuleInterface,UpdateModule,
// BridgeBehaviorInterface,DamageModuleInterface,DieModuleInterface}@@@ at
// +0x00/+0x0C/+0x10/+0x20/+0x24/+0x28. The sound arrays use the recorded
// AudioEventRTS ctor/dtor ILTs (0x0002F153/0x00026F35). The field offsets
// match the matched xfer/onDamage/removeScaffolding bodies
// (m_scaffoldPresent +0x47D, m_scaffoldObjectIDList +0x480).

#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Thing;
class ModuleData;
class Object;
class ObjectCreationList;
class FXList;

enum ObjectID { INVALID_ID = 0 };
typedef std::list<ObjectID> ObjectIDList;

enum { BRIDGE_MAX_TOWERS = 4 };
enum { BODY_PRISTINE = 0, BODYDAMAGETYPE_COUNT = 4 };
enum { MAX_BRIDGE_BODY_FX = 3 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioEventRTS
{
public:
	AudioEventRTS();
	~AudioEventRTS();
private:
	unsigned char m_bfmeData[0x70];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();
private:
	const ModuleData *m_moduleData;
	Object *m_object;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData)
		: ObjectModule(thing, moduleData) {}
	virtual ~BehaviorModule() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: BehaviorModule(thing, moduleData),
		  m_nextCallFrameAndPhase(0), m_indexInLogic(-1), m_updateState(-1) {}
	virtual ~UpdateModule() {}
private:
	UnsignedInt m_nextCallFrameAndPhase;
	Int m_indexInLogic;
	Int m_updateState;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h
class BridgeBehaviorInterface
{
public:
	virtual void setTower();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h
class DamageModuleInterface
{
public:
	virtual void onDamage();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleInterface
{
public:
	virtual void onDie();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h
class BridgeBehavior : public UpdateModule,
					   public BridgeBehaviorInterface,
					   public DamageModuleInterface,
					   public DieModuleInterface
{
public:
	BridgeBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~BridgeBehavior();

private:
	ObjectID m_towerID[BRIDGE_MAX_TOWERS];
	const ObjectCreationList *m_damageToOCL[BODYDAMAGETYPE_COUNT][MAX_BRIDGE_BODY_FX];
	const FXList *m_damageToFX[BODYDAMAGETYPE_COUNT][MAX_BRIDGE_BODY_FX];
	AudioEventRTS m_damageToSound[BODYDAMAGETYPE_COUNT];
	const ObjectCreationList *m_repairToOCL[BODYDAMAGETYPE_COUNT][MAX_BRIDGE_BODY_FX];
	const FXList *m_repairToFX[BODYDAMAGETYPE_COUNT][MAX_BRIDGE_BODY_FX];
	AudioEventRTS m_repairToSound[BODYDAMAGETYPE_COUNT];
	Bool m_fxResolved;
	Bool m_scaffoldPresent;
	ObjectIDList m_scaffoldObjectIDList;
	UnsignedInt m_deathFrame;
};

// ??0BridgeBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
BridgeBehavior::BridgeBehavior( Thing *thing, const ModuleData *moduleData )
							: UpdateModule( thing, moduleData )
{
	Int i;
	m_scaffoldObjectIDList.clear();
	m_scaffoldPresent = false;

	for( i = 0; i < BRIDGE_MAX_TOWERS; ++i )
		m_towerID[ i ] = INVALID_ID;

	m_fxResolved = false;
	for( Int bodyState = BODY_PRISTINE; bodyState < BODYDAMAGETYPE_COUNT; ++bodyState )
	{
		// initialize the fx and ocl lists
		for( i = 0; i < MAX_BRIDGE_BODY_FX; ++i )
		{
			m_damageToOCL[ bodyState ][ i ] = 0;
			m_damageToFX[ bodyState ][ i ] = 0;
			m_repairToOCL[ bodyState ][ i ] = 0;
			m_repairToFX[ bodyState ][ i ] = 0;
		}
	}

	m_deathFrame = 0;
}
