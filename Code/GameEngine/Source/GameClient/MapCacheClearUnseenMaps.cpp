// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// MapCache::clearUnseenMaps, retail 0x00456920, 290 bytes.
//
// MapCache::loadUserMaps calls this standalone entry after rebuilding its
// per-directory seen set.  The by-value directory parameter, m_seen at +0x0c,
// and the map erase traversal reproduce the original MapUtil.cpp algorithm.
// The older claim at 0x004578EB is an interior continuation of loadUserMaps,
// not a function entry; it has no prologue and shares that caller's EBP frame.

#include <map>
#include <string.h>

typedef bool Bool;
typedef int Int;
typedef unsigned short UnsignedShort;

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() {}
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

public:
	void toLower();
	Bool startsWithNoCase(const T *text, Int length) const;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void toLower()
	{
		((StringBase<char> *)this)->toLower();
	}

	const char *str() const
	{
		return m_data ? &m_data->m_text[0] : (const char *)0x0107388b;
	}

	Bool startsWithNoCase(const char *text) const
	{
		return ((const StringBase<char> *)this)->startsWithNoCase(
			text, text ? strlen(text) : 0);
	}
};

inline Bool operator<(const AsciiString &left, const AsciiString &right)
{
	return strcmp(left.str(), right.str()) < 0;
}

class MapMetaData
{
	char m_opaque[4];
};

class MapCache : public std::map<AsciiString, MapMetaData>
{
private:
	Bool clearUnseenMaps(AsciiString dirName);
	std::map<AsciiString, Bool> m_seen;
};

// ?clearUnseenMaps@MapCache@@AAE_NVAsciiString@@@Z
Bool MapCache::clearUnseenMaps(AsciiString dirName)
{
	dirName.toLower();
	Bool erasedSomething = false;
	std::map<AsciiString, Bool>::iterator it = m_seen.begin();
	while (it != m_seen.end())
	{
		AsciiString mapName = it->first;
		if (!it->second && mapName.startsWithNoCase(dirName.str()))
		{
			erase(mapName);
			erasedSomething = true;
		}
		++it;
	}
	return erasedSomething;
}
