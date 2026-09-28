// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2

typedef unsigned short WideChar;
typedef unsigned int UnsignedInt;
typedef int Int;

class UnicodeString;
class Rva00434810SubtitleEntry;

template <typename T>
class StringBase
{
	friend class UnicodeString;
	friend class Rva00434810SubtitleEntry;

	private:
	StringBase(const T *text);

	public:
	~StringBase() {}

	protected:
	struct Header
	{
		Int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString(const WideChar *text) : StringBase<WideChar>(text) {}
	UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
	~UnicodeString() {}

	const WideChar *str() const
	{
		return m_data ? m_data->data : reinterpret_cast<const WideChar *>(0x0107388C);
	}
};

class GameFont;

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
	bool m_displayed;
};

class DisplayString
{
public:
	virtual ~DisplayString();
	virtual void setText(UnicodeString text);
	virtual UnicodeString getText();
	virtual Int getTextLength();
	virtual void notifyTextChanged();
	virtual void reset();
	virtual void setFont(GameFont *font);
};

class Rva0048EC80Manager
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual void f7();
	virtual void f8();
	virtual DisplayString *newDisplayString();
};

extern Rva0048EC80Manager *Rva0048EC80TheManager;

extern "C" __declspec(dllimport) WideChar *__cdecl wcscpy(
	WideChar *destination, const WideChar *source);
extern "C" __declspec(dllimport) WideChar *__cdecl wcstok(
	WideChar *string, const WideChar *control);

class Rva00434810SubtitleEntry : public SubtitleEntry
{
public:
	Rva00434810SubtitleEntry(GameFont *font, const UnicodeString &text,
		UnsignedInt color, Int style, Int alignment, Int line,
		Int startFrame, Int endFrame);

private:
	DisplayString *m_displayStrings[3];
	Int m_displayStringCount;
	Int m_displayStringCapacity;
};

Rva00434810SubtitleEntry::Rva00434810SubtitleEntry(GameFont *font,
	const UnicodeString &text, UnsignedInt color, Int style, Int alignment,
	Int line, Int startFrame, Int endFrame) :
	SubtitleEntry(text, color & 0x00FFFFFF, style, alignment, line, startFrame,
		endFrame),
	m_displayStrings(),
	m_displayStringCount(0),
	m_displayStringCapacity(0)
{
	m_displayStrings[0] = 0;
	m_displayStrings[1] = 0;
	m_displayStrings[2] = 0;
	WideChar buffer[0x400];
	wcscpy(buffer, text.str());
	WideChar *token = wcstok(buffer,
		reinterpret_cast<const WideChar *>(0x01084C10));
	while (token)
	{
		m_displayStrings[m_displayStringCount] =
			Rva0048EC80TheManager->newDisplayString();
		m_displayStrings[m_displayStringCount]->setFont(font);
		m_displayStrings[m_displayStringCount]->setText(UnicodeString(token));
		token = wcstok(0, reinterpret_cast<const WideChar *>(0x01084C10));
		++m_displayStringCount;
	}
}
