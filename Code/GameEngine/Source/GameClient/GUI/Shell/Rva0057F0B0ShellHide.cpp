// cl: /DNDEBUG /MD /EHsc
// The retail body at 0x0057F0B0 hides each of the sixteen shell layouts and
// then notifies the global shell listener at 0x012F3344.

typedef bool Bool;

class Rva0057F0B0ShellScreen
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void hide(Bool value) = 0;
};

class Rva0057F0B0ShellGlobal
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void notifyHidden() = 0;
};

extern Rva0057F0B0ShellGlobal *Glo012F3344;

class Rva0057F0B0Shell
{
public:
	virtual void slot00() = 0;
	void hide(Bool value);

private:
	unsigned int m_unreconstructed04;
	Rva0057F0B0ShellScreen *m_screenStack[16];
};

// ?hide@Rva0057F0B0Shell@@QAEX_N@Z
void Rva0057F0B0Shell::hide(Bool value)
{
	for (int i = 0; i < 16; ++i)
	{
		if (m_screenStack[i])
			m_screenStack[i]->hide(value);
	}

	if (Glo012F3344)
		Glo012F3344->notifyHidden();
}
