// 0x0075BF30, 73 bytes. Identity is NOT proven: callers_of finds no named
// caller, find_emitter finds no owning TU, and no vtable slot harvest names an
// owner, so the class keeps its address token. What the body itself proves:
// a __thiscall taking one pointer, assigning it to an aggregate member at
// +0x1cc through the pinned assignment at ILT 0x00015744, then reading a
// pointer at +8, an item at +0xfc of that pointer, and forwarding
// (item + 0x38, item[+0x44], &localValue) to virtual slot 30 on `this`.
//
// The three-operation window at +0x2c is what 12 earlier verdicts stalled on:
// retail loads item[+0x44], then the vftable, then spills the call result,
// while the flat spelling spills first. Giving the call result its own block
// scope (docs/shape_levers.md "put the local in its own block") is what orders
// them: the local dies at the closing brace, so VC7.1 schedules both loads
// ahead of the spill instead of anchoring the spill to the statement.

class ObjectAttemptDamageFlagHook
{
public:
	int value();

	unsigned char m_pad00[0x38];
	unsigned char m_at38[0xc];
	int m_value44;
};

class Rva0075BF30Holder
{
public:
	unsigned char m_pad00[0xfc];
	ObjectAttemptDamageFlagHook *m_itemFC;
};

class RadiusDecalTemplate
{
public:
	void operator=(const RadiusDecalTemplate &other);
};

class Rva0075BF30Forwarder
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30(void *at, int value, int *out);

	void apply(void *arg);

	unsigned char m_pad04[4];
	Rva0075BF30Holder *m_holder08;
	unsigned char m_pad0C[0x1c0];
	RadiusDecalTemplate m_sub1CC;
};

void Rva0075BF30Forwarder::apply(void *arg)
{
	if (arg == 0)
		return;

	m_sub1CC = *(RadiusDecalTemplate *)arg;

	ObjectAttemptDamageFlagHook *item = m_holder08->m_itemFC;

	if (item == 0)
		return;

	{
		int value = item->value();

		slot30(item->m_at38, item->m_value44, &value);
	}
}
