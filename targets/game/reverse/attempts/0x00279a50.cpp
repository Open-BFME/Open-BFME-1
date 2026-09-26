// ?getNextMoodTarget@AIUpdateInterface@@QAEPAVObject@@_N0@Z
// partial score=0.2 date=2026-09-19
// Best focused source for RVA 0x00279A50. Extracted from AIUpdate.cpp after the final
// non-EH lever pass; helper adapters and the method body are preserved verbatim.

struct Rva00279A50ObjectIntBoolCall
{
	typedef Bool (Rva00279A50ObjectIntBoolCall::*Function)(Int);
};

static __forceinline Bool rva00279A50ObjectIntBool(const void *object, Int value)
{
	union { void (*raw)(void); Rva00279A50ObjectIntBoolCall::Function member; } route;
	route.raw = j_000016a4;
	return (reinterpret_cast<Rva00279A50ObjectIntBoolCall *>(const_cast<void *>(object))->*route.member)(value);
}

struct Rva00279A50FlagsIntBoolCall
{
	typedef Bool (Rva00279A50FlagsIntBoolCall::*Function)(Int);
};

static __forceinline Bool rva00279A50FlagsIntBool(const void *flags, Int value)
{
	union { void (*raw)(void); Rva00279A50FlagsIntBoolCall::Function member; } route;
	route.raw = j_0000666d;
	return (reinterpret_cast<Rva00279A50FlagsIntBoolCall *>(const_cast<void *>(flags))->*route.member)(value);
}

struct Rva00279A50ObjectIntBool3BCall
{
	typedef Bool (Rva00279A50ObjectIntBool3BCall::*Function)(Int);
};

static __forceinline Bool rva00279A50ObjectIntBool3B(const void *object, Int value)
{
	union { void (*raw)(void); Rva00279A50ObjectIntBool3BCall::Function member; } route;
	route.raw = j_00003b1b;
	return (reinterpret_cast<Rva00279A50ObjectIntBool3BCall *>(const_cast<void *>(object))->*route.member)(value);
}

struct Rva00279A50ObjectPlayerCall
{
	typedef Player *(Rva00279A50ObjectPlayerCall::*Function)(void);
};

static __forceinline Player *rva00279A50ControllingPlayer(const void *object)
{
	union { void (*raw)(void); Rva00279A50ObjectPlayerCall::Function member; } route;
	route.raw = j_00020824;
	return (reinterpret_cast<Rva00279A50ObjectPlayerCall *>(const_cast<void *>(object))->*route.member)();
}

struct Rva00279A50ObjectKindCall
{
	typedef Bool (Rva00279A50ObjectKindCall::*Function)(Int);
};

static __forceinline Bool rva00279A50KindOf(const void *object, Int kind)
{
	union { void (*raw)(void); Rva00279A50ObjectKindCall::Function member; } route;
	route.raw = j_0003251f;
	return (reinterpret_cast<Rva00279A50ObjectKindCall *>(const_cast<void *>(object))->*route.member)(kind);
}

struct Rva00279A50GameLogicFindCall
{
	typedef Object *(Rva00279A50GameLogicFindCall::*Function)(ObjectID);
};

static __forceinline Object *rva00279A50FindObject(void *gameLogic, ObjectID id)
{
	union { void (*raw)(void); Rva00279A50GameLogicFindCall::Function member; } route;
	route.raw = j_0001f253;
	return (reinterpret_cast<Rva00279A50GameLogicFindCall *>(gameLogic)->*route.member)(id);
}

struct Rva00279A50NoArgObjectCall
{
	typedef Object *(Rva00279A50NoArgObjectCall::*Function)(void);
};

static __forceinline Object *rva00279A50TeamTarget(void *team)
{
	union { void (*raw)(void); Rva00279A50NoArgObjectCall::Function member; } route;
	route.raw = j_000296a9;
	return (reinterpret_cast<Rva00279A50NoArgObjectCall *>(team)->*route.member)();
}

struct Rva00279A50MoodStateCall
{
	typedef Int (Rva00279A50MoodStateCall::*Function)(void);
};

struct Rva00279A50ObjectNoArgIntCall
{
	typedef Int (Rva00279A50ObjectNoArgIntCall::*Function)(void);
};

static __forceinline Int rva00279A50MoodState(const void *aiUpdate)
{
	union { void (*raw)(void); Rva00279A50MoodStateCall::Function member; } route;
	route.raw = j_000187a0;
	return (reinterpret_cast<Rva00279A50MoodStateCall *>(const_cast<void *>(aiUpdate))->*route.member)();
}

struct Rva00279A50MoodFlagsCall
{
	typedef UnsignedInt (Rva00279A50MoodFlagsCall::*Function)(void);
};

static __forceinline UnsignedInt rva00279A50MoodFlags(const void *aiUpdate)
{
	union { void (*raw)(void); Rva00279A50MoodFlagsCall::Function member; } route;
	route.raw = j_0001bb3f;
	return (reinterpret_cast<Rva00279A50MoodFlagsCall *>(const_cast<void *>(aiUpdate))->*route.member)();
}

struct Rva00279A50ObjectByteAddressCall
{
	typedef unsigned char *(Rva00279A50ObjectByteAddressCall::*Function)(void);
};

static __forceinline unsigned char *rva00279A50ByteAddress(const void *object)
{
	union { void (*raw)(void); Rva00279A50ObjectByteAddressCall::Function member; } route;
	route.raw = j_000209fa;
	return (reinterpret_cast<Rva00279A50ObjectByteAddressCall *>(const_cast<void *>(object))->*route.member)();
}

struct Rva00279A50ObjectWeaponCall
{
	typedef Weapon *(Rva00279A50ObjectWeaponCall::*Function)(Int *);
};

static __forceinline Weapon *rva00279A50CurrentWeapon(const void *object)
{
	union { void (*raw)(void); Rva00279A50ObjectWeaponCall::Function member; } route;
	route.raw = j_00031a7f;
	return (reinterpret_cast<Rva00279A50ObjectWeaponCall *>(const_cast<void *>(object))->*route.member)(NULL);
}

struct Rva00279A50WeaponRangeCall
{
	typedef Bool (Rva00279A50WeaponRangeCall::*Function)(const Object *, const Object *, Int);
};

static __forceinline Bool rva00279A50WeaponInRange(void *weapon, const Object *source,
	const Object *target)
{
	union { void (*raw)(void); Rva00279A50WeaponRangeCall::Function member; } route;
	route.raw = j_0002e85c;
	return (reinterpret_cast<Rva00279A50WeaponRangeCall *>(weapon)->*route.member)(source, target, 0);
}

struct Rva00279A50ObjectPostCall
{
	typedef Object *(Rva00279A50ObjectPostCall::*Function)(const Object *, Bool);
};

static __forceinline Object *rva00279A50PostObject(void *object, const Object *owner, Bool add)
{
	union { void (*raw)(void); Rva00279A50ObjectPostCall::Function member; } route;
	route.raw = j_000051be;
	return (reinterpret_cast<Rva00279A50ObjectPostCall *>(object)->*route.member)(owner, add);
}

struct Rva00279A50ObjectDistanceCall
{
	typedef Real (Rva00279A50ObjectDistanceCall::*Function)(const Object *);
};

static __forceinline Real rva00279A50ObjectDistance(void *object, const Object *other)
{
	union { void (*raw)(void); Rva00279A50ObjectDistanceCall::Function member; } route;
	route.raw = j_0002253e;
	return (reinterpret_cast<Rva00279A50ObjectDistanceCall *>(object)->*route.member)(other);
}

struct Rva00279A50ObjectGapCall
{
	typedef Real (Rva00279A50ObjectGapCall::*Function)(const Object *);
};

static __forceinline Real rva00279A50ObjectGap(void *object, const Object *other)
{
	union { void (*raw)(void); Rva00279A50ObjectGapCall::Function member; } route;
	route.raw = j_00043ced;
	return (reinterpret_cast<Rva00279A50ObjectGapCall *>(object)->*route.member)(other);
}

struct Rva00279A50CoordLengthCall
{
	typedef Real (Rva00279A50CoordLengthCall::*Function)(void);
};

static __forceinline Real rva00279A50CoordLength(void *coord)
{
	union { void (*raw)(void); Rva00279A50CoordLengthCall::Function member; } route;
	route.raw = j_0002fe0f;
	return (reinterpret_cast<Rva00279A50CoordLengthCall *>(coord)->*route.member)();
}

struct Rva00279A50ObjectBoolCall
{
	typedef Bool (Rva00279A50ObjectBoolCall::*Function)(void);
};

static __forceinline Bool rva00279A50CanAttack(const void *object)
{
	union { void (*raw)(void); Rva00279A50ObjectBoolCall::Function member; } route;
	route.raw = j_00001fd7;
	return (reinterpret_cast<Rva00279A50ObjectBoolCall *>(const_cast<void *>(object))->*route.member)();
}

static __forceinline Bool rva00279A50BodyResultTest(void *result)
{
	struct Rva00279A50BodyResultTestCall
	{
		typedef Bool (Rva00279A50BodyResultTestCall::*Function)(void);
	};
	union { void (*raw)(void); Rva00279A50BodyResultTestCall::Function member; } route;
	route.raw = j_0000572c;
	return (reinterpret_cast<Rva00279A50BodyResultTestCall *>(result)->*route.member)();
}

static __forceinline Int rva00279A50RandomValue(Int low, Int high)
{
	typedef Int (__cdecl *Function)(Int, Int, const char *, Int);
	return ((Function)j_00001bae)(low, high, (const char *)0x010B97D8, 0x1D67);
}

static __forceinline Bool rva00279A50PairTest(Object *first, Object *second)
{
	typedef Bool (__cdecl *Function)(Object *, Object *);
	return ((Function)j_00004c37)(first, second);
}

class Rva00279A50FindClosestRoute
{
public:
	typedef Object *(Rva00279A50FindClosestRoute::*Function)(const Object *, Real,
		UnsignedInt, const AttackPriorityInfo *, void *);
};

static __forceinline Object *rva00279A50FindClosest(AI *ai, const Object *owner,
	Real range, UnsignedInt flags, const AttackPriorityInfo *info, void *filter)
{
	union { void (*raw)(void); Rva00279A50FindClosestRoute::Function member; } route;
	route.raw = j_0003f990;
	return (reinterpret_cast<Rva00279A50FindClosestRoute *>(ai)->*route.member)(
		owner, range, flags, info, filter);
}

class Rva00279A50StateProbe;

#define RVA00279A50_SLOT(N) virtual void slot##N(void) = 0
class Rva00279A50UpdateVtable
{
public:
	RVA00279A50_SLOT(000); RVA00279A50_SLOT(001); RVA00279A50_SLOT(002); RVA00279A50_SLOT(003);
	RVA00279A50_SLOT(004); RVA00279A50_SLOT(005); RVA00279A50_SLOT(006); RVA00279A50_SLOT(007);
	RVA00279A50_SLOT(008); RVA00279A50_SLOT(009); RVA00279A50_SLOT(010); RVA00279A50_SLOT(011);
	RVA00279A50_SLOT(012); RVA00279A50_SLOT(013); RVA00279A50_SLOT(014); RVA00279A50_SLOT(015);
	RVA00279A50_SLOT(016); RVA00279A50_SLOT(017); RVA00279A50_SLOT(018); RVA00279A50_SLOT(019);
	RVA00279A50_SLOT(020); RVA00279A50_SLOT(021); RVA00279A50_SLOT(022); RVA00279A50_SLOT(023);
	RVA00279A50_SLOT(024); RVA00279A50_SLOT(025); RVA00279A50_SLOT(026); RVA00279A50_SLOT(027);
	RVA00279A50_SLOT(028); RVA00279A50_SLOT(029); RVA00279A50_SLOT(030); RVA00279A50_SLOT(031);
	RVA00279A50_SLOT(032); RVA00279A50_SLOT(033); RVA00279A50_SLOT(034); RVA00279A50_SLOT(035);
	RVA00279A50_SLOT(036); RVA00279A50_SLOT(037); RVA00279A50_SLOT(038); RVA00279A50_SLOT(039);
	RVA00279A50_SLOT(040); RVA00279A50_SLOT(041); RVA00279A50_SLOT(042); RVA00279A50_SLOT(043);
	RVA00279A50_SLOT(044); RVA00279A50_SLOT(045); RVA00279A50_SLOT(046); RVA00279A50_SLOT(047);
	RVA00279A50_SLOT(048); RVA00279A50_SLOT(049); RVA00279A50_SLOT(050); RVA00279A50_SLOT(051);
	RVA00279A50_SLOT(052); RVA00279A50_SLOT(053); RVA00279A50_SLOT(054); RVA00279A50_SLOT(055);
	RVA00279A50_SLOT(056); RVA00279A50_SLOT(057); RVA00279A50_SLOT(058); RVA00279A50_SLOT(059);
	RVA00279A50_SLOT(060); RVA00279A50_SLOT(061); RVA00279A50_SLOT(062); RVA00279A50_SLOT(063);
	RVA00279A50_SLOT(064); RVA00279A50_SLOT(065); RVA00279A50_SLOT(066); RVA00279A50_SLOT(067);
	RVA00279A50_SLOT(068); RVA00279A50_SLOT(069); RVA00279A50_SLOT(070); RVA00279A50_SLOT(071);
	RVA00279A50_SLOT(072); RVA00279A50_SLOT(073); RVA00279A50_SLOT(074); RVA00279A50_SLOT(075);
	RVA00279A50_SLOT(076); RVA00279A50_SLOT(077); RVA00279A50_SLOT(078);
	virtual Rva00279A50StateProbe *slot079(void) = 0;
	RVA00279A50_SLOT(080); RVA00279A50_SLOT(081); RVA00279A50_SLOT(082); RVA00279A50_SLOT(083);
	RVA00279A50_SLOT(084); RVA00279A50_SLOT(085); RVA00279A50_SLOT(086); RVA00279A50_SLOT(087);
	RVA00279A50_SLOT(088); RVA00279A50_SLOT(089); RVA00279A50_SLOT(090); RVA00279A50_SLOT(091);
	RVA00279A50_SLOT(092); RVA00279A50_SLOT(093); RVA00279A50_SLOT(094); RVA00279A50_SLOT(095);
	RVA00279A50_SLOT(096);
	virtual Bool slot097(void) = 0;
};

class Rva00279A50StateProbe
{
public:
	RVA00279A50_SLOT(00); RVA00279A50_SLOT(04); RVA00279A50_SLOT(08); RVA00279A50_SLOT(0C);
	RVA00279A50_SLOT(10); RVA00279A50_SLOT(14); RVA00279A50_SLOT(18); RVA00279A50_SLOT(1C);
	virtual Bool slot20(void) = 0;
	virtual Int slot24(void) = 0;
};

class Rva00279A50ModuleVtable
{
public:
	RVA00279A50_SLOT(00); RVA00279A50_SLOT(04); RVA00279A50_SLOT(08); RVA00279A50_SLOT(0C);
	RVA00279A50_SLOT(10); RVA00279A50_SLOT(14); RVA00279A50_SLOT(18); RVA00279A50_SLOT(1C);
	RVA00279A50_SLOT(20); RVA00279A50_SLOT(24); RVA00279A50_SLOT(28); RVA00279A50_SLOT(2C);
	RVA00279A50_SLOT(30); RVA00279A50_SLOT(34); RVA00279A50_SLOT(38); RVA00279A50_SLOT(3C);
	RVA00279A50_SLOT(40); RVA00279A50_SLOT(44); RVA00279A50_SLOT(48); RVA00279A50_SLOT(4C);
	RVA00279A50_SLOT(50); RVA00279A50_SLOT(54); RVA00279A50_SLOT(58); RVA00279A50_SLOT(5C);
	RVA00279A50_SLOT(60); RVA00279A50_SLOT(64);
	virtual void *slot68(void) = 0;
	RVA00279A50_SLOT(6C); RVA00279A50_SLOT(70); RVA00279A50_SLOT(74); RVA00279A50_SLOT(78);
	RVA00279A50_SLOT(7C); RVA00279A50_SLOT(80); RVA00279A50_SLOT(84); RVA00279A50_SLOT(88);
	RVA00279A50_SLOT(8C); RVA00279A50_SLOT(90); RVA00279A50_SLOT(94); RVA00279A50_SLOT(98);
	RVA00279A50_SLOT(9C); RVA00279A50_SLOT(A0);
	virtual Bool slotA4(void) = 0;
	RVA00279A50_SLOT(A8); RVA00279A50_SLOT(AC); RVA00279A50_SLOT(B0); RVA00279A50_SLOT(B4);
	RVA00279A50_SLOT(B8); RVA00279A50_SLOT(BC); RVA00279A50_SLOT(C0); RVA00279A50_SLOT(C4);
	RVA00279A50_SLOT(C8); RVA00279A50_SLOT(CC); RVA00279A50_SLOT(D0); RVA00279A50_SLOT(D4);
	RVA00279A50_SLOT(D8); RVA00279A50_SLOT(DC);
	virtual Bool slotE0(void) = 0;
};

class Rva00279A50BodyVtable
{
public:
	RVA00279A50_SLOT(00); RVA00279A50_SLOT(04); RVA00279A50_SLOT(08); RVA00279A50_SLOT(0C);
	RVA00279A50_SLOT(10); RVA00279A50_SLOT(14); RVA00279A50_SLOT(18); RVA00279A50_SLOT(1C);
	RVA00279A50_SLOT(20); RVA00279A50_SLOT(24); RVA00279A50_SLOT(28); RVA00279A50_SLOT(2C);
	RVA00279A50_SLOT(30); RVA00279A50_SLOT(34); RVA00279A50_SLOT(38);
	virtual void *slot3C(void) = 0;
};

class Rva00279A50BodySubVtable
{
public:
	RVA00279A50_SLOT(00); RVA00279A50_SLOT(04); RVA00279A50_SLOT(08); RVA00279A50_SLOT(0C);
	RVA00279A50_SLOT(10); RVA00279A50_SLOT(14); RVA00279A50_SLOT(18); RVA00279A50_SLOT(1C);
	RVA00279A50_SLOT(20); RVA00279A50_SLOT(24); RVA00279A50_SLOT(28); RVA00279A50_SLOT(2C);
	RVA00279A50_SLOT(30); RVA00279A50_SLOT(34); RVA00279A50_SLOT(38); RVA00279A50_SLOT(3C);
	RVA00279A50_SLOT(40); RVA00279A50_SLOT(44); RVA00279A50_SLOT(48); RVA00279A50_SLOT(4C);
	RVA00279A50_SLOT(50); RVA00279A50_SLOT(54); RVA00279A50_SLOT(58); RVA00279A50_SLOT(5C);
	RVA00279A50_SLOT(60); RVA00279A50_SLOT(64); RVA00279A50_SLOT(68); RVA00279A50_SLOT(6C);
	RVA00279A50_SLOT(70); RVA00279A50_SLOT(74); RVA00279A50_SLOT(78); RVA00279A50_SLOT(7C);
	RVA00279A50_SLOT(80); RVA00279A50_SLOT(84); RVA00279A50_SLOT(88); RVA00279A50_SLOT(8C);
	RVA00279A50_SLOT(90); RVA00279A50_SLOT(94); RVA00279A50_SLOT(98);
	virtual void *slot9C(Coord3D *, Object *, Int) = 0;
};

class Rva00279A50TerrainVtable
{
public:
	RVA00279A50_SLOT(00); RVA00279A50_SLOT(04); RVA00279A50_SLOT(08); RVA00279A50_SLOT(0C);
	RVA00279A50_SLOT(10); RVA00279A50_SLOT(14);
	virtual Real slot18(Real, Real, Int) = 0;
};

class Rva00279A50TacticalVtable
{
public:
	RVA00279A50_SLOT(00); RVA00279A50_SLOT(04); RVA00279A50_SLOT(08); RVA00279A50_SLOT(0C);
	RVA00279A50_SLOT(10); RVA00279A50_SLOT(14); RVA00279A50_SLOT(18); RVA00279A50_SLOT(1C);
	RVA00279A50_SLOT(20); RVA00279A50_SLOT(24); RVA00279A50_SLOT(28); RVA00279A50_SLOT(2C);
	virtual void slot30(Coord3D *, Real, UnsignedInt, Int) = 0;
};

class Rva00279A50FunctorFilter
{
public:
	Rva00279A50FunctorFilter(Object *object)
		: m_vtable((void *)0x010B9340), m_zero(0), m_object(object) {}
	~Rva00279A50FunctorFilter()
	{
		m_vtable = (void *)0x01083B5C;
	}

private:
	void *m_vtable;
	UnsignedInt m_zero;
	Object *m_object;
};

#undef RVA00279A50_SLOT

// addTargeter is vtable slot 115 (+0x1cc) of the AIUpdateInterface.
class BFMEAddTargeterAI
{

// getNextMoodTarget body from the same best attempt.

Object* AIUpdateInterface::getNextMoodTarget( Bool calledByAI, Bool calledDuringIdle )
{
	unsigned char *self = reinterpret_cast<unsigned char *>(this);
	Object *obj = *reinterpret_cast<Object **>(self + 0x08);
	unsigned char *object = reinterpret_cast<unsigned char *>(obj);
	Coord3D scratch;

	unsigned char objectFlags = object[0x344];
	if ((objectFlags & 1) != 0)
		return NULL;
	if ((objectFlags & 8) != 0)
		return NULL;
	UnsignedInt objectStatus = *reinterpret_cast<UnsignedInt *>(object + 0x98);
	if ((objectStatus & 0x20) != 0)
		return NULL;
	void *objectAi = *reinterpret_cast<void **>(object + 0x204);
	if (objectAi != NULL && *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(objectAi) + 0x34) != NULL)
		return NULL;
	if ((*reinterpret_cast<UnsignedInt *>(object + 0x90) & 0x800000) != 0)
		return NULL;
	if (rva00279A50ObjectIntBool(obj, 0x25))
		return NULL;
	if (rva00279A50ObjectIntBool(obj, 0x49))
		return NULL;

	if (rva00279A50FlagsIntBool(object + 0x110, 0xCF)
		|| rva00279A50FlagsIntBool(object + 0x110, 0x12C))
		return NULL;

	Bool controllerIsHuman = FALSE;
	if (!rva00279A50ObjectIntBool(obj, 0x43))
	{
		Player *player = rva00279A50ControllingPlayer(obj);
		controllerIsHuman = (*reinterpret_cast<Int *>(reinterpret_cast<unsigned char *>(player) + 0x2C) == 0);
		if (rva00279A50KindOf(obj, 0x0E))
		{
			Rva00279A50StateProbe *state = reinterpret_cast<Rva00279A50UpdateVtable *>(this)->slot079();
			if (state != NULL)
			{
				if (state->slot24() != -1)
					return NULL;
				if (state->slot20())
					return NULL;
			}
		}
	}
	(void)controllerIsHuman;

	ObjectID pending = *reinterpret_cast<ObjectID *>(self + 0x1A4);
	if (pending != 0)
	{
		void *gameLogic = reinterpret_cast<void *>(TheGameLogic);
		Object *pendingObject = rva00279A50FindObject(gameLogic, pending);
		if (pendingObject == NULL
			|| ((*reinterpret_cast<unsigned char *>(reinterpret_cast<unsigned char *>(pendingObject) + 0x344) & 1) != 0)
			|| rva00279A50ObjectIntBool(pendingObject, 0x31))
			return NULL;
		return pendingObject;
	}
	*reinterpret_cast<ObjectID *>(self + 0x1A4) = (ObjectID)0;
	unsigned char *moduleData = *reinterpret_cast<unsigned char **>(self + 0x04);
	void *gameLogic = reinterpret_cast<void *>(TheGameLogic);

	if (calledDuringIdle)
	{
		if ((moduleData[0x20] & 1) == 0)
			return NULL;
		if (reinterpret_cast<Rva00279A50UpdateVtable *>(this)->slot097())
		{
			if ((moduleData[0x20] & 8) != 0)
				return NULL;
			void *module = *reinterpret_cast<void **>(object + 0x214);
			if (module != NULL && moduleData[0x29] == 0
				&& !rva00279A50ObjectIntBool(obj, 0x24))
			{
				void *moduleData2 = *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(module) + 0x1FC);
				if (moduleData2 != NULL
					&& !reinterpret_cast<Rva00279A50ModuleVtable *>(moduleData2)->slotA4())
					return NULL;
			}
		}
	}

	if (calledDuringIdle && rva00279A50ObjectIntBool3B(obj, 0))
	{
		if ((moduleData[0x20] & 2) != 0)
			return NULL;
		void *body = *reinterpret_cast<void **>(object + 0x214);
		if (body == NULL)
			return NULL;
		void *bodyData = *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(body) + 0x1FC);
		void *bodyResult = reinterpret_cast<Rva00279A50BodySubVtable *>(bodyData)->slot9C(
			&scratch, obj, 1);
		if (!rva00279A50BodyResultTest(bodyResult)
			|| rva00279A50ObjectIntBool(obj, 0x10))
			return NULL;
	}

	UnsignedInt now = *reinterpret_cast<UnsignedInt *>(reinterpret_cast<unsigned char *>(gameLogic) + 0x3C);
	Object *teamVictim = NULL;
	if (calledByAI)
	{
		void *team = *reinterpret_cast<void **>(object + 0x23C);
		if (team != NULL)
		{
			void *teamData = *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(team) + 4);
			if (teamData != NULL && *reinterpret_cast<unsigned char *>(reinterpret_cast<unsigned char *>(teamData) + 0x1C2) != 0)
				teamVictim = rva00279A50TeamTarget(team);
		}
		if (teamVictim != NULL && rva00279A50MoodState(this) >= 0)
			return teamVictim;
		if (now < *reinterpret_cast<UnsignedInt *>(self + 0x1FC))
			return NULL;
		Int checkRate = *reinterpret_cast<Int *>(moduleData + 0x1C);
		*reinterpret_cast<UnsignedInt *>(self + 0x1FC) = now + checkRate;
		if (self[0x32A] != 0)
		{
			Int halfRate = checkRate >> 1;
			*reinterpret_cast<UnsignedInt *>(self + 0x1FC) +=
				rva00279A50RandomValue(-halfRate, halfRate);
			self[0x32A] = 0;
		}
	}

	Real rangeToFindWithin = AI::getAdjustedVisionRangeForObject(obj, 3);
	if (rangeToFindWithin <= BfmeZeroRange)
		return NULL;
	void *container = *reinterpret_cast<void **>(object + 0x214);
	if (container != NULL)
		rangeToFindWithin += *reinterpret_cast<Real *>(reinterpret_cast<unsigned char *>(container) + 0xBC);

	UnsignedInt mood = rva00279A50MoodFlags(this);
	if ((mood & 0x202) == 0x202)
	{
		void *body = *reinterpret_cast<void **>(object + 0x200);
		if (body == NULL)
			return NULL;
		void *damage = reinterpret_cast<Rva00279A50BodyVtable *>(body)->slot3C();
		ObjectID sourceID = *reinterpret_cast<ObjectID *>(reinterpret_cast<unsigned char *>(damage) + 8);
		return rva00279A50FindObject(gameLogic, sourceID);
	}
	if ((mood & 0x2000) != 0)
		return NULL;

	if (rva00279A50KindOf(obj, 0x6C) && rva00279A50ObjectIntBool(obj, 0x39))
	{
		void *module = *reinterpret_cast<void **>(object + 0x1FC);
		if (module != NULL)
		{
			void *active = reinterpret_cast<Rva00279A50ModuleVtable *>(module)->slot68();
			if (active != NULL && !reinterpret_cast<Rva00279A50ModuleVtable *>(active)->slotE0())
				return NULL;
		}
	}

	AI *globalAI = TheAI;
	unsigned char *aiData = *reinterpret_cast<unsigned char **>(reinterpret_cast<unsigned char *>(globalAI) + 0x14);
	UnsignedInt flags = 2;
	if (aiData[0x67] != 0)
	{
		if (rva00279A50KindOf(obj, 0x3A))
			flags = 3;
	}
	if (aiData[0x68] != 0)
		flags |= 4;
	if ((moduleData[0x20] & 0x10) != 0)
		flags |= 8;
	if (calledDuringIdle)
	{
		Player *player = rva00279A50ControllingPlayer(obj);
		if (player != NULL && *reinterpret_cast<Int *>(reinterpret_cast<unsigned char *>(player) + 0x2C) == 0)
			flags |= 0x20;
	}
	flags |= 0x40;
	if (calledByAI)
		flags |= 0x10;
	Player *player = rva00279A50ControllingPlayer(obj);
	if (player != NULL && *reinterpret_cast<Int *>(reinterpret_cast<unsigned char *>(player) + 0x2C) == 1)
		flags |= 0x80;

	Object *newVictim = NULL;
	if (self[0x33A] != 0 && calledByAI && calledDuringIdle)
	{
		void *body = *reinterpret_cast<void **>(object + 0x200);
		if (body != NULL)
		{
			void *damage = reinterpret_cast<Rva00279A50BodyVtable *>(body)->slot3C();
			if (damage != NULL)
			{
				Weapon *weapon = rva00279A50CurrentWeapon(obj);
				Object *candidate = rva00279A50FindObject(gameLogic,
					*reinterpret_cast<ObjectID *>(reinterpret_cast<unsigned char *>(damage) + 8));
				if (candidate != NULL && weapon != NULL)
				{
					if (rva00279A50ObjectGap(obj, candidate) > g_bfmeDefaultBU)
						self[0x33A] = 0;
					if (rva00279A50WeaponInRange(weapon, obj, candidate))
						newVictim = candidate;
				}
			}
		}
	}

	if (newVictim == NULL)
	{
		union { void (*raw)(void); Rva00279A50ObjectNoArgIntCall::Function member; } route;
		route.raw = j_00026cf6;
		Int sourceID = (reinterpret_cast<Rva00279A50ObjectNoArgIntCall *>(obj)->*route.member)();
		Object *source = rva00279A50FindObject(gameLogic, (ObjectID)sourceID);
		if (source != NULL)
		{
			newVictim = rva00279A50PostObject(source, obj, TRUE);
			if (newVictim != NULL
				&& rva00279A50ObjectDistance(newVictim, obj) > rangeToFindWithin * rangeToFindWithin)
				newVictim = NULL;
		}
	}

	if (TheWritableGlobalData != NULL
		&& *reinterpret_cast<unsigned char *>(reinterpret_cast<unsigned char *>(TheWritableGlobalData) + 0xEC8) != 0)
	{
		scratch.x = *reinterpret_cast<Real *>(object + 0x38);
		scratch.y = *reinterpret_cast<Real *>(object + 0x3C);
		scratch.z = *reinterpret_cast<Real *>(object + 0x40);
		reinterpret_cast<Rva00279A50TerrainVtable *>(TheTerrainLogic)->slot18(scratch.x, scratch.y, 0);
		reinterpret_cast<Rva00279A50TacticalVtable *>(TheTacticalView)->slot30(
			&scratch, rangeToFindWithin, 0xFF00FF00, 0);
	}

	{
		Rva00279A50FunctorFilter filter(obj);
		Player *owner = rva00279A50ControllingPlayer(obj);
		void *optionalFilter = NULL;
		if (owner != NULL && *reinterpret_cast<Int *>(reinterpret_cast<unsigned char *>(owner) + 0x2C) != 0)
			optionalFilter = &filter;
		const AttackPriorityInfo *attackInfo = *reinterpret_cast<const AttackPriorityInfo **>(self + 0x70);
		newVictim = rva00279A50FindClosest(globalAI, obj, rangeToFindWithin, flags,
			attackInfo, optionalFilter);
	}

	if (newVictim != NULL && !rva00279A50KindOf(obj, 0x6C)
		&& rva00279A50KindOf(newVictim, 0x6C))
		newVictim = rva00279A50PostObject(newVictim, obj, FALSE);
	if (calledDuringIdle && calledByAI && newVictim && !rva00279A50PairTest(obj, newVictim))
		return NULL;
	if (!rva00279A50CanAttack(obj))
		return NULL;
	if (newVictim == NULL)
		return NULL;
	if ((*rva00279A50ByteAddress(obj) & 0x80) == 0
		|| rva00279A50PairTest(obj, newVictim))
		return newVictim;

	Real attackRange = *reinterpret_cast<Real *>(moduleData + 0x2C);
	if (attackRange <= BfmeZeroRange)
		return NULL;
	scratch.x = *reinterpret_cast<Real *>(reinterpret_cast<unsigned char *>(newVictim) + 0x38)
		- *reinterpret_cast<Real *>(object + 0x38);
	scratch.y = *reinterpret_cast<Real *>(reinterpret_cast<unsigned char *>(newVictim) + 0x3C)
		- *reinterpret_cast<Real *>(object + 0x3C);
	scratch.z = *reinterpret_cast<Real *>(reinterpret_cast<unsigned char *>(newVictim) + 0x40)
		- *reinterpret_cast<Real *>(object + 0x40);
	if (rva00279A50CoordLength(&scratch) > attackRange)
		return NULL;
	if (rva00279A50KindOf(obj, 0x6C))
	{
		Object *body = *reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(newVictim) + 0x214);
		if (body != NULL && rva00279A50KindOf(body, 0x6C))
			newVictim = body;
	}
	return newVictim;
}
