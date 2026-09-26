// cl: /O2 /GX-
// 0x007FA4D0 is the FESL transactor request-slot operation.  The constructor
// and dispatch rows establish Rva007FA2C0 as the owner; the four stack
// arguments and ret 0x10 establish the request, cdecl callback, context and
// timeout ABI.  The original semantic member name is not recoverable, so the
// method remains address-derived.

class Rva007E8810Message
{
public:
	Rva007E8810Message() throw();
	~Rva007E8810Message() throw();
	void setError(int code);

	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	char *m_10;
	int m_14;
	int m_18;
	unsigned m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	char m_30;
	char m_pad31[3];
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

class Rva007FA5E0Id
{
public:
	virtual void v0();
	virtual void *id();
};

class Rva007FA5E0Hub
{
public:
	virtual void v0(void *arg, void *slotId);
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void *v5(void *arg, int first, int second);
};

struct Rva007FA170Slot
{
	void *m_00;
	int m_04;
	Rva007E8810Message *m_08;
	void (__cdecl *m_0C)(Rva007E8810Message *message, void *context);
	void *m_10;
};

struct BfmeSlotRecord;

class BfmeSlotPool
{
public:
	BfmeSlotRecord *acquireSlot(void);
};

class Rva007FA2C0
{
public:
	void rva007FA4D0(Rva007FA5E0Arg *arg, void *callback,
		void *context, unsigned timeout);
	void rva007F95A0(Rva007FA170Slot *slot, unsigned timeout);
	void dispatch(void *arg, void *tag);

private:
	char m_pad00[0x1C];
	void *m_1C;
	char m_pad20[4];
	Rva007FA5E0Hub *m_24;
	char m_pad28[0x680];
	Rva007FA5E0Id *m_6A8;
	void *m_6AC;
};

typedef void (__cdecl *Rva007FA4D0Callback)(
	Rva007E8810Message *message, void *context);

void Rva007FA2C0::rva007FA4D0(Rva007FA5E0Arg *arg, void *callback,
	void *context, unsigned timeout)
{
	if (callback)
	{
		if (arg->valid())
		{
			Rva007E8810Message message;
			message.setError(-103);
			((Rva007FA4D0Callback)callback)(&message, context);
			return;
		}

		void *want = arg->m_2C;
		if (want != m_6A8->id())
		{
			((Rva007E8810Message *)arg)->setError(-105);
			return;
		}

		Rva007FA170Slot *slot = (Rva007FA170Slot *)
			((BfmeSlotPool *)this)->acquireSlot();
		if (!slot)
		{
			Rva007E8810Message message;
			message.setError(-101);
			((Rva007FA4D0Callback)callback)(&message, context);
			return;
		}

		rva007F95A0(slot, timeout);
		slot->m_10 = context;
		slot->m_0C = (Rva007FA4D0Callback)callback;
		slot->m_04 = 1;
		m_24->v0(arg, slot->m_00);
		arg->m_28 = slot->m_00;
	}
	else
		arg->m_28 = 0;

	arg->m_20 = m_24->v5(arg, 1, 0);
	const char *tag;
	if (callback)
		tag = "->N";
	else
		tag = "->O";
	dispatch(arg, (void *)tag);
}
