// ??0BfmeOwnerAAA@@QAE@IPAXPAVBfmeArgAAA@@@Z
// partial score=0.88 date=2026-09-08
struct BfmeStringData3AF0
{
	unsigned short m_bfmeRefAAA;
	unsigned short m_bfmeLenAAA;
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;

class BfmeStrAAA
{
public:
	BfmeStrAAA()
	{
		m_bfmeDataAAA = &g_bfmeDefaultString1284;
		++g_bfmeDefaultString1284.m_bfmeRefAAA;
	}

	~BfmeStrAAA();

	BfmeStringData3AF0 *m_bfmeDataAAA;
};

class BfmeHandleAAA
{
public:
	BfmeHandleAAA() { m_bfmePtrAAA = 0; }
	~BfmeHandleAAA();

	void *m_bfmePtrAAA;
};

class BfmeArgAAA
{
public:
	virtual void bfmeNotifyAAA();
};

class BfmeBaseAAA
{
public:
	BfmeBaseAAA(unsigned int flags)
	{
		unsigned int f = m_bfme04AAA & 0xffffffc0;

		f |= flags;
		f &= 0xb000803f;
		f |= 0x8000;
		m_bfme04AAA = f;
	}

	unsigned int m_bfme04AAA;
};

class BfmeOwnerAAA : public BfmeBaseAAA
{
public:
	BfmeOwnerAAA(unsigned int flags, void *owner, BfmeArgAAA *arg);
	virtual ~BfmeOwnerAAA();

	BfmeHandleAAA m_bfme08AAA;
	BfmeStrAAA m_bfme0CAAA;
	float m_bfme10AAA;
	float m_bfme14AAA;
	float m_bfme18AAA;
	float m_bfme1CAAA;
	float m_bfme20AAA;
	float m_bfme24AAA;
	float m_bfme28AAA;
	float m_bfme2CAAA;
	float m_bfme30AAA;
	float m_bfme34AAA;
	float m_bfme38AAA;
	float m_bfme3CAAA;
	float m_bfme40AAA;
	float m_bfme44AAA;
	void *m_bfme48AAA;
	BfmeArgAAA *m_bfme4CAAA;
	void *m_bfme50AAA;
	void *m_bfme54AAA;
	void *m_bfme58AAA;
	int m_bfme5CAAA;
	unsigned int m_bfme60AAA;
};

BfmeOwnerAAA::BfmeOwnerAAA(unsigned int flags, void *owner, BfmeArgAAA *arg)
	: BfmeBaseAAA(flags)
{
	m_bfme48AAA = 0;
	m_bfme4CAAA = arg;
	m_bfme50AAA = owner;
	m_bfme54AAA = 0;
	m_bfme58AAA = 0;
	m_bfme5CAAA = -1;

	m_bfme10AAA = 1.0f;
	m_bfme14AAA = 0.0f;
	m_bfme18AAA = 0.0f;
	m_bfme1CAAA = 1.0f;
	m_bfme20AAA = 0.0f;
	m_bfme24AAA = 0.0f;
	m_bfme28AAA = 1.0f;
	m_bfme2CAAA = 1.0f;
	m_bfme30AAA = 1.0f;
	m_bfme34AAA = 1.0f;
	m_bfme38AAA = 0.0f;
	m_bfme3CAAA = 0.0f;
	m_bfme40AAA = 0.0f;
	m_bfme44AAA = 0.0f;

	if (arg != 0)
		arg->bfmeNotifyAAA();

	unsigned int h = m_bfme60AAA;
	unsigned int g = *(volatile unsigned int *)&m_bfme04AAA;

	h &= 0xfff0ffff;
	g &= 0xffffc07f;
	m_bfme60AAA = h;
	g |= 0x40;

	*(unsigned short *)&m_bfme60AAA = 0;

	m_bfme04AAA = g;
}
