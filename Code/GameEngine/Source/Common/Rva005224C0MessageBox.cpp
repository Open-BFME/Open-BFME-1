// cl: /O2
//
// AptGuiFX::MessageBoxHiding callback, retail 0x005224C0 (52B).
// The 0x00522E00 constructor registers this callback by its ILT 0x0002C381;
// the registration string is "AptGuiFX::MessageBoxHiding".  The callback
// forwards event code 2 through the object stored at this + 0x40.
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

class Rva005224C0Iface
{
public:
	virtual void v0();
	virtual void apply(int a);
};

class Rva005224C0Ptr
{
public:
	operator Rva005224C0Iface *() const
	{
		return m_p;
	}

	Rva005224C0Iface *operator->() const
	{
		if (m_p == 0)
		{
			BfmeErr1042 e;
			bfmeFatal1042(&e, g_bfmeMsg1042);
		}
		return m_p;
	}

private:
	Rva005224C0Iface *m_p;
};

class Gen00522E00
{
public:
	void messageBoxHiding(int unused);

private:
	char m_lead[0x40];
	Rva005224C0Ptr m_40;
};

// ?messageBoxHiding@Gen00522E00@@QAEXH@Z
void Gen00522E00::messageBoxHiding(int)
{
	if (m_40)
		m_40->apply(2);
}
