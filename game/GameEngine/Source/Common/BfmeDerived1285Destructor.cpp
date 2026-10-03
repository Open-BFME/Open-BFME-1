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

// The child teardown this base destructor reaches is an ILT thunk in retail:
// the call at +0x6C of the 0x008BEDC0 body lands on ?j_0089cc70@@YAXXZ
// (0x0089CC70), whose matched five-byte body lives in
// game/gen_small/thunks_037.cpp.  That decorated symbol is what the call must
// relocate against; VC7.1 reserves __thiscall in a free-function-pointer
// typedef, so the pointer-to-member cast idiom (as BfmeConv1002.cpp uses for
// the same ?j_0003f5da ILT) keeps the proven shape: ECX holds the child, the
// dtor takes no stack argument and its callee pops none.
extern void j_0089cc70();
struct BfmeChildDtorThunk1285 { void Call(); };
typedef void (BfmeChildDtorThunk1285::*BfmeChildDtorCall1285)();

class BfmeChildB
{
public:
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

		union { void (*asFunction)(); BfmeChildDtorCall1285 asMember; } fnCast;
		BfmeChildB *child = m_child;
		if (child)
		{
			fnCast.asFunction = j_0089cc70;
			(reinterpret_cast<BfmeChildDtorThunk1285 *>(child)->*fnCast.asMember)();
			TheBfmeFree(child, 0x10);
		}
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
