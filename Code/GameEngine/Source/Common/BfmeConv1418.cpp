// Open-BFME5 conversions.

extern "C" void *memset(void *d, int c, unsigned n);
#pragma intrinsic(memset)

class BfmeSubVLS
{
public:
	bool bfmeCheckVLS();
};

class BfmeThingVLS
{
public:
	char m_bfmePad00[0xc];
	char m_bfme0c;
	char m_bfmePad0d[0x4b];
	BfmeSubVLS m_bfme58;
};

class BfmeMgrVLS
{
public:
	virtual void bfmeSlot00VLS();
	virtual void bfmeSlot01VLS();
	virtual void bfmeSlot02VLS();
	virtual void bfmeSlot03VLS();
	virtual void bfmeSlot04VLS();
	virtual void bfmeSlot05VLS();
	virtual void bfmeSlot06VLS();
	virtual void bfmeSlot07VLS();
	virtual void bfmeSlot08VLS();
	virtual void bfmeSlot09VLS();
	virtual void bfmeSlot10VLS();
	virtual void bfmeSlot11VLS();
	virtual void bfmeSlot12VLS();
	virtual void bfmeSlot13VLS();
	virtual void bfmeSlot14VLS();
	virtual void bfmeSlot15VLS();
	virtual void bfmeSlot16VLS();
	virtual void bfmeSlot17VLS();
	virtual void bfmeSlot18VLS();
	virtual void bfmeSlot19VLS();
	virtual void bfmeSlot20VLS();
	virtual void bfmeSlot21VLS();
	virtual void bfmeSlot22VLS();
	virtual void bfmeSlot23VLS();
	virtual void bfmeSlot24VLS();
	virtual void bfmeSlot25VLS();
	virtual void bfmeSlot26VLS();
	virtual void bfmeSlot27VLS();
	virtual void bfmeSlot28VLS();
	virtual void bfmeSlot29VLS();
	virtual void bfmeSlot30VLS();
	virtual void bfmeSlot31VLS();
	virtual void bfmeSlot32VLS();
	virtual void bfmeSlot33VLS();
	virtual void bfmeSlot34VLS();
	virtual void bfmeSlot35VLS();
	virtual void bfmeSlot36VLS();
	virtual void bfmeSlot37VLS();
	virtual void bfmeSlot38VLS();
	virtual void bfmeSlot39VLS();
	virtual void bfmeSlot40VLS();
	virtual void bfmeSlot41VLS();
	virtual void bfmeSlot42VLS();
	virtual void bfmeSlot43VLS();
	virtual void bfmeSlot44VLS();
	virtual void bfmeSlot45VLS();
	virtual void bfmeSlot46VLS();
	virtual void bfmeSlot47VLS();
	virtual BfmeThingVLS *bfmeGetVLS();
};

extern BfmeMgrVLS *g_bfmeMgrVLS;

void bfmeDoVLS(BfmeThingVLS *t, void *dst, int n);

void bfmeReadVLS(void *dst, int n)
{
	if (g_bfmeMgrVLS->bfmeGetVLS() != 0)
	{
		BfmeThingVLS *t = g_bfmeMgrVLS->bfmeGetVLS();
		if (t->m_bfme0c != 0 && t->m_bfme58.bfmeCheckVLS())
		{
			bfmeDoVLS(g_bfmeMgrVLS->bfmeGetVLS(), dst, n);
			return;
		}
	}
	memset(dst, 0, n);
}
