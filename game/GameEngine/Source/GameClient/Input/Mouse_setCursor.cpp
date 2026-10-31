// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?setCursor@Mouse@@: game/GameEngine/Source/GameClient/Input/Mouse.cpp
// Identity: ILT 0x0000E520 -> 0x005A5A30 (symbols.csv pin). BFME layout:
// cursor infos at +0x08 (0x54-byte stride), current cursor +0x4DA8, cursor
// text display string +0x4DAC.
// class-gate: allow AsciiString retail inlines isEmpty (cmp word [m_data+4]); ascii_string.h/string_base.h declare it out of line, which emits movzx/test (probe 0.962)

// isEmpty is a file-static helper: an inline AsciiString::isEmpty member is
// emitted as a non-retail COMDAT (link queue #3) even though every call inlines.
class AsciiString;
static __forceinline bool asciiIsEmpty(const AsciiString &s);

template <typename T>
class StringBase
{
	friend bool asciiIsEmpty(const AsciiString &s);
	friend class AsciiString;
	friend class UnicodeString;

	StringBase() : m_data(0) {}
	StringBase(const T *str);
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();

	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	friend bool asciiIsEmpty(const AsciiString &s);
	const char *str() const { return m_data ? m_data->data : ""; }
};

static __forceinline bool asciiIsEmpty(const AsciiString &s) { return s.m_data == 0 || s.m_data->length == 0; }

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString(const unsigned short *str) : StringBase<unsigned short>(str) {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

struct RGBAColorInt
{
	unsigned int red, green, blue, alpha;
};

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

struct CursorInfo
{
	int pad0;
	AsciiString cursorText;
	RGBAColorInt cursorTextColor;
	RGBAColorInt cursorTextDropColor;
	char pad1[0x54 - 0x28];
};

class DisplayString;

class Mouse
{
public:
	enum MouseCursor { };

	virtual void setCursor(MouseCursor cursor);
	void setMouseText(UnicodeString text, const RGBAColorInt *color,
	                  const RGBAColorInt *dropColor);

private:
	int m_pad4;
	CursorInfo m_cursorInfo[1];
	char m_pad0[0x4DA8 - 0x08 - sizeof(CursorInfo)];
	MouseCursor m_currentCursor;
	DisplayString *m_cursorTextDisplayString;
};

void Mouse::setCursor(MouseCursor cursor)
{
	if (m_currentCursor == cursor)
		return;
	if (m_cursorTextDisplayString == 0)
		return;

	CursorInfo *cursorInfo = &m_cursorInfo[cursor];
	if (asciiIsEmpty(cursorInfo->cursorText) == false)
		setMouseText(TheGameText->fetch(cursorInfo->cursorText.str()),
		             &cursorInfo->cursorTextColor, &cursorInfo->cursorTextDropColor);
	else
		setMouseText(UnicodeString((const unsigned short *)L""), 0, 0);
}
