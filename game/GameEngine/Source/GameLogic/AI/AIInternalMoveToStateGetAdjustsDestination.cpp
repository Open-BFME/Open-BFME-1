// ?getAdjustsDestination@AIInternalMoveToState@@IBE_NXZ
// Retail 0x001724B0. Identity: matched computePath caller via ILT 0x00010109.
// Layout witnesses: docs/analysis/0x00172600.md and retail body.
// Logger ABI: cdecl varargs through 0x0003A17A -> 0x00065C80.
// Preserve the status-bit expression: a signed less-than-zero comparison
// emits JGE instead of JNS and also changes the sink/AI register allocation.
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

#define TEN_VIRTUAL_SLOTS(PREFIX) \
	virtual void v##PREFIX##0(); virtual void v##PREFIX##1(); \
	virtual void v##PREFIX##2(); virtual void v##PREFIX##3(); \
	virtual void v##PREFIX##4(); virtual void v##PREFIX##5(); \
	virtual void v##PREFIX##6(); virtual void v##PREFIX##7(); \
	virtual void v##PREFIX##8(); virtual void v##PREFIX##9();

class AIUpdateInterface
{
public:
	TEN_VIRTUAL_SLOTS(0)
	TEN_VIRTUAL_SLOTS(1)
	TEN_VIRTUAL_SLOTS(2)
	TEN_VIRTUAL_SLOTS(3)
	TEN_VIRTUAL_SLOTS(4)
	TEN_VIRTUAL_SLOTS(5)
	TEN_VIRTUAL_SLOTS(6)
	TEN_VIRTUAL_SLOTS(7)
	TEN_VIRTUAL_SLOTS(8)
	virtual void v90();
	virtual void v91();
	virtual void v92();
	virtual Bool isAllowedToAdjustDestination() const;
};

#undef TEN_VIRTUAL_SLOTS

struct Object
{
	unsigned char m_beforeStatus[0x90];
	// Low-byte view of Object::m_status at +0x90; this body tests bit 7 only.
	signed char m_status;
	unsigned char m_beforeAI[0x204 - 0x91];
	AIUpdateInterface *m_ai;
};

struct StateMachine
{
	unsigned char m_beforeOwner[0x10];
	Object *m_owner;
};

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_0003a17a(void);
typedef void (__cdecl *BfmeCritterDesyncLog)(void *, const char *, ...);

class State
{
	protected:
	virtual void stateSlot();
	unsigned char m_beforeMachine[0x18];
	StateMachine *m_machine;
};

class AIInternalMoveToState : public State
{
	protected:
	Bool getAdjustsDestination() const;

	private:
	unsigned char m_beforeAdjustDestinations[0x4c - 0x20];
	Bool m_adjustDestinations;
};

Bool AIInternalMoveToState::getAdjustsDestination() const
{
	AIInternalMoveToState *self = (AIInternalMoveToState *)this;
	if (g_012F0239 && g_012ED4FC)
		((BfmeCritterDesyncLog)j_0003a17a)(g_012ED4FC,
			"CritterDesync: getAdjustsDestination() entered.");

	StateMachine *machine = self->m_machine;
	Object *obj = machine->m_owner;
	if (obj->m_status & 0x80)
	{
		if (g_012F0239 && g_012ED4FC)
			((BfmeCritterDesyncLog)j_0003a17a)(g_012ED4FC,
				"CritterDesync: getAdjustsDestination1 - parachuting returning FALSE.");
		return false;
	}

	AIUpdateInterface *ai = obj->m_ai;
	if (ai && !ai->isAllowedToAdjustDestination())
	{
		if (g_012F0239 && g_012ED4FC)
			((BfmeCritterDesyncLog)j_0003a17a)(g_012ED4FC,
				"CritterDesync: getAdjustsDestination1 - isAllowedToAdjustDestination FALSE, returning FALSE.");
		return false;
	}

	if (g_012F0239 && g_012ED4FC)
		((BfmeCritterDesyncLog)j_0003a17a)(g_012ED4FC,
			"CritterDesync: getAdjustsDestination1 - m_adjustsDestinations = %s",
			self->m_adjustDestinations ? "TRUE" : "FALSE");

	return self->m_adjustDestinations;
}
