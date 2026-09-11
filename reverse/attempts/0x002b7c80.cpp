// ?construct@DozerAIUpdate@@WCAA@AEPAVObject@@PBVThingTemplate@@PBUCoord3D@@MPAVPlayer@@_N@Z
// partial score=0.97 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// BFME's DozerAIInterface construct slot enters through the interface slice
// at owner+0x340.  Keep the moved BFME fields local to this conversion.
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct Coord3D
{
	__forceinline Coord3D(const Coord3D &other)
		: z(other.z), x(other.x), y(other.y) { }

	Real x;
	Real y;
	Real z;
};

class Object;
class Player;
class Team;
class ThingTemplate;

template <Int NUMBITS>
class Rva002B7C80BitFlags
{
	public:
	enum InitTag { kInit };

	Rva002B7C80BitFlags() { }

	Rva002B7C80BitFlags(InitTag, Int index)
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

typedef Rva002B7C80BitFlags<86> ObjectStatusMaskType;

struct Rva002B7C80ModelMask
{
	UnsignedInt m_words[10];
};

class Rva002B7C80ClearMask
{
public:
	UnsignedInt m_words[10];
};

class Rva002B7C80SetMask
{
public:
	UnsignedInt m_words[10];
};

template <Int N>
class Rva002B7C80VirtualSlots : public Rva002B7C80VirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class Rva002B7C80VirtualSlots<0>
{
};

class Rva002B7C80BodyHealth : public Rva002B7C80VirtualSlots<4>
{
public:
	virtual Real getHealth(Int unused) const = 0;
};

class Rva002B7C80BodyModule : public Rva002B7C80BodyHealth
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

class Rva002B7C80Object
{
public:
	void setProducer(const Object *producer);
	void setBuilder(const Object *builder);
	void setPosition(const Coord3D *position);
	void setOrientation(Real angle);
	void clearAndSetModelConditionFlags(
		const Rva002B7C80ModelMask &clear,
		const Rva002B7C80ModelMask &set);

	Rva002B7C80BodyModule *getBodyModule()
	{
		return m_body;
	}

	unsigned char m_pad000[0x200];
	Rva002B7C80BodyModule *m_body;
	unsigned char m_pad204[0x1c];
	Real m_constructionPercent;
	unsigned char m_pad224[0x34];
	Real m_constructionCost;
};

class Rva002B7C80Player
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
};

class Rva002B7C80Money
{
public:
	UnsignedInt withdraw(UnsignedInt amount, Bool playSound);
};

class Rva002B7C80ThingTemplate
{
public:
	Int calcCostToBuild(const Player *player, Int buildIndex) const;
};

class Rva002B7C80ThingFactory
{
public:
	Object *newObject(const ThingTemplate *what, Team *team,
		const volatile ObjectStatusMaskType &statusBits, UnsignedInt extra);
};

class Rva002B7C80BuildAssistantPre
	: public Rva002B7C80VirtualSlots<10>
{
public:
	virtual Int isLocationLegalToBuild(const Coord3D *pos,
		const ThingTemplate *what, Real angle, UnsignedInt flags,
		Object *object, Player *player) = 0;
};

class Rva002B7C80BuildAssistant : public Rva002B7C80BuildAssistantPre
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

class Rva002B7C80TerrainLogicPre : public Rva002B7C80VirtualSlots<6>
{
public:
	virtual Real getGroundHeight(Real x, Real y,
		Coord3D *normal = 0) const = 0;
};

class Rva002B7C80TerrainLogic
{
public:
	void flattenTerrain(Object *object);
};

class Rva002B7C80Pathfinder
{
public:
	void addObjectToPathfindMap(Object *object);
};

class Rva002B7C80AI
{
public:
	Rva002B7C80Pathfinder *pathfinder() const
	{
		return *(Rva002B7C80Pathfinder * const *)((const char *)this + 0x0c);
	}
};

class DozerAIUpdate
{
public:
	void createMachines();
};

class Rva002B7C80DozerAIInterface
{
public:
	virtual void onDelete(void) = 0;
	virtual Real getRepairHealthPerSecond(void) const = 0;
	virtual Real getBoredTime(void) const = 0;
	virtual Real getBoredRange(void) const = 0;
	virtual Object *construct(const ThingTemplate *what, const Coord3D *pos,
		Real angle, Player *owningPlayer, Bool isRebuild) = 0;
	virtual Int getMostRecentCommand(void) = 0;
	virtual Bool isTaskPending(Int task) = 0;
	virtual UnsignedInt getTaskTarget(Int task) = 0;
	virtual Bool isAnyTaskPending(void) = 0;
	virtual Int getCurrentTask(void) const = 0;
	virtual void setCurrentTask(Int task) = 0;
	virtual Bool getIsRebuild(void) = 0;
	virtual void newTask(Int task, Object *target) = 0;

	Object *getObject() const
	{
		return *(Object * const *)((const char *)this - 0x338);
	}

	void setRebuild(Bool isRebuild)
	{
		*(Bool *)((char *)this + 0x94) = isRebuild;
	}
};

extern void j_00001f41();
extern void j_00004048();
extern void j_000095ed();
extern void j_0000b81b();
extern void j_0000d990();
extern void j_0000da8a();
extern void j_00023033();
extern void j_0003a1a7();
extern void j_0003aa8f();
extern void j_0003d424();
extern void j_000399a5();
extern void j_00041894();
extern void j_0004494a();
extern void j_00049d2d();

typedef void (DozerAIUpdate::*CreateMachinesCall)();
typedef Object *(Rva002B7C80ThingFactory::*NewObjectCall)(
	const ThingTemplate *, Team *, const volatile ObjectStatusMaskType &,
	UnsignedInt);
typedef Int (Rva002B7C80ThingTemplate::*CalcCostCall)(
	const Player *, Int) const;
typedef UnsignedInt (Rva002B7C80Money::*WithdrawCall)(UnsignedInt, Bool);
typedef void (Rva002B7C80Object::*SetProducerCall)(const Object *);
typedef void (Rva002B7C80Object::*SetBuilderCall)(const Object *);
typedef void (Rva002B7C80Object::*SetPositionCall)(const Coord3D *);
typedef void (Rva002B7C80Object::*SetOrientationCall)(Real);
typedef void (Rva002B7C80Object::*ClearAndSetCall)(
	const Rva002B7C80ModelMask &, const Rva002B7C80ModelMask &);
typedef void (Rva002B7C80Player::*OnStructureCreatedCall)(Object *, Object *);
typedef void (Rva002B7C80TerrainLogic::*FlattenTerrainCall)(Object *);
typedef void (Rva002B7C80Pathfinder::*AddObjectCall)(Object *);
typedef Rva002B7C80ClearMask *(Rva002B7C80ClearMask::*ConstructClearCall)(
	void *, UnsignedInt);
typedef Rva002B7C80SetMask *(Rva002B7C80SetMask::*ConstructSetCall)(
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

static __forceinline void bfmeCreateMachines(DozerAIUpdate *owner)
{
	CreateMachinesCallBits call;
	call.raw = j_00023033;
	(owner->*call.member)();
}

static __forceinline Object *bfmeNewObject(Rva002B7C80ThingFactory *factory,
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
	return ((Rva002B7C80ThingTemplate *)what->*call.member)(
		player, buildIndex);
}

static __forceinline void bfmeSetProducer(Object *object,
	const Object *producer)
{
	SetProducerCallBits call;
	call.raw = j_0000d990;
	(((Rva002B7C80Object *)object)->*call.member)(producer);
}

static __forceinline void bfmeSetBuilder(Object *object,
	const Object *builder)
{
	SetBuilderCallBits call;
	call.raw = j_00001f41;
	(((Rva002B7C80Object *)object)->*call.member)(builder);
}

static __forceinline void bfmeWithdraw(Rva002B7C80Money *money,
	UnsignedInt amount, Bool playSound)
{
	WithdrawCallBits call;
	call.raw = j_00041894;
	(money->*call.member)(amount, playSound);
}

static __forceinline void bfmeSetPosition(Object *object,
	const Coord3D *position)
{
	SetPositionCallBits call;
	call.raw = j_0003a1a7;
	(((Rva002B7C80Object *)object)->*call.member)(position);
}

static __forceinline void bfmeSetOrientation(Object *object, Real angle)
{
	SetOrientationCallBits call;
	call.raw = j_000399a5;
	(((Rva002B7C80Object *)object)->*call.member)(angle);
}

static __forceinline void bfmeFlattenTerrain(
	Rva002B7C80TerrainLogic *terrain, Object *object)
{
	FlattenTerrainCallBits call;
	call.raw = j_00049d2d;
	(terrain->*call.member)(object);
}

static __forceinline void bfmeAddObject(Rva002B7C80Pathfinder *pathfinder,
	Object *object)
{
	AddObjectCallBits call;
	call.raw = j_0000b81b;
	(pathfinder->*call.member)(object);
}

static __forceinline void bfmeOnStructureCreated(
	Rva002B7C80Player *player, Object *builder, Object *structure)
{
	OnStructureCreatedCallBits call;
	call.raw = j_0003aa8f;
	(player->*call.member)(builder, structure);
}

static __forceinline void bfmeClearAndSet(Object *object,
	const Rva002B7C80ModelMask &set,
	const Rva002B7C80ModelMask &clear)
{
	ClearAndSetCallBits call;
	call.raw = j_000095ed;
	(((Rva002B7C80Object *)object)->*call.member)(clear, set);
}

static __forceinline Rva002B7C80Money *bfmeGetMoney(Player *player)
{
	return (Rva002B7C80Money *)((char *)player + 0x48);
}

#define TheBuildAssistant (*(Rva002B7C80BuildAssistant **)0x012ED83C)
#define TheThingFactory (*(Rva002B7C80ThingFactory **)0x012EF1D8)
#define TheTerrainLogic (*(Rva002B7C80TerrainLogicPre **)0x012EF4CC)
#define TheAI (*(Rva002B7C80AI **)0x012EF214)
#define BFME_UINT32_SCALE (*(const Real *)0x01075358)
#define BFME_DEFAULT_HEALTH (*(const Real *)0x01075334)

// ?construct@DozerAIUpdate@@WCAA@AEPAVObject@@PBVThingTemplate@@PBUCoord3D@@MPAVPlayer@@_N@Z
Object *Rva002B7C80DozerAIInterface::construct(const ThingTemplate *what,
	const Coord3D *pos, Real angle, Player *owningPlayer, Bool isRebuild)
{
	setRebuild(isRebuild);
	bfmeCreateMachines((DozerAIUpdate *)((char *)this - 0x340));

	if (what == 0 || pos == 0 || owningPlayer == 0)
		return 0;

	if (isRebuild == false &&
		((Rva002B7C80Player *)owningPlayer)->getPlayerType() != 1)
	{
		if (TheBuildAssistant->canMakeUnit(getObject(), what, -1) != 0)
			return 0;
		if (TheBuildAssistant->isLocationLegalToBuild(
				pos, what, angle, 0x17, getObject(), 0) != 0)
			return 0;
	}

	ObjectStatusMaskType statusBits(ObjectStatusMaskType::kInit, 2);
	if (isRebuild)
		statusBits.set(21);

	Object *obj = bfmeNewObject(TheThingFactory, what,
		((Rva002B7C80Player *)owningPlayer)->getDefaultTeam(), statusBits, 0);
	bfmeSetProducer(obj, getObject());
	bfmeSetBuilder(obj, getObject());

	if (isRebuild == false)
	{
		Int cost = bfmeCalcCost(what, owningPlayer, -1);
		bfmeWithdraw(bfmeGetMoney(owningPlayer),
			(UnsignedInt)cost, true);
		((Rva002B7C80Object *)obj)->m_constructionCost =
			(Real)(UnsignedInt)cost;
	}

	bfmeSetPosition(obj, pos);
	bfmeSetOrientation(obj, angle);
	bfmeFlattenTerrain((Rva002B7C80TerrainLogic *)TheTerrainLogic, obj);
	Coord3D adjustedPos = *pos;
	adjustedPos.z = TheTerrainLogic->getGroundHeight(pos->x, pos->y);
	bfmeSetPosition(obj, &adjustedPos);
	bfmeAddObject(TheAI->pathfinder(), obj);
	bfmeOnStructureCreated((Rva002B7C80Player *)owningPlayer,
		getObject(), obj);

	((Rva002B7C80Object *)obj)->m_constructionPercent = 0.0f;
	Rva002B7C80BodyModule *body =
		((Rva002B7C80Object *)obj)->getBodyModule();
	body->internalChangeHealth(-body->getHealth(0) + BFME_DEFAULT_HEALTH);

	Rva002B7C80ClearMask clearMask;
	Rva002B7C80SetMask setMask;
	ConstructClearCallBits clearCall;
	clearCall.raw = j_0003d424;
	ConstructSetCallBits setCall;
	setCall.raw = j_00004048;
	ClearAndSetCallBits clearAndSet;
	clearAndSet.raw = j_000095ed;
	(((Rva002B7C80Object *)obj)->*clearAndSet.member)(
		(const Rva002B7C80ModelMask &)*(setMask.*setCall.member)(
			0, 0x43, 0x44),
		(const Rva002B7C80ModelMask &)*(clearMask.*clearCall.member)(0, 0x42));

	newTask(0, obj);
	return obj;
}
