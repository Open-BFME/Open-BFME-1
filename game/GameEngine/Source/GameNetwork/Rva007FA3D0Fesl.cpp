// cl: /O2
// 0x007FA3D0 is the next unclaimed FESL transactor operation after the
// matched Rva007FA2C0 request/dispatch family.  Its complete body resets the
// supplied message, validates the request argument, acquires a slot, stamps
// its timeout, dispatches it through the matched hub, and retires a completed
// slot.  The original semantic member name is not recoverable, so it remains
// address-derived.

class Rva007E8810Message
{
public:
	void reset();
	void setError(int code);
};

class Rva007FA5E0Arg
{
public:
	bool valid();

	char m_pad00[0x20];
	void *m_20;
	char m_pad24[4];
	void *m_28;
	void *m_2C;
};

struct Rva007FA170Slot
{
	void *m_00;
	int m_04;
	Rva007E8810Message *m_08;
	void *m_0C;
	void *m_10;
};

struct BfmeSlotRecord;

class BfmeSlotPool
{
public:
	BfmeSlotRecord *acquireSlot();
};

class Rva007FA3D0Id
{
public:
	virtual void v0();
	virtual void *v1();
};

class Rva007FA2C0Hub
{
public:
	virtual void v0(void *arg, void *slotId);
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void *v5(void *arg, int first, int second);
};

class T_007ea5e0
{
public:
	void m();
};

struct Rva007E9B70Obj
{
public:
	virtual void v0();
	virtual void v1(int value);
};

Rva007E9B70Obj *Rva007E9B70Get();

class Rva007FA2C0
{
public:
	void dispatch(void *arg, void *tag);
	void rva007F95A0(Rva007FA170Slot *slot, unsigned timeout);
	void clearSlot(void *slot);
	void rva007FA3D0(Rva007FA5E0Arg *arg,
		Rva007E8810Message *message, unsigned timeout);

private:
	char m_pad00[0x14];
	void *m_14;
	char m_pad18[4];
	void *m_1C;
	T_007ea5e0 *m_20;
	Rva007FA2C0Hub *m_24;
	char m_pad28[0x680];
	Rva007FA3D0Id *m_6A8;
	void *m_6AC;
};

void Rva007FA2C0::rva007FA3D0(Rva007FA5E0Arg *arg,
	Rva007E8810Message *message, unsigned timeout)
{
	message->reset();
	if (arg->valid())
	{
		message->setError(-103);
		return;
	}

	void *requested = arg->m_2C;
	void *current = m_6A8->v1();
	if (requested != current)
	{
		message->setError(-105);
		return;
	}

	Rva007FA170Slot *slot =
		(Rva007FA170Slot *)((BfmeSlotPool *)this)->acquireSlot();
	if (!slot)
	{
		message->setError(-101);
		return;
	}
	if (m_14)
	{
		message->setError(-109);
		return;
	}

	slot->m_08 = message;
	rva007F95A0(slot, timeout);
	m_24->v0(arg, slot->m_00);
	arg->m_28 = slot->m_00;
	slot->m_04 = 1;
	arg->m_20 = m_24->v5(arg, 1, 0);
	dispatch(arg, (void *)"->B");
	do
	{
		m_20->m();
		Rva007E9B70Get()->v1(10);
	} while (slot->m_04 != 2);
	clearSlot((void *)slot);
}
