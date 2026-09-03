// BFME layout reconstruction for the state-exit body at retail RVA 0x00179A90.

typedef bool Bool;

enum StateExitType
{
	STATE_EXIT_NORMAL = 0
};

class Rva00179A90Field
{
public:
	virtual void slot000(int);
	virtual void slot001(int);
	virtual void slot002(int);
	virtual void slot003(int);
	virtual void slot004(int);
	virtual void slot005(int);
	virtual void slot006(int);
	virtual void slot007(int);
	virtual void slot008(int);
};

class Rva00179A90Locomotor
{
public:
	unsigned char m_pad00[0x40];
	unsigned int m_flags;
};

class Rva00179A90AI
{
public:
	unsigned char m_pad00[0x194];
	int m_field194;
	unsigned char m_pad198[0x34];
	Rva00179A90Locomotor *m_locomotor;
	unsigned char m_pad1d0[0x154];
	unsigned char m_field324;
	unsigned char m_field325;
	unsigned char m_field326;
	unsigned char m_field327;
	unsigned char m_field328;
	unsigned char m_pad329[0x1a];
};

class Rva00179A90CallTarget
{
public:
	void call(float);
};

class Object
{
public:
	unsigned char m_pad00[0x204];
	Rva00179A90AI *m_ai;
};

class Rva00179A90Machine
{
public:
	unsigned char m_pad00[0x10];
	Object *m_owner;
};

class AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);

protected:
	unsigned char m_pad00[0x18];
	Rva00179A90Machine *m_machine;
};

extern void j_00048ca7();

class Rva00179A90State : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);

private:
	unsigned char m_pad20[0x40];
	Rva00179A90Field *m_field60;
};

void Rva00179A90State::onExit(StateExitType status)
{
	if (m_field60)
		m_field60->slot008(0);

	AIInternalMoveToState::onExit(status);

	Rva00179A90AI *ai = (Rva00179A90AI *)m_machine->m_owner->m_ai;
	if (ai)
	{
		Rva00179A90Locomotor *locomotor = ai->m_locomotor;
		ai->m_field328 = 0;
		if (locomotor)
			locomotor->m_flags &= ~8u;
		typedef void (Rva00179A90CallTarget::*Rva00179A90Call)(float);
		union { void *asVoid; Rva00179A90Call asMember; } callCast;
		callCast.asVoid = (void *)j_00048ca7;
		(reinterpret_cast<Rva00179A90CallTarget *>(ai)->*callCast.asMember)(999999.0f);
		ai->m_field194 = -1;
	}
}
