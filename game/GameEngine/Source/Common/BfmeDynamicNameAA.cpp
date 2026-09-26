// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the dynamic-name builder at retail 0x0036E370, 88 bytes.
// The caller supplies the string to fill; the name is taken from the last
// node of a chain, and the id is read before the walk so it survives it.

class StringBaseNarrowAA
{
public:
	void __cdecl format(class AsciiStringAA text, ...);

protected:
	StringBaseNarrowAA(void)
	{
		m_bfmeNarrowAA = 0;
	}

	StringBaseNarrowAA(const char *text);

	StringBaseNarrowAA(const StringBaseNarrowAA &other);

	~StringBaseNarrowAA(void);

	char *m_bfmeNarrowAA;
};

class AsciiStringAA : public StringBaseNarrowAA
{
public:
	AsciiStringAA(void)
	{
	}

	AsciiStringAA(const char *text) : StringBaseNarrowAA(text)
	{
	}

	AsciiStringAA(const AsciiStringAA &other) : StringBaseNarrowAA(other)
	{
	}

	~AsciiStringAA(void)
	{
	}

	const char *bfmeTextAA(void) const
	{
		return (m_bfmeNarrowAA != 0) ? m_bfmeNarrowAA + 8 : "";
	}
};

class BfmeNodeAA
{
public:
	BfmeNodeAA *bfmeLastAA(void);

	char m_bfmePadAAA[4];
	BfmeNodeAA *m_bfmeNextAA;
	char m_bfmePadBAA[24];
	AsciiStringAA m_bfmeNameAA;
};

class BfmePartAA
{
public:
	char m_bfmePadCAA[4];
	BfmeNodeAA *m_bfmeNodeAA;
	char m_bfmePadDAA[108];
	int m_bfmeIdAA;
};

class BfmeOwnerAA
{
public:
	void bfmeMakeNameAA(AsciiStringAA &out, int index);

	char m_bfmePadEAA[8];
	BfmePartAA *m_bfmePartAA;
};

void BfmeOwnerAA::bfmeMakeNameAA(AsciiStringAA &out, int index)
{
	BfmePartAA *part = m_bfmePartAA;

	if (part == 0)
		return;

	int id = part->m_bfmeIdAA;

	BfmeNodeAA *node = part->m_bfmeNodeAA;

	if (node != 0 && node->m_bfmeNextAA != 0)
		node = node->m_bfmeNextAA->bfmeLastAA();

	out.format(AsciiStringAA("Dynamic_%s_of_id_%d_at_index_%d"),
			node->m_bfmeNameAA.bfmeTextAA(), id, index);
}
