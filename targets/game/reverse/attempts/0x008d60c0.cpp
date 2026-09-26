// ?d_008d60c0@@YAXXZ
// partial score=0.21 date=2026-09-22
// Retail 0x008D60C0: opaque Apt frame-stack constructor.
// The address-derived type preserves unresolved ownership while retaining the decoded ABI.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern void *(*Rva008C5D70Alloc)(unsigned int bytes);
class BfmeItemDX;
extern void bfmePush(BfmeItemDX *item);

class BfmeHeld99CB0
{
public:
	virtual void addref();
};

class Rva0089C860State;

class RvaD60Virtual
{
public:
	virtual void retain();
	virtual void release();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual bool slot05();
	virtual void *slot06();
};

struct RvaD60Link
{
	char m_padding00[8];
	RvaD60Virtual *m_value08;
};

class Rva0089C860State
{
public:
	Rva0089C860State *initialize(int value);

	int m_value;
	int m_first;
	int m_second;
	RvaD60Virtual *m_third;
};

class Rva008D20F0Node
{
public:
	char m_padding00[4];
	unsigned int m_kind;
	char m_padding08[0x4C - 8];
	Rva008D20F0Node *m_next;

	Rva008D20F0Node *walk();
};

class BfmeNestedBE;
extern BfmeNestedBE *Rva008930C0AptLookup(int value);

class Rva89ACB0Holder
{
public:
	static void *operator new(unsigned int bytes)
	{
		char *block = (char *)Rva008C5D70Alloc(bytes);
		block += 8;
		bfmePush((BfmeItemDX *)block);
		return block;
	}

	Rva89ACB0Holder(BfmeHeld99CB0 *held);
	char m_padding00[0x24];
};

class BfmeNestedBE
{
public:
	virtual void bfmeLinked1284();
};

class Rva00899C20LookupResult
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual RvaD60Link *slot18();
};

class BfmeTab1024
{
public:
	int bfmeFind1024(int key);
};

struct Rva00899C20Registry
{
	char m_padding00[8];
	BfmeTab1024 m_table;
};

extern Rva00899C20Registry *g_Va013387D8;
extern char g_rva8D0D80CreateTag;

class Rva008D60C0Base
{
public:
	Rva008D60C0Base();
	virtual ~Rva008D60C0Base();

	protected:
	unsigned int m_flags;
	Rva0089C860State m_state;
	unsigned int m_stateBits;
	unsigned int m_bits;
	};

Rva008D60C0Base::Rva008D60C0Base()
{
	m_flags = (m_flags & 0xb000800a) | 0x0000800a;
	Rva0089C860State &state = m_state;
	*(unsigned int *)this = 0x01136058;
	state.initialize(8);
	*(unsigned char *)&m_bits = 0;
	unsigned int bits = m_bits;
	bits &= 0xfffffcff;
	m_stateBits = 0;
	m_bits = bits;
}

class Rva008D60C0FrameStack : public Rva008D60C0Base
{
public:
	Rva008D60C0FrameStack(unsigned int first, unsigned int second, RvaD60Virtual *value);
	virtual ~Rva008D60C0FrameStack();

	private:
	unsigned int m_first;
	unsigned int m_second;
	RvaD60Virtual *m_value;
	RvaD60Virtual *m_lookup;
};

Rva008D60C0FrameStack::Rva008D60C0FrameStack(
	unsigned int first, unsigned int second, RvaD60Virtual *value)
{
	Rva0089C860State &state = m_state;
	m_first = first;
	*(unsigned int *)this = 0x01137770;
	m_value = value;
	value->retain();
	m_second = second;

	Rva008D20F0Node *node = (Rva008D20F0Node *)value;
	if ((node->m_kind & 0x3f) >= 0x0c && (node->m_kind & 0x3f) <= 0x13 &&
		((node->m_kind >> 15) & 1) == 0)
	{
		m_lookup = (RvaD60Virtual *)node->walk();
	}
	else
	{
		m_lookup = (RvaD60Virtual *)Rva008930C0AptLookup(0);
	}
	((BfmeNestedBE *)m_lookup)->bfmeLinked1284();

	Rva89ACB0Holder *holder = new Rva89ACB0Holder((BfmeHeld99CB0 *)this);
	RvaD60Virtual *oldHolder = state.m_third;
	if (holder != 0)
	{
		((RvaD60Virtual *)holder)->retain();
	}
	if (oldHolder != 0)
	{
		oldHolder->release();
	}
	if (holder == 0)
	{
		state.m_third = 0;
	}
	else
	{
		RvaD60Virtual *newHolder = (RvaD60Virtual *)holder;
		if (newHolder->slot05() == true)
			newHolder = (RvaD60Virtual *)((unsigned int)newHolder | 1);
		state.m_third = newHolder;
	}

	Rva00899C20LookupResult *result = (Rva00899C20LookupResult *)
		g_Va013387D8->m_table.bfmeFind1024((int)&g_rva8D0D80CreateTag);
	RvaD60Link *firstLink = result->slot18();
	RvaD60Link *holderLink = (RvaD60Link *)((RvaD60Virtual *)holder)->slot06();
	RvaD60Virtual *firstValue = (RvaD60Virtual *)((unsigned int)firstLink->m_value08 & ~1u);
	RvaD60Virtual *oldValue = (RvaD60Virtual *)((unsigned int)holderLink->m_value08 & ~1u);
	if (firstValue != 0)
		firstValue->retain();
	if (oldValue != 0)
		oldValue->release();
	if (firstValue == 0)
	{
		holderLink->m_value08 = 0;
	}
	else
	{
		RvaD60Virtual *stored = firstValue;
		if (stored->slot05() == true)
			stored = (RvaD60Virtual *)((unsigned int)stored | 1);
		holderLink->m_value08 = stored;
	}
}
