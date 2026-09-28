// ?publish@Rva00435A40Sink@@QAEXABV?$StringBase@G@@I@Z
// partial score=0.423 date=2026-09-28
// stlport
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00435A40 (747 bytes): word-wraps a subtitle's wide text into
// (line, colour) entries.  Caller 0x006EE520 (Rva006EE520SubtitleUpdate.cpp)
// passes the text reference and colour through ILT 0x0001CCCE, which is where
// the address-qualified class and method name come from.  The object is the
// one Rva00435270Layout (0x00435270) drives: its +0x08 vector of 8-byte
// elements, +0x14 fade state, +0x1C timer and +0x28 progress are the fields
// this body resets.  The +0x00 member's slots 1 and 0x3C are BFME's
// DisplayString::setText (by-value UnicodeString) and getSize, as in the
// matched Drawable_drawConstructPercent.cpp model.  The element type keeps the
// address-derived name of its matched _M_insert_overflow (0x004358A0).
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "unicode_string.h"

typedef int Int;
typedef float Real;

template <typename T> inline const T *StringBase<T>::str() const
{
	static const T TheNullChr = 0;
	return m_data ? m_data->data : &TheNullChr;
}
inline UnicodeString::UnicodeString() : m_text(0) {}
inline UnicodeString::UnicodeString(const wchar_t *s, int len)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase((const unsigned short *)s, len);
}
inline UnicodeString::UnicodeString(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&s);
}
inline UnicodeString::UnicodeString(const UnicodeString &s, int start, int len)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&s, start, len);
}
inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::~StringBase();
}

class GameFont;

class DisplayString
{
public:
	virtual void slot00();
	virtual void setText( UnicodeString text );
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void setFont( GameFont *font );
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void getSize( Int *width, Int *height );
};

namespace _STL
{
struct Rva004358A0Element
{
	Rva004358A0Element( const UnicodeString &text, unsigned int color ) : m_text( text ), m_color( color ) {}

	UnicodeString m_text;
	unsigned int m_color;
};
}

typedef _STL::Rva004358A0Element SubtitleLine;

class Rva00435A40Sink
{
public:
	void publish( const StringBase<unsigned short> &text, unsigned int color );

private:
	DisplayString *m_displayString;
	char m_unreconstructed04[ 0x04 ];
	_STL::vector<SubtitleLine> m_lines;
	Int m_state14;
	Int m_timerStart18;
	Int m_timer1c;
	char m_unreconstructed20[ 0x08 ];
	Int m_progress28;
	char m_unreconstructed2C[ 0x30 ];
	Real m_textLeft5C;
	char m_unreconstructed60[ 0x04 ];
	Real m_textRight64;
};

enum
{
	SUBTITLE_SPACE = 0x20,
	SUBTITLE_BULLET = 0x95,
	SUBTITLE_NEWLINE = 0x0A
};

// ?publish@Rva00435A40Sink@@QAEXABV?$StringBase@G@@I@Z
void Rva00435A40Sink::publish( const StringBase<unsigned short> &text, unsigned int color )
{
	Int maxWidth = (Int)(m_textRight64 - m_textLeft5C);
	const UnicodeString &source = *(const UnicodeString *)&text;
	const unsigned short *p = text.str();

	while( *p )
	{
		const unsigned short *lineStart = p;
		while( *lineStart && (*lineStart == SUBTITLE_SPACE || *lineStart == SUBTITLE_BULLET) )
			++lineStart;

		p = lineStart;
		const unsigned short *lineEnd = lineStart;
		while( *p )
		{
			while( *p && (*p == SUBTITLE_SPACE || *p == SUBTITLE_BULLET) )
				++p;
			while( *p && *p != SUBTITLE_SPACE && *p != SUBTITLE_BULLET && *p != SUBTITLE_NEWLINE )
				++p;

			UnicodeString candidate( (const wchar_t *)lineStart, p - lineStart );
			m_displayString->setText( candidate );
			Int width;
			Int height;
			m_displayString->getSize( &width, &height );
			if( width <= maxWidth )
			{
				lineEnd = p;
				if( *p != 0 && *p != SUBTITLE_NEWLINE )
					continue;
			}

			if( lineEnd == lineStart )
				lineEnd = p;
			UnicodeString line( source, lineStart - text.str(), lineEnd - lineStart );
			m_lines.push_back( SubtitleLine( line, color ) );
			if( *p == SUBTITLE_NEWLINE )
				++p;
			if( *lineEnd == SUBTITLE_SPACE || *lineEnd == SUBTITLE_BULLET )
				p = lineEnd;
			break;
		}
	}

	m_lines.push_back( SubtitleLine( UnicodeString(), color ) );

	if( m_state14 == 1 || m_state14 == 4 )
		m_progress28 = 0;
	m_timer1c = m_timerStart18;
	if( m_state14 != 3 )
		m_state14 = 0;
}
