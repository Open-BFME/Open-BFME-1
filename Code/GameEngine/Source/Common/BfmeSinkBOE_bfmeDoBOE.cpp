// ?d_0040c660@@YAXXZ
// BFME BfmeSinkBOE::bfmeDoBOE body reached through thunk 0x00020E3C.
// The sink owns a displayed-credit-style list; its second argument supplies
// the current display dimensions as two floats.

typedef int Int;
typedef float Real;
typedef unsigned char UnsignedByte;
typedef int Color;

template <typename T>
inline T Rva0040C660Clamp(T low, T value, T high)
{
	if (value < low)
		return low;
	else if (value > high)
		return high;
	return value;
}

inline Color GameMakeColor(UnsignedByte red, UnsignedByte green,
	UnsignedByte blue, UnsignedByte alpha)
{
	return (alpha << 24) |
		(red << 16) | (green << 8) | blue;
}

extern void GameGetColorComponents(Color color,
	UnsignedByte *red, UnsignedByte *green,
	UnsignedByte *blue, UnsignedByte *alpha);

class Rva0040C660DisplayString
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void setColor(Color color, Color dropColor) = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void draw(Int x, Int y, Int scaleX, Int scaleY) = 0;
	virtual void getSize(Int *width, Int *height) = 0;
};

struct Rva0040C660Line
{
	Int m_style;
	unsigned char m_pad0004[0xc];
	Rva0040C660DisplayString *m_displayString;
	Rva0040C660DisplayString *m_secondDisplayString;
	Int m_posX;
	Int m_posY;
	unsigned char m_pad0020[4];
	Color m_color;
};

struct Rva0040C660Node
{
	Rva0040C660Node *m_next;
	Rva0040C660Node *m_prev;
	Rva0040C660Line *m_line;
};

struct Rva0040C660Size
{
	Int m_width;
	Int m_height;
};

class Rva0040C660BfmeSinkBOE
{
public:
	void bfmeDoBOE(void *one, void *two);

private:
	unsigned char m_pad0000[0x10];
	Rva0040C660Node *m_displayedLineList;
	unsigned char m_pad0014[0x28];
	Int m_displayWidth;
	Int m_displayHeight;
};

// ?bfmeDoBOE@BfmeSinkBOE@@QAEXPAX0@Z
void Rva0040C660BfmeSinkBOE::bfmeDoBOE(void *one, void *two)
{
	const Real *display = reinterpret_cast<const Real *>(one);
	const Real *dimensions = reinterpret_cast<const Real *>(two);
	m_displayWidth = (Int)dimensions[0];
	m_displayHeight = (Int)dimensions[1];

	Rva0040C660Node *drawIt = m_displayedLineList->m_next;
	while (drawIt != m_displayedLineList)
	{
		Rva0040C660Line *cLine = drawIt->m_line;
		Int heightChunk = m_displayHeight / 3;
		Real perc = 0.0f;
		if (cLine->m_posY < heightChunk || cLine->m_posY > heightChunk * 2)
		{
			if (cLine->m_posY < 0 || cLine->m_posY > m_displayHeight)
				perc = 0.0f;
			else if (cLine->m_posY < heightChunk)
				perc = (Real)cLine->m_posY / heightChunk;
			else
				perc = 1.0f - (Real)(cLine->m_posY - 2 * heightChunk) / heightChunk;
		}
		else
			perc = 1.0f;

		UnsignedByte r, g, b, a;
		GameGetColorComponents(cLine->m_color, &r, &g, &b, &a);
		Int color = GameMakeColor(r, g, b,
			(UnsignedByte)Rva0040C660Clamp(0, (Int)(a * perc), 255));
		Int bColor = GameMakeColor(0, 0, 0,
			(UnsignedByte)Rva0040C660Clamp(0, (Int)(a * perc), 255));

		switch (cLine->m_style)
		{
		case 0:
		case 1:
		case 2:
			if (cLine->m_displayString != 0)
			{
				cLine->m_displayString->setColor(color, bColor);
				cLine->m_displayString->draw(
					(Int)((Real)cLine->m_posX + display[0]),
					(Int)((Real)cLine->m_posY + display[1]), 1, 1);
			}
			break;
		case 3:
			{
				Int chunk = m_displayWidth / 3;
				Rva0040C660Size size;
				if (cLine->m_displayString != 0)
				{
					cLine->m_displayString->getSize(&size.m_width, &size.m_height);
					cLine->m_displayString->setColor(color, bColor);
					cLine->m_displayString->draw(
						(Int)(display[0] + chunk - (size.m_width / 2)),
						(Int)((Real)cLine->m_posY + display[1]), 1, 1);
				}
				if (cLine->m_secondDisplayString != 0)
				{
					cLine->m_secondDisplayString->getSize(&size.m_width, &size.m_height);
					cLine->m_secondDisplayString->setColor(color, bColor);
					cLine->m_secondDisplayString->draw(
						(Int)(display[0] + 2 * chunk - (size.m_width / 2)),
						(Int)((Real)cLine->m_posY + display[1]), 1, 1);
				}
			}
			break;
		}

		drawIt = drawIt->m_next;
	}
}
