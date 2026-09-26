// ?evaluateSkirmishSuppliesWithinDistancePerimeter@ScriptConditions@@IAE_NPAVParameter@@000@Z
// partial score=0.55 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// The retail body inlines the parameter-mask and player-list calls.  Keep
// those ABI edges explicit while recovering the surrounding condition in C++.
#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef unsigned short PlayerMaskType;

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum KindOfType { KINDOF_STRUCTURE = 7 };
enum AllowPlayerRelationship { ALLOW_NEUTRAL = 8 };
enum DistanceCalculationType { FROM_CENTER_2D = 0 };
enum IterOrderType { ITER_FASTEST = 0 };

struct Coord3D {
	Real x;
	Real y;
	Real z;
};

class Parameter {
public:
	Int getInt() const { return m_int; }
	Real getReal() const { return m_real; }
	const AsciiString &getString() const { return m_string; }

private:
	unsigned char m_prefix[8];
	Int m_int;
	Real m_real;
	AsciiString m_string;
};

class Player;
class ScriptEngine;

class BfmeScriptEngineParameterMaskCall {
public:
	virtual PlayerMaskType getPlayerMask(Parameter *parameter) = 0;
};

extern void j_000230b5(void);

static __forceinline PlayerMaskType bfmeGetPlayerMask(ScriptEngine *engine, Parameter *parameter) {
	typedef PlayerMaskType (BfmeScriptEngineParameterMaskCall::*Function)(Parameter *);
	union {
		void (*raw)(void);
		Function member;
	} fn;
	fn.raw = j_000230b5;
	return (reinterpret_cast<BfmeScriptEngineParameterMaskCall *>(engine)->*fn.member)(parameter);
}

class PlayerList {
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
};

class PolygonTrigger {
public:
	void getCenterPoint(Coord3D *center) const;
	Real getRadius() const;
};

class ScriptEngine {
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
	virtual PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name) = 0;
};

class Player {
public:
	UnsignedInt getSupplyBoxValue();
};

class Module;

class SupplyWarehouseDockUpdate {
public:
	Int getBoxesStored() const {
		return *(const Int *)((const unsigned char *)this + 0x88);
	}
};

class Object {
public:
	Module *findModule(NameKeyType key) const;
	SupplyWarehouseDockUpdate *findUpdateModule(NameKeyType key) const {
		return (SupplyWarehouseDockUpdate *)findModule(key);
	}
};

class NameKeyGenerator {
public:
	NameKeyType nameToKey(const char *name);
};

#define NAMEKEY(name) (TheNameKeyGenerator->nameToKey(name))

class KindOfMaskType {
public:
	enum InitType { INIT_ZERO = 0 };

	KindOfMaskType() {
		for (int i = 0; i != 6; ++i) {
			m_bits[i] = 0;
		}
	}
	KindOfMaskType(InitType, int bit) {
		for (int i = 0; i != 6; ++i) {
			m_bits[i] = 0;
		}
		m_bits[bit >> 5] |= 1u << (bit & 31);
	}

private:
	UnsignedInt m_bits[6];
};

class PartitionFilter {
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *object) = 0;
	PartitionFilter *m_next;
};

extern const KindOfMaskType KINDOFMASK_NONE;

class PartitionFilterAcceptByKindOf : public PartitionFilter {
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}
	virtual Bool allow(Object *object);

private:
	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

class PartitionFilterPlayerAffiliation : public PartitionFilter {
public:
	PartitionFilterPlayerAffiliation(const Player *player,
		UnsignedInt affiliation, Bool match)
		: m_player(player), m_match(match), m_affiliation(affiliation) {}
	virtual Bool allow(Object *object);

private:
	const Player *m_player;
	Bool m_match;
	UnsignedInt m_affiliation;
};

class PartitionFilterOnMap : public PartitionFilter {
public:
	PartitionFilterOnMap() {}
	protected: virtual Bool allow(Object *object);
};

class MemoryPool {
public:
	void freeBlock(void *block);
};

class MemoryPoolObject {
protected:
	virtual ~MemoryPoolObject() {}
	virtual MemoryPool *getObjectMemoryPool() = 0;

public:
	void deleteInstance() {
		if (this) {
			MemoryPool *pool = getObjectMemoryPool();
			this->~MemoryPoolObject();
			pool->freeBlock(this);
		}
	}
};

class ObjectIterator : public MemoryPoolObject {
public:
	virtual Object *first() = 0;
	virtual Object *next() = 0;
};

class SimpleObjectIterator : public ObjectIterator {
};

class MemoryPoolObjectHolder {
public:
	MemoryPoolObjectHolder(MemoryPoolObject *object) : m_object(object) {}
	~MemoryPoolObjectHolder() { m_object->deleteInstance(); }

private:
	MemoryPoolObject *m_object;
};

class PartitionManager {
public:
	SimpleObjectIterator *iterateObjectsInRange(const Coord3D *center,
		Real distance, DistanceCalculationType calculation,
		PartitionFilter **filters, IterOrderType order);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern NameKeyGenerator *TheNameKeyGenerator;
extern PartitionManager *ThePartitionManager;

class ScriptConditions {
protected:
	Bool evaluateSkirmishSuppliesWithinDistancePerimeter(Parameter *p0,
		Parameter *p1, Parameter *p2, Parameter *p3);
};

Bool ScriptConditions::evaluateSkirmishSuppliesWithinDistancePerimeter(
	Parameter *p0, Parameter *p1, Parameter *p2, Parameter *p3) {
	PlayerMaskType mask = bfmeGetPlayerMask(TheScriptEngine, p0);
	Player *player = 0;
	if (mask) {
		player = ThePlayerList->getEachPlayerFromMask(mask);
	}
	if (!player) {
		return false;
	}

	PolygonTrigger *trigger =
		TheScriptEngine->getQualifiedTriggerAreaByName(p2->getString());
	if (!trigger) {
		return false;
	}

	Coord3D center;
	trigger->getCenterPoint(&center);
	Real distance = trigger->getRadius() + p1->getReal();
	Real compareToValue = p3->getReal();

	PartitionFilterAcceptByKindOf filterKind(
		KindOfMaskType(KindOfMaskType::INIT_ZERO, KINDOF_STRUCTURE),
		KINDOFMASK_NONE);
	PartitionFilterPlayerAffiliation filterPlayer(player, ALLOW_NEUTRAL, true);
	PartitionFilterOnMap filterMapStatus;
	PartitionFilter *filters[] = {
		&filterKind, &filterPlayer, &filterMapStatus, 0
	};

	SimpleObjectIterator *iter = ThePartitionManager->iterateObjectsInRange(
		&center, distance, FROM_CENTER_2D, filters, ITER_FASTEST);
	MemoryPoolObjectHolder holder(iter);
	Real maxValue = 0;
	static const NameKeyType keyWarehouseUpdate =
		NAMEKEY("SupplyWarehouseDockUpdate");
	for (Object *object = iter->first(); object; object = iter->next()) {
		SupplyWarehouseDockUpdate *warehouseModule =
			object->findUpdateModule(keyWarehouseUpdate);
		if (!warehouseModule) {
			continue;
		}
		Real value = player->getSupplyBoxValue() *
			warehouseModule->getBoxesStored();
		if (value > maxValue) {
			maxValue = value;
		}
	}
	return maxValue > compareToValue;
}
