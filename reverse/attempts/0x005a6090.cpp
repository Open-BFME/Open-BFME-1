// ?drawTooltip@Mouse@@QAEXXZ
// partial score=0.78 date=2026-09-10
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Readable BFME body of ?drawTooltip@Mouse@@QAEXXZ.
//
// Retail's anonymous 599-byte body starts at 0x005A6090 and ends at the ret
// at 0x005A62E7.  W3DMouse::draw is the named caller: its ILT 0x000350BC is
// the drawTooltip route to this body.  The tooltip display helper reached by
// this method remains an existing anonymous callee; it is not claimed here.

typedef unsigned int UnsignedInt;

template <typename T>
class StringBase
{
public:
	StringBase() : m_data(0) {}
	~StringBase();
	bool isEmpty() const;
	int compare(const StringBase<T> &other) const;
	void set(const StringBase<T> &other);
	void releaseBuffer();

	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T text[1];
	};

	Header *m_data;
};

template <typename T>
bool operator!=(const StringBase<T> &left, const StringBase<T> &right);

typedef StringBase<char> AsciiString;

class UnicodeString
{
public:
	UnicodeString &operator=(const UnicodeString &other);

	bool isEmpty() const
	{
		return reinterpret_cast<const StringBase<unsigned short> *>(this)->isEmpty();
	}

	void set(const UnicodeString &other)
	{
		reinterpret_cast<StringBase<unsigned short> *>(this)->set(
			*reinterpret_cast<const StringBase<unsigned short> *>(&other));
	}

	int compare(const UnicodeString &other) const
	{
		return reinterpret_cast<const StringBase<unsigned short> *>(this)->compare(
			*reinterpret_cast<const StringBase<unsigned short> *>(&other));
	}

	bool differs(const UnicodeString &other) const
	{
		return *reinterpret_cast<const StringBase<unsigned short> *>(this) !=
			*reinterpret_cast<const StringBase<unsigned short> *>(&other);
	}

	void releaseBuffer()
	{
		reinterpret_cast<StringBase<unsigned short> *>(this)->releaseBuffer();
	}

	StringBase<unsigned short>::Header *m_data;
};

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
	unsigned char m_fontBold;
};

extern BfmeGlobalWR *g_bfmeGlobalWR;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

// These are existing incremental-link routes.  Their generic bodies remain
// owned by their own ledger rows; the typed unions only describe the retail
// call ABI at this call site.
extern void j_0002497e();
extern void j_00033280();
extern void j_000339c9();

typedef void (*BfmeTooltipDispatch)(UnicodeString *, AsciiString *, int, int,
	UnsignedInt);
typedef void (*BfmeMousePositionDispatch)(float, float);

union BfmeTooltipDispatchThunk
{
	void (*function)(void);
	BfmeTooltipDispatch typed;
};

union BfmeMousePositionDispatchThunk
{
	void (*function)(void);
	BfmeMousePositionDispatch typed;
};

union BfmeFontAttributes
{
	unsigned char bold;
	int bits;
};

class Mouse
{
public:
	void drawTooltip();

private:
	unsigned char m_pad0[0x1070];
	AsciiString m_tooltipFontName;
	int m_tooltipFontSize;
	unsigned char m_tooltipFontIsBold;
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
	int m_currentX;
	int m_currentY;
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

	int delay = m_tooltipDelayTime;
	if (m_tooltipDelay >= 0)
		delay = m_tooltipDelay;

	if (!TheWritableGlobalData->m_flagA90)
	{
		m_displayTooltip = 0;
	}
	else if ((now - m_stillTime) < (UnsignedInt)delay)
	{
		m_displayTooltip = 0;
	}
	else
	{
		if (!m_displayTooltip)
		{
			m_tooltipHighlight = 0;
			m_tooltipHighlightStart = timeGetTime();
			m_displayTooltip = 1;
		}
	}

	if (TheScriptEngine->m_fade != 0)
		goto clearTooltip;

	if (!TheWritableGlobalData->m_showTooltips || !m_displayTooltip ||
		TheDisplay == 0 || m_buttonActivity != 0 || m_cursorText.isEmpty())
		goto clearTooltip;

	if (m_tooltipState.differs(m_cursorText))
	{
		m_tooltipState = m_cursorText;

		{
			AsciiString fontName;
			BfmeFontAttributes fontAttributes;
			int fontSize;

			if (g_bfmeGlobalWR != 0 && !g_bfmeGlobalWR->m_fontName.isEmpty())
			{
				fontName.set(g_bfmeGlobalWR->m_fontName);
				fontSize = g_bfmeGlobalWR->m_fontSize;
				fontAttributes.bold = g_bfmeGlobalWR->m_fontBold;
			}
			else
			{
				fontName.set(m_tooltipFontName);
				fontSize = m_tooltipFontSize;
				fontAttributes.bold = m_tooltipFontIsBold;
			}

			UnsignedInt color =
				(static_cast<UnsignedInt>(m_tooltipColorAlpha) << 24) |
				(static_cast<UnsignedInt>(m_tooltipColorRed) << 16) |
				(static_cast<UnsignedInt>(m_tooltipColorGreen) << 8) |
				m_tooltipColorBlue;

			BfmeTooltipDispatchThunk tooltipDispatch;
			tooltipDispatch.function = j_00033280;
			tooltipDispatch.typed(&m_tooltipState, &fontName, fontSize,
				fontAttributes.bits, color);

			BfmeMousePositionDispatchThunk positionDispatch;
			positionDispatch.function = j_000339c9;
			positionDispatch.typed((float)m_currentX, (float)m_currentY);
		}

	}

	m_tooltipTimer = 4;
	return;

clearTooltip:
	if (m_tooltipState.m_data && m_tooltipState.m_data->length != 0)
	{
		int timer = m_tooltipTimer - 1;
		m_tooltipTimer = timer;
		if (timer <= 0)
		{
			j_0002497e();
			m_tooltipState.releaseBuffer();
		}
	}
}
