// ?findClosestEnemy@AI@@QAEPAVObject@@PBV2@MIPBVAttackPriorityInfo@@PAVPartitionFilter@@@Z
// partial score=0.38 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "PreRTS.h"

#include "Common/AsciiString.h"
#include "Common/Player.h"
#include "GameLogic/AI.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/ScriptEngine.h"

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

#include <math.h>

#pragma warning(disable:4234)

class AssistedTargetingObjectShim
{
public:
	Bool check();
};

struct BfmeNoArgBoolCall { Bool call(); };
struct BfmeNoArgPlayerCall { Player *call(); };
struct BfmeNoArgInfoCall { const AttackPriorityInfo *call(); };
struct BfmeNoArgThingCall { void *call(); };
struct BfmePriorityCall { Int call(const void *thing); };
struct BfmeFinalCall { void *call(); };
struct BfmeMeleeCall { Object *call(int mode); };
struct BfmeDistanceCall { Real call(const Object *other); };
struct BfmeFindModuleCall { void *call(unsigned int key); };
struct BfmeKindOfCall { Bool call(int kind); };
struct BfmeAskCall { Bool call(Object *object); };
struct BfmeAcceptSourceCall { Bool call(Int first, Int second); };
struct BfmeAcceptCall { Bool call(const Object *source, const void *target, Bool possible); };
struct BfmeAppendCall { void call(void *filter); };
struct BfmeRejectCall { void call(const Object *object); };
struct BfmeStealthCall { void call(const Object *object, int allow); };
struct BfmePairCall { void call(unsigned int *first, void *second); };
struct BfmeReleaseCall { void call(); };
struct BfmeNameKeyCall { unsigned int nameToKey(const char *name); };

extern void j_00001fd7(void);
extern void j_000022bb(void);
extern void j_000051be(void);
extern void j_000084b8(void);
extern void j_00009c41(void);
extern void j_0000b59b(void);
extern void j_0000faa6(void);
extern void j_0001641e(void);
extern void j_0001b347(void);
extern void j_00020824(void);
extern void j_0002ae23(void);
extern void j_0002c471(void);
extern void j_00032b46(void);
extern void j_000382fd(void);
extern void j_00043ced(void);
extern void j_00046a97(void);
extern void j_0003251f(void);
extern void d_004a5950(void);
extern void d_0043add7(void);
extern void d_009f2a70(void);
extern void d_009f2ae0(void);

static __forceinline Bool bfmeIsAbleToAttack(const Object *object)
{
	return reinterpret_cast<AssistedTargetingObjectShim *>(const_cast<Object *>(object))->check();
}

static __forceinline Player *bfmeControllingPlayer(const Object *object)
{
	typedef Player *(BfmeNoArgPlayerCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00020824;
	return (reinterpret_cast<BfmeNoArgPlayerCall *>(const_cast<Object *>(object))->*fn.member)();
}

static __forceinline const AttackPriorityInfo *bfmeDefaultAttackInfo(void)
{
	typedef const AttackPriorityInfo *(BfmeNoArgInfoCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0000b59b;
	void *scriptEngine = *(void **)0x012F076C;
	return (reinterpret_cast<BfmeNoArgInfoCall *>(scriptEngine)->*fn.member)();
}

static __forceinline void *bfmeGetThing(const Object *object)
{
	typedef void *(BfmeNoArgThingCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000084b8;
	return (reinterpret_cast<BfmeNoArgThingCall *>(const_cast<Object *>(object))->*fn.member)();
}

static __forceinline Int bfmeGetPriority(const AttackPriorityInfo *info, const void *thing)
{
	typedef Int (BfmePriorityCall::*Function)(const void *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001641e;
	return (reinterpret_cast<BfmePriorityCall *>(const_cast<AttackPriorityInfo *>(info))->*fn.member)(thing);
}

static __forceinline void *bfmeFinalOverride(void *thing)
{
	typedef void *(BfmeFinalCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000022bb;
	return (reinterpret_cast<BfmeFinalCall *>(thing)->*fn.member)();
}

static __forceinline Object *bfmeResolveMeleeTarget(Object *object)
{
	typedef Object *(BfmeMeleeCall::*Function)(int);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0000faa6;
	return (reinterpret_cast<BfmeMeleeCall *>(object)->*fn.member)(0);
}

static __forceinline Real bfmeDistanceSquared(const Object *me, const Object *other)
{
	typedef Real (BfmeDistanceCall::*Function)(const Object *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00043ced;
	return (reinterpret_cast<BfmeDistanceCall *>(const_cast<Object *>(me))->*fn.member)(other);
}

static __forceinline void *bfmeFindModule(Object *object, unsigned int key)
{
	typedef void *(BfmeFindModuleCall::*Function)(unsigned int);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0002ae23;
	return (reinterpret_cast<BfmeFindModuleCall *>(object)->*fn.member)(key);
}

static __forceinline Bool bfmeIsKindOf(Object *object, int kind)
{
	typedef Bool (BfmeKindOfCall::*Function)(int);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0003251f;
	return (reinterpret_cast<BfmeKindOfCall *>(object)->*fn.member)(kind);
}

static __forceinline Bool bfmeAskResult(void *filter, Object *object)
{
	typedef Bool (BfmeAskCall::*Function)(Object *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = d_009f2a70;
	return (reinterpret_cast<BfmeAskCall *>(filter)->*fn.member)(object);
}

static __forceinline Bool bfmeAskOptional(PartitionFilter *filter, Object *object)
{
	typedef Bool (BfmeAskCall::*Function)(Object *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = d_004a5950;
	return (reinterpret_cast<BfmeAskCall *>(filter)->*fn.member)(object);
}

static __forceinline unsigned int bfmeNameToKey(void *generator, const char *name)
{
	typedef unsigned int (BfmeNameKeyCall::*Function)(const char *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = d_0043add7;
	return (reinterpret_cast<BfmeNameKeyCall *>(generator)->*fn.member)(name);
}

static __forceinline void bfmePostClosest(Object *object, const Object *source)
{
	struct BfmePostCall { void call(const Object *, Bool); };
	typedef void (BfmePostCall::*Function)(const Object *, Bool);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000051be;
	(reinterpret_cast<BfmePostCall *>(object)->*fn.member)(source, TRUE);
}

struct BfmeFilterHead
{
	void * volatile m_vftable;
	void * volatile m_next;
	const Object * volatile m_object;
};

struct BfmeFilterAlive
{
	void * volatile m_vftable;
	void * volatile m_next;
};

struct BfmeFilterWithin
{
	void * volatile m_vftable;
	void * volatile m_next;
	unsigned int volatile m_value;
};

struct BfmeFilter8
{
	void *m_vftable;
	void *m_next;
};

struct BfmeFilter16
{
	unsigned char m_data[16];
};

class BfmeRejectFilter
{
public:
	BfmeRejectFilter(const Object *object);

	void *m_vftable;
	void *m_next;
	const Object *m_object;
	unsigned char m_acquireEnemies;
};

class BfmeStealthFilter
{
public:
	BfmeStealthFilter(const Object *object, Bool allow);

	void *m_vftable;
	void *m_next;
	const Object *m_object;
	unsigned char m_allow;
};

struct BfmeFilter32
{
	void *m_vftable;
	void *m_next;
	unsigned int m_maskA;
	unsigned int m_maskB;
	unsigned int m_maskC;
	unsigned int m_maskD;
	unsigned int m_maskE;
	unsigned int m_maskF;
};

struct BfmeStatusMask3
{
	public:
	enum BogusInitType { kInit = 0 };

	__forceinline BfmeStatusMask3(BogusInitType, Int bit)
	{
		m_word[0] = 0;
		m_word[1] = 0;
		m_word[2] = 0;
		m_word[bit >> 5] |= 1 << (bit & 31);
	}

	unsigned int m_word[3];
};

class BfmeStatusFilter
{
public:
	BfmeStatusFilter(Int mustBeSetBit, Int mustBeClearBit)
	{
		BfmeStatusMask3 mustBeSet(BfmeStatusMask3::kInit, mustBeSetBit);
		BfmeStatusMask3 mustBeClear(BfmeStatusMask3::kInit, mustBeClearBit);
		m_vftable = (void *)0x010956D4;
		m_next = NULL;
		m_maskA = mustBeSet.m_word[0];
		m_maskB = mustBeSet.m_word[1];
		m_maskC = mustBeSet.m_word[2];
		m_maskD = mustBeClear.m_word[0];
		m_maskE = mustBeClear.m_word[1];
		m_maskF = mustBeClear.m_word[2];
	}

	void * volatile m_vftable;
	void * volatile m_next;
	unsigned int volatile m_maskA;
	unsigned int volatile m_maskB;
	unsigned int volatile m_maskC;
	unsigned int volatile m_maskD;
	unsigned int volatile m_maskE;
	unsigned int volatile m_maskF;
};

class BfmeLineFilter
{
public:
	BfmeLineFilter(const Object *object)
	{
		m_vftable = (void *)0x010956B0;
		m_next = NULL;
		m_object = object;
	}

	void * volatile m_vftable;
	void * volatile m_next;
	const Object * volatile m_object;
};

class BfmeAttackFilter
{
public:
	BfmeAttackFilter(const Object *object)
	{
		m_vftable = (void *)0x010956C4;
		m_next = NULL;
		m_object = object;
		m_command = 2;
		m_zero = 0;
	}

	void * volatile m_vftable;
	void * volatile m_next;
	const Object * volatile m_object;
	unsigned int volatile m_command;
	unsigned int volatile m_zero;
};

class BfmeInsignificantFilter
{
public:
	BfmeInsignificantFilter(Bool value, Bool value2)
	{
		m_vftable = (void *)0x010956E4;
		m_next = NULL;
		m_value = value;
		m_value2 = value2;
	}

	void * volatile m_vftable;
	void * volatile m_next;
	unsigned char volatile m_value;
	unsigned char volatile m_value2;
	unsigned char volatile m_pad[2];
};

class BfmeFogFilter
{
public:
	BfmeFogFilter(unsigned int value)
	{
		m_vftable = (void *)0x010956F4;
		m_next = NULL;
		m_value = value;
	}

	void * volatile m_vftable;
	void * volatile m_next;
	unsigned int volatile m_value;
};

struct BfmeFilter12
{
	void *m_vftable;
	void *m_next;
	unsigned int m_value;
};

struct BfmeFilter12Bool
{
	void *m_vftable;
	void *m_next;
	unsigned char m_value;
	unsigned char m_value2;
	unsigned char m_pad[2];
};

struct BfmeFilter20
{
	void *m_vftable;
	void *m_next;
	const Object *m_object;
	unsigned int m_command;
	unsigned int m_zero;
};

struct BfmeFilter24
{
	void *m_vftable;
	unsigned int m_data[5];
};

struct BfmeFilterPair
{
	void *m_vftable;
	unsigned int m_zero;
	unsigned int m_first[6];
	unsigned int m_second[6];
};

struct BfmeModulePriorityInfo
{
	Int priority;
	const AttackPriorityInfo *info;
};

class BfmeModulePriorityCall
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void modulePriority(const void *name, BfmeModulePriorityInfo *priority, Bool useDefault) = 0;
};

class BfmeModuleSpecialCall
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual Bool allowModule(const Object *source, Object **result) = 0;
};

class BfmeModuleCheckCall
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual Bool check() = 0;
};

// 0x0002C471 is the destructor used by the range-result holder and by the
// return-forwarder temporaries in this body.
struct BfmeRange;

class Gen_uw_0002c471
{
public:
	void *m_value;
	BfmeRange *operator->() const { return (BfmeRange *)m_value; }
	~Gen_uw_0002c471();
};

struct BfmeResultA
{
	void *m_value;
	BfmeResultA() {}
	BfmeResultA(const BfmeResultA &that);
};

struct BfmeWideResult
{
	void *m_value;
	BfmeWideResult() {}
	BfmeWideResult(const BfmeWideResult &that);
};

class BfmeResultForwardB
{
	char m_pad[12];
	void *m_source;

public:
	BfmeResultA bfmeForwardResultB(int value);
};

class BfmeWideForwardC
{
	char m_pad[12];
	void *m_source;

public:
	BfmeWideResult bfmeForwardWideC(int a, int b, int c, int d, int e);
};

class BfmeP1050
{
public:
	void bfmeFwd1050(int a, int b, int c, int d, int e);
};

class BfmeC1050
{
public:
	Object *bfmeGo1050D(int a, int b, int c, int d);

	char m_pad[12];
	BfmeP1050 *m_source;
};

struct BfmeRangeNode
{
	Object *m_object;
	unsigned int m_pad;
};

struct BfmeRange
{
	BfmeRangeNode *m_begin;
	BfmeRangeNode *m_first;
	BfmeRangeNode *m_end;
	BfmeRangeNode *m_current;
	unsigned int m_refCount;
};

static __forceinline void bfmeAppend(BfmeFilterHead *head, void *filter)
{
	typedef void (BfmeAppendCall::*Function)(void *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = d_009f2ae0;
	(reinterpret_cast<BfmeAppendCall *>(head)->*fn.member)(filter);
}

static __forceinline void bfmeInitRejectBuildings(BfmeFilter16 *filter, const Object *object)
{
	typedef void (BfmeRejectCall::*Function)(const Object *);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001b347;
	(reinterpret_cast<BfmeRejectCall *>(filter)->*fn.member)(object);
}

static __forceinline void bfmeInitStealth(BfmeFilter16 *filter, const Object *object)
{
	typedef void (BfmeStealthCall::*Function)(const Object *, int);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00046a97;
	(reinterpret_cast<BfmeStealthCall *>(filter)->*fn.member)(object, 0);
}

static __forceinline void bfmeInitPair(BfmeFilterPair *pair, unsigned int *first)
{
	typedef void (BfmePairCall::*Function)(unsigned int *first, void *second);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000382fd;
	(reinterpret_cast<BfmePairCall *>(pair)->*fn.member)(first, (void *)0x012ED8B8);
}

static __forceinline void bfmeReleaseResult(Gen_uw_0002c471 *result)
{
	typedef void (BfmeReleaseCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0002c471;
	(reinterpret_cast<BfmeReleaseCall *>(result)->*fn.member)();
}

extern void Gen0082E5F0(void *memory, unsigned int bytes);

static __forceinline Int bfmeModulePriority(void *module, Int priority, const AttackPriorityInfo *info)
{
	BfmeModulePriorityInfo modulePriority;
	modulePriority.priority = priority;
	modulePriority.info = info;
	reinterpret_cast<BfmeModulePriorityCall *>(module)->modulePriority((const void *)0x0054B880,
		&modulePriority, TRUE);
	return modulePriority.priority;
}

static __forceinline Bool bfmeAllowModule(void *module, const Object *source, Object **result)
{
	return reinterpret_cast<BfmeModuleSpecialCall *>(module)->allowModule(source, result);
}

static __forceinline Bool bfmeModuleCheck(void *module)
{
	return reinterpret_cast<BfmeModuleCheckCall *>(module)->check();
}

static __forceinline Bool bfmeAcceptCandidate(void *acceptor, const Object *me, Object *candidate)
{
	typedef Bool (BfmeAcceptSourceCall::*SourceFunction)(Int, Int);
	union { void (*raw)(void); SourceFunction member; } sourceFn;
	sourceFn.raw = j_00009c41;
	Bool possible = (reinterpret_cast<BfmeAcceptSourceCall *>(const_cast<Object *>(me))->*sourceFn.member)(0, 1);

	typedef Bool (BfmeAcceptCall::*AcceptFunction)(const Object *, const void *, Bool);
	union { void (*raw)(void); AcceptFunction member; } acceptFn;
	acceptFn.raw = j_00032b46;
	void *context = *(void **)((char *)*(void **)0x012EF214 + 0x0C);
	(void)acceptor;
	return (reinterpret_cast<BfmeAcceptCall *>(context)->*acceptFn.member)(me, (char *)candidate + 0x38, possible);
}

// ?findClosestEnemy@AI@@QAEPAVObject@@PBV2@MIPBVAttackPriorityInfo@@PAVPartitionFilter@@@Z
Object *AI::findClosestEnemy(const Object *me, Real range, UnsignedInt qualifiers,
	const AttackPriorityInfo *info, PartitionFilter *optionalFilter)
{
	Object *bestEnemy = NULL;
	Int withinRange;
	Int bestPriority = 0;
	volatile Int canAttack = qualifiers & CAN_ATTACK;
	if (canAttack && !me->isAbleToAttack())
		return NULL;

	BfmeFilterHead filterObvious;
	BfmeFilterAlive filterAlive;
	BfmeFilterWithin filterWithin;
	filterObvious.m_next = NULL;
	filterObvious.m_vftable = (void *)0x01095734;
	filterObvious.m_object = me;
	filterAlive.m_next = NULL;
	filterAlive.m_vftable = (void *)0x01083B80;
	filterWithin.m_next = NULL;
	filterWithin.m_vftable = (void *)0x01095744;
	filterWithin.m_value = (unsigned int)me;

	BfmeRejectFilter filterBldgs(me);
	BfmeStealthFilter filterStealth(me, FALSE);
	BfmeStatusFilter filterStatus(49, 0);
	BfmeLineFilter filterLOS(me);
	BfmeAttackFilter filterAttack(me);
	BfmeInsignificantFilter filterInsignificant(TRUE, FALSE);
	BfmeFogFilter filterFog(me->getControllingPlayer()->getPlayerIndex());
	BfmeFilterPair filterPair;
	unsigned int filterBlock[6];

	for (Int i = 0; i != 6; ++i)
		filterBlock[i] = 0;
	filterBlock[4] = 0x82;
	bfmeInitPair(&filterPair, filterBlock);

	bfmeAppend(&filterObvious, &filterAlive);
	if (!(qualifiers & ATTACK_BUILDINGS))
		bfmeAppend(&filterObvious, &filterBldgs);
	if (qualifiers & 0x40)
		bfmeAppend(&filterObvious, &filterPair);
	withinRange = qualifiers & WITHIN_ATTACK_RANGE;
	if (withinRange)
		bfmeAppend(&filterObvious, &filterWithin);
	if (qualifiers & CAN_SEE)
		bfmeAppend(&filterObvious, &filterLOS);
	if (qualifiers & UNFOGGED)
		bfmeAppend(&filterObvious, &filterFog);
	if (qualifiers & IGNORE_INSIGNIFICANT_BUILDINGS)
		bfmeAppend(&filterObvious, &filterInsignificant);
	bfmeAppend(&filterObvious, &filterStealth);
	bfmeAppend(&filterObvious, &filterStatus);
	if (canAttack)
	{
		bfmeAppend(&filterObvious, &filterAttack);
		if (canAttack)
		{
			void *specialModule = *(void **)((char *)me + 0x214);
			if ((*(unsigned char *)((char *)me + 0x94) & 0x10) != 0 && specialModule != NULL)
			{
				void *module = *(void **)((char *)specialModule + 0x1fc);
				if (module != NULL)
				{
					Object *special = NULL;
					if (bfmeAllowModule(module, me, &special))
					{
						if (special == NULL)
							return NULL;
						if (!bfmeAskResult(&filterObvious, special))
							return NULL;
						if (info != NULL && info != bfmeDefaultAttackInfo() &&
						bfmeGetPriority(info, bfmeGetThing(special)) == 0)
							return NULL;
						return special;
					}
				}
			}
		}
	}

	const AttackPriorityInfo *attackInfo = info;
	if (attackInfo == NULL || attackInfo == bfmeDefaultAttackInfo())
	{
		BfmeC1050 **manager = (BfmeC1050 **)0x012ED5B8;
		Object *closest = manager[0]->bfmeGo1050D((int)((char *)me + 0x38),
			*(int *)&range, 1, (int)&filterObvious);
		if (closest != NULL && canAttack)
			bfmePostClosest(closest, me);
		return closest;
	}

	Gen_uw_0002c471 rangeObjects;
	Int rangeKind;
	BfmeWideResult wideResult;
	BfmeResultA closestResult;
	if (range < *(Real *)0x010959E8)
	{
		BfmeWideForwardC **wide = (BfmeWideForwardC **)0x012ED5B8;
		wideResult = wide[0]->bfmeForwardWideC((int)((char *)me + 0x38),
			*(int *)&range, 1, (int)&filterObvious, 0);
		rangeObjects.m_value = wideResult.m_value;
		rangeKind = 1;
	}
	else
	{
		BfmeResultForwardB **closest = (BfmeResultForwardB **)0x012ED5B8;
		closestResult = closest[0]->bfmeForwardResultB((int)&filterObvious);
		rangeObjects.m_value = closestResult.m_value;
		rangeKind = 2;
	}

	++rangeObjects->m_refCount;
	if (rangeKind & 2)
		bfmeReleaseResult((Gen_uw_0002c471 *)&closestResult);
	if (rangeKind & 1)
		bfmeReleaseResult((Gen_uw_0002c471 *)&wideResult);

	Real bestScore = 0.0f;
	Bool bestAccepted = FALSE;
	for (BfmeRangeNode *node = rangeObjects->m_current;
		node != rangeObjects->m_first;
		node = rangeObjects->m_current)
	{
		Int priority;
		register Object *enemy = node->m_object;
		rangeObjects->m_current = node + 1;
		if (enemy == NULL)
			break;

		void *thing = *(void **)((char *)enemy + 4);
		if (thing != NULL && *(void **)((char *)thing + 4) != NULL)
			thing = bfmeFinalOverride(thing);

		priority = bfmeGetPriority(attackInfo, thing);
		if (*(unsigned char *)((char *)enemy + 0x94) & 0x20)
		{
			Object *melee = bfmeResolveMeleeTarget(enemy);
			if (melee != NULL)
			{
				if (*(void **)((char *)melee + 0x214) != NULL)
					continue;
				void *meleeThing = *(void **)((char *)melee + 4);
				if (meleeThing != NULL && *(void **)((char *)meleeThing + 4) != NULL)
					meleeThing = bfmeFinalOverride(meleeThing);
				Int meleePriority = bfmeGetPriority(attackInfo, meleeThing);
				Int *selectedPriority = &priority;
				if (priority <= meleePriority)
					selectedPriority = &meleePriority;
				priority = *selectedPriority;
			}
		}

		if (priority == 0)
			continue;
		if (*(unsigned int *)((char *)enemy + 0x98) & 0x400000)
			continue;

		thing = *(void **)((char *)enemy + 4);
		if (thing != NULL && *(void **)((char *)thing + 4) != NULL)
			thing = bfmeFinalOverride(thing);
		if (*(unsigned int *)((char *)thing + 0xd8) & 0x100)
		{
			if ((*(unsigned char *)0x012EF224 & 1) == 0)
			{
				*(unsigned int *)0x012EF224 |= 1;
				*(unsigned int *)0x012EF220 = bfmeNameToKey(*(void **)0x012ED600,
					(const char *)0x01085EC0);
			}
			void *found = bfmeFindModule(enemy, *(unsigned int *)0x012EF220);
			if (found != NULL)
			{
				found = (char *)found - 4;
				if (found != NULL && bfmeModuleCheck(found))
					continue;
			}
		}

		void *module = *(void **)((char *)enemy + 0x1fc);
		Int modulePriority;
		if (module != NULL)
		{
			modulePriority = bfmeModulePriority(module, priority, attackInfo);
			if (modulePriority > priority)
				priority = modulePriority;
		}

		Int scoreBase = priority + 100;
		Real baseScore = (Real)scoreBase;
		Real score = baseScore -
			(Real)sqrt(bfmeDistanceSquared(me, enemy)) /
			TheAI->getAiData()->m_attackPriorityDistanceModifier;

	if ((signed char)qualifiers < 0)
		{
			Player *player = bfmeControllingPlayer(enemy);
			if (((StringBase<char> *)((char *)player + 0x1C))->compare((const char *)0x010959D8) == 0 &&
				bfmeIsKindOf(enemy, 0xAC))
				score = 1.0f;
		}

		Bool continueFlag = FALSE;
		if (score > bestScore)
			continueFlag = TRUE;
		else if (score == bestScore && priority > bestPriority)
			continueFlag = TRUE;
		if (!continueFlag && bestAccepted)
			continue;

			Bool accepted = bfmeAcceptCandidate((void *)0, me, enemy);
		if (!accepted && bestAccepted)
			continue;
		if (!continueFlag)
		{
			if (!accepted)
				continue;
			if (bestAccepted)
				continue;
		}
		if (optionalFilter != NULL && !bfmeAskOptional(optionalFilter, enemy))
			continue;
		if (!accepted && bestAccepted && bestEnemy != NULL)
			continue;

		bestScore = score;
		bestPriority = priority;
		bestAccepted = accepted;
		bestEnemy = enemy;
	}

	if (bestEnemy != NULL && (qualifiers & CAN_ATTACK) && withinRange == 0)
	{
		bfmePostClosest(bestEnemy, me);
		return bestEnemy;
	}

	BfmeRangeNode *begin = rangeObjects->m_begin;
	Int result = --rangeObjects->m_refCount;
	if (result == 0)
	{
		if (begin != NULL)
		{
			unsigned int bytes = (unsigned int)(((char *)rangeObjects->m_end -
				(char *)begin) / 8) * 8;
			if (bytes > 0x80)
				::operator delete(begin);
			else
				Gen0082E5F0(begin, bytes);
		}
		::operator delete(rangeObjects.m_value);
	}
	(void)rangeKind;
	return bestEnemy;
}
