// ?apply@Rva002CA0E0@@QAEXXZ
// partial score=0.97 date=2026-09-02
// cl: /O2 /Ob0

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	int aiIdle(CommandSourceType cmdSource);
};

class AIPrimaryRva002CA0E0
{
	unsigned char m_pad[0x20];
};

class AIUpdateInterface : public AIPrimaryRva002CA0E0, public AICommandInterface
{
};

class HostRva002CA0E0
{
public:
	char m_lead[0x204];
	AIUpdateInterface *m_ai;
};

class StateRva002CA0E0
{
public:
	void *m_unused;
	int m_id;
};

class ThingRva002CA0E0
{
public:
	virtual void pad00();
	virtual void pad04();
	virtual void pad08();
	virtual void pad0c();
	virtual void pad10();
	virtual void pad14();
	virtual void pad18();
	virtual void pad1c();
	virtual void setValue(int value);

	char m_mid[0x18];
	StateRva002CA0E0 *m_state;
};

class Rva002CA0E0
{
public:
	void apply();

	char m_pad[0xD4];
	ThingRva002CA0E0 *m_thing;
};

void Rva002CA0E0::apply()
{
	if (!m_thing->m_state)
		return;
	if (m_thing->m_state->m_id != 1)
		return;
	AIUpdateInterface *ai = *(AIUpdateInterface **)(*(char **)((char *)this - 0x340) + 0x204);
	if (ai)
		ai->aiIdle(CMD_FROM_AI);
	m_thing->setValue(0);
}
