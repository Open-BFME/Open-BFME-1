// ?getAdjustsDestination@AIInternalMoveToState@@IBE_NXZ
// partial score=0.95 date=2026-09-03
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
	signed char m_statusParachutingByte;
	unsigned char m_beforeAI[0x204 - 0x91];
	AIUpdateInterface *m_ai;
};

struct StateMachine
{
	unsigned char m_beforeOwner[0x10];
	Object *m_owner;
};

extern Bool g_logCritterDesync;
struct _iobuf;
typedef _iobuf FILE;
extern FILE *g_critterDesyncLog;
extern "C" int __cdecl fprintf(FILE *log, const char *format, ...);

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
	if (g_logCritterDesync && g_critterDesyncLog)
		fprintf(g_critterDesyncLog,
			"CritterDesync: getAdjustsDestination() entered.");

	StateMachine *machine = self->m_machine;
	Object *obj = machine->m_owner;
	if (obj->m_statusParachutingByte < 0)
	{
		if (g_logCritterDesync && g_critterDesyncLog)
			fprintf(g_critterDesyncLog,
				"CritterDesync: getAdjustsDestination1 - parachuting returning FALSE.");
		return false;
	}

	AIUpdateInterface *ai = obj->m_ai;
	if (ai && !ai->isAllowedToAdjustDestination())
	{
		if (g_logCritterDesync && g_critterDesyncLog)
			fprintf(g_critterDesyncLog,
				"CritterDesync: getAdjustsDestination1 - isAllowedToAdjustDestination FALSE, returning FALSE.");
		return false;
	}

	if (g_logCritterDesync && g_critterDesyncLog)
		fprintf(g_critterDesyncLog,
			"CritterDesync: getAdjustsDestination1 - m_adjustsDestinations = %s",
			self->m_adjustDestinations ? "TRUE" : "FALSE");

	return self->m_adjustDestinations;
}
