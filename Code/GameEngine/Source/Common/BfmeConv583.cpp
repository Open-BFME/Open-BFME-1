class BfmeOwnerCDE
{
public:
	void bfmeOneCDE(void *what);
};

class BfmeThingCDE
{
public:
	void bfmeDtorCDE();
	void bfmeGoCDE();
	BfmeOwnerCDE *m_bfmeOwner;
	void *m_bfmePtr;
	void *m_bfme08;
	void *m_bfme0c;
	void *m_bfme10;
	void *m_bfme14;
	void *m_bfme18;
	void *m_bfme1c;
	unsigned int m_bfme20;
};

void bfmeFreeCDE(void *what);

void d_008f7990(void);
void d_008f7ec0(void);
void ArrayDeleteHelperBodyThunk(void);
void __cdecl operator delete[](void *);

class BfmeCdeCallback
{
public:
	virtual void callback0();
	virtual void callback1();
	virtual void callback2();
	virtual void callback3(int);
};

class BfmeCdeRelease
{
public:
	virtual void release();
};

typedef void (__stdcall *BfmeArrayDeleteHelper)(void *, unsigned int, int, void *);
typedef void (__fastcall *BfmeCdeCleanup)(BfmeThingCDE *);

void BfmeThingCDE::bfmeDtorCDE()
{
	d_008f7990();

	if (m_bfmePtr != 0)
	{
		unsigned char *object = (unsigned char *)m_bfmePtr;
		unsigned int offset = *(unsigned int *)(*(unsigned char **)(object + 4) + 4);
		unsigned char *entry = object + offset + 4;
		((BfmeCdeCallback *)entry)->callback3(0);
	}

	if (m_bfme08 != 0)
	{
		unsigned char *object = (unsigned char *)m_bfme08;
		unsigned int offset = *(unsigned int *)(*(unsigned char **)(object + 4) + 4);
		unsigned char *entry = object + offset + 4;
		((BfmeCdeCallback *)entry)->callback3(0);
		((BfmeCdeRelease *)m_bfme08)->release();
		m_bfme08 = 0;
	}

	((BfmeCdeCleanup)d_008f7ec0)(this);

	if (m_bfme1c != 0)
	{
		unsigned char *begin = (unsigned char *)m_bfme1c - 4;
		((BfmeArrayDeleteHelper)ArrayDeleteHelperBodyThunk)(m_bfme1c, 0x10, *(unsigned int *)begin,
			(void *)0x00CF7BD0);
		operator delete[](begin);
	}

	if (m_bfme14 != 0)
	{
		*(void **)m_bfme14 = m_bfme18;
		if (m_bfme18 != 0)
			*(void **)((unsigned char *)m_bfme18 + 0x14) = m_bfme14;
		m_bfme14 = 0;
	}
	if (m_bfme10 != 0)
		*(void **)((unsigned char *)m_bfme10 + 0x0c) = m_bfme0c;
	*(void **)m_bfme0c = m_bfme10;
}

void BfmeThingCDE::bfmeGoCDE()
{
	if (m_bfmePtr != 0)
	{
		m_bfmeOwner->bfmeOneCDE(m_bfmePtr);
		return;
	}
	bfmeDtorCDE();
	bfmeFreeCDE(this);
}
