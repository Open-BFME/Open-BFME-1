// cl: /O2
//
// AptGuiFX::MessageBoxShown callback, retail 0x00522470 (52B).
// The 0x00522E00 constructor registers this callback by its ILT 0x0002924E;
// the registration string is "AptGuiFX::MessageBoxShown".  The callback
// forwards event code 1 through the object stored at this + 0x40.
//
// g_bfmeMsg1042 is a legacy relocation alias: retail DIR32 0x011E1CE4 is
// MSVC ThrowInfo for FunctorNotSet/exception, not message text.

class BfmeErr1042
{
public:
	BfmeErr1042();
	char m_bfmePad[0xc];
};

extern char g_bfmeMsg1042[];
__declspec(noreturn) void __stdcall bfmeFatal1042(BfmeErr1042 *e, char *m);

class Rva00522470Iface
{
public:
	virtual void v0();
	virtual void apply(int a);
};

class Rva00522470Ptr
{
public:
	operator Rva00522470Iface *() const
	{
		return m_p;
	}

	Rva00522470Iface *operator->() const
	{
		if (m_p == 0)
		{
			BfmeErr1042 e;
			bfmeFatal1042(&e, g_bfmeMsg1042);
		}
		return m_p;
	}

private:
	Rva00522470Iface *m_p;
};

class Gen00522E00
{
public:
	void messageBoxShown(int unused);

private:
	char m_lead[0x40];
	Rva00522470Ptr m_40;
};

// ?messageBoxShown@Gen00522E00@@QAEXH@Z
void Gen00522E00::messageBoxShown(int)
{
	if (m_40)
		m_40->apply(1);
}
