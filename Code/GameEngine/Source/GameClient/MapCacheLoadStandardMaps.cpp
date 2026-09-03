// cl: /DNDEBUG /MD /EHsc /Oy-
// readable body of ?loadStandardMaps@MapCache@@AAEXXZ: Code/GameEngine/Source/GameClient/MapUtil.cpp
//
// Retail 0x004507A0, 234 bytes. Ghidra split the body at the `jmp` over a
// 6-byte catch into the 46B epilogue; /Oy- keeps the EBP frame and the try
// around INI::load emits that catch. INI is the 0x848-byte BFME stack object
// (ControlBarResizer precedent). INI::load at 0x00853CB0 is the four-arg
// overload (file, loadType, reload, xfer); the xfer slot is the retail
// code-mid immediate 0x004312EB.

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
	const char *str() const { return m_data ? m_data->m_text : ""; }
};

class Xfer;

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
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
	AsciiString getMapDir() const;

private:
	void loadStandardMaps();
};

// ?loadStandardMaps@MapCache@@AAEXXZ
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
