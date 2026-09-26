// ?bfmeStopTwoAQA@BfmeSubAQA@@QAEXXZ
// Full retail cleanup [0x003C9320, 0x003C9428); matched caller 0x0060D360.
// Calls: ILT 0x10FFA -> 0x617A10 (handle removal), 0x9737 -> 0x3B9500,
// and 0x307CE -> 0x61B100. The imported vector move is MSVCR71 memmove.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class BfmeSubAQA;


class BfmeOneAQA
{
public:
	void bfmeStopAQA();
};

class BfmeSinkAM
{
public:
	void bfmeDrop(int handle);
};

extern BfmeSinkAM *g_bfmeSinkAM;

class BfmeW1105
{
public:
	void bfmeGo1105A(void);
};

class LivingWorldRegion
{
public:
	void rva0061B100(void);
};

class BfmeAQAElement
{
private:
	char m_bfmePad[0xAC];

public:
	int m_bfmeHandle;
};

extern "C" __declspec(dllimport) void * __cdecl BfmeMemMove(void *destination, const void *source, unsigned int bytes);

inline BfmeAQAElement **bfmeCopyAQA(
	BfmeAQAElement **destination,
	BfmeAQAElement **first,
	BfmeAQAElement **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;
	return (BfmeAQAElement **)((char *)BfmeMemMove(destination, first, bytes) + bytes);
}

class BfmeAQAElementVector
{
public:
	unsigned int bfmeSize(void) const
	{
		return (unsigned int)(m_bfmeFinish - m_bfmeStart);
	}

	BfmeAQAElement *bfmeAt(unsigned int index) const
	{
		return m_bfmeStart[index];
	}

	void bfmeClear(void)
	{
		m_bfmeFinish = bfmeCopyAQA(m_bfmeStart, m_bfmeFinish, m_bfmeFinish);
	}

	BfmeAQAElement **m_bfmeStart;
	BfmeAQAElement **m_bfmeFinish;
	BfmeAQAElement **m_bfmeEnd;
};

class BfmeAQARegionVector
{
public:
	unsigned int bfmeSize(void) const
	{
		return (unsigned int)(m_bfmeFinish - m_bfmeStart);
	}

	LivingWorldRegion *bfmeAt(unsigned int index) const
	{
		return m_bfmeStart[index];
	}

	LivingWorldRegion **m_bfmeStart;
	LivingWorldRegion **m_bfmeFinish;
	LivingWorldRegion **m_bfmeEnd;
};

inline void bfmeResetAQAState(void *object)
{
	char *bytes = (char *)object;
	*(int *)(bytes + 0x08) = 0;
	*(int *)(bytes + 0x0C) = 0;
	*(int *)(bytes + 0x20) = 0;
}

class BfmeAQAOwner
{
private:
	char m_bfmeHead[0x30];

public:
	BfmeAQARegionVector m_bfmeRegions;

private:
	char m_bfmeGap[4];

public:
	BfmeW1105 m_bfmeDispatcher;
};

class BfmeAQARef
{
public:
	virtual void bfmeDestroy(void);
	virtual void bfmeSlot01(void);
	virtual void bfmeSlot02(void);
	virtual void bfmeSlot03(void);
	virtual void bfmeSlot04(void);
	virtual void bfmeSlot05(void);
	virtual void bfmeSlot06(void);
	virtual void bfmeSlot07(void);
	virtual void bfmeSlot08(void);
	virtual void bfmeSlot09(void);
	virtual void bfmeSlot10(void);
	virtual void bfmeSlot11(void);
	virtual void bfmeSlot12(void);
	virtual void bfmeSlot13(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot15(void);
	virtual void bfmeNotify(void);

	void bfmeRelease(void)
	{
		bfmeNotify();
		--m_bfmeRefCount;
		if (m_bfmeRefCount == 0)
			bfmeDestroy();
	}

	int m_bfmeRefCount;
};

class BfmeAQARefSlot
{
public:
	operator BfmeAQARef *(void) const
	{
		return m_bfmePtr;
	}

	BfmeAQARef *operator->(void) const
	{
		return m_bfmePtr;
	}

	void reset()
	{
		BfmeAQARef *p = m_bfmePtr;
		if (p != 0)
		{
			p->bfmeRelease();
			m_bfmePtr = 0;
		}
	}
	BfmeAQARef *m_bfmePtr;
};

class BfmeSubAQA
{
public:
	void bfmeStopTwoAQA();

private:
	char m_bfmeHead[4];
	BfmeAQAOwner *m_bfmeOwner;
	int m_bfme08;
	int m_bfme0C;
	unsigned char m_bfme10;
	unsigned char m_bfmeGap11[3];
	BfmeAQAElementVector m_bfmeElements;
	int m_bfme20;
	BfmeAQARefSlot m_bfmeSink;
	char m_bfmeGap28[0x0C];
	BfmeAQAElementVector m_bfmeOther;
};

class BfmeTwoAQA
{
public:
	void bfmeSendAQA(void *what);
	void bfmeFinishAQA();
	unsigned char m_bfmeHead[0x28];
	BfmeSubAQA *m_bfmeSub;
};

extern BfmeOneAQA *g_bfmeOneAQA;
extern BfmeTwoAQA *g_bfmeTwoAQA;

void BfmeSubAQA::bfmeStopTwoAQA(void)
{
	for (unsigned int index = 0; index < m_bfmeElements.bfmeSize(); ++index)
		g_bfmeSinkAM->bfmeDrop(m_bfmeElements.bfmeAt(index)->m_bfmeHandle);

	m_bfmeOther.m_bfmeStart = 0;
	m_bfmeOther.m_bfmeFinish = 0;
	m_bfmeOther.m_bfmeEnd = 0;
	m_bfmeElements.bfmeClear();
	bfmeResetAQAState(this);
	// Retail completes these state stores before loading the first reference.
	_ReadWriteBarrier();

	BfmeAQARef *firstSink = m_bfmeSink.m_bfmePtr;
	if (firstSink != 0)
	{
		firstSink->bfmeRelease();
		m_bfmeSink.m_bfmePtr = 0;
	}

	if (m_bfmeOwner != 0)
	{
		m_bfmeOwner->m_bfmeDispatcher.bfmeGo1105A();

		BfmeAQARegionVector *regions = &m_bfmeOwner->m_bfmeRegions;
		for (unsigned int index = 0; index < regions->bfmeSize(); ++index)
			regions->bfmeAt(index)->rva0061B100();
	}

	m_bfme10 = 1;
	if (m_bfmeSink != 0)
		m_bfmeSink.reset();

	m_bfmeSink.m_bfmePtr = 0;
	m_bfmeOwner = 0;
}

void __stdcall bfmeGoAQA(void *what)
{
	if (g_bfmeOneAQA != 0)
		g_bfmeOneAQA->bfmeStopAQA();
	if (g_bfmeTwoAQA->m_bfmeSub != 0)
		g_bfmeTwoAQA->m_bfmeSub->bfmeStopTwoAQA();
	g_bfmeTwoAQA->bfmeSendAQA(what);
	g_bfmeTwoAQA->bfmeFinishAQA();
}
