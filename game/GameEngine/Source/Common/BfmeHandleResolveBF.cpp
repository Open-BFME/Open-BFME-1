// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the cached handle resolve at retail 0x0013EE70, 59 bytes.  The
// name is looked up once and then released, so the handle is what survives.

class AsciiStringBF
{
public:
	void bfmeClearBF(void);

	bool bfmeEmptyBF(void) const
	{
		return (m_bfmeNarrowBF == 0) || (*(const unsigned short *)(m_bfmeNarrowBF + 4) == 0);
	}

	char *m_bfmeNarrowBF;
};

class BfmeRegistryBF
{
public:
	void *bfmeFindBF(const AsciiStringBF &name);
};

extern BfmeRegistryBF *g_bfmeRegistryBF;		// retail 0x012F6924

class BfmeHolderBF
{
public:
	void *bfmeResolveBF(void);

	char m_bfmePadABF[0x30];
	AsciiStringBF m_bfmeNameBF;
	char m_bfmePadBBF[0x35c];
	void *m_bfmeHandleBF;
};

void *BfmeHolderBF::bfmeResolveBF(void)
{
	if (!m_bfmeNameBF.bfmeEmptyBF() && g_bfmeRegistryBF != 0)
	{
		m_bfmeHandleBF = g_bfmeRegistryBF->bfmeFindBF(m_bfmeNameBF);

		m_bfmeNameBF.bfmeClearBF();
	}

	return m_bfmeHandleBF;
}
