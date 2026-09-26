// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// WouldMapTransfer(GameInfo *), retail 0x004515F0, 188 bytes.
//
// The matched LANAPI::RequestHasMap and WOL game-setup callers pass their
// GameInfo object to the ILT at 0x000393FB, whose target is this body.  BFME's
// overload first rejects official maps through GameInfo::m_mapMask, then asks
// whether the game's map begins with MapCache::getUserMapDir().  Keeping the
// two returned AsciiString temporaries in the source expression preserves the
// retail compiler's construction order and register schedule.

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
	Bool startsWithNoCase(const T *text, Int length) const;

	Bool startsWithNoCase(const StringBase<T> &other) const
	{
		const Int length = other.m_data != 0 ? other.m_data->m_length : 0;
		const T *text = other.m_data != 0
			? &other.m_data->m_text[0]
			: (const T *)0x0107388b;
		return startsWithNoCase(text, length);
	}
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	Bool startsWithNoCase(const AsciiString &other) const
	{
		return ((const StringBase<char> *)this)->startsWithNoCase(
			*(const StringBase<char> *)&other);
	}
};

class MapCache
{
public:
	AsciiString getUserMapDir() const;
};

extern MapCache *TheMapCache;

class GameInfo
{
public:
	AsciiString getMap() const;

	char m_prefix[0x3c];
	AsciiString m_mapName;
	Int m_mapCRC;
	Int m_mapSize;
	Int m_mapMask;
};

// ?WouldMapTransfer@@YA_NPAVGameInfo@@@Z
Bool WouldMapTransfer(GameInfo *game)
{
	if ((game->m_mapMask & 0x200) != 0)
		return false;

	return game->getMap().startsWithNoCase(TheMapCache->getUserMapDir());
}
