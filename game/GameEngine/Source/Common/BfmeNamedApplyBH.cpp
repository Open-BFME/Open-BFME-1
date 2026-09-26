// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the named apply at retail 0x002F83D0, 62 bytes.  The name is
// handed to the registry by value; nothing happens unless it resolves.

class StringBaseNarrowBH
{
protected:
	StringBaseNarrowBH(const StringBaseNarrowBH &other) throw();

	~StringBaseNarrowBH(void) throw();

	char *m_bfmeNarrowBH;
};

class AsciiStringBH : public StringBaseNarrowBH
{
public:
	AsciiStringBH(const AsciiStringBH &other) throw() : StringBaseNarrowBH(other)
	{
	}

	~AsciiStringBH(void) throw()
	{
	}
};

class BfmeRegistryBH
{
public:
	void *bfmeFindBH(AsciiStringBH name) throw();
};

extern BfmeRegistryBH *g_bfmeRegistryBH;		// retail 0x012ED80C

class BfmeSubBH
{
public:
	char m_bfmePadSBH[4];
};

class BfmeTargetBH
{
public:
	char m_bfmePadTBH[0x38];
	BfmeSubBH m_bfmeSubBH;
};

class BfmeApplierBH
{
public:
	void bfmeApplyBH(void *owner, void *found, BfmeSubBH *sub) throw();

	void bfmeAddBH(void *owner, const AsciiStringBH &name, BfmeTargetBH *target);
};

void BfmeApplierBH::bfmeAddBH(void *owner, const AsciiStringBH &name,
		BfmeTargetBH *target)
{
	void *found = g_bfmeRegistryBH->bfmeFindBH(name);

	if (found != 0)
		bfmeApplyBH(owner, found, &target->m_bfmeSubBH);
}
