// cl: /O2
//
// Fourth 66B twin of the d_0050fec0.asm cluster documented in
// Rva005222A0NoteCalls.cpp: skip-if-null then BfmeErr1043 throw + vslot 1,
// this one with imm 1 (apply0=0x005222A0, apply1=0x00522300 (this file),
// apply2=0x00522360, apply3=0x005223C0). Same layout/throw path; only the
// pushed vslot-call argument differs.

class BfmeErr1043
{
public:
	BfmeErr1043();
	char m_bfmePad[0xc];
};

extern char g_bfmeMsg1043[];
__declspec(noreturn) void __stdcall bfmeFatal1043(BfmeErr1043 *e, char *m);

class Rva005222A0Iface
{
public:
	virtual void v0();
	virtual void apply(int a);
};

class Rva005222A0Ptr
{
public:
	operator Rva005222A0Iface *() const
	{
		return m_p;
	}

	Rva005222A0Iface *operator->() const
	{
		if (m_p == 0)
		{
			BfmeErr1043 e;
			bfmeFatal1043(&e, g_bfmeMsg1043);
		}
		return m_p;
	}

private:
	Rva005222A0Iface *m_p;
};

class Rva00522300Host
{
public:
	void apply1(int unused);

private:
	char m_lead[0x34];
	int m_34;
	int m_38;
	Rva005222A0Ptr m_3C;
};

// ?apply1@Rva00522300Host@@QAEXH@Z
void Rva00522300Host::apply1(int)
{
	Rva005222A0Iface *p = m_3C;
	m_38 = 4;
	m_34 = 0;
	if (p)
		m_3C->apply(1);
}
