// cl: /O2
// 0x007E9FC0: if the peer arg is live, stash both args and slot4 through
// +0x250; otherwise send the +0x30/0/+0x90 triple or report -203.

class Rva007E9FC0Iface
{
public:
	virtual void v0();
	virtual void v1();
	virtual void sendTriple(char *a, char *b, char *c, int n, int tag, void *self);
};

class Rva007E9FC0Inner
{
public:
	virtual void v0();
	virtual void v1();
	virtual void slot2(int a, void *arg);
};

class Rva007E9FC0Nested
{
public:
	char m_pad[0x6A8];
	Rva007E9FC0Inner *m_inner;
};

class Rva007E9FC0Slot
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual int slot4(void *buf, unsigned char n);
};

class Rva007E9FC0Owner
{
public:
	void begin(int n, void *peer);

private:
	char m_pad00[0x0C];
	Rva007E9FC0Iface *m_0C;
	char m_pad10[0x20];
	char m_buf30[0x60];
	char m_buf90[0x10];
	char m_A0;
	char m_padA1[0x18F];
	unsigned char m_230;
	char m_pad231[0x1F];
	Rva007E9FC0Slot *m_250;
	Rva007E9FC0Nested *m_254;
	char m_258[8];
	void *m_260;
	int m_264;
	char m_pad268[0x44];
	char m_2AC;
};

void Rva007E9FC0Owner::begin(int n, void *peer)
{
	if (peer)
	{
		m_260 = peer;
		m_264 = n;
		m_254->m_inner->slot2(2, 0);
		Rva007E9FC0Slot *s = m_250;
		int r = s->slot4(m_258, m_230);
		if (r)
		{
			int tmp = r;
			m_254->m_inner->slot2(0, &tmp);
		}
	}
	else if (!m_A0 && !m_2AC)
	{
		m_2AC = 1;
		m_0C->sendTriple(m_buf30, 0, m_buf90, n, 0x00BEAC10, this);
	}
	else
	{
		m_2AC = 0;
		int err = -203;
		m_254->m_inner->slot2(0, &err);
	}
}
