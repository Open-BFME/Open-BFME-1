// W3DDebugDisplay::drawText, retail 0x006E6D30, 220 bytes.
// partial score=0.99 date=2026-09-08
// The reference W3DDebugDisplay.cpp supplies the method body. The receiver
// offsets and DisplayString slots match the retail body at this address.

typedef int Int;
typedef int Color;
typedef char Char;
typedef unsigned short WideChar;

#pragma intrinsic( _ReadWriteBarrier )
extern "C" void _ReadWriteBarrier();

class BFMERetailAsciiString;

template <typename T> class StringBase
{
friend class BFMERetailAsciiString;
friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();
	void *m_data;
};

class BFMERetailAsciiString : private StringBase<Char>
{
public:
	BFMERetailAsciiString( const Char *text ) : StringBase<Char>( text ) {}
	~BFMERetailAsciiString() {}
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString( const UnicodeString &other )
		: StringBase<WideChar>( other ) {}
	~UnicodeString() {}
	void translate( const BFMERetailAsciiString &text );
};

class DisplayString
{
public:
	virtual void unused00();
	virtual void setText( UnicodeString text );
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void setTextColor( Color text, Color drop );
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void draw( Int x, Int y, Color text, Color drop );
};

class GameFont;

class DebugDisplayInterface
{
public:
	virtual ~DebugDisplayInterface() {}
};

class DebugDisplay : public DebugDisplayInterface
{
public:
	virtual ~DebugDisplay() {}

protected:
	char m_padding04[0x1c];
};

class W3DDebugDisplay : public DebugDisplay
{
public:
	virtual ~W3DDebugDisplay();
	void drawText( Int x, Int y, Char *text );

protected:
	GameFont *m_font;
	Int m_fontWidth;
	Int m_fontHeight;
	DisplayString *m_displayString;
};

void W3DDebugDisplay::drawText( Int x, Int y, Char *text )
{
	if ( m_font == 0 || m_displayString == 0 )
		return;

	Color textColor = -1;
	Color dropColor = 0xff000000;
	UnicodeString unicode;
	_ReadWriteBarrier();
	{
		BFMERetailAsciiString ascii( text );
		unicode.translate( ascii );
	}
	m_displayString->setText( unicode );
	m_displayString->setTextColor( textColor, dropColor );
	m_displayString->draw( x * m_fontWidth, 13 + y * m_fontHeight, 1, 1 );
}
