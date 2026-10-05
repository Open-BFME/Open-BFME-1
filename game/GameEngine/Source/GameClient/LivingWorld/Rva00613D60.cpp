// ?rva00613d60@Rva00613D60Owner@@QAEXPAURva00613D60Region@@@Z
// Address-derived reconstruction of the retail body at RVA 0x00613D60.
// Rva003C2530Owner::prepare at 0x003BCC70 reaches it through ILT 0x000309EA
// and passes one pointer argument.
// Retail returns with ret 4 at +0x201 and begins INT3 padding at +0x204,
// for 516 bytes.
// The body builds a map path from the argument and queues message 0x1E.
// No evidence names the owner or method, so this source keeps address-derived names.
//
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Rva0036CA00Str;

class Rva00386090
{
public:
	void set(Rva0036CA00Str *value);
};

class Rva003860F0
{
public:
	void set(Rva0036CA00Str *first, Rva0036CA00Str *second,
		Rva0036CA00Str *third);
};

class Rva00618E60FieldAddress { public: const void *get() const; };
class Rva00618E70FieldAddress { public: const void *get() const; };
class Rva00618E80FieldAddress { public: const void *get() const; };
class Rva00618E90FieldAddress { public: const void *get() const; };

struct RGBColor;

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

// upstream layout: reference/shims/stringinline/StringInline.h
template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void __cdecl format(AsciiString text, ...);

	const char *str(void) const
	{
		return m_data ? m_data->m_text : "";
	}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}

	static UnicodeString TheEmptyString;
};

enum RecorderModeType
{
	RECORDERMODETYPE_RECORD = 0
};

class RecorderClass
{
public:
	RecorderModeType getMode(void);								///< ILT 0x00043EEB
	void stopRecording(void);										///< ILT 0x0001E745
};

extern RecorderClass *TheRecorder;

class BfmeHost961
{
public:
	void bfmeFallback961(int a, int b);							///< ILT 0x0001C46D
};

class BfmeGameLogicPause
{
public:
	void setGamePaused(Bool paused, int mode, Bool force);		///< ILT 0x00006F50
};

struct Rva00367E30Logic
{
	void rva00010fc8(int value);								///< ILT 0x00010FC8
	void rva00001569(int value);								///< ILT 0x00001569
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeZ1100
{
public:
	void bfmeEnd1100(int value);								///< ILT 0x0003D578
};

class Mouse
{
public:
	void setCursorTooltip(UnicodeString text, int width,
		const RGBColor *color, float delay);					///< ILT 0x000346E9
};

extern Mouse *TheMouse;

class BfmeHostAAY
{
public:
	void bfmeStep6AAY(void);									///< ILT 0x00010438
};

struct Rva006C9270GlobalData
{
	char m_pad000[0xB84];
	AsciiString m_mapPath;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

void __cdecl InitGameLogicRandom(unsigned int now);										///< ILT 0x0002E8BB

extern int (__cdecl *g_bfmeNowVNH)(void);

class GameMessage
{
public:
	void appendIntegerArgument(int value);						///< ILT 0x00001370
};

class MessageStream
{
public:
	virtual void m00();
	virtual void m04();
	virtual void m08();
	virtual void m0C();
	virtual void m10();
	virtual void m14();
	virtual void m18();
	virtual void m1C();
	virtual void m20();
	virtual void m24();
	virtual void m28();
	virtual void m2C();
	virtual void m30();
	virtual GameMessage *appendMessage(int type);
};

extern MessageStream *TheMessageStream;

class AptPalantir
{
public:
	void hide(Bool hidden);										///< ILT 0x0001420E
};

class Glo012F4B98Type;

extern Glo012F4B98Type *Glo012F4B98;

class InGameUI
{
public:
	virtual void u00();
	virtual void u04();
	virtual void u08();
	virtual void u0C();
	virtual void u10();
};

extern InGameUI *TheInGameUI;

class Glo012F7090Type
{
public:
								///< ILT 0x0001B5DB
};

extern Glo012F7090Type *Glo012F7090;

class GameInfo
{
public:
	void setMap(AsciiString path);
};

class Glo012F1028Type
{
public:
	char m_pad00[0x90];
	int m_at90;
};

extern Glo012F1028Type *Glo012F1028;

struct Rva00613D60Region
{
										///< ILT 0x00040D31
										///< ILT 0x000149B6
									///< ILT 0x0003F31E
									///< ILT 0x00024505

	char m_pad00[8];
	AsciiString m_name;
};

class Rva00613D60Owner
{
public:
	void rva00613d60(Rva00613D60Region *region);
};

void Rva00613D60Owner::rva00613d60(Rva00613D60Region *region)
{
	if (TheRecorder->getMode() == RECORDERMODETYPE_RECORD)
		TheRecorder->stopRecording();

	((BfmeHost961 *)TheBfmeGameLogic)->bfmeFallback961(0, 0);
	((BfmeZ1100 *)TheMouse)->bfmeEnd1100(0);
	((BfmeHostAAY *)this)->bfmeStep6AAY();

	const char *name = region->m_name.str();
	AsciiString path;
	path.format(AsciiString("maps\\%s\\%s.map"), name, name);
	TheWritableGlobalData->m_mapPath.format(path);

	if (Glo012F7090 != 0)
		InitGameLogicRandom(g_bfmeNowVNH());
	else
		InitGameLogicRandom(0);

	GameMessage *message = TheMessageStream->appendMessage(0x1E);

	((BfmeGameLogicPause *)TheBfmeGameLogic)->setGamePaused(true, 1, false);
	((BfmeGameLogicPause *)TheBfmeGameLogic)->setGamePaused(false, 1, false);

	((Rva00386090 *)TheBfmeGameLogic)->set((Rva0036CA00Str *)((Rva00618E60FieldAddress *)region)->get());
	((Rva003860F0 *)TheBfmeGameLogic)->set(
		(Rva0036CA00Str *)((Rva00618E70FieldAddress *)region)->get(),
		(Rva0036CA00Str *)((Rva00618E80FieldAddress *)region)->get(),
		(Rva0036CA00Str *)((Rva00618E90FieldAddress *)region)->get());

	((AptPalantir *)Glo012F4B98)->hide(true);
	TheInGameUI->u10();
	TheMouse->setCursorTooltip(UnicodeString::TheEmptyString, -1, 0, 1.0f);

	int extra;
	if (Glo012F7090 != 0)
	{
		((GameInfo *)Glo012F7090)->setMap(path);
		message->appendIntegerArgument(6);
		extra = Glo012F1028->m_at90;
		message->appendIntegerArgument(extra);
		message->appendIntegerArgument(0);
	}
	else
	{
		message->appendIntegerArgument(0);
		extra = Glo012F1028->m_at90;
		message->appendIntegerArgument(extra);
		message->appendIntegerArgument(0);
	}
}
