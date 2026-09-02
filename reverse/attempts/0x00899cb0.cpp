// ??0Rva89ACB0Holder@@QAE@PAVBfmeHeld99CB0@@@Z
// partial score=0.9 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0089C860State
{
public:
	Rva0089C860State(int value);
	~Rva0089C860State();

private:
	int m_value;
	int m_first;
	int m_second;
	int m_third;
};

class BfmeHeld99CB0
{
public:
	virtual void addref();
};

class BfmeBase99CB0
{
public:
	__forceinline BfmeBase99CB0()
	{
		unsigned int flags = m_flags;
		flags &= 0xb000801c;
		flags |= 0x0000801c;
		m_flags = flags;
	}

protected:
	unsigned int m_flags;
};

class Rva89ACB0Holder : public BfmeBase99CB0
{
public:
	Rva89ACB0Holder(BfmeHeld99CB0 *held);
	virtual ~Rva89ACB0Holder();

private:
	Rva0089C860State m_state;
	BfmeHeld99CB0 *m_held;
};

Rva89ACB0Holder::Rva89ACB0Holder(BfmeHeld99CB0 *held) :
	m_state(8)
{
	m_held = held;
	if (held)
		held->addref();
}
