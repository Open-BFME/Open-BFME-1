// cl: /DNDEBUG /MD /EHsc
// readable body of ??0BattlePlanUpdate@@QAE@PAVThing@@PBVModuleData@@@Z: game/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdate.cpp
// BattlePlanUpdate::BattlePlanUpdate at 0x00286260 (383 B): the Zero Hour body
// on BFME's layout. BFME keeps the pack/unpack sounds as one 16-entry
// AudioEventRTS array (0x70-byte elements, +0x44..+0x744), allocates
// BattlePlanBonuses with plain operator new (0x44 bytes, two memset-cleared
// 192-bit KindOf masks) and orders the members as below. The final vtable
// stores resolve to the recorded ??_7BattlePlanUpdate@@6B{ObjectModule,
// BehaviorModuleInterface,UpdateModule}@@@ addresses.
//
// SpecialPowerUpdateInterface is listed directly as BattlePlanUpdate's second
// base: with ZH's intermediate SpecialPowerUpdateModule class, VC7.1 drops the
// base-chain vtable and UpdateModule field stores that retail keeps (344 vs 383
// bytes), while the flattened list reproduces them exactly.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Thing;
class ModuleData;
class Object;
class ObjectCreationList;
class FXList;

enum ObjectID { INVALID_ID = 0 };

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


typedef float Real;
extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)
// BFME's KindOf mask is a 192-bit bitset; its ctor clears the words with memset.
struct KindOfMaskType { unsigned int m_bits[6]; KindOfMaskType() { memset(m_bits, 0, sizeof(m_bits)); } };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerUpdateModule.h
class SpecialPowerUpdateInterface
{
public:
	virtual void initiateIntentToDoSpecialPower();
};


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BattlePlanUpdate.h
struct BattlePlanBonuses
{
	Real m_armorScalar;
	Int m_bombardment;
	Int m_searchAndDestroy;
	Int m_holdTheLine;
	Real m_sightRangeScalar;
	KindOfMaskType m_validKindOf;
	KindOfMaskType m_invalidKindOf;
};

class BattlePlanUpdateModuleData
{
public:
	unsigned char m_unreconstructed00[0x54];
	KindOfMaskType m_validMemberKindOf;
	KindOfMaskType m_invalidMemberKindOf;
};

class SpecialPowerModule;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BattlePlanUpdate.h
class BattlePlanUpdate : public UpdateModule, public SpecialPowerUpdateInterface
{
public:
	BattlePlanUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~BattlePlanUpdate();
	const BattlePlanUpdateModuleData *getBattlePlanUpdateModuleData() const
	{
		return *(const BattlePlanUpdateModuleData * const *)((const unsigned char *)this + 4);
	}
private:
	Int m_currentPlan;
	Int m_desiredPlan;
	Int m_planAffectingArmy;
	Int m_status;
	UnsignedInt m_nextReadyFrame;
	SpecialPowerModule *m_specialPowerModule;
	Bool m_invalidSettings;
	Bool m_centeringTurret;
	BattlePlanBonuses *m_bonuses;
	AudioEventRTS m_audio[16];
	ObjectID m_visionObjectID;
};

// ??0BattlePlanUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
BattlePlanUpdate::BattlePlanUpdate( Thing *thing, const ModuleData* moduleData ) :
	UpdateModule( thing, moduleData ),
	m_bonuses(0)
{
	const BattlePlanUpdateModuleData *data = getBattlePlanUpdateModuleData();

	m_status = 0;
	m_currentPlan = 0;
	m_desiredPlan = 0;
	m_planAffectingArmy = 0;
	m_nextReadyFrame = 0;
	m_invalidSettings = false;
	m_centeringTurret = false;

	m_bonuses = new BattlePlanBonuses;
	m_bonuses->m_armorScalar = 1.0f;
	m_bonuses->m_sightRangeScalar = 1.0f;
	m_bonuses->m_bombardment = 0;
	m_bonuses->m_searchAndDestroy = 0;
	m_bonuses->m_holdTheLine = 0;
	m_bonuses->m_validKindOf = data->m_validMemberKindOf;
	m_bonuses->m_invalidKindOf = data->m_invalidMemberKindOf;

	m_visionObjectID = INVALID_ID;
	m_specialPowerModule = 0;
}
