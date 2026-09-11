// ?d_002c96d0@@YAXXZ
// partial score=0.84 date=2026-09-11
// BFME retail 0x002C96D0, 593 bytes.
//
// The entry is the WorkerAIUpdate construct slot as seen through the Dozer
// secondary interface.  The local views retain BFME's moved Worker fields and
// secondary-interface offsets without changing the shared ZH headers.
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;
class Player;
class Team;
class ThingTemplate;

template <Int NUMBITS>
class Rva002C96D0BitFlags
{
	public:
	enum InitTag { kInit };

	Rva002C96D0BitFlags() { }

	Rva002C96D0BitFlags(InitTag, Int index)
	{
		m_bits.set(index);
	}

	void set(Int index)
	{
		m_bits._Unchecked_set(index);
	}

	private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef Rva002C96D0BitFlags<86> ObjectStatusMaskType;

struct Rva002C96D0ModelMask
{
	UnsignedInt m_words[10];
};

class Rva002C96D0ClearMask
{
public:
	UnsignedInt m_words[10];
};

class Rva002C96D0SetMask
{
public:
	UnsignedInt m_words[10];
};

template <Int N>
class Rva002C96D0VirtualSlots : public Rva002C96D0VirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class Rva002C96D0VirtualSlots<0>
{
};

class Rva002C96D0BodyHealth : public Rva002C96D0VirtualSlots<4>
{
public:
	virtual Real getHealth(Int unused) const = 0;
};

class Rva002C96D0BodyModule : public Rva002C96D0BodyHealth
{
public:
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
	virtual void internalChangeHealth(Real delta) = 0;
};

class Rva002C96D0Object
{
public:
	void setProducer(const Object *producer);
	void setBuilder(const Object *builder);
	void setStatusBit(Int status, Bool set);
	void setPosition(const Coord3D *position);
	void setOrientation(Real angle);
	void clearAndSetModelConditionFlags(const Rva002C96D0ModelMask &clear,
		const Rva002C96D0ModelMask &set);

	Rva002C96D0BodyModule *getBodyModule()
	{
		return m_body;
	}

	unsigned char m_pad000[0x200];
	Rva002C96D0BodyModule *m_body;
	unsigned char m_pad204[0x1c];
	Real m_constructionPercent;
	unsigned char m_pad224[0x34];
	Real m_constructionCost;
};

class Rva002C96D0Player
{
public:
	Int getPlayerType() const
	{
		return *(const Int *)((const char *)this + 0x2c);
	}

	Team *getDefaultTeam() const
	{
		return *(Team * const *)((const char *)this + 0x230);
	}

	class Money *getMoney() const;
	void onStructureCreated(Object *builder, Object *structure);
};

class Rva002C96D0Money
{
public:
	UnsignedInt withdraw(UnsignedInt amount, Bool playSound);
};

class Rva002C96D0ThingTemplate
{
public:
	Int calcCostToBuild(const Player *player, Int buildIndex) const;
};

class Rva002C96D0ThingFactory
{
public:
	Object *newObject(const ThingTemplate *what, Team *team,
		const volatile ObjectStatusMaskType &statusBits, UnsignedInt extra);
};

class Rva002C96D0BuildAssistantPre : public Rva002C96D0VirtualSlots<10>
{
public:
	virtual Int isLocationLegalToBuild(const Coord3D *pos,
		const ThingTemplate *what, Real angle, UnsignedInt flags,
		Object *object, Player *player) = 0;
};

class Rva002C96D0BuildAssistant : public Rva002C96D0BuildAssistantPre
{
public:
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual Int canMakeUnit(Object *object, const ThingTemplate *what,
		Int buildIndex) = 0;
};

class Rva002C96D0TerrainLogicPre : public Rva002C96D0VirtualSlots<6>
{
public:
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const = 0;
};

class Rva002C96D0TerrainLogic
{
public:
	void flattenTerrain(Object *object);
};

class Rva002C96D0Pathfinder
{
public:
	void addObjectToPathfindMap(Object *object);
};

class Rva002C96D0AI
{
public:
	Rva002C96D0Pathfinder *pathfinder() const
	{
		return *(Rva002C96D0Pathfinder * const *)((const char *)this + 0x0c);
	}
};

class Rva002C96D0FullWorker
{
public:
	void createMachines();
};

class Rva002C96D0SupplyTruckInterface
{
public:
	virtual void exitingSupplyTruckState() = 0;
};

class Rva002C96D0WorkerAIUpdate : public Rva002C96D0VirtualSlots<4>
{
public:
	virtual Object *construct(const ThingTemplate *what, const Coord3D *pos,
		Real angle, Player *owningPlayer, Bool isRebuild) = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual Object *newTask(Int task, Object *object) = 0;

	Object *getObject() const
	{
		return *(Object * const *)((const char *)this - 0x338);
	}

	void setRebuild(Bool isRebuild)
	{
		*(Bool *)((char *)this + 0xd9) = isRebuild;
	}
};

extern void j_00001f41();
extern void j_00004048();
extern void j_000095ed();
extern void j_0000b81b();
extern void j_0000d990();
extern void j_0000da8a();
extern void j_0003a1a7();
extern void j_00032dee();
extern void j_0003aa8f();
extern void j_0003d424();
extern void j_0003fa53();
extern void j_000399a5();
extern void j_00041894();
extern void j_0004494a();
extern void j_00049d2d();

typedef void (Rva002C96D0FullWorker::*CreateMachinesCall)();
typedef Object *(Rva002C96D0ThingFactory::*NewObjectCall)(
	const ThingTemplate *, Team *, const volatile ObjectStatusMaskType &, UnsignedInt);
typedef Int (Rva002C96D0ThingTemplate::*CalcCostCall)(const Player *, Int) const;
typedef UnsignedInt (Rva002C96D0Money::*WithdrawCall)(UnsignedInt, Bool);
typedef void (Rva002C96D0Object::*SetProducerCall)(const Object *);
typedef void (Rva002C96D0Object::*SetBuilderCall)(const Object *);
typedef void (Rva002C96D0Object::*SetStatusBitCall)(Int, Bool);
typedef void (Rva002C96D0Object::*SetPositionCall)(const Coord3D *);
typedef void (Rva002C96D0Object::*SetOrientationCall)(Real);
typedef void (Rva002C96D0Object::*ClearAndSetCall)(
	const Rva002C96D0ModelMask &, const Rva002C96D0ModelMask &);
typedef void (Rva002C96D0Player::*OnStructureCreatedCall)(Object *, Object *);
typedef void (Rva002C96D0TerrainLogic::*FlattenTerrainCall)(Object *);
typedef void (Rva002C96D0Pathfinder::*AddObjectCall)(Object *);
typedef Rva002C96D0ClearMask *(Rva002C96D0ClearMask::*ConstructClearCall)(
	void *, UnsignedInt);
typedef Rva002C96D0SetMask *(Rva002C96D0SetMask::*ConstructSetCall)(
	Int, UnsignedInt, UnsignedInt);

union CreateMachinesCallBits
{
	void (*raw)();
	CreateMachinesCall member;
};

union NewObjectCallBits
{
	void (*raw)();
	NewObjectCall member;
};

union CalcCostCallBits
{
	void (*raw)();
	CalcCostCall member;
};

union WithdrawCallBits
{
	void (*raw)();
	WithdrawCall member;
};

union SetProducerCallBits
{
	void (*raw)();
	SetProducerCall member;
};

union SetBuilderCallBits
{
	void (*raw)();
	SetBuilderCall member;
};

union SetStatusBitCallBits
{
	void (*raw)();
	SetStatusBitCall member;
};

union SetPositionCallBits
{
	void (*raw)();
	SetPositionCall member;
};

union SetOrientationCallBits
{
	void (*raw)();
	SetOrientationCall member;
};

union ClearAndSetCallBits
{
	void (*raw)();
	ClearAndSetCall member;
};

union OnStructureCreatedCallBits
{
	void (*raw)();
	OnStructureCreatedCall member;
};

union FlattenTerrainCallBits
{
	void (*raw)();
	FlattenTerrainCall member;
};

union AddObjectCallBits
{
	void (*raw)();
	AddObjectCall member;
};

union ConstructClearCallBits
{
	void (*raw)();
	ConstructClearCall member;
};

union ConstructSetCallBits
{
	void (*raw)();
	ConstructSetCall member;
};

static __forceinline void bfmeCreateMachines(Rva002C96D0FullWorker *worker)
{
	CreateMachinesCallBits call;
	call.raw = j_0003fa53;
	(worker->*call.member)();
}

static __forceinline Object *bfmeNewObject(Rva002C96D0ThingFactory *factory,
	const ThingTemplate *what, Team *team,
	const volatile ObjectStatusMaskType &statusBits, UnsignedInt extra)
{
	NewObjectCallBits call;
	call.raw = j_0004494a;
	return (factory->*call.member)(what, team, statusBits, extra);
}

static __forceinline Int bfmeCalcCost(const ThingTemplate *what,
	const Player *player, Int buildIndex)
{
	CalcCostCallBits call;
	call.raw = j_0000da8a;
	return ((Rva002C96D0ThingTemplate *)what->*call.member)(player, buildIndex);
}

static __forceinline void bfmeSetProducer(Object *object, const Object *producer)
{
	SetProducerCallBits call;
	call.raw = j_0000d990;
	(((Rva002C96D0Object *)object)->*call.member)(producer);
}

static __forceinline void bfmeSetBuilder(Object *object, const Object *builder)
{
	SetBuilderCallBits call;
	call.raw = j_00001f41;
	(((Rva002C96D0Object *)object)->*call.member)(builder);
}

static __forceinline void bfmeWithdraw(Rva002C96D0Money *money,
	UnsignedInt amount, Bool playSound)
{
	WithdrawCallBits call;
	call.raw = j_00041894;
	(money->*call.member)(amount, playSound);
}

static __forceinline void bfmeSetStatusBit(Object *object, Int status, Bool set)
{
	SetStatusBitCallBits call;
	call.raw = j_00032dee;
	(((Rva002C96D0Object *)object)->*call.member)(status, set);
}

static __forceinline void bfmeSetPosition(Object *object, const Coord3D *position)
{
	SetPositionCallBits call;
	call.raw = j_0003a1a7;
	(((Rva002C96D0Object *)object)->*call.member)(position);
}

static __forceinline void bfmeSetOrientation(Object *object, Real angle)
{
	SetOrientationCallBits call;
	call.raw = j_000399a5;
	(((Rva002C96D0Object *)object)->*call.member)(angle);
}

static __forceinline void bfmeFlattenTerrain(Rva002C96D0TerrainLogic *terrain,
	Object *object)
{
	FlattenTerrainCallBits call;
	call.raw = j_00049d2d;
	(terrain->*call.member)(object);
}

static __forceinline void bfmeAddObject(Rva002C96D0Pathfinder *pathfinder,
	Object *object)
{
	AddObjectCallBits call;
	call.raw = j_0000b81b;
	(pathfinder->*call.member)(object);
}

static __forceinline void bfmeOnStructureCreated(Rva002C96D0Player *player,
	Object *builder, Object *structure)
{
	OnStructureCreatedCallBits call;
	call.raw = j_0003aa8f;
	(player->*call.member)(builder, structure);
}

static __forceinline void bfmeClearAndSet(Object *object,
	const Rva002C96D0ModelMask &set, const Rva002C96D0ModelMask &clear)
{
	ClearAndSetCallBits call;
	call.raw = j_000095ed;
	(((Rva002C96D0Object *)object)->*call.member)(set, clear);
}

static __forceinline Rva002C96D0Money *bfmeGetMoney(Player *player)
{
	return (Rva002C96D0Money *)((char *)player + 0x48);
}

#define TheBuildAssistant (*(Rva002C96D0BuildAssistant **)0x012ED83C)
#define TheThingFactory (*(Rva002C96D0ThingFactory **)0x012EF1D8)
#define TheTerrainLogic (*(Rva002C96D0TerrainLogicPre **)0x012EF4CC)
#define TheAI (*(Rva002C96D0AI **)0x012EF214)
extern const Real g_bfmeUint32Scale;
#define BFME_DEFAULT_HEALTH (*(const Real *)0x01075334)

// ?construct@WorkerAIUpdate@@WCAA@AEPAVObject@@PBVThingTemplate@@PBUCoord3D@@MPAVPlayer@@_N@Z
Object *Rva002C96D0WorkerAIUpdate::construct(const ThingTemplate *what,
	const Coord3D *pos, Real angle, Player *owningPlayer, Bool isRebuild)
{
	setRebuild(isRebuild);
	bfmeCreateMachines((Rva002C96D0FullWorker *)((char *)this - 0x340));

	if (what == 0 || pos == 0 || owningPlayer == 0)
		return 0;

	if (isRebuild == false)
	{
		if (((Rva002C96D0Player *)owningPlayer)->getPlayerType() == 1)
		{
			if (TheBuildAssistant->isLocationLegalToBuild(
					pos, what, angle, 6, getObject(), 0) != 0)
				return 0;
		}
		else
		{
			if (TheBuildAssistant->canMakeUnit(getObject(), what, -1) != 0)
				return 0;
			if (TheBuildAssistant->isLocationLegalToBuild(
					pos, what, angle, 0x17, getObject(), 0) != 0)
				return 0;
		}
	}

	ObjectStatusMaskType statusBits(ObjectStatusMaskType::kInit, 2);
	if (isRebuild)
		statusBits.set(21);

	Object *obj = bfmeNewObject(TheThingFactory, what,
		((Rva002C96D0Player *)owningPlayer)->getDefaultTeam(), statusBits, 0);
	bfmeSetProducer(obj, getObject());
	bfmeSetBuilder(obj, getObject());
	((Rva002C96D0SupplyTruckInterface *)((char *)this + 8))
		->exitingSupplyTruckState();

	if (isRebuild == false)
	{
		Int cost = bfmeCalcCost(what, owningPlayer, -1);
		bfmeWithdraw(bfmeGetMoney(owningPlayer), (UnsignedInt)cost, true);
		((Rva002C96D0Object *)obj)->m_constructionCost =
			(Real)(UnsignedInt)cost;
	}

	bfmeSetStatusBit(obj, 2, true);
	bfmeSetPosition(obj, pos);
	bfmeSetOrientation(obj, angle);
	bfmeFlattenTerrain((Rva002C96D0TerrainLogic *)TheTerrainLogic, obj);
	Coord3D adjustedPos;
	adjustedPos.z = pos->z;
	adjustedPos.y = pos->y;
	adjustedPos.x = pos->x;
	adjustedPos.z = TheTerrainLogic->getGroundHeight(pos->x, pos->y);
	bfmeSetPosition(obj, &adjustedPos);
	bfmeAddObject(TheAI->pathfinder(), obj);
	bfmeOnStructureCreated((Rva002C96D0Player *)owningPlayer,
		getObject(), obj);

	((Rva002C96D0Object *)obj)->m_constructionPercent = 0.0f;
	Rva002C96D0BodyModule *body = ((Rva002C96D0Object *)obj)->getBodyModule();
	Real healthDelta = -body->getHealth(0) + BFME_DEFAULT_HEALTH;
	body->internalChangeHealth(healthDelta);

	Rva002C96D0ClearMask clearMask;
	Rva002C96D0SetMask setMask;
	ConstructClearCallBits clearCall;
	clearCall.raw = j_0003d424;
	ConstructSetCallBits setCall;
	setCall.raw = j_00004048;
	bfmeClearAndSet(obj,
		(const Rva002C96D0ModelMask &)*(setMask.*setCall.member)(0, 0x43, 0x44),
		(const Rva002C96D0ModelMask &)*(clearMask.*clearCall.member)(0, 0x42));

	newTask(0, obj);
	return obj;
}
