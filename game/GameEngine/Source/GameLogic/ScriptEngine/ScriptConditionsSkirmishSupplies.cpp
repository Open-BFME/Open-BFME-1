// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// Retail 0x0032D300, 835 bytes through the final branch to the ret 16 epilogue.
// Identity: ScriptConditions dispatcher 0x0032D720 calls this ILT for the
// supplies-within-distance condition; the Zero Hour twin supplies the radius,
// SupplyWarehouseDockUpdate lookup and maximum supply-value comparison.
// BFME additionally walks every player in the mask and uses linked temporary
// filters and the owning BfmeWideResult ABI (009F2960), as witnessed by the
// landed range-query callers. The filter tables are 0109687C, 0109689C,
// 01083B70; the payload is a vector of eight-byte entries, cursor +0x0c,
// references +0x10. Canonical ScriptConditions.cpp retains conflicting ZH
// filter/iterator definitions, so this BFME body uses its own class-home TU.
// A while-declaration at the iterator head avoids duplicating its next body.
// Model: gpt-6-astra.
// stlport
#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <bitset>
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

template<int N> class BitFlags {
public:
 enum InitType { INIT_ZERO = 0 };
 BitFlags(InitType, int bit) { m_bits._Unchecked_set(bit); }
 _STL::bitset<N> m_bits;
};
typedef BitFlags<192> KindOfMaskType;

class PartitionFilter {
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *object) = 0;
 virtual Int getPlayerMask();
 PartitionFilter *link(PartitionFilter *next);
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

// Native BFME result ABI: witnessed by 009F2960 and landed range callers.
struct SuppliesEntry0032D300 { Object *object; unsigned distanceBits; };
struct SuppliesResult0032D300 {
 _STL::vector<SuppliesEntry0032D300> entries;
 SuppliesEntry0032D300 *current;
 int references;
};
struct BfmeWideResult {
 SuppliesResult0032D300 *m_value;
 BfmeWideResult();
 BfmeWideResult(const BfmeWideResult &);
 ~BfmeWideResult() { if (--m_value->references == 0) delete m_value; }
 Object *next() {
  if(m_value->current == m_value->entries.end()) return 0;
  return (m_value->current++)->object;
 }
};
class BfmeWideForwardC {
// RVA 0x009F2960 forwards five raw stack words; use its ledger signature.
public: BfmeWideResult bfmeForwardWideC(int,int,int,int,int);
};
class BfmeThingDTJ { public: float bfmeGoDTJ(); };

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern NameKeyGenerator *TheNameKeyGenerator;
class PartitionManager;
extern PartitionManager *ThePartitionManager;


class ScriptConditions {
protected:
	Bool evaluateSkirmishSuppliesWithinDistancePerimeter(Parameter *p0,
		Parameter *p1, Parameter *p2, Parameter *p3);
};

Bool ScriptConditions::evaluateSkirmishSuppliesWithinDistancePerimeter(
 Parameter *p0, Parameter *p1, Parameter *p2, Parameter *p3) {
 PlayerMaskType mask = bfmeGetPlayerMask(TheScriptEngine, p0);
 while(mask) {
  Player *player = ThePlayerList->getEachPlayerFromMask(mask);
  if (!player) continue;
  PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName(p2->getString());
  if (!trigger) continue;
  Coord3D center;
  trigger->getCenterPoint(&center);
  Real distance = reinterpret_cast<BfmeThingDTJ *>(trigger)->bfmeGoDTJ() + p1->getReal();
  Real compareToValue = p3->getReal();
  Real maxValue = 0;
  BfmeWideResult iter = (*reinterpret_cast<BfmeWideForwardC **>(&ThePartitionManager))->bfmeForwardWideC((int)&center, *reinterpret_cast<const int*>(&distance), 0,
   (int)PartitionFilterAcceptByKindOf(KindOfMaskType(KindOfMaskType::INIT_ZERO, KINDOF_STRUCTURE),KINDOFMASK_NONE).link(
    PartitionFilterPlayerAffiliation(player, ALLOW_NEUTRAL, true).link(&PartitionFilterOnMap())), 0);
  while (Object *object = iter.next()) {
   static const NameKeyType keyWarehouseUpdate = NAMEKEY("SupplyWarehouseDockUpdate");
   SupplyWarehouseDockUpdate *warehouseModule = object->findUpdateModule(keyWarehouseUpdate);
   if (!warehouseModule) continue;
   Real value = player->getSupplyBoxValue() * warehouseModule->getBoxesStored();
   if (value > maxValue) maxValue = value;
  }
  if(maxValue > compareToValue) return true;
 }
 return false;
}
