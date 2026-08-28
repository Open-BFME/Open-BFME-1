// Two small helpers, each of which the retail image emits twice: a held block
// let go of with the counts reset, and a thing whose buffer is let go of before
// the thing itself. Both copies of each are converted here, under their own
// names, so the two ledger rows stay distinct.

extern "C" __declspec(dllimport) void __cdecl free(void *block);

struct BfmeThingJA
{
	void bfmeClearJA(void);

	void *m_bfmeAt;				// 0x0
	int m_bfmeCount;			// 0x4
	int m_bfmeCap;				// 0x8
};

void BfmeThingJA::bfmeClearJA(void)
{
	void *at = m_bfmeAt;

	if (at != 0)
	{
		free(at);

		m_bfmeAt = 0;
	}

	m_bfmeCount = 0;
	m_bfmeCap = 0;
}

struct BfmeThingJB
{
	unsigned char m_bfmeHead[0x14];		// 0x00
	void *m_bfmeBuf;			// 0x14
};

void bfmeDropJB(BfmeThingJB *what)
{
	if (what != 0)
	{
		if (what->m_bfmeBuf != 0)
			free(what->m_bfmeBuf);

		free(what);
	}
}

struct BfmeThingJE
{
	void bfmeClearJE(void);

	void *m_bfmeAt;				// 0x0
	int m_bfmeCount;			// 0x4
	int m_bfmeCap;				// 0x8
};

void BfmeThingJE::bfmeClearJE(void)
{
	void *at = m_bfmeAt;

	if (at != 0)
	{
		free(at);

		m_bfmeAt = 0;
	}

	m_bfmeCount = 0;
	m_bfmeCap = 0;
}

struct BfmeThingJF
{
	unsigned char m_bfmeHead[0x14];		// 0x00
	void *m_bfmeBuf;			// 0x14
};

void bfmeDropJF(BfmeThingJF *what)
{
	if (what != 0)
	{
		if (what->m_bfmeBuf != 0)
			free(what->m_bfmeBuf);

		free(what);
	}
}
