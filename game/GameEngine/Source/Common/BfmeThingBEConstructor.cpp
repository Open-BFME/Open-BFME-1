extern void *(*WideAllocPtr)(unsigned int bytes);
// Defining name at 0x00897300: void __cdecl bfmePush(BfmeItemDX *), defined in
// game/GameEngine/Source/Common/Bfme5FiftyFour.cpp.
class BfmeItemDX;
void __cdecl bfmePush(BfmeItemDX *item);

struct BfmeStringData3AF0
{
	unsigned short m_bfmeRefAAA;
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;

class BfmeBaseAAA
{
public:
	BfmeBaseAAA(unsigned int flags)
	{
		unsigned int value = m_flags & 0xffffffc0;
		value |= flags;
		value &= 0xb000803f;
		value |= 0x8000;
		m_flags = value;
	}

	virtual ~BfmeBaseAAA() {}

	unsigned int m_flags;
};

class Rva00891B80
{
	BfmeStringData3AF0 *m_block;

public:
	void release();
};

class BfmeStrAAA
{
	BfmeStringData3AF0 *m_block;

public:
	BfmeStrAAA()
	{
		m_block = &g_bfmeDefaultString1284;
		++g_bfmeDefaultString1284.m_bfmeRefAAA;
	}

	~BfmeStrAAA() { ((Rva00891B80 *)this)->release(); }
};

class BfmeArgAAA
{
public:
	virtual void bfmeNotifyAAA();
};

class BfmeNestedBE : public BfmeBaseAAA
{
public:
	BfmeNestedBE(int kind, unsigned int marker, int value);
	virtual void bfmeLinked1284();

	void *operator new(unsigned int bytes)
	{
		char *raw = (char *)WideAllocPtr(bytes + 8);
		char *block = raw + 8;
		bfmePush((BfmeItemDX *)block);
		return block;
	}

	void operator delete(void *block);

	int m_bfme08;
	BfmeStrAAA m_bfme0c;
	float m_bfme10;
	float m_bfme14;
	float m_bfme18;
	float m_bfme1c;
	float m_bfme20;
	float m_bfme24;
	float m_bfme28;
	float m_bfme2c;
	float m_bfme30;
	float m_bfme34;
	float m_bfme38;
	float m_bfme3c;
	float m_bfme40;
	float m_bfme44;
	void *m_bfme48;
	int m_bfme4c;
	unsigned int m_bfme50;
	void *m_bfme54;
	void *m_bfme58;
	int m_bfme5c;
	unsigned int m_bfme60;
};

BfmeNestedBE::BfmeNestedBE(int kind, unsigned int marker, int value)
	: BfmeBaseAAA(kind), m_bfme08(0)
{
	m_bfme48 = 0;
	m_bfme4c = value;
	m_bfme50 = marker;
	m_bfme54 = 0;
	m_bfme58 = 0;
	m_bfme5c = -1;

	m_bfme10 = 1.0f;
	m_bfme14 = 0.0f;
	m_bfme18 = 0.0f;
	m_bfme1c = 1.0f;
	m_bfme20 = 0.0f;
	m_bfme24 = 0.0f;
	m_bfme28 = 1.0f;
	m_bfme2c = 1.0f;
	m_bfme30 = 1.0f;
	m_bfme34 = 1.0f;
	m_bfme38 = 0.0f;
	m_bfme3c = 0.0f;
	m_bfme40 = 0.0f;
	m_bfme44 = 0.0f;

	if (value != 0)
		((BfmeArgAAA *)value)->bfmeNotifyAAA();

	unsigned int h;
	unsigned int g;
	h = m_bfme60;
	g = m_flags;
	h &= 0xfff0ffff;
	g &= 0xffffc07f;
	m_bfme60 = h;
	g |= 0x40;
	*(unsigned short *)&m_bfme60 = 0;
	m_flags = g;
}

class BfmeThingBE
{
public:
	BfmeThingBE();

private:
	BfmeNestedBE *m_nested;
};

BfmeThingBE::BfmeThingBE()
{
	m_nested = new BfmeNestedBE(0x1b, 0xbaadf00d, 0);
	m_nested->m_flags &= ~0x8000;
	m_nested->m_flags = (m_nested->m_flags & 0xffffc07f) | 0x40;
	m_nested->m_bfme08 = -1;
	m_nested->m_bfme58 = 0;
	m_nested->m_bfme54 = 0;
}
