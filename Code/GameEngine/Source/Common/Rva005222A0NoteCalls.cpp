// cl: /O2
//
// Owner unified by constructor00522E00: its typed callbacks bind the same
// complete receiver; the Showing registration names the former opaque apply.
// Cluster on d_0050fec0.asm: skip-if-null then BfmeErr1042 throw + vslot 1.
// Three 66B twins at +0x3C (imm 0/2/3) and a 52B sibling at +0x40 (imm 0).
// Same throw ILT/ThrowInfo as BfmeA1042::bfmeGo1042B at 0x00521EE0.

class BfmeErr1042
{
public:
	BfmeErr1042();
	char m_bfmePad[0xc];
};

extern char g_bfmeMsg1042[];
__declspec(noreturn) void __stdcall bfmeFatal1042(BfmeErr1042 *e, char *m);

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
			BfmeErr1042 e;
			bfmeFatal1042(&e, g_bfmeMsg1042);
		}
		return m_p;
	}

private:
	Rva005222A0Iface *m_p;
};

class Gen00522E00
{
public:
	void apply0(int unused);
	void apply2(int unused);
	void apply3(int unused);
	void messageBoxShowing(int unused);

private:
	char m_lead[0x34];
	int m_34;
	int m_38;
	Rva005222A0Ptr m_3C;
	Rva005222A0Ptr m_40;
};

// ?apply0@Gen00522E00@@QAEXH@Z
void Gen00522E00::apply0(int)
{
	Rva005222A0Iface *p = m_3C;
	m_38 = 4;
	m_34 = 0;
	if (p)
		m_3C->apply(0);
}

// ?apply2@Gen00522E00@@QAEXH@Z
void Gen00522E00::apply2(int)
{
	Rva005222A0Iface *p = m_3C;
	m_38 = 4;
	m_34 = 0;
	if (p)
		m_3C->apply(2);
}

// ?apply3@Gen00522E00@@QAEXH@Z
void Gen00522E00::apply3(int)
{
	Rva005222A0Iface *p = m_3C;
	m_38 = 4;
	m_34 = 0;
	if (p)
		m_3C->apply(3);
}

// ?messageBoxShowing@Gen00522E00@@QAEXH@Z
void Gen00522E00::messageBoxShowing(int)
{
	if (m_40)
		m_40->apply(0);
}
