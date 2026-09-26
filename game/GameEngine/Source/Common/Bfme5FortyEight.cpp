// Four more: a two-level constructor, a range comparison, a fastcall offset
// and a mode comparison.

extern int g_bfmeVtableDQa[];					// retail 0x010F9AD8
extern int g_bfmeVtableDQb[];					// retail 0x010F9B0C

class BfmeBaseDQ;

extern BfmeBaseDQ *g_bfmeListDQ;				// retail 0x012F3350

class BfmeBaseDQ
{
public:
	// Forced inline so the base constructor leaves no body of its own.
	__forceinline BfmeBaseDQ(void)
	{
		m_bfmeVtable = g_bfmeVtableDQa;

		m_bfmeNext = g_bfmeListDQ;

		g_bfmeListDQ = this;

		m_bfmeCount = 0;
		m_bfmeArmed = true;
	}

	int *m_bfmeVtable;					// +0x00
	BfmeBaseDQ *m_bfmeNext;					// +0x04
	int m_bfmeCount;					// +0x08
	bool m_bfmeArmed;					// +0x0C
};

class Gen_00490500 : public BfmeBaseDQ
{
public:
	Gen_00490500(void);

private:
	int m_bfmeExtra;					// +0x10
};

// ??0Gen_00490500@@QAE@XZ
Gen_00490500::Gen_00490500(void)
{
	m_bfmeVtable = g_bfmeVtableDQb;

	m_bfmeExtra = 0;
}

// ?bfmeEqual@@YA_NPBH00@Z
bool __cdecl bfmeEqual(const int *first, const int *last, const int *other)
{
	while (first != last)
	{
		if (*first != *other)
			return false;

		++first;
		++other;
	}

	return true;
}

class BfmeSwitchDR
{
public:
	int m_bfmeHead[7];					// +0x00
	bool m_bfmeUseHigh;					// +0x1C
};

class BfmeBaseDR
{
public:
	char m_bfmeHead[0xE70];					// +0x000
	int m_bfmeLow;						// +0xE70
	int m_bfmeHigh;						// +0xE74
};

extern BfmeSwitchDR *g_bfmeSwitchDR;				// retail 0x012F1024
extern BfmeBaseDR *g_bfmeBaseDR;				// retail 0x012ED5C8

// ?bfmeOffset@@YIHH@Z
int __fastcall bfmeOffset(int base)
{
	if (g_bfmeSwitchDR->m_bfmeUseHigh)
		return g_bfmeBaseDR->m_bfmeHigh + base;

	return g_bfmeBaseDR->m_bfmeLow + base;
}

class BfmeThingDR
{
public:
	int m_bfmeHead[3];					// +0x00
	unsigned int m_bfmeFlags;				// +0x0C
};

// ?bfmeSameMode@@YAHPBVBfmeThingDR@@0@Z
int __cdecl bfmeSameMode(const BfmeThingDR *first, const BfmeThingDR *second)
{
	int a = (first->m_bfmeFlags & 7) == 2;
	int b = (second->m_bfmeFlags & 7) == 2;

	return a == b;
}
