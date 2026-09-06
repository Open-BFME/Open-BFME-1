// ?d_004515f0@@YAXXZ
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /O2
// BFME's GameInfo overload of WouldMapTransfer, retail 0x004515F0.

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
		const T *text = other.m_data != 0 ? &other.m_data->m_text[0] : (const T *)0x0107388b;
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
};

extern MapCache *TheMapCache;

class MapCacheThunk
{
public:
	AsciiString getUserMapDirThunk() const;
};

class GameInfo
{
	public:
	char m_prefix[0x3c];
	AsciiString m_mapName;
	Int m_mapCRC;
	Int m_mapSize;
	Int m_mapMask;

};

class GameInfoThunk
{
public:
	AsciiString getMapThunk() const;
};

// ?WouldMapTransfer@@YA_NPAVGameInfo@@@Z
Bool WouldMapTransfer(GameInfo *game)
{
	if ((game->m_mapMask & 0x200) != 0)
		return false;

	MapCache *mapCache = TheMapCache;
	AsciiString userMapDir = reinterpret_cast<const MapCacheThunk *>(mapCache)->getUserMapDirThunk();
	AsciiString gameMap = reinterpret_cast<const GameInfoThunk *>(game)->getMapThunk();
	return gameMap.startsWithNoCase(userMapDir);
}
