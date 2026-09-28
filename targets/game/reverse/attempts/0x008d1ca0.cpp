// ?d_008d1ca0@@YAXXZ
// partial score=0.4248 date=2026-09-28
#include <new>

// Apt's dispatch table at VA 0x00ED5A68 points to this body from slot 105.
// Its action identity is unproven, so the source name remains address-derived.
//
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva8D0D80String;
class Rva8D0D80Value
{
public:
	virtual void addRef();
	virtual void release();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	void getName(Rva8D0D80String *name);
	int toInteger();
	unsigned int m_flags;
};

class Rva8D0D80Result;
class Rva8D0D80State
{
public:
	Rva8D0D80Result *create(void *, void *, void *, int, int);
	int m_count;
	int m_unused;
	Rva8D0D80Value **m_stack;
};

struct Rva8D0D80Context
{
	void *m_zero;
	void *m_owner;
	void *m_scope;
};

class Gen_008C5E80
{
public:
	bool bfmeIsKind(void) const;
	int m_bfmeHead;
	unsigned int m_bfmeBits;
};

class BfmeTaggedItem
{
public:
	virtual void bfmeSlot0();
	virtual void bfmeSlot1();
	virtual void bfmeSlot2();
	virtual void bfmeSlot3();
	virtual void bfmeSlot4();
	virtual char bfmeKind();
};

class Gen_00899320
{
public:
	void bfmeSet(BfmeTaggedItem *value);
	int m_bfmeFields[3];
	unsigned int m_bfmeTagged;
};

class Gen_008992C0
{
public:
	void bfmeSet(BfmeTaggedItem *value);
	int m_bfmeFields[2];
	unsigned int m_bfmeTagged;
};

class Rva008D1CA0ValueView
{
public:
	virtual void addRef();
	virtual void release();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual Gen_00899320 *slot18();
	virtual void slot1C();
	virtual void slot20(int);
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40(unsigned int *, int);
};

class Rva008D1CA0ResultView
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual Gen_008992C0 *slot18();
};

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
	virtual ~BfmeBase99CB0();
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

typedef char CheckHolderSize[sizeof(Rva89ACB0Holder) == 0x1c ? 1 : -1];

extern char g_rva8D0D80CreateTag;
extern void *Rva00897560(unsigned int bytes);

void rva008D1CA0(Rva8D0D80State *state, Rva8D0D80Context *context)
{
	Rva8D0D80Value *top = state->m_stack[state->m_count - 1];
	Rva8D0D80Value *under = state->m_stack[state->m_count - 2];
	Rva008D1CA0ValueView *topView = (Rva008D1CA0ValueView *)top;
	Rva008D1CA0ValueView *underView = (Rva008D1CA0ValueView *)under;
	Rva8D0D80Result *created = state->create(context->m_owner, context->m_scope,
		&g_rva8D0D80CreateTag, 0, 0);

	if (created != 0 && ((Gen_008C5E80 *)top)->bfmeIsKind() &&
		((Gen_008C5E80 *)under)->bfmeIsKind())
	{
		unsigned int topHeld = topView->slot18()->m_bfmeTagged & ~1U;
		unsigned int underHeld = underView->slot18()->m_bfmeTagged & ~1U;
		if (topHeld == 0)
		{
			Rva89ACB0Holder *holder =
				(Rva89ACB0Holder *)Rva00897560(0x1c);
			if (holder != 0)
				holder = new (holder) Rva89ACB0Holder((BfmeHeld99CB0 *)top);
			topHeld = (unsigned int)holder;
			topView->slot18()->bfmeSet((BfmeTaggedItem *)holder);
		}

		if (underHeld == 0)
		{
			Rva89ACB0Holder *holder =
				(Rva89ACB0Holder *)Rva00897560(0x1c);
			if (holder != 0)
				holder = new (holder) Rva89ACB0Holder((BfmeHeld99CB0 *)under);
			underView->slot18()->bfmeSet((BfmeTaggedItem *)holder);
		}

		topView->slot20(1);
		underView->slot20(1);
		underView->slot18()->bfmeSet((BfmeTaggedItem *)created);
		((Rva008D1CA0ResultView *)created)->slot18()->bfmeSet((BfmeTaggedItem *)topHeld);
		unsigned int *holderSlot = (unsigned int *)Rva00897560(4);
		*holderSlot = topHeld;
		underView->slot40(holderSlot, 1);
	}

	for (int index = 1; index <= 2; ++index)
	{
		Rva8D0D80Value *old = state->m_stack[state->m_count - index];
		if (!((unsigned char)(old->m_flags >> 30) & 1))
			old->release();
	}
	state->m_count -= 2;
}
