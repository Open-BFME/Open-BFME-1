// cl: /DNDEBUG /MD /EHsc
// BFME retail 0x002B8100: DozerActionMoveToActionPosState::update.

typedef unsigned char Bool;
typedef float Real;
typedef int ObjectID;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum DozerTask
{
	DOZER_TASK_BUILD = 0,
	DOZER_TASK_REPAIR = 1
};

enum KindOfType
{
	KINDOF_DOZER = 15
};

struct BfmePt951
{
	Real x;
	Real y;
	Real z;
};

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class Object;

class BfmeMoveStateMachine : public BfmeVirtualSlots<14>
{
public:
	virtual void setGoalObject(const Object *object) = 0;

	unsigned char m_pad04[0x0c];
	Object *m_owner;
	unsigned char m_pad14[0x10];
	BfmePt951 m_goalPosition;
};

class State
{
protected:
	virtual void baseSlot() = 0;
	unsigned char m_pad04[0x18];
	BfmeMoveStateMachine *m_machine;
	unsigned char m_pad20[4];
};

class DozerActionMoveToActionPosState : public State
{
public:
	virtual StateReturnType update();

	DozerTask m_task;
};

class BfmeMoveObject
{
public:
	unsigned char m_pad00[0x74];
	ObjectID m_id;
	unsigned char m_pad78[0x48];
	Real m_boundingSphereRadius;
	unsigned char m_padC4[0x140];
	class AIUpdateInterface *m_ai;
};

class BfmeGap951
{
public:
	Real bfmeGapB951(const BfmePt951 *point) const;
};

class BfmeThing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class BfmeHealingObject
{
public:
	ObjectID getSoleHealingBenefactor() const;
};

class BfmeI1166
{
public:
	unsigned int m_words[10];
};

class Rva00170C70BitSet
{
public:
	unsigned int m_words[10];
};

class BfmeC1166
{
public:
	unsigned int m_words[10];
};

class BfmeModelConditionObject
{
public:
	void clearAndSetModelConditionFlags(const BfmeC1166 &clear,
		const BfmeC1166 &set);
};

class DozerAIInterface : public BfmeVirtualSlots<14>
{
public:
	virtual Bool internalTaskComplete(DozerTask task) = 0;
};

class AIUpdateInterface : public BfmeVirtualSlots<79>
{
public:
	virtual DozerAIInterface *getDozerAIInterface() = 0;
};

class BfmeDozerAI : public BfmeVirtualSlots<96>
{
public:
	virtual Bool isIdle() const = 0;
};

extern void j_000029d7();
extern void j_00004048();
extern void j_000095ed();
extern void j_0000e570();
extern void j_000158b1();
extern void j_0003251f();
extern void j_0003d424();

typedef Bool (BfmeThing::*IsKindOf)(KindOfType) const;
typedef ObjectID (BfmeHealingObject::*GetBenefactor)() const;
typedef Real (BfmeGap951::*GetDistance)(const BfmePt951 *) const;
typedef BfmeI1166 *(BfmeI1166::*ConstructI)(int, unsigned int, unsigned int);
typedef Rva00170C70BitSet *(Rva00170C70BitSet::*ConstructBitSet)(
	void *, unsigned int);
typedef void (BfmeModelConditionObject::*ClearAndSet)(
	const BfmeC1166 &, const BfmeC1166 &);

union IsKindOfCall
{
	void (*freeFunction)();
	IsKindOf memberFunction;
};

union GetBenefactorCall
{
	void (*freeFunction)();
	GetBenefactor memberFunction;
};

union GetDistanceCall
{
	void (*freeFunction)();
	GetDistance memberFunction;
};

union ConstructICall
{
	void (*freeFunction)();
	ConstructI memberFunction;
};

union ConstructBitSetCall
{
	void (*freeFunction)();
	ConstructBitSet memberFunction;
};

union ClearAndSetCall
{
	void (*freeFunction)();
	ClearAndSet memberFunction;
};

inline const Real &bfmeMax(const Real &left, const Real &right)
{
	return left > right ? left : right;
}

#define BFME_ACTION_SLOP (*(const Real *)0x010888F0)
#define BFME_MIN_ACTION_TOLERANCE (*(const Real *)0x010C6788)

StateReturnType DozerActionMoveToActionPosState::update()
{
	register DozerActionMoveToActionPosState *self = this;
	typedef Object * (__fastcall *GetGoalObject)(BfmeMoveStateMachine *);
	Object *goalObject = ((GetGoalObject)j_0000e570)(self->m_machine);
	BfmeMoveObject *dozer = (BfmeMoveObject *)self->m_machine->m_owner;
	if (goalObject == 0 || dozer == 0)
		return STATE_FAILURE;

	AIUpdateInterface *ai = dozer->m_ai;
	if (self->m_task == DOZER_TASK_REPAIR)
	{
		IsKindOfCall isKindOf;
		isKindOf.freeFunction = j_0003251f;
		if (!( (BfmeThing *)dozer->*isKindOf.memberFunction)(KINDOF_DOZER))
		{
			GetBenefactorCall getBenefactor;
			getBenefactor.freeFunction = j_000029d7;
			ObjectID currentRepairer =
				((BfmeHealingObject *)goalObject->*getBenefactor.memberFunction)();
			if (currentRepairer != 0 && currentRepairer != dozer->m_id)
			{
				if (ai != 0)
				{
					DozerAIInterface *dozerAI = ai->getDozerAIInterface();
					if (dozerAI != 0)
						dozerAI->internalTaskComplete(self->m_task);
				}
				self->m_machine->setGoalObject(0);
				return STATE_FAILURE;
			}
		}
	}

	GetDistanceCall getDistance;
	getDistance.freeFunction = j_000158b1;
	Real distSqr =
		((BfmeGap951 *)dozer->*getDistance.memberFunction)(
			(const BfmePt951 *)&self->m_machine->m_goalPosition);
	Real radiusPlusSlop = dozer->m_boundingSphereRadius + BFME_ACTION_SLOP;
	const Real &allowableDistance =
		bfmeMax(BFME_MIN_ACTION_TOLERANCE, radiusPlusSlop);
	if (distSqr <= allowableDistance * allowableDistance)
	{
		if (self->m_task == DOZER_TASK_BUILD)
		{
			BfmeI1166 setMask;
			ConstructICall constructI;
			constructI.freeFunction = j_00004048;

			Rva00170C70BitSet clearMask;
			ConstructBitSetCall constructBitSet;
			constructBitSet.freeFunction = j_0003d424;

			ClearAndSetCall clearAndSet;
			clearAndSet.freeFunction = j_000095ed;
			((BfmeModelConditionObject *)goalObject->*clearAndSet.memberFunction)(
				(const BfmeC1166 &)*(clearMask.*constructBitSet.memberFunction)(
					0, 0x42),
				(const BfmeC1166 &)*(setMask.*constructI.memberFunction)(
					0, 0x43, 0x44));
		}
		return STATE_SUCCESS;
	}

	if (ai != 0 && ((BfmeDozerAI *)ai)->isIdle())
		return STATE_FAILURE;
	return STATE_CONTINUE;
}
