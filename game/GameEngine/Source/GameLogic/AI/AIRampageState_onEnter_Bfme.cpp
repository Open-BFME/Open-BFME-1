// cl: /DNDEBUG /MD /EHsc
//
// BFME reconstruction of AIRampageState::onEnter at retail 0x0017EA20.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

extern "C" void *memset(void *destination, int value, unsigned int count);
#pragma intrinsic(memset)
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

template <int NUMBITS>
class BitFlags
{
public:
	enum { NUM_WORDS = (NUMBITS + 31) / 32 };

	BitFlags()
	{
		memset(m_bits, 0, sizeof(m_bits));
	}

	void set(int bit)
	{
		m_bits[bit >> 5] |= 1u << (bit & 31);
	}

private:
	UnsignedInt m_bits[NUM_WORDS];
};

class GameLogic
{
public:
	UnsignedInt getFrame() const
	{
		return m_frame;
	}

	void deselectObject(Object *object, unsigned short playerMask, Bool affectClient);

private:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheBfmeGameLogic;

class Pathfinder
{
public:
	void removeGoal(Object *object);
	void snapPosition(Object *object, Coord3D *destinationPosition);
};

class AI
{
public:
	Pathfinder *pathfinder() const
	{
		return m_pathfinder;
	}

private:
	unsigned char m_pad00[0x0c];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

template <int N>
class AIUpdateVirtualSlots : public AIUpdateVirtualSlots<N - 1>
{
public:
	virtual void unusedSlot(char (*)[N]);
};

template <>
class AIUpdateVirtualSlots<0>
{
};

class AIUpdateModuleData
{
public:
	unsigned char m_pad00[0x48];
	UnsignedInt m_field48;
};

class AIUpdateInterface : public AIUpdateVirtualSlots<127>
{
public:
	virtual void slot1FC(UnsignedInt value);

	const AIUpdateModuleData *m_moduleData;
	unsigned char m_pad08[0x333 - 8];
	Bool m_flag333;
	Bool m_flag334;
};

class Object
{
public:
	AIUpdateInterface *getAIUpdateInterface() const
	{
		return m_ai;
	}

	void clearCondition(int condition);
	void setStatus(const BitFlags<86> &status, Bool set);

	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0x204 - 0x44];
	AIUpdateInterface *m_ai;
};

class StateMachine
{
public:
	virtual void unusedSlot();

	unsigned char m_pad04[0x0c];
	Object *m_owner;
};

class State
{
public:
	virtual StateReturnType onEnter();

protected:
	unsigned char m_pad04[0x18];
	StateMachine *m_machine;
	unsigned char m_pad20[0x28 - 0x20];
};

class AIRampageState : public State
{
public:
	virtual StateReturnType onEnter();

private:
	UnsignedInt m_field28;
	UnsignedInt m_field2c;
};

extern void j_00039338();

class BfmeRampageDuration
{
public:
	int value() const;
};

static __forceinline int bfmeRampageDuration(const AIUpdateInterface *ai)
{
	typedef int (BfmeRampageDuration::*Function)() const;
	union
	{
		void (*asRaw)();
		Function asMember;
	} cast;
	cast.asRaw = j_00039338;
	return (reinterpret_cast<const BfmeRampageDuration *>(ai)->*cast.asMember)();
}

StateReturnType AIRampageState::onEnter()
{
	Object *owner = m_machine->m_owner;
	if (!owner)
		return STATE_FAILURE;

	AIUpdateInterface *aiUpdate = owner->getAIUpdateInterface();
	aiUpdate->slot1FC(8);

	Coord3D ownerPosition;
	ownerPosition.x = owner->m_position.x;
	ownerPosition.y = owner->m_position.y;
	ownerPosition.z = owner->m_position.z;
	TheAI->pathfinder()->removeGoal(owner);
	TheAI->pathfinder()->snapPosition(owner, &ownerPosition);

	aiUpdate->m_flag334 = true;
	aiUpdate->m_flag333 = true;
	owner->clearCondition(8);
	TheBfmeGameLogic->deselectObject(owner, 0xffff, true);

	{
		BitFlags<86> status;
		status.set(3);
		owner->setStatus(status, true);
	}
	{
		BitFlags<86> status;
		status.set(56);
		owner->setStatus(status, true);
	}

	int durationOrNextFrame = bfmeRampageDuration(aiUpdate);
	m_field28 = TheBfmeGameLogic->getFrame() + durationOrNextFrame;

	UnsignedInt period = aiUpdate->m_moduleData->m_field48;
	if (period == 0)
	{
		m_field2c = 0xffffffff;
		return STATE_CONTINUE;
	}

	GameLogic *logic = TheBfmeGameLogic;
	_ReadWriteBarrier();
	if (durationOrNextFrame)
		durationOrNextFrame = logic->getFrame() + period;
	else
		durationOrNextFrame = logic->getFrame();
	m_field2c = durationOrNextFrame;
	return STATE_CONTINUE;
}
