// cl: /O2 /Ob0 /MD /EHsc

class UnicodeString
{
private:
	void *m_data;
};

class SubtitleEntryUnicodeBase
{
public:
	SubtitleEntryUnicodeBase(const UnicodeString &other);
	~SubtitleEntryUnicodeBase();

private:
	void *m_data;
};

class SubtitleEntry
{
public:
	SubtitleEntry(const UnicodeString &text, unsigned int color, int style,
		int alignment, int line, int startFrame, int endFrame);

protected:
	virtual ~SubtitleEntry();

private:
	SubtitleEntryUnicodeBase m_text;
	unsigned int m_color;
	int m_style;
	int m_alignment;
	int m_line;
	int m_startFrame;
	int m_endFrame;
	bool m_displayed;
};

SubtitleEntry::SubtitleEntry(const UnicodeString &text, unsigned int color,
	int style, int alignment, int line, int startFrame, int endFrame) :
	m_text(text),
	m_color(color),
	m_style(style),
	m_alignment(alignment),
	m_line(line),
	m_startFrame(startFrame),
	m_endFrame(endFrame),
	m_displayed(false)
{
}

SubtitleEntry::~SubtitleEntry()
{
}
