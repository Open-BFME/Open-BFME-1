// ?onEnter@AIAttackMeleeHordeApproachTargetState@@UAEHXZ
// partial score=0.27 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// AIAttackMeleeHordeApproachTargetState::onEnter, retail RVA 0x001834E0.
// Identity proven by the constructor at 0x0017F610
// (AIAttackMeleeHordeApproachTargetStateCtor.cpp) installing the same
// vtable, by the shared field layout of the already-landed
// AIAttackMeleeHordeApproachTargetState::onExit sibling
// (AIAttackMeleeHordeApproachTargetState_onExit.cpp), and by the three
// "CritterDesync: ..." strings embedded in this body (read from the
// retail EXE at their DIR32 addresses).

class Object;

class StateMachineView
{
public:
	unsigned char m_pad000[0x10];
	Object *m_owner;
};

class Player
{
public:
	unsigned char m_pad000[0x2c];
	Int m_field2c;
};

class AIUpdateInterface
{
public:
	unsigned char m_pad000[0x33a];
	unsigned char m_field33a;
};

class Object
{
public:
	unsigned char m_pad000[0x98];
	UnsignedInt m_field98;
	unsigned char m_pad09c[0x1fc - 0x9c];
	void *m_field1fc;
	unsigned char m_pad200[0x204 - 0x200];
	AIUpdateInterface *m_ai;
};

extern void j_00020824();
extern void j_0000e570();
extern void j_0000432c();
extern void j_0002056d();
extern void j_00004c37();
extern "C" void __cdecl _bfmeRetailCritterDesyncLog(void *check, const char *format, ...);

extern bool Glo012F0239;
extern void *TheCRCParameterCheck;

static Player *ownerGetControllingPlayer(Object *self)
{
	struct Thunk { void *call(); };
	typedef void *(Thunk::*Function)();
	union { void (*raw)(); Function member; } fn;
	fn.raw = j_00020824;
	return reinterpret_cast<Player *>((reinterpret_cast<Thunk *>(self)->*fn.member)());
}

static Object *machineGetGoalObject(StateMachineView *self)
{
	struct Thunk { void *call(); };
	typedef void *(Thunk::*Function)();
	union { void (*raw)(); Function member; } fn;
	fn.raw = j_0000e570;
	return reinterpret_cast<Object *>((reinterpret_cast<Thunk *>(self)->*fn.member)());
}

static Bool machineIsGoalObjectDestroyed(StateMachineView *self)
{
	struct Thunk { Bool call(); };
	typedef Bool (Thunk::*Function)();
	union { void (*raw)(); Function member; } fn;
	fn.raw = j_0000432c;
	return (reinterpret_cast<Thunk *>(self)->*fn.member)();
}

static Bool bfmeMeleeHordeTargetInvalid(Object *owner, Object *goal)
{
	typedef Bool (__cdecl *Call)(Object *, Object *);
	union { void (*raw)(void); Call member; } fn;
	fn.raw = (void (*)(void))j_0002056d;
	return fn.member(owner, goal);
}

static Bool bfmeCallENJ(Object *owner, Object *goal)
{
	typedef Bool (__cdecl *Call)(void *, void *);
	union { void (*raw)(void); Call member; } fn;
	fn.raw = (void (*)(void))j_00004c37;
	return fn.member(owner, goal);
}

static Bool rawVCallBool0(void *self, unsigned int slotOffset)
{
	struct Thunk { Bool call(); };
	typedef Bool (Thunk::*Function)();
	void (*raw)() = *reinterpret_cast<void (**)()>(
		*reinterpret_cast<char **>(self) + slotOffset);
	union { void (*r)(); Function member; } fn;
	fn.r = raw;
	return (reinterpret_cast<Thunk *>(self)->*fn.member)();
}

static void *rawVCall0(void *self, unsigned int slotOffset)
{
	struct Thunk { void *call(); };
	typedef void *(Thunk::*Function)();
	void (*raw)() = *reinterpret_cast<void (**)()>(
		*reinterpret_cast<char **>(self) + slotOffset);
	union { void (*r)(); Function member; } fn;
	fn.r = raw;
	return (reinterpret_cast<Thunk *>(self)->*fn.member)();
}

static Bool rawVCall1(void *self, unsigned int slotOffset, void *arg)
{
	struct Thunk { Bool call(void *); };
	typedef Bool (Thunk::*Function)(void *);
	void (*raw)() = *reinterpret_cast<void (**)()>(
		*reinterpret_cast<char **>(self) + slotOffset);
	union { void (*r)(); Function member; } fn;
	fn.r = raw;
	return (reinterpret_cast<Thunk *>(self)->*fn.member)(arg);
}

static void rawVCallInt(void *self, unsigned int slotOffset, Int arg)
{
	struct Thunk { void call(Int); };
	typedef void (Thunk::*Function)(Int);
	void (*raw)() = *reinterpret_cast<void (**)()>(
		*reinterpret_cast<char **>(self) + slotOffset);
	union { void (*r)(); Function member; } fn;
	fn.r = raw;
	(reinterpret_cast<Thunk *>(self)->*fn.member)(arg);
}

class AIInternalMoveToState
{
public:
	virtual Int onEnter();

protected:
	unsigned char m_unmodelled004[0x18];
	StateMachineView *m_machine;
};

class AIAttackMeleeHordeApproachTargetState : public AIInternalMoveToState
{
public:
	virtual Int onEnter();

private:
	unsigned char m_unmodelled020[4];
	Coord3D m_goalPosition;
	unsigned char m_unmodelled030[0x4c - 0x30];
	unsigned char m_field4c;
	unsigned char m_unmodelled04d[0x5c - 0x4d];
	Int m_field5c;
	unsigned char m_field60;
	unsigned char m_field61;
};

Int AIAttackMeleeHordeApproachTargetState::onEnter()
{
	StateMachineView *machine = m_machine;
	Object *owner = machine->m_owner;

	Player *player = ownerGetControllingPlayer(owner);
	register Int field2c = player->m_field2c;
	if (field2c == 1)
		m_field61 = false;

	machine = m_machine;
	Object *goalObject = machineGetGoalObject(machine);
	if (goalObject == 0)
		return -2;

	if (machineIsGoalObjectDestroyed(machine))
		return -1;

	if (owner->m_field1fc != 0 && !bfmeMeleeHordeTargetInvalid(owner, goalObject))
	{
		void *bodyInterface = rawVCall0(owner->m_field1fc, 0x68);
		if (bodyInterface != 0 && rawVCall1(bodyInterface, 0x124, goalObject))
			return -1;
	}

	if ((owner->m_field98 & 8) != 0 || owner->m_ai->m_field33a != 0)
	{
		if (bfmeCallENJ(owner, goalObject))
			return -1;

		rawVCallInt(machine, 0x38, 0);
		return -2;
	}

	m_goalPosition.x = 0.0f;
	m_goalPosition.y = 0.0f;
	m_goalPosition.z = 0.0f;
	m_field5c = -5;

	if (Glo012F0239 && TheCRCParameterCheck != 0)
		_bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: ComputePath11");

	if (!rawVCallBool0(this, 0x44))
		return m_field60 ? -1 : -2;

	if (Glo012F0239 && TheCRCParameterCheck != 0)
		_bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: setAdjustDestination(FALSE) 24");

	m_field4c = 0;
	Int baseResult = AIInternalMoveToState::onEnter();

	if (Glo012F0239 && TheCRCParameterCheck != 0)
		_bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: setAdjustDestination(TRUE) 25");

	m_field4c = m_field61;
	return baseResult;
}
