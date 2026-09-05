// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the start-game announcement at retail 0x00649DB0, 177 bytes.
// The room is marked closed, then the peer library is told to start with the
// game number as its message.

class StringBaseNarrowAJ
{
public:
	void __cdecl format(class AsciiStringAJ text, ...);

protected:
	StringBaseNarrowAJ(void)
	{
		m_bfmeNarrowAJ = 0;
	}

	StringBaseNarrowAJ(const char *text);

	StringBaseNarrowAJ(const StringBaseNarrowAJ &other);

	~StringBaseNarrowAJ(void);

	char *m_bfmeNarrowAJ;
};

class AsciiStringAJ : public StringBaseNarrowAJ
{
public:
	AsciiStringAJ(void)
	{
	}

	AsciiStringAJ(const char *text) : StringBaseNarrowAJ(text)
	{
	}

	AsciiStringAJ(const AsciiStringAJ &other) : StringBaseNarrowAJ(other)
	{
	}

	~AsciiStringAJ(void)
	{
	}

	const char *bfmeTextAJ(void) const
	{
		return (m_bfmeNarrowAJ != 0) ? m_bfmeNarrowAJ + 8 : "";
	}
};

extern "C" void peerStartGameA(void *peer, const char *message, int reportIntention);

class BfmeRoomAJ
{
public:
	void bfmeSetAJ(const char *key, const char *value);

	char m_bfmePadRAJ[4];
};

class BfmeSessionAJ
{
public:
	void bfmeStartAJ(void *peer);

	char m_bfmePadAAJ[0x90];
	int m_bfmeNumberAJ;
	char m_bfmePadBAJ[0x2c];
	BfmeRoomAJ m_bfmeRoomAJ;
	char m_bfmePadCAJ[788];
	char m_bfmeStartedAJ;
};

void BfmeSessionAJ::bfmeStartAJ(void *peer)
{
	AsciiStringAJ message;

	message.format(AsciiStringAJ("%d"), m_bfmeNumberAJ);

	m_bfmeRoomAJ.bfmeSetAJ("closedplaying", "");

	peerStartGameA(peer, message.bfmeTextAJ(), 2);

	m_bfmeStartedAJ = 1;
}
