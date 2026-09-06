// cl: /DNDEBUG /MD /EHsc
// readable body of ?getUserMapDir@MapCache@@QBE?AVAsciiString@@XZ: Code/GameEngine/Source/GameClient/MapUtil.cpp
// readable body of ?loadStandardMaps@MapCache@@AAEXXZ: Code/GameEngine/Source/GameClient/MapUtil.cpp
//
// The two map-cache bodies that build a path and then read from it:
// getUserMapDir at 0x00451460 answers where the player's own maps live, and
// loadStandardMaps at 0x004507A0 parses MapCache.ini out of the shipped map
// directory. They shared a 34-line copy of the StringBase / AsciiString model
// apiece; 185 lines across two files become 152 in one.
//
// That model is the by-value string shape: a single Data pointer, with the
// copy constructor and destructor inline forwarders onto StringBase<char> so
// that a string built into an argument slot emits the in-place construction
// retail emits. It is the reason these two cannot join the getMapDir /
// getMapExtension / findMap merge next door, whose bodies call
// ??0AsciiString@@QAE@PBD@Z out of line instead.
//
// loadStandardMaps used to ask for /Oy- to keep the EBP frame its try/catch
// around INI::load needs. It does not need asking: the catch keeps the frame
// on its own, and getUserMapDir positively requires /Oy- to be absent -- under
// it the whole body moves to ebp-relative locals and stops matching. The
// merged TU carries loadStandardMaps' other flags and no /Oy-, and both bodies
// byte-verify.

#include <string.h>

typedef int Int;
typedef unsigned short UnsignedShort;

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	struct Data
	{
		Int m_refCount;
		UnsignedShort m_length;
		UnsignedShort m_capacity;
		T m_text[1];
	};
	Data *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void __cdecl format(AsciiString fmt, ...);
	void set(const char *text, Int len);
	void concat(const char *text, Int len);

	const char *str() const { return m_data ? m_data->m_text : ""; }
	Int getLength() const { return m_data ? m_data->m_length : 0; }

	void setFrom(const AsciiString &src)
	{
		const char *path = src.str();
		set(path, path ? (Int)strlen(path) : 0);
	}
	void concatFrom(const AsciiString &src)
	{
		concat(src.str(), src.getLength());
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	AsciiString getPath_UserData() const;
};

extern GlobalData *TheWritableGlobalData;

bool bfmeLocalUserMapsReady(void);

class Xfer;

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
// The 0x848-byte parser BFME builds on the stack (ControlBarResizer precedent).
class INI
{
public:
	INI();
	~INI();
	void load(AsciiString filename, int loadType, int reload, void *xfer);

private:
	char m_storage[0x848];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapCache
{
public:
	AsciiString getUserMapDir() const;
	AsciiString getMapDir() const;

private:
	void loadStandardMaps();
};

// ?getUserMapDir@MapCache@@QBE?AVAsciiString@@XZ
// Retail 0x00451460, 318 bytes. BFME's own local-user-maps probe comes first:
// when it answers yes the path is the fixed UserData\Maps, and only otherwise
// is it the user data path with the map directory appended.
AsciiString MapCache::getUserMapDir() const
{
	AsciiString tmp;
	if (bfmeLocalUserMapsReady())
	{
		tmp.format(AsciiString("%s"), "UserData\\Maps");
	}
	else
	{
		tmp.setFrom(TheWritableGlobalData->getPath_UserData());
		tmp.concatFrom(getMapDir());
	}
	return tmp;
}

// ?loadStandardMaps@MapCache@@AAEXXZ
// Retail 0x004507A0, 234 bytes. INI::load here is the four-argument overload
// at 0x00853CB0 (file, loadType, reload, xfer); the xfer slot is retail's own
// code-mid immediate 0x004312EB, and a parse failure is swallowed.
void MapCache::loadStandardMaps()
{
	INI ini;
	AsciiString fname;
	fname.format(AsciiString("%s\\%s"), getMapDir().str(), "MapCache.ini");
	try
	{
		ini.load(fname, INI_LOAD_OVERWRITE, 0, (void *)0x004312EB);
	}
	catch (...)
	{
	}
}
