// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the two-name resolve at retail 0x002DE300, 73 bytes.  The first
// name always goes to its registry by value; the second only when it is set,
// and that one goes by reference.

class StringBaseNarrowBN
{
protected:
	StringBaseNarrowBN(const StringBaseNarrowBN &other) throw();

	~StringBaseNarrowBN(void) throw();

	char *m_bfmeNarrowBN;
};

class AsciiStringBN : public StringBaseNarrowBN
{
public:
	AsciiStringBN(const AsciiStringBN &other) throw() : StringBaseNarrowBN(other)
	{
	}

	~AsciiStringBN(void) throw()
	{
	}

	bool bfmeEmptyBN(void) const
	{
		return (m_bfmeNarrowBN == 0) || (*(const unsigned short *)(m_bfmeNarrowBN + 4) == 0);
	}
};

class BfmeRegistryBN
{
public:
	void *bfmeFindBN(AsciiStringBN name) throw();
};

class BfmeOtherBN
{
public:
	void *bfmeLookupBN(const AsciiStringBN &name) throw();
};

extern BfmeRegistryBN *g_bfmeRegistryBN;		// retail 0x012EF738
extern BfmeOtherBN *g_bfmeOtherBN;			// retail 0x012EF1D8

class BfmeResolverBN
{
public:
	void bfmeRefreshBN(void);

	void bfmeResolveBN(void);

	char m_bfmePadBN[0x58];
	void *m_bfmeFirstBN;
	void *m_bfmeSecondBN;
	AsciiStringBN m_bfmeNameBN;
	AsciiStringBN m_bfmeOtherNameBN;
};

void BfmeResolverBN::bfmeResolveBN(void)
{
	bfmeRefreshBN();

	m_bfmeFirstBN = g_bfmeRegistryBN->bfmeFindBN(m_bfmeNameBN);

	if (!m_bfmeOtherNameBN.bfmeEmptyBN())
		m_bfmeSecondBN = g_bfmeOtherBN->bfmeLookupBN(m_bfmeOtherNameBN);
}
