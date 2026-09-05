// cl: /DNDEBUG /MD /EHsc
// BFME state-exit reconstruction for retail RVA 0x0017ADC0.

typedef unsigned int UnsignedInt;

enum StateExitType
{
	STATE_EXIT_NORMAL = 0
};

class Rva0017ADC0Locomotor
{
public:
	void clearAllowInvalidPosition()
	{
		m_flags &= ~2u;
	}

private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_flags;
};

class Rva0017ADC0AI
{
public:
	Rva0017ADC0Locomotor *getCurLocomotor() const
	{
		return m_locomotor;
	}

	void clearCanPathThroughUnits()
	{
		m_canPathThroughUnits = 0;
	}

private:
	unsigned char m_pad00[0x1cc];
	Rva0017ADC0Locomotor *m_locomotor;
	unsigned char m_pad1d0[0x158];
	unsigned char m_canPathThroughUnits;
};

class Rva0017ADC0Object
{
public:
	Rva0017ADC0AI *getAI() const
	{
		return m_ai;
	}

private:
	unsigned char m_pad00[0x204];
	Rva0017ADC0AI *m_ai;
};

class Rva0017ADC0Machine
{
public:
	Rva0017ADC0Object *getOwner() const
	{
		return m_owner;
	}

private:
	unsigned char m_pad00[0x10];
	Rva0017ADC0Object *m_owner;
};

class AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);

protected:
	unsigned char m_pad00[0x18];
	Rva0017ADC0Machine *m_machine;
};

extern void j_0002d24f();

class Rva0017ADC0CallTarget
{
public:
	void call(void *waypoint);
};

class Rva0017ADC0State : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);

private:
	unsigned char m_pad20[0x30];
	void *m_waypoint;
};

void Rva0017ADC0State::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
	Rva0017ADC0AI *ai = m_machine->getOwner()->getAI();
	if (ai)
	{
		typedef void (Rva0017ADC0CallTarget::*WaypointCall)(void *);
		union { void *asVoid; WaypointCall asMember; } callCast;
		callCast.asVoid = (void *)j_0002d24f;
		(reinterpret_cast<Rva0017ADC0CallTarget *>(ai)->*callCast.asMember)(m_waypoint);
		ai->clearCanPathThroughUnits();
		ai->getCurLocomotor()->clearAllowInvalidPosition();
	}
}
