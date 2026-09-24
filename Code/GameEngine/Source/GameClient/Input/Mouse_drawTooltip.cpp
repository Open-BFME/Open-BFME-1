// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME Mouse::drawTooltip: tooltip delay bookkeeping and display-string refresh.
// Caller W3DMouse::draw reaches this body through ILT 0x000350BC.

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef unsigned int UnsignedInt;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

struct Header
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
};

// Local view: the shared unicode_string.h has no set, clear or buffer access.
class UnicodeString
{
public:
	UnicodeString &operator=(const UnicodeString &that);
	void clear();

	bool isEmpty() const
	{
		return ((const StringBase<unsigned short> *)this)->isEmpty();
	}

	int compare(const UnicodeString &that) const
	{
		return ((const StringBase<unsigned short> *)this)->compare(
			*(const StringBase<unsigned short> *)&that);
	}

	void set(const UnicodeString &that)
	{
		((StringBase<unsigned short> *)this)->set(
			*(const StringBase<unsigned short> *)&that);
	}

	Header *m_data;
};

inline bool operator!=(const UnicodeString &a, const UnicodeString &b)
{
	return *(const StringBase<unsigned short> *)&a != *(const StringBase<unsigned short> *)&b;
}

struct BfmeGlobalData
{
	unsigned char m_pad0[0xA8F];
	bool m_showTooltips;
	bool m_flagA90;
};

extern BfmeGlobalData *TheWritableGlobalData;

class ScriptEngine
{
public:
	unsigned char m_pad0[0x170B4];
	int m_fade;
};

extern ScriptEngine *TheScriptEngine;

class Display;
extern Display *TheDisplay;

struct BfmeGlobalWR
{
	unsigned char m_pad0[0xB8];
	AsciiString m_fontName;
	int m_fontSize;
	bool m_fontBold;
};

extern BfmeGlobalWR *g_bfmeGlobalWR;

void bfmeGo995B(void);
void bfmeGo1074A(float a, float b);

// ILT route to the unconverted cdecl body at 0x00510DC0 (five stack arguments).
extern void j_00033280();

typedef void (*BfmeTooltipDispatch)(UnicodeString *, AsciiString *, int, bool,
	UnsignedInt);

union BfmeTooltipDispatchThunk
{
	void (*function)(void);
	BfmeTooltipDispatch typed;
};

struct ICoord2D
{
	int x;
	int y;
};

// Leading field of the 0x3C-byte MouseIO record; the rest is not read here.
struct MouseIO
{
	ICoord2D pos;
};

class Mouse
{
public:
	void drawTooltip();

private:
	unsigned char m_pad0[0x1070];
	AsciiString m_tooltipFontName;
	int m_tooltipFontSize;
	bool m_tooltipFontIsBold;
	unsigned char m_pad1[0x1080 - 0x1079];
	int m_tooltipDelayTime;
	unsigned char m_pad2[0x108C - 0x1084];
	unsigned char m_buttonActivity;
	unsigned char m_pad3[0x10FC - 0x108D];
	UnicodeString m_tooltipState;
	UnicodeString m_tooltipString;
	UnicodeString m_cursorText;
	int m_tooltipTimer;
	unsigned char m_displayTooltip;
	unsigned char m_pad4[0x4D10 - 0x110D];
	MouseIO m_currMouse;
	unsigned char m_pad5[0x4DD0 - 0x4D18];
	int m_tooltipDelay;
	int m_tooltipHighlight;
	UnsignedInt m_tooltipHighlightStart;
	UnsignedInt m_stillTime;
	unsigned char m_tooltipColorRed;
	unsigned char m_pad6[3];
	unsigned char m_tooltipColorGreen;
	unsigned char m_pad7[3];
	unsigned char m_tooltipColorBlue;
	unsigned char m_pad8[3];
	unsigned char m_tooltipColorAlpha;
	unsigned char m_pad9[0x4E00 - 0x4DED];
};

void Mouse::drawTooltip()
{
	UnsignedInt now = timeGetTime();

	if (m_tooltipString.compare(m_cursorText))
	{
		m_cursorText.set(m_tooltipString);
		m_stillTime = now;
		m_buttonActivity = 0;
	}

	UnsignedInt delay = m_tooltipDelayTime;
	if (m_tooltipDelay >= 0)
		delay = m_tooltipDelay;
	if (TheWritableGlobalData->m_flagA90)
		delay = 0;

	if (now - m_stillTime >= delay)
	{
		if (!m_displayTooltip)
		{
			m_tooltipHighlight = 0;
			m_tooltipHighlightStart = timeGetTime();
		}
		m_displayTooltip = 1;
	}
	else
	{
		m_displayTooltip = 0;
	}

	if (TheScriptEngine->m_fade != 0)
		return;

	if (TheWritableGlobalData->m_showTooltips && m_displayTooltip &&
		TheDisplay != 0 && !m_buttonActivity && !m_tooltipString.isEmpty())
	{
		if (m_tooltipState != m_tooltipString)
		{
			m_tooltipState = m_tooltipString;

			AsciiString fontName;
			int fontSize;
			bool fontBold;
			const AsciiString *globalName;

			if (g_bfmeGlobalWR != 0 &&
				!(globalName = &g_bfmeGlobalWR->m_fontName)->isEmpty())
			{
				fontName.set(*globalName);
				fontSize = g_bfmeGlobalWR->m_fontSize;
				fontBold = g_bfmeGlobalWR->m_fontBold;
			}
			else
			{
				fontName.set(m_tooltipFontName);
				fontSize = m_tooltipFontSize;
				fontBold = m_tooltipFontIsBold;
			}

			BfmeTooltipDispatchThunk tooltipDispatch;
			tooltipDispatch.function = j_00033280;
			tooltipDispatch.typed(&m_tooltipState, &fontName, fontSize, fontBold,
				(static_cast<UnsignedInt>(m_tooltipColorAlpha) << 24) |
				(static_cast<UnsignedInt>(m_tooltipColorRed) << 16) |
				(static_cast<UnsignedInt>(m_tooltipColorGreen) << 8) |
				m_tooltipColorBlue);

			bfmeGo1074A((float)m_currMouse.pos.x, (float)m_currMouse.pos.y);
		}
		m_tooltipTimer = 4;
		return;
	}

	UnicodeString *tooltip = &m_tooltipState;
	if (tooltip->m_data && tooltip->m_data->length != 0)
	{
		if (--m_tooltipTimer <= 0)
		{
			bfmeGo995B();
			tooltip->clear();
		}
	}
}
