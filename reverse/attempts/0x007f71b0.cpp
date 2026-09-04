// ?bfmeGoVJT@BfmeThingVJT@@QAEXHH@Z
// partial score=0.95 date=2026-09-04
// EA FESL gamebrowser host-slot registration at retail 0x007F71B0.
// cl: /O2 /Ob0

class BfmeMsgVJH
{
public:
	BfmeMsgVJH(char *buf, int n) throw();
	~BfmeMsgVJH() throw();
	char m_pad[0x34];
};

class Rva00800290Buffer
{
public:
	void append(const char *text);
	char *m_ptr;
	int m_size;
};

extern const char g_Rva0107301CEmptyString[];

class BfmeHostVJT
{
public:
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	char m_14;
	char m_pad15[3];
	int m_18;
	Rva00800290Buffer m_buf;
	int m_24;
	int m_28;
	char m_pad2c[0x40];
	char m_6c;
	char m_pad70[0x24];
};

class BfmeHostTableVJT
{
public:
	virtual void v00() throw();
	virtual void v04() throw();
	virtual void v08() throw();
	virtual void v0c() throw();
	virtual void v10() throw();
	virtual void v14() throw();
	virtual void v18() throw();
	virtual void v1c() throw();
	virtual void v20() throw();
	virtual void v24() throw();
	virtual void v28() throw();
	virtual void send(BfmeHostVJT *slot, int value) throw();
};

class BfmeHostFailureVJT
{
public:
	virtual void v00() throw();
	virtual void v04() throw();
	virtual void v08() throw();
	virtual void v0c() throw();
	virtual void v10() throw();
	virtual void v14() throw();
	virtual void v18() throw();
	virtual void v1c() throw();
	virtual void v20() throw();
	virtual void v24() throw();
	virtual void v28() throw();
	virtual void send(BfmeHostVJT *slot, int value) throw();
};

class BfmeHostMatchVJT
{
public:
	virtual void v00() throw();
	virtual void v04() throw();
	virtual void v08() throw();
	virtual void v0c() throw();
	virtual void v10() throw();
	virtual void v14() throw();
	virtual void v18() throw();
	virtual void v1c() throw();
	virtual void v20() throw();
	virtual int *matchFirst(int *value) throw();
	virtual int *matchSecond(int *value) throw();
};

class BfmeRequestVJT
{
public:
	virtual void v00() throw();
	virtual void v04() throw();
	virtual void v08() throw();
	virtual void v0c() throw();
	virtual void v10() throw();
	virtual void v14() throw();
	virtual void v18() throw();
	virtual void v1c() throw();
	virtual void v20() throw();
	virtual void v24() throw();
	virtual void v28() throw();
	virtual void v2c() throw();
	virtual void v30() throw();
	virtual void v34() throw();
	virtual void send(BfmeMsgVJH *msg, int a1, int a2, int selected) throw();
};

class BfmeNotifyVJT
{
public:
	virtual void v00() throw();
	virtual void v04() throw();
	virtual void send(BfmeMsgVJH *msg, void (__stdcall *callback)(),
		void *owner, int value) throw();
};

extern void __stdcall BfmeGameBrowserVJTCallback();

class BfmeThingVJT
{
public:
	void bfmeGoVJT(volatile int a1, int a2) throw();

	char m_pad00[0x10];
	BfmeRequestVJT *m_bfme10;
	BfmeNotifyVJT *m_bfme14;
	char m_pad18[4];
	union
	{
		BfmeHostTableVJT *m_bfme1c;
		BfmeHostFailureVJT *m_bfme1cFailure;
	};
	char m_pad20[8];
	int m_bfme28;
	int m_bfme2c;
	int m_bfme30;
	char m_bfme34;
	char m_bfme35;
	char m_pad36[0x22];
	BfmeHostVJT m_slots[4];
	char m_pad2a8[0x30];
	BfmeHostMatchVJT *m_bfme2d8;
	char m_bfmeBuf[0x400];
	int m_bfme6dc;
};

void BfmeThingVJT::bfmeGoVJT(volatile int a1, int a2) throw()
{
	BfmeHostVJT *slot = &m_slots[0];
	BfmeHostVJT *end = &m_slots[4];
	register int zero = 0;
	struct Flag
	{
		char pad[3];
		char value;
	};
	volatile Flag flag;
	while (slot < end)
	{
		if (slot->m_08 == zero)
			goto found;
		++slot;
	}
	m_bfme1cFailure->send((BfmeHostVJT *)zero, -0x65);
	return;

found:
	int key2 = a2;
	register int *key = &a2;
	slot->m_04 = (int)this;
	flag.value = 0;
	if (m_bfme2d8)
	{
		int *first = m_bfme2d8->matchFirst(key);
		if (*first == a1)
		{
			int *second = m_bfme2d8->matchSecond(key);
			if (*second == key2)
				flag.value = 1;
		}
	}
	slot->m_08 = zero;
	slot->m_0c = (int)zero;
	slot->m_10 = (int)zero;
	slot->m_14 = (char)zero;
	slot->m_18 = (int)zero;
	slot->m_buf.append(g_Rva0107301CEmptyString);
	slot->m_6c = (char)zero;
	slot->m_28 = a1;
	slot->m_24 = key2;
	slot->m_08 = 1;
	slot->m_14 = flag.value;
	m_bfme1c->send(slot, (int)zero);

	BfmeMsgVJH msg(m_bfmeBuf, 0x400);
	int selected = m_bfme2c;
	if (selected == 0)
		selected = m_bfme28;
	m_bfme10->send(&msg, a1, key2, selected);
	m_bfme14->send(&msg, BfmeGameBrowserVJTCallback, slot, m_bfme6dc);
}
