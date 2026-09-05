// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the level-path builder at retail 0x004675F0, 206 bytes.  The
// level number becomes a suffix, and the result is assembled into a shared
// buffer whose address the caller gets back.

class StringBaseNarrowAN
{
public:
	void __cdecl format(class AsciiStringAN text, ...);

protected:
	StringBaseNarrowAN(void)
	{
		m_bfmeNarrowAN = 0;
	}

	StringBaseNarrowAN(const char *text);

	StringBaseNarrowAN(const StringBaseNarrowAN &other);

	~StringBaseNarrowAN(void);

	char *m_bfmeNarrowAN;
};

class AsciiStringAN : public StringBaseNarrowAN
{
public:
	AsciiStringAN(void)
	{
	}

	AsciiStringAN(const char *text) : StringBaseNarrowAN(text)
	{
	}

	AsciiStringAN(const AsciiStringAN &other) : StringBaseNarrowAN(other)
	{
	}

	~AsciiStringAN(void)
	{
	}

	const char *bfmeTextAN(void) const
	{
		return (m_bfmeNarrowAN != 0) ? m_bfmeNarrowAN + 8 : "";
	}
};

extern char g_bfmeBufferAN[];

void bfmeAssembleAN(int a, char *buffer, const char *text, int p3, int p4, int p5,
		int p6, int p7, int p8);

class BfmeLevelAN
{
public:
	char *bfmeBuildAN(unsigned int level, int p2, int p3, int p4, int p5, int p6,
			int p7, int p8);

	char m_bfmePadAN[0x1c4];
	char m_bfmeBuiltAN;
};

char *BfmeLevelAN::bfmeBuildAN(unsigned int level, int p2, int p3, int p4, int p5,
		int p6, int p7, int p8)
{
	g_bfmeBufferAN[0] = 0;

	if (level < 12)
	{
		AsciiStringAN suffix;

		suffix.format(AsciiStringAN("/_level%d"), level);

		bfmeAssembleAN(p2, g_bfmeBufferAN, suffix.bfmeTextAN(), p3, p4, p5, p6, p7, p8);

		m_bfmeBuiltAN = 1;
	}

	return g_bfmeBufferAN;
}
