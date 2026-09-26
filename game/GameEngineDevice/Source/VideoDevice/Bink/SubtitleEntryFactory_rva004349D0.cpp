// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// BFME's video-player setup installs this callback beside the registry-language
// and SUBTITLE: lookup callbacks.  SubtitleManager::addSubtitle proves the
// nine-argument callback ABI; the called 0x00434810 constructor proves the
// concrete SubtitleEntry layout and non-trivial base lifetime.

typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;

class AsciiString
{
private:
	void *m_data;
};

class UnicodeString
{
private:
	void *m_data;
};

class GameFont;

class FontLibrary
{
public:
	GameFont *getFont(AsciiString *name, Real pointSize, Bool bold);
};

extern FontLibrary *TheFontLibrary;

class SubtitleEntry
{
public:
	SubtitleEntry(const UnicodeString &text, UnsignedInt color, Int style,
		Int alignment, Int line, Int startFrame, Int endFrame);
	virtual ~SubtitleEntry();

private:
	UnicodeString m_text;
	UnsignedInt m_color;
	Int m_style;
	Int m_alignment;
	Int m_line;
	Int m_startFrame;
	Int m_endFrame;
	Bool m_displayed;
};

class Rva00434810SubtitleEntry : public SubtitleEntry
{
public:
	Rva00434810SubtitleEntry(GameFont *font, const UnicodeString &text,
		UnsignedInt color, Int style, Int alignment, Int line,
		Int startFrame, Int endFrame);

private:
	void *m_displayStrings[3];
	Int m_displayStringCount;
	Int m_displayStringCapacity;
};

SubtitleEntry *rva004349D0CreateSubtitleEntry(AsciiString *fontName,
	Int pointSize, const UnicodeString &text, UnsignedInt color, Int style,
	Int alignment, Int line, Int startFrame, Int endFrame)
{
	GameFont *font = TheFontLibrary->getFont(fontName, (Real)pointSize, false);
	return new Rva00434810SubtitleEntry(font, text, color, style, alignment,
		line, startFrame, endFrame);
}
