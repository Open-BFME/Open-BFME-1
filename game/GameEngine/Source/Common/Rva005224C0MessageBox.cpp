// cl: /O2
//
// AptGuiFX::MessageBoxHiding callback, retail 0x005224C0 (52B).
// The 0x00522E00 constructor registers this callback by its ILT 0x0002C381;
// the registration string is "AptGuiFX::MessageBoxHiding".  The callback
// forwards event code 2 through the object stored at this + 0x40.
//
// The throw below pushes retail ThrowInfo 0xDE1CE4 (FunctorNotSet),
// which the compiler now emits itself for `throw FunctorNotSet()`.

#include <exception>

class FunctorNotSet : public std::exception
{
public:
	FunctorNotSet() : std::exception() {}
};


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
			throw FunctorNotSet();
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
