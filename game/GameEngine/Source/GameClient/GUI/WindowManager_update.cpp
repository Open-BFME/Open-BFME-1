// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// WindowManager::update, retail 0x0046E850 (813 bytes).
//
// Identity: WindowManager's vtable 0x010F72A8, installed by the matched
// constructor 0x0046E5E0 and destructor 0x0046D8E0, holds this body in slot 5
// (ILT 0x0000622B), BFME SubsystemInterface's update slot (slot 2 is the
// matched SubsystemInterface::loadIniFilesFromLegend).  The member offsets
// follow the matched constructor: callback map at +0x80 (same hash_map type as
// the +0x08 map WindowManager::invokeCallback searches), twelve 0x14-byte APT
// window records at +0xA8, timestamp at +0x1A8 and flag bytes +0x1AC..+0x1C4.

#include <exception>
#include <hash_map>

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern "C" __declspec(dllimport) int __cdecl strncmp(const char *, const char *, unsigned int);
extern "C" __declspec(dllimport) int __cdecl isdigit(int);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *);
extern "C" unsigned int __cdecl strlen(const char *);
#pragma intrinsic(strlen)

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	StringBase(const StringBase<T> &other, int start, int length);
	StringBase(const T *text);
	~StringBase() { releaseBuffer(); }

	void releaseBuffer();

public:
	void set(const StringBase<T> &other);
	void set(const T *text, int length);
	void concat(const T *text, int length);

protected:
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T text[1];
	};

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString(const AsciiString &other, int start, int length)
		: StringBase<char>(other, start, length) {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}

	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}
	AsciiString &operator=(const char *text)
	{
		StringBase<char>::set(text, strlen(text));
		return *this;
	}

	Bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	const char *str() const
	{
		static const char TheNullChr = 0;
		return m_data ? m_data->text : &TheNullChr;
	}
	int getLength() const { return m_data ? m_data->length : 0; }
	char getCharAt(int index) const { return m_data ? m_data->text[index] : 0; }

	void concat(const char *text)
	{
		StringBase<char>::concat(text, strlen(text));
	}
};

AsciiString operator+(AsciiString left, const AsciiString &right);

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
	~UnicodeString() {}

	int getLength() const { return m_data ? m_data->length : 0; }
};

// ---------------------------------------------------------------------------
// Callback map: the same instantiation WindowManager::invokeCallback searches
// (its _M_find is pinned at ILT 0x000056A5 -> matched 0x0046A130).

class FunctorNotSet : public std::exception
{
public:
	FunctorNotSet() : std::exception() {}
};

class Rva0046C000Callback
{
public:
	virtual ~Rva0046C000Callback();
	virtual void invoke(void *argument);
};

struct Rva0046C000Mapped
{
	__forceinline void operator()(void *argument) const
	{
		if (m_callback == 0)
			throw FunctorNotSet();
		m_callback->invoke(argument);
	}

	Rva0046C000Callback *m_callback;
};

namespace rts
{
template <class T> struct hash;
template <class T> struct equal_to;

template <> struct hash<AsciiString>
{
	unsigned int operator()(AsciiString value) const;
};

template <> struct equal_to<AsciiString>
{
	int operator()(const AsciiString &left, const AsciiString &right) const;
};
}

typedef std::hash_map<AsciiString, Rva0046C000Mapped,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > Rva0046C000Map;
typedef _STL::pair<const AsciiString, Rva0046C000Mapped> Rva0046C000Pair;
typedef _STL::_Hashtable_node<Rva0046C000Pair> Rva0046C000Node;

// ---------------------------------------------------------------------------
// Other subsystems.

class Shell
{
public:
	void pop();
};

extern Shell *TheShell;

struct RGBColor;

class Mouse
{
public:
	void setCursorTooltip(UnicodeString tooltip, Int delay,
		const RGBColor *color, float width);
};

extern Mouse *TheMouse;

// Matched 0x005A44F0 (DispFieldAddressGetters.cpp, reached through ILT
// 0x00017B52): returns the address of the member at this+0x1100.  Called here
// on TheMouse; the body tests that member's length halfword, so it is a string.
class Rva005A44F0FieldAddress
{
public:
	char *get();
};

class GameWindow;

class GameWindowManager
{
public:
	virtual void slot00(void); virtual void slot01(void); virtual void slot02(void);
	virtual void slot03(void); virtual void slot04(void); virtual void slot05(void);
	virtual void slot06(void); virtual void slot07(void); virtual void slot08(void);
	virtual void slot09(void); virtual void slot10(void); virtual void slot11(void);
	virtual void slot12(void); virtual void slot13(void); virtual void slot14(void);
	virtual void slot15(void); virtual void slot16(void); virtual void slot17(void);
	virtual void slot18(void); virtual void slot19(void); virtual void slot20(void);
	virtual void slot21(void); virtual void slot22(void); virtual void slot23(void);
	virtual void slot24(void); virtual void slot25(void); virtual void slot26(void);
	virtual void slot27(void); virtual void slot28(void); virtual void slot29(void);
	virtual void slot30(void); virtual void slot31(void); virtual void slot32(void);
	virtual void slot33(void); virtual void slot34(void); virtual void slot35(void);
	virtual void slot36(void); virtual void slot37(void); virtual void slot38(void);
	virtual void slot39(void); virtual void slot40(void); virtual void slot41(void);
	virtual void slot42(void); virtual void slot43(void); virtual void slot44(void);
	virtual void slot45(void); virtual void slot46(void); virtual void slot47(void);
	virtual GameWindow *bfmeGetWindow(void);	// slot 48, as Rva00465D50PointConvert.cpp
};

extern GameWindowManager *TheWindowManager;

// Retail materialises this test as a byte (`neg; sbb al,al; inc al; cmp al,bl`)
// before branching, the shape of an inlined Bool-returning helper; its
// original name is not recovered.
static inline Bool bfmeNoWindow()
{
	if (TheWindowManager)
		return TheWindowManager->bfmeGetWindow() == 0;
	return true;
}

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void reset() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

// Retail 0x00892210: tests a field of the singleton at 0x013377D8 and returns
// a byte (the caller tests al).  Defining spelling, matched in
// game/GameEngine/Source/Common/Bfme5TinySix3.cpp.
int __cdecl bfmeIsSet(void);
// Retail 0x008922A0: copies a path string into the caller's buffer.
void bfmeGo929E(void *buffer);

// Address-derived helpers: their bodies are still generated dumps, so each
// name is pinned in symbols.csv at the ILT/jump stub retail calls.  ABIs read
// from the bodies (ret forms and argument use) and from these call sites.
void __cdecl bfmeRva00462A20();					// ILT 0x0001F271
void __cdecl bfmeRva00894660(UnsignedInt elapsed);	// stub 0x00894780

// ---------------------------------------------------------------------------

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual Bool loadIniFilesFromLegend();
	virtual void postProcessLoad();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw();

private:
	UnsignedInt m_name;
};

struct WindowManagerAptRecord
{
	AsciiString m_at00;
	UnsignedInt m_at04;
	UnsignedInt m_at08;
	UnsignedInt m_at0C;
	UnsignedInt m_at10;
};

class WindowManager : public SubsystemInterface
{
public:
	virtual void update();

	void bfmeRva00467F20(Int index);	// ILT 0x0001DE9E
	void bfmeRva0046E170();			// ILT 0x0000364D

private:
	unsigned char m_unreconstructed08[0x80 - 0x08];
	Rva0046C000Map m_at80;
	unsigned char m_unreconstructed94[0xA8 - 0x94];
	WindowManagerAptRecord m_atA8[12];
	UnsignedInt m_at198;
	UnsignedInt m_at19C;
	UnsignedInt m_at1A0;
	Bool m_at1A4;
	UnsignedInt m_at1A8;
	Bool m_at1AC;
	Bool m_at1AD;
	Bool m_at1AE;
	UnsignedInt m_at1B0;
	UnsignedInt m_at1B4;
	UnsignedInt m_at1B8;
	UnsignedInt m_at1BC;
	UnsignedInt m_at1C0;
	Bool m_at1C4;
};

void WindowManager::update()
{
	if (m_at1AC)
	{
		TheShell->pop();
		m_at1AC = false;
	}

	if (m_at1AD)
	{
		m_at1AD = false;
		for (Int i = 0; i < 12; ++i)
		{
			if (m_atA8[i].m_at10 & 1)
				bfmeRva00467F20(i);
		}
		m_at1A4 = true;
	}

	bfmeRva00462A20();
	bfmeRva0046E170();

	UnsignedInt now = timeGetTime();
	UnsignedInt elapsed = now - m_at1A8;
	if (elapsed > 60)
		elapsed = 60;
	if (m_at1C4 && elapsed < 34)
		elapsed = 34;
	m_at1AE = true;
	bfmeRva00894660(elapsed);
	m_at1AE = false;
	m_at1A8 = now;

	if (!(unsigned char)bfmeIsSet())
		return;

	const UnicodeString *mouseString = reinterpret_cast<const UnicodeString *>(
		reinterpret_cast<Rva005A44F0FieldAddress *>(TheMouse)->get());
	if (mouseString->getLength() != 0)
		return;

	if (!bfmeNoWindow())
		return;

	AsciiString name;
	char path[0x200];
	bfmeGo929E(path);

	if (strncmp(path, "_level", 6) == 0 && isdigit(path[6]))
	{
		const char *cursor = path + 6;
		Int level = atoi(cursor);
		if (level >= 0 && (UnsignedInt)level < 12)
		{
			name = m_atA8[level].m_at00;
			for (Int i = name.getLength(); i > 0; --i)
			{
				if (name.getCharAt(i - 1) == '.')
				{
					name = AsciiString(name, 0, i - 1);
					break;
				}
			}
			do
				++cursor;
			while (*cursor != 0 && *cursor != '/');
			name.concat(cursor);
		}
	}
	else
	{
		name = path;
	}

	if (name.isEmpty())
		return;

	Rva0046C000Map::const_iterator it = m_at80.find(name);
	if (it != m_at80.end())
	{
		(*it).second((void *)name.str());
	}
	else if (name.getCharAt(name.getLength() - 1) != '/')
	{
		TheMouse->setCursorTooltip(
			TheGameText->fetch(AsciiString("TOOLTIP:") + name), -1, 0, 1.0f);
	}
}
