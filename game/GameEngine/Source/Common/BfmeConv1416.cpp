// Open-BFME5 conversions.

extern "C" void *memset(void *d, int c, unsigned n);
#pragma intrinsic(memset)

static void bfmeFillVLQ(char *last, char *first)
{
	if (first != last)
		memset(first, 0, last - first);
}

struct BfmeNodeVLQ
{
	int m_bfme00;
	int m_bfme04;
	BfmeNodeVLQ *m_bfme08;
	BfmeNodeVLQ *m_bfme0c;
};

// Retail's 0x0004B65F ILT routes to the private _STL::_Rb_tree::_M_erase
// body at 0x0058CC20; call the ledger-owned thunk directly.
extern void j_0004b65f(void);

class BfmeListVLQ
{
public:
	BfmeNodeVLQ *volatile m_bfme00;
	int m_bfme04;
};

class BfmeOwnVLQ
{
public:
	void bfmeResetVLQ();
	char m_bfmePad000[0x4b8];
	char m_bfme4b8[0xc];
	char m_bfme4c4;
	char m_bfme4c5;
	char m_bfmePad4c6[0x36];
	BfmeListVLQ m_bfme4fc;
};

void BfmeOwnVLQ::bfmeResetVLQ()
{
	bfmeFillVLQ(m_bfme4b8 + 0xc, m_bfme4b8);
	m_bfme4c4 = 0;
	BfmeListVLQ *l = &m_bfme4fc;
	if (l->m_bfme04 != 0)
	{
		union
		{
			void (*function)(void);
			void (BfmeListVLQ::*method)(int);
		} erase;
		erase.function = j_0004b65f;
		(l->*erase.method)(l->m_bfme00->m_bfme04);
		BfmeNodeVLQ *n1 = l->m_bfme00;
		n1->m_bfme08 = n1;
		l->m_bfme00->m_bfme04 = 0;
		BfmeNodeVLQ *n3 = l->m_bfme00;
		n3->m_bfme0c = n3;
		l->m_bfme04 = 0;
	}
	m_bfme4c5 = 0;
}
