// cl: /O2 /DNDEBUG /MD

typedef int Int;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Color;

inline Color GameMakeColor(UnsignedByte red, UnsignedByte green,
	UnsignedByte blue, UnsignedByte alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

class DisplayString
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void setColor(Color color, Color dropColor);
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void draw(Int x, Int y, Int scaleX, Int scaleY);
	virtual void getSize(Int *width, Int *height);
};

class Mouse
{
public:
	void drawCursorText();

private:
	char m_pad0[0x4d10];
	Int m_posX;
	Int m_posY;
	char m_pad1[0x4dac - 0x4d18];
	DisplayString *m_cursorTextDisplayString;
	UnsignedInt m_cursorTextRed;
	UnsignedInt m_cursorTextGreen;
	UnsignedInt m_cursorTextBlue;
	UnsignedInt m_cursorTextAlpha;
	UnsignedInt m_cursorTextDropRed;
	UnsignedInt m_cursorTextDropGreen;
	UnsignedInt m_cursorTextDropBlue;
	UnsignedInt m_cursorTextDropAlpha;
};

void Mouse::drawCursorText()
{
	if (m_cursorTextDisplayString == 0)
		return;

	Color color = GameMakeColor((UnsignedByte)m_cursorTextRed,
		(UnsignedByte)m_cursorTextGreen, (UnsignedByte)m_cursorTextBlue,
		(UnsignedByte)m_cursorTextAlpha);
	Color dropColor = GameMakeColor((UnsignedByte)m_cursorTextDropRed,
		(UnsignedByte)m_cursorTextDropGreen, (UnsignedByte)m_cursorTextDropBlue,
		(UnsignedByte)m_cursorTextDropAlpha);
	Int width;
	Int height;
	m_cursorTextDisplayString->getSize(&width, &height);
	Int x = m_posX - width / 2;
	Int y = m_posY - height / 2;
	m_cursorTextDisplayString->setColor(color, dropColor);
	m_cursorTextDisplayString->draw(x, y, 1, 1);
}
