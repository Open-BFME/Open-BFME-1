// BFME layout reconstruction for retail RVA 0x0017EE60.

typedef bool Bool;

enum StateExitType
{
	STATE_EXIT_NORMAL = 0
};

class Object;

template <int N>
class Rva0017EE60Virtuals : public Rva0017EE60Virtuals<N - 1>
{
public:
	virtual void slot(char (*)[N]);
};

template <>
class Rva0017EE60Virtuals<0>
{
};

class Rva0017EE60AI : public Rva0017EE60Virtuals<127>
{
public:
	virtual void ignoreObstacle(Object *);
};

class Object
{
public:
	unsigned char m_pad00[0x11c];
	unsigned int m_flags11c;
	unsigned char m_pad120[0xe4];
	Rva0017EE60AI *m_ai;

	void notifyModelConditionChanged();
};

struct Rva0017EE60StateMachine
{
	unsigned char m_pad00[0x10];
	Object *m_owner;
	unsigned char m_pad14[0x2e];
	unsigned char m_flag42;
};

class AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);

protected:
	unsigned char m_pad00[0x18];
	Rva0017EE60StateMachine *m_machine;
};

class Rva0017EE60StatusTarget
{
public:
	void apply(int);
};

extern void j_00007513();

class Rva0017EE60State : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);
};

void Rva0017EE60State::onExit(StateExitType status)
{
    Rva0017EE60State *self = this;
    Object *owner = self->m_machine->m_owner;
	if (!owner)
		return;

	Rva0017EE60AI *ai = owner->m_ai;
	if (!ai)
		return;

	if (owner->m_flags11c & 0x10000000)
	{
		owner->m_flags11c &= ~0x10000000u;
		owner->notifyModelConditionChanged();
	}

	ai->ignoreObstacle(0);

	typedef void (Rva0017EE60StatusTarget::*StatusCall)(int);
	union { void *asVoid; StatusCall asMember; } statusCast;
	statusCast.asVoid = (void *)j_00007513;
	(reinterpret_cast<Rva0017EE60StatusTarget *>(owner)->*statusCast.asMember)(1);

    self->m_machine->m_flag42 = 0;
	AIInternalMoveToState::onExit(status);
}
