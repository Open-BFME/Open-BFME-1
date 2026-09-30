// ?update@AutoHealBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.9951 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// BANK 0x001EEDE0 AutoHealBehavior::update (1216 B): this is the WHOLE
// AutoHealBehavior_playerScan.cpp TU with update appended (update must share the
// TU with the static rva001EE670EligibleForAutoHeal to get its EAX/EBX private
// convention).  checkForAutoHeal 0x001EED80 and the predicate 0x001EE670 still
// probe EXACT under these declarations.  update: 1216/1216 bytes, 6 non-reloc
// bytes differ at +0x3B0 (retail lea eax,[esp+0x64] then mov ebx,esi; ours the
// reverse).  Landing prerequisites (probe masks relocations): pin
// ?iterateObjectsInRange@PartitionManager@@QAE?AUBfmeWideResult@@PBUCoord3D@@MW4DistanceCalculationType@@PAVPartitionFilter@@W4IterOrderType@@@Z
// at 0x009F2960 (ledger placeholder bfmeForwardWideC; ZH twin call evidence),
// and confirm the filter vtable names against dir32_addresses.csv.
// BFME's player-wide auto-heal scan uses a 24-byte kind-of mask and three
// policy bytes at scan-data offsets 0x20..0x22, unlike the Zero Hour callback.
// Keep the predicate in this translation unit: VC7.1 passes its scan data in
// EAX and candidate in EBX instead of using a public calling convention.
// The retail list append calls the out-of-line STLport allocator at 0x0082E540.
// Its inline wrapper instead folds to the different global operator new.

#include "ascii_string.h"
#include <string.h>
#pragma intrinsic(memset)

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class Object;

struct Coord3D
{
	Real x, y, z;

	void set(Real ax, Real ay, Real az)
	{
		x = ax;
		y = ay;
		z = az;
	}
};

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
	unsigned char m_bfmeBody[0x5c];
};

class Player
{
public:
	void iterateObjects(void (*func)(Object *, void *), void *userData) const;
};

template <int N>
class BitFlags
{
public:
	BitFlags()
	{
		memset(m_bits, 0, sizeof(m_bits));
	}
	UnsignedInt m_bits[6];
};

class Thing
{
public:
	Bool isAnyKindOf(const BitFlags<69> &mask) const;
};

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
};

class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual Real getHealth() const = 0;
	virtual void slot14() = 0;
	virtual Real getMaxHealth() const = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual UnsignedInt getLastDamageTimestamp() const = 0;
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	Bool isEffectivelyDead() const { return (reinterpret_cast<const unsigned char *>(&m_status)[0] & 1) != 0; }
	Bool isOffMap() const { return (reinterpret_cast<const unsigned char *>(&m_status)[0] & 8) != 0; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }

	Bool getAttributeModifierBonus(int kind, Real *out) const;
	const Coord3D *getPosition() const { return &m_position; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }

private:
	unsigned char m_pad000[0x38];
	Coord3D m_position;
	unsigned char m_pad044[0xac - 0x44];
	GeometryInfo m_geometryInfo;
	unsigned char m_padAC[0x200 - 0xac - sizeof(GeometryInfo)];
	BodyModuleInterface *m_body;
	AIUpdateInterface *m_ai;
	unsigned char m_pad208[0x344 - 0x208];
	UnsignedInt m_status;
};

class GameLogic
{
public:
	unsigned char m_pad000[0x3c];
	UnsignedInt m_frame;
	unsigned char m_pad040[0x92 - 0x40];
	Bool m_drawIconUI;
};

extern GameLogic *TheGameLogic;

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate(unsigned int bytes);
};
}

struct AutoHealScanListNode
{
	AutoHealScanListNode *next;
	AutoHealScanListNode *prev;
	Object *value;
};

class ObjectPointerList
{
public:
	void push_back(Object *object)
	{
		AutoHealScanListNode *head = m_node;
		AutoHealScanListNode *node = (AutoHealScanListNode *)_STL::__new_alloc::allocate(12);
		Object **value = &node->value;
		if (value)
			*value = object;
		AutoHealScanListNode *prev = head->prev;
		node->next = head;
		node->prev = prev;
		prev->next = node;
		head->prev = node;
	}

	AutoHealScanListNode *m_node;
};

struct AutoHealPlayerScanHelper
{
	BitFlags<69> m_kindOfToTest;
	Object *m_theHealer;
	ObjectPointerList *m_objectList;
	Bool m_bfmeFlag20;
	Bool m_bfmeFlag21;
	Bool m_skipSelfForHealing;
};

// ?rva001EE670EligibleForAutoHeal@@YA_NPBUAutoHealPlayerScanHelper@@PAVObject@@@Z
static Bool rva001EE670EligibleForAutoHeal(
	const AutoHealPlayerScanHelper *helper, Object *testObj)
{
	if (helper->m_skipSelfForHealing && testObj == helper->m_theHealer)
		return false;

	if (helper->m_theHealer)
	{
		if (helper->m_bfmeFlag21)
		{
			AIUpdateInterface *ai = helper->m_theHealer->getAIUpdateInterface();
			if (ai && ai->getCurrentVictim())
				return false;
		}

		if (helper->m_bfmeFlag20)
		{
			Object *healer = helper->m_theHealer;
			BodyModuleInterface *body = healer->getBodyModule();
			UnsignedInt frame = TheGameLogic->m_frame;
			if (body->getLastDamageTimestamp() < frame)
			{
				Object *laterHealer = helper->m_theHealer;
				BodyModuleInterface *laterBody = laterHealer->getBodyModule();
				UnsignedInt laterFrame = TheGameLogic->m_frame;
				if (laterBody->getLastDamageTimestamp() + 5 > laterFrame)
					return false;
			}
		}
	}

	if (testObj->isEffectivelyDead())
		return false;

	Player *owner = helper->m_theHealer->getControllingPlayer();
	if (testObj->getControllingPlayer() != owner)
		return false;

	if (testObj->isOffMap())
		return false;
	if (!testObj->isAnyKindOf(helper->m_kindOfToTest))
		return false;

	BodyModuleInterface *body = testObj->getBodyModule();
	Real health = body->getHealth();
	if (body->getMaxHealth() <= health)
		return false;
	return true;
}

int checkForAutoHeal(Object *testObj, void *userData)
{
	AutoHealPlayerScanHelper *helper = (AutoHealPlayerScanHelper *)userData;
	if (rva001EE670EligibleForAutoHeal(helper, testObj))
		helper->m_objectList->push_back(testObj);
	return 1;
}

// ---------------------------------------------------------------------------
// AutoHealBehavior::update, retail 0x001EEDE0 (1216 bytes).  It lives in this
// TU because its range path calls the static eligibility predicate above with
// VC7.1's private EAX/EBX convention.


// The whole-player path's STLport list<Object*>: constructor, clear and base
// destructor are the out-of-line instantiations (ILTs 0x0001677F, 0x0002FB8A,
// 0x0000E68D).  Declared by hand so this TU keeps the hand-built push_back
// that checkForAutoHeal needs.
namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};

template <class T, class A> class _List_base
{
public:
	~_List_base();
	void clear();
	AutoHealScanListNode *_M_node;
};

template <class T, class A = allocator<T> > class list : public _List_base<T, A>
{
public:
	explicit list(const A &a = A());
	AutoHealScanListNode *beginNode() const { return this->_M_node->next; }
	AutoHealScanListNode *endNode() const { return this->_M_node; }
};
}

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class Anim2DTemplate;
class Anim2DCollection
{
public:
	Anim2DTemplate *findTemplate(const AsciiString &name);
};
extern Anim2DCollection *TheAnim2DCollection;

enum WorldAnimationOptions
{
	WORLD_ANIM_NO_OPTIONS = 0x00,
	WORLD_ANIM_FADE_ON_EXPIRE = 0x01
};

class InGameUI
{
public:
	void addWorldAnimation(Anim2DTemplate *animTemplate, const Coord3D *pos,
		WorldAnimationOptions options, Real durationInSeconds, Real zRisePerSecond);
};
extern InGameUI *TheInGameUI;

class GlobalData
{
public:
	unsigned char m_pad000[0x20c];
	AsciiString m_getHealedAnimationName;
	Real m_getHealedAnimationDisplayTimeInSeconds;
	Real m_getHealedAnimationZRisePerSecond;
};
extern GlobalData *TheGlobalData;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual Bool allow(Object *objOther);
	virtual ~PartitionFilter() {}
	PartitionFilter *link(PartitionFilter *next);

protected:
	PartitionFilter *m_next;
};

class PartitionFilterSameMapStatus : public PartitionFilter
{
public:
	PartitionFilterSameMapStatus(const Object *obj) : m_obj(obj) {}
	virtual Bool allow(Object *objOther);
	virtual ~PartitionFilterSameMapStatus() {}

private:
	const Object *m_obj;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *objOther);
	virtual ~Rva0025ED50RootFilter() {}
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	enum RelationshipAllowTypes
	{
		ALLOW_ENEMIES = 1 << 0,
		ALLOW_NEUTRAL = 1 << 1,
		ALLOW_ALLIES = 1 << 2
	};

	PartitionFilterRelationship(const Object *obj, Int flags, Bool bfmeFlag = false)
		: m_obj(obj), m_flags(flags), m_bfmeFlag10(bfmeFlag) {}
	virtual Bool allow(Object *objOther);
	virtual ~PartitionFilterRelationship() {}

private:
	const Object *m_obj;
	Int m_flags;
	Bool m_bfmeFlag10;
};

struct ObjectIteratorEntry
{
	Object *object;
	Real distance;
};

struct ObjectIteratorVector
{
	ObjectIteratorEntry *m_start;
	ObjectIteratorEntry *m_finish;
	ObjectIteratorEntry *m_endOfStorage;
	ObjectIteratorEntry *end() const { return m_finish; }
};

struct ObjectIteratorData
{
	ObjectIteratorVector entries;
	ObjectIteratorEntry *current;
	Int references;
};

// BFME returns the range scan as a reference-counted handle (0x009F2960);
// its out-of-line release is the ILT 0x0002C471 destructor.
struct Gen_uw_0002c471
{
	ObjectIteratorData *value;
	~Gen_uw_0002c471();
};

struct BfmeWideResult : public Gen_uw_0002c471
{

	Object *next()
	{
		if (value->current == value->entries.end())
			return 0;
		Object *object = value->current->object;
		++value->current;
		return object;
	}
};

enum DistanceCalculationType
{
	FROM_CENTER_2D = 0,
	FROM_CENTER_3D = 1
};

enum IterOrderType
{
	ITER_FASTEST = 0
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, Real maxDist,
		DistanceCalculationType dc, PartitionFilter *filters, IterOrderType order);
};
extern PartitionManager *ThePartitionManager;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};


struct AutoHealBehaviorModuleData
{
	unsigned char m_pad_000[0x72];
	Bool m_singleBurst;
	Int m_healingAmount;
	UnsignedInt m_healingDelay;
	UnsignedInt m_startHealingDelay;
	Int m_radius;
	Bool m_affectsWholePlayer;
	Bool m_bfmeFlag85;
	Bool m_bfmeFlag86;
	BitFlags<69> m_kindOf;
	Bool m_bfmeFlagA0;
	const FXList *m_bfmeFXA4;
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpgradeMuxInterface
{
public:
	virtual Bool isAlreadyUpgraded() const = 0;
};


class AHB_ModuleBase
{
public:
	virtual ~AHB_ModuleBase();

protected:
	const AutoHealBehaviorModuleData *m_moduleData;	// +0x04
	Object *m_object;								// +0x08
	void *m_behaviorModuleInterfaceVptr;			// +0x0C
};

class AHB_UpdateBase : public UpdateModuleInterface
{
	unsigned char m_updateModuleState[0x0c];		// +0x14
};

class AutoHealBehavior : public AHB_ModuleBase, public AHB_UpdateBase, public UpgradeMuxInterface
{
public:
	virtual UpdateSleepTime update();
	void pulseHealObject(Object *obj);
	Bool isUpgradeActive() const { return isAlreadyUpgraded(); }

	Object *getObject() const { return m_object; }
	const AutoHealBehaviorModuleData *getAutoHealBehaviorModuleData() const { return m_moduleData; }

private:
	unsigned char m_upgradeMuxState[0x2c - 0x24];
	UnsignedInt m_soonestHealFrame;					// +0x2C
	Bool m_stopped;									// +0x30
};


// ?update@AutoHealBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime AutoHealBehavior::update()
{
	if (m_stopped)
		return UPDATE_SLEEP_FOREVER;

	Object *obj = getObject();
	const AutoHealBehaviorModuleData *d = getAutoHealBehaviorModuleData();

	if (!isUpgradeActive() || obj->isEffectivelyDead())
		return UPDATE_SLEEP_FOREVER;

	if (d->m_bfmeFlag86)
	{
		AIUpdateInterface *ai = obj->getAIUpdateInterface();
		if (ai && ai->getCurrentVictim())
		{
			UnsignedInt delay = d->m_startHealingDelay;
			if (delay > 0)
				return (UpdateSleepTime)delay;
			return (UpdateSleepTime)5;
		}
	}

	Real bonus;
	obj->getAttributeModifierBonus(0x11, &bonus);
	Int amount = (Int)((Real)d->m_healingAmount + bonus);
	if (amount <= 0)
		return UPDATE_SLEEP_NONE;

	if (d->m_affectsWholePlayer)
	{
		_STL::list<Object *> objectsToHeal;
		Player *owningPlayer = getObject()->getControllingPlayer();
		if (owningPlayer)
		{
			AutoHealPlayerScanHelper helper;
			helper.m_kindOfToTest = getAutoHealBehaviorModuleData()->m_kindOf;
			helper.m_objectList = (ObjectPointerList *)&objectsToHeal;
			helper.m_theHealer = getObject();
			helper.m_bfmeFlag20 = getAutoHealBehaviorModuleData()->m_bfmeFlag85;
			helper.m_bfmeFlag21 = getAutoHealBehaviorModuleData()->m_bfmeFlag86;
			helper.m_skipSelfForHealing = getAutoHealBehaviorModuleData()->m_bfmeFlagA0;

			owningPlayer->iterateObjects((void (*)(Object *, void *))checkForAutoHeal, &helper);

			for (AutoHealScanListNode *iter = objectsToHeal.beginNode(); iter != objectsToHeal.endNode(); iter = iter->next)
			{
				FXList::doFXObj(d->m_bfmeFXA4, iter->value, 0);
				pulseHealObject(iter->value);
			}
			objectsToHeal.clear();
		}
		return (UpdateSleepTime)d->m_healingDelay;
	}
	else if (getAutoHealBehaviorModuleData()->m_radius == 0)
	{
		BodyModuleInterface *body = obj->getBodyModule();
		if (body->getHealth() < body->getMaxHealth())
		{
			pulseHealObject(obj);
			return (UpdateSleepTime)d->m_healingDelay;
		}
		return UPDATE_SLEEP_FOREVER;
	}
	else
	{
		BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(
			obj->getPosition(), (Real)d->m_radius, FROM_CENTER_2D,
			PartitionFilterRelationship(obj, PartitionFilterRelationship::ALLOW_ALLIES).link(
				Rva0025ED50RootFilter().link(&PartitionFilterSameMapStatus(obj))),
			ITER_FASTEST);

		while ((obj = iter.next()) != 0)
		{
			if (!obj->isAnyKindOf(d->m_kindOf))
				continue;

			FXList::doFXObj(getAutoHealBehaviorModuleData()->m_bfmeFXA4, obj, 0);

			BodyModuleInterface *body = obj->getBodyModule();
			if (!(body->getHealth() < body->getMaxHealth()))
				continue;

			AutoHealPlayerScanHelper helper;
			helper.m_kindOfToTest = getAutoHealBehaviorModuleData()->m_kindOf;
			helper.m_objectList = 0;
			helper.m_theHealer = getObject();
			helper.m_bfmeFlag20 = getAutoHealBehaviorModuleData()->m_bfmeFlag85;
			helper.m_bfmeFlag21 = getAutoHealBehaviorModuleData()->m_bfmeFlag86;
			helper.m_skipSelfForHealing = getAutoHealBehaviorModuleData()->m_bfmeFlagA0;
			if (!rva001EE670EligibleForAutoHeal(&helper, obj))
				continue;

			pulseHealObject(obj);

			if (d->m_singleBurst && TheGameLogic->m_drawIconUI)
			{
				if (TheAnim2DCollection)
				{
					const AsciiString &animName = TheGlobalData->m_getHealedAnimationName;
					if (animName.isEmpty() == false)
					{
						Anim2DTemplate *animTemplate = TheAnim2DCollection->findTemplate(animName);
						if (animTemplate)
						{
							Coord3D iconPosition;
							iconPosition.set(obj->getPosition()->x,
								obj->getPosition()->y,
								obj->getPosition()->z + obj->getGeometryInfo().getMaxHeightAbovePosition());
							TheInGameUI->addWorldAnimation(animTemplate, &iconPosition, WORLD_ANIM_FADE_ON_EXPIRE,
								TheGlobalData->m_getHealedAnimationDisplayTimeInSeconds,
								TheGlobalData->m_getHealedAnimationZRisePerSecond);
						}
					}
				}
			}
		}

		return (UpdateSleepTime)(d->m_singleBurst ? UPDATE_SLEEP_FOREVER : d->m_healingDelay);
	}
}
