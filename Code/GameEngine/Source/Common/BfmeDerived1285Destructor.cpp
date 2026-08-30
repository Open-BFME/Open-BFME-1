extern void (__cdecl *TheBfmeFree)(void *storage, unsigned int size);
extern char g_bfmeBase1285Vtable;

class BfmeInner1285
{
public:
	virtual void reserved0() = 0;
	virtual void reserved1() = 0;
	virtual void destroy() = 0;

	char m_padding04[0x50 - 0x04];
	int m_state;
};

class BfmeOwnedWrapper1285
{
public:
	~BfmeOwnedWrapper1285()
	{
		m_inner->m_state = 0;
		m_inner->destroy();
	}

	void operator delete(void *storage, unsigned int size)
	{
		TheBfmeFree(storage, size);
	}

private:
	BfmeInner1285 *m_inner;
};

class BfmeD1046
{
public:
	void bfmeReset1046(int enabled);
	~BfmeD1046()
	{
		bfmeReset1046(0);
		delete m_owned;
	}

private:
	BfmeOwnedWrapper1285 *m_owned;
};

class BfmeChildB
{
public:
	~BfmeChildB();

	void operator delete(void *storage, unsigned int size)
	{
		TheBfmeFree(storage, size);
	}

private:
	char m_padding00[0x10];
};

class BfmeBase1285
{
public:
	~BfmeBase1285()
	{
		m_vtable = &g_bfmeBase1285Vtable;
		delete m_child;
	}

private:
	void *m_vtable;
	char m_padding04[0x10 - 0x04];
	BfmeChildB *m_child;
	char m_padding14[0x20 - 0x14];
};

class BfmeDerived1285 : public BfmeBase1285
{
public:
	~BfmeDerived1285();

private:
	BfmeD1046 m_owned;
};

BfmeDerived1285::~BfmeDerived1285() {}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
