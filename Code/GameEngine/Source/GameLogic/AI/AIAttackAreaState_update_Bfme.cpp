// cl: /DNDEBUG /MD /EHsc
// BFME layout reconstruction for retail RVA 0x0017E900.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class Object;
class PolygonTrigger;
class AttackPriorityInfo;

class BfmeCurrentState
{
public:
	unsigned char m_pad00[4];
	UnsignedInt m_id;
};

class GameLogic
{
	unsigned char m_pad00[0x3c];

public:
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;
extern void *TheAI;

class BfmeStateMachine
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual StateReturnType updateStateMachine() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual StateReturnType setState(UnsignedInt state) = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void setGoalObject(const Object *object) = 0;

	unsigned char m_pad04[0x10 - 4];
	Object *m_owner;
	unsigned char m_pad14[0x1c - 0x14];
	BfmeCurrentState *m_currentState;
	unsigned char m_pad20[0x40 - 0x20];
	Bool m_locked;

public:
	UnsignedInt getCurrentStateID() const
	{
		return m_currentState ? m_currentState->m_id : 0xffffffff;
	}
};

class State
{
protected:
	virtual void baseSlot() = 0;
	unsigned char m_pad04[0x1c - 4];
	BfmeStateMachine *m_machine;
	unsigned char m_pad20[4];
};

#define BFME_AI_SLOT(n) virtual void slot##n() = 0;

class BfmeAIUpdate
{
public:
	BFME_AI_SLOT(000) BFME_AI_SLOT(004) BFME_AI_SLOT(008) BFME_AI_SLOT(00c)
	BFME_AI_SLOT(010) BFME_AI_SLOT(014) BFME_AI_SLOT(018) BFME_AI_SLOT(01c)
	BFME_AI_SLOT(020) BFME_AI_SLOT(024) BFME_AI_SLOT(028) BFME_AI_SLOT(02c)
	BFME_AI_SLOT(030) BFME_AI_SLOT(034) BFME_AI_SLOT(038) BFME_AI_SLOT(03c)
	BFME_AI_SLOT(040) BFME_AI_SLOT(044) BFME_AI_SLOT(048) BFME_AI_SLOT(04c)
	BFME_AI_SLOT(050) BFME_AI_SLOT(054) BFME_AI_SLOT(058) BFME_AI_SLOT(05c)
	BFME_AI_SLOT(060) BFME_AI_SLOT(064) BFME_AI_SLOT(068) BFME_AI_SLOT(06c)
	BFME_AI_SLOT(070) BFME_AI_SLOT(074) BFME_AI_SLOT(078) BFME_AI_SLOT(07c)
	BFME_AI_SLOT(080) BFME_AI_SLOT(084) BFME_AI_SLOT(088) BFME_AI_SLOT(08c)
	BFME_AI_SLOT(090) BFME_AI_SLOT(094) BFME_AI_SLOT(098) BFME_AI_SLOT(09c)
	BFME_AI_SLOT(0a0) BFME_AI_SLOT(0a4) BFME_AI_SLOT(0a8) BFME_AI_SLOT(0ac)
	BFME_AI_SLOT(0b0) BFME_AI_SLOT(0b4) BFME_AI_SLOT(0b8) BFME_AI_SLOT(0bc)
	BFME_AI_SLOT(0c0) BFME_AI_SLOT(0c4) BFME_AI_SLOT(0c8) BFME_AI_SLOT(0cc)
	BFME_AI_SLOT(0d0) BFME_AI_SLOT(0d4) BFME_AI_SLOT(0d8) BFME_AI_SLOT(0dc)
	BFME_AI_SLOT(0e0) BFME_AI_SLOT(0e4) BFME_AI_SLOT(0e8) BFME_AI_SLOT(0ec)
	BFME_AI_SLOT(0f0) BFME_AI_SLOT(0f4) BFME_AI_SLOT(0f8) BFME_AI_SLOT(0fc)
	BFME_AI_SLOT(100) BFME_AI_SLOT(104) BFME_AI_SLOT(108) BFME_AI_SLOT(10c)
	BFME_AI_SLOT(110) BFME_AI_SLOT(114) BFME_AI_SLOT(118) BFME_AI_SLOT(11c)
	BFME_AI_SLOT(120) BFME_AI_SLOT(124) BFME_AI_SLOT(128) BFME_AI_SLOT(12c)
	BFME_AI_SLOT(130) BFME_AI_SLOT(134) BFME_AI_SLOT(138) BFME_AI_SLOT(13c)
	BFME_AI_SLOT(140) BFME_AI_SLOT(144) BFME_AI_SLOT(148) BFME_AI_SLOT(14c)
	BFME_AI_SLOT(150) BFME_AI_SLOT(154) BFME_AI_SLOT(158) BFME_AI_SLOT(15c)
	BFME_AI_SLOT(160) BFME_AI_SLOT(164) BFME_AI_SLOT(168) BFME_AI_SLOT(16c)
	BFME_AI_SLOT(170) BFME_AI_SLOT(174) BFME_AI_SLOT(178) BFME_AI_SLOT(17c)
	BFME_AI_SLOT(180) BFME_AI_SLOT(184) BFME_AI_SLOT(188) BFME_AI_SLOT(18c)
	BFME_AI_SLOT(190) BFME_AI_SLOT(194) BFME_AI_SLOT(198) BFME_AI_SLOT(19c)
	BFME_AI_SLOT(1a0) BFME_AI_SLOT(1a4) BFME_AI_SLOT(1a8)
	virtual const PolygonTrigger *getAreaToGuard() const = 0;

	unsigned char m_pad04[0x70 - 4];
	const AttackPriorityInfo *m_attackInfo;
};

#undef BFME_AI_SLOT

class Object
{
public:
	unsigned char m_pad00[0x204];
	BfmeAIUpdate *m_ai;
};

class AIAttackAreaState : public State
{
public:
	virtual StateReturnType update();

private:
	BfmeStateMachine *m_attackMachine;
	UnsignedInt m_nextEnemyScanTime;
};

extern void j_000331c7(void);
extern void j_0003251f(void);
extern void j_0001d7b9(void);
extern void j_000051be(void);

struct BfmeNoArgBoolCall { Bool call(); };
struct BfmeKindOfCall { Bool call(int kind); };
struct BfmeFindClosestCall
{
	Object *call(const PolygonTrigger *area, Object *owner,
		const AttackPriorityInfo *info);
};
struct BfmePostClosestCall { Object *call(const Object *owner, Bool add); };

static __forceinline Bool bfmeIsOutOfAmmo(Object *object)
{
	typedef Bool (BfmeNoArgBoolCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000331c7;
	return (reinterpret_cast<BfmeNoArgBoolCall *>(object)->*fn.member)();
}

static __forceinline Bool bfmeIsKindOf(Object *object, int kind)
{
	typedef Bool (BfmeKindOfCall::*Function)(int);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0003251f;
	return (reinterpret_cast<BfmeKindOfCall *>(object)->*fn.member)(kind);
}

static __forceinline Object *bfmePostClosest(Object *object, const Object *owner)
{
	typedef Object *(BfmePostClosestCall::*Function)(const Object *, Bool);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_000051be;
	return (reinterpret_cast<BfmePostClosestCall *>(object)->*fn.member)(owner, true);
}

StateReturnType AIAttackAreaState::update()
{
	register AIAttackAreaState *self = this;
	register UnsignedInt now = TheGameLogic->m_frame;
	if (now >= self->m_nextEnemyScanTime)
	{
		Object *owner = self->m_machine->m_owner;

		if (bfmeIsOutOfAmmo(owner) && !bfmeIsKindOf(owner, 0x19))
			return STATE_FAILURE;

		self->m_nextEnemyScanTime = now + 5;

		BfmeAIUpdate *ai = owner->m_ai;
		if (ai->getAreaToGuard() == 0)
			return STATE_FAILURE;

		const AttackPriorityInfo *info = ai->m_attackInfo;
		typedef Object *(BfmeFindClosestCall::*Function)(
			const PolygonTrigger *, Object *, const AttackPriorityInfo *);
		union { void (*raw)(void); Function member; } fn;
		fn.raw = j_0001d7b9;
		Object *victim = (reinterpret_cast<BfmeFindClosestCall *>(TheAI)->*fn.member)(
			ai->getAreaToGuard(), owner, info);

		if (victim != 0 && bfmeIsKindOf(victim, 0x6c))
			victim = bfmePostClosest(victim, owner);

		self->m_attackMachine->setGoalObject(victim);
		if (self->m_attackMachine->getCurrentStateID() == 0 && victim)
			self->m_attackMachine->setState(10);
		if (victim == 0)
			return STATE_SUCCESS;
	}

	self->m_machine->m_locked = true;
	StateReturnType ret = self->m_attackMachine->updateStateMachine();
	self->m_machine->m_locked = false;
	return ret > STATE_CONTINUE ? STATE_CONTINUE : ret;
}
