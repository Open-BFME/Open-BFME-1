// cl: /O2 /Ob1 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "unicode_string.h"

// Retail inlines the UnicodeString forwarding members and calls the
// StringBase<unsigned short> copy and release bodies directly.
inline UnicodeString::UnicodeString(const UnicodeString &other)
{
	((StringBase<unsigned short> *)this)
		->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&other);
}

inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}

class SubtitleEntry
{
public:
	SubtitleEntry(const UnicodeString &text, unsigned int color, int style,
		int alignment, int line, int startFrame, int endFrame);

protected:
	virtual ~SubtitleEntry();

private:
	UnicodeString m_text;
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
