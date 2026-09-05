// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the name resolve at retail 0x002DAE80, 42 bytes.  The stored
// name is copied into the by-value argument slot the registry lookup takes,
// so the callee owns it and no unwind frame is emitted.

class StringBaseNarrowAS
{
protected:
	StringBaseNarrowAS(const StringBaseNarrowAS &other);

	~StringBaseNarrowAS(void);

	char *m_bfmeNarrowAS;
};

class AsciiStringAS : public StringBaseNarrowAS
{
public:
	AsciiStringAS(const AsciiStringAS &other) : StringBaseNarrowAS(other)
	{
	}

	~AsciiStringAS(void)
	{
	}
};

class BfmeRegistryAS
{
public:
	void *bfmeFindAS(AsciiStringAS name);
};

extern BfmeRegistryAS *g_bfmeRegistryAS;		// retail 0x012EF738

class BfmeResolverAS
{
public:
	void bfmeRefreshAS(void);

	void bfmeResolveAS(void);

	char m_bfmePadAAS[0x58];
	void *m_bfmeResultAS;
	char m_bfmePadBAS[4];
	AsciiStringAS m_bfmeNameAS;
};

void BfmeResolverAS::bfmeResolveAS(void)
{
	bfmeRefreshAS();

	m_bfmeResultAS = g_bfmeRegistryAS->bfmeFindAS(m_bfmeNameAS);
}
