// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the order description at retail 0x00676290, 190 bytes.
// Here the name comes from a virtual call on the owner the order points at,
// so the struct return slot is passed to an indirect call.

class StringBaseNarrowZT
{
public:
	void __cdecl format(class AsciiStringZT text, ...);

protected:
	StringBaseNarrowZT(void)
	{
		m_bfmeNarrowZT = 0;
	}

	StringBaseNarrowZT(const char *text);

	StringBaseNarrowZT(const StringBaseNarrowZT &other);

	~StringBaseNarrowZT(void);

	char *m_bfmeNarrowZT;
};

class AsciiStringZT : public StringBaseNarrowZT
{
public:
	AsciiStringZT(void)
	{
	}

	AsciiStringZT(const char *text) : StringBaseNarrowZT(text)
	{
	}

	AsciiStringZT(const AsciiStringZT &other) : StringBaseNarrowZT(other)
	{
	}

	~AsciiStringZT(void)
	{
	}

	const char *bfmeTextZT(void) const
	{
		return (m_bfmeNarrowZT != 0) ? m_bfmeNarrowZT + 8 : "";
	}
};

class BfmeOwnerZT
{
public:
	virtual void bfmeSlot0ZT(void) = 0;
	virtual void bfmeSlot1ZT(void) = 0;
	virtual void bfmeSlot2ZT(void) = 0;
	virtual AsciiStringZT bfmeNameZT(void) = 0;
};

class BfmeOrderZT
{
public:
	AsciiStringZT bfmeDescribeZT(void);

	BfmeOwnerZT *m_bfmeOwnerZT;
	char m_bfmePadZT[8];
	unsigned char m_bfmeRelayZT;
};

AsciiStringZT BfmeOrderZT::bfmeDescribeZT(void)
{
	AsciiStringZT text;

	text.format(AsciiStringZT("%s, relay=0x%X"),
			m_bfmeOwnerZT->bfmeNameZT().bfmeTextZT(), m_bfmeRelayZT);

	return text;
}
