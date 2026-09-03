// cl: /DNDEBUG /MD /EHsc
// readable body of ?getUserMapDir@MapCache@@QBE?AVAsciiString@@XZ: Code/GameEngine/Source/GameClient/MapUtil.cpp
//
// Retail 0x00451460, 318 bytes. BFME adds a local-user-maps probe: if ready,
// format("%s", "UserData\\Maps"); else set from getPath_UserData (strlen) and
// concat getMapDir (WORD length at header +4).

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapCache
{
public:
	AsciiString getUserMapDir() const;
	AsciiString getMapDir() const;
};

// ?getUserMapDir@MapCache@@QBE?AVAsciiString@@XZ
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
