// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/vendor/stlport /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib

// The alternate BFME LAN startup path at retail RVA 0x004D18B0.
// The shutdown caller and the pinned bfmeAltAAV symbol establish the identity.

#define __PLACEMENT_VEC_NEW_INLINE
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef unsigned short WideChar;

template <typename T> struct BfmeStringData
{
	Int m_refCount;
	UnsignedShort m_length;
	UnsignedShort m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase(void) : m_data(0) {}
	StringBase(const StringBase<T> &other);
	StringBase(const T *text);

public:
	~StringBase(void) { releaseBuffer(); }
	void removeLastChar(void);
	void set(const StringBase<T> &other);
	UnsignedShort getLength(void) const
	{
		return m_data ? m_data->m_length : 0;
	}

	private:
	void releaseBuffer(void);
	BfmeStringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(void) : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other)
		: StringBase<char>(*(const StringBase<char> *)&other) {}
	~AsciiString(void) {}

	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(*(const StringBase<char> *)&other);
		return *this;
	}
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString(void) : StringBase<WideChar>() {}
	UnicodeString(const WideChar *text) : StringBase<WideChar>(text) {}
	UnicodeString(const UnicodeString &other)
		: StringBase<WideChar>(*(const StringBase<WideChar> *)&other) {}
	~UnicodeString(void) {}

	UnsignedShort getLength(void) const
	{
		return StringBase<WideChar>::getLength();
	}

	void removeLastChar(void)
	{
		StringBase<WideChar>::removeLastChar();
	}
};

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const;
};
}

typedef _STL::map<AsciiString, AsciiString, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, AsciiString> > > PreferenceMap;

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences(void);
	virtual Bool load(AsciiString filename);
	virtual Bool write(void);

private:
	AsciiString m_filename;
};

class LANPreferences : public UserPreferences
{
public:
	LANPreferences(void);
	virtual ~LANPreferences(void);
	UnicodeString getUserName(void);
};

#pragma comment(linker, "/alternatename:??0LANPreferences@@QAE@XZ=?j_00025b80@@YAXXZ")
#pragma comment(linker, "/alternatename:??1LANPreferences@@UAE@XZ=?j_00040db3@@YAXXZ")
#pragma comment(linker, "/alternatename:?getUserName@LANPreferences@@QAE?AVUnicodeString@@XZ=?j_000351c5@@YAXXZ")

extern AsciiString AsciiStringToQuotedPrintable(AsciiString original);

struct Rva006C9270GlobalData
{
	unsigned char m_head[0xB84];
	AsciiString m_pendingFile;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;
extern void *g_bfmePtrAAV;

#define LANAPI_SLOT(n) virtual void bfmeSlot##n(void);

class LANAPI
{
public:
	LANAPI(void);
	~LANAPI(void);

	LANAPI_SLOT(00)
	virtual void init(void);
	LANAPI_SLOT(02)
	LANAPI_SLOT(03)
	virtual void reset(void);
	LANAPI_SLOT(05)
	LANAPI_SLOT(06)
	LANAPI_SLOT(07)
	LANAPI_SLOT(08)
	LANAPI_SLOT(09)
	virtual void RequestLocations(void);
	LANAPI_SLOT(11)
	LANAPI_SLOT(12)
	LANAPI_SLOT(13)
	LANAPI_SLOT(14)
	LANAPI_SLOT(15)
	LANAPI_SLOT(16)
	LANAPI_SLOT(17)
	LANAPI_SLOT(18)
	LANAPI_SLOT(19)
	LANAPI_SLOT(20)
	LANAPI_SLOT(21)
	virtual void RequestGameCreate(UnicodeString gameName, Bool isDirectConnect);
	LANAPI_SLOT(23)
	virtual void RequestSetName(UnicodeString newName);
	LANAPI_SLOT(25)
	LANAPI_SLOT(26)
	LANAPI_SLOT(27)
	LANAPI_SLOT(28)
	LANAPI_SLOT(29)
	LANAPI_SLOT(30)
	LANAPI_SLOT(31)
	LANAPI_SLOT(32)
	LANAPI_SLOT(33)
	LANAPI_SLOT(34)
	LANAPI_SLOT(35)
	LANAPI_SLOT(36)
	LANAPI_SLOT(37)
	LANAPI_SLOT(38)
	LANAPI_SLOT(39)
	LANAPI_SLOT(40)
	LANAPI_SLOT(41)
	LANAPI_SLOT(42)
	virtual void SetLocalIP(AsciiString localIP);
	virtual Bool SetLocalIP(UnsignedInt localIP);

	unsigned char m_unreconstructed[0x64];
};

#undef LANAPI_SLOT

#pragma comment(linker, "/alternatename:??0LANAPI@@QAE@XZ=?j_0003ecc5@@YAXXZ")
#pragma comment(linker, "/alternatename:??1LANAPI@@UAE@XZ=?j_00030224@@YAXXZ")

extern LANAPI *TheLAN;

class GameEngine
{
public:
	void Rva0006C180(void *value);
};

extern void j_0002e8fc(void);
#pragma comment(linker, "/alternatename:?Rva0006C180@GameEngine@@QAEXPAX@Z=?j_0002e8fc@@YAXXZ")
#pragma comment(linker, "/include:?j_0002e8fc@@YAXXZ")

extern GameEngine *TheGameEngine;

void bfmeAltAAV(void)
{
	if (TheLAN == 0)
		TheLAN = new LANAPI;
	else
		TheLAN->reset();

	TheLAN->init();
	TheLAN->SetLocalIP(AsciiString("127.0.0.1"));

	LANPreferences pref;
	pref["Map"] = AsciiStringToQuotedPrintable(TheWritableGlobalData->m_pendingFile);
	pref.write();

	UnicodeString userName = pref.getUserName();
	while (userName.getLength() > 12)
		userName.removeLastChar();

	TheLAN->RequestSetName(userName);
	TheLAN->RequestLocations();
	TheLAN->RequestGameCreate(UnicodeString((const WideChar *)0x01088AF4), false);
	TheGameEngine->Rva0006C180(g_bfmePtrAAV);
}
