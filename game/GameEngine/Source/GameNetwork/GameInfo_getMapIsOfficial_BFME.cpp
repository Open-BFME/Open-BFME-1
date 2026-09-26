// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// BFME's GameInfo map-name member is four bytes later than the Zero Hour
// layout used by the public header.  This TU keeps the retail metadata copy
// shape local to the body while reusing the already pinned retail string and
// MapCache callees.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &src);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString
{
public:
	// Retail inlines this forwarder, so the call site encodes
	// StringBase<char>'s copy ctor at 0x00887B60 directly.
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString();
	void toLower();

private:
	void *m_data;
};

class BfmeMemberB_000C1490
{
public:
	BfmeMemberB_000C1490(const BfmeMemberB_000C1490 &other);

	unsigned char m_prefix[0x20];
	int m_isOfficial;
	unsigned char m_suffix[0xd8];
};

class Gen_uw_0002756b
{
public:
	~Gen_uw_0002756b();
};

struct MapCacheNode
{
	unsigned char m_treeLinks[0x14];
	BfmeMemberB_000C1490 second;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapCache
{
public:
	MapCacheNode *bfmeFind(const AsciiString &mapName);

	MapCacheNode *m_head;
};

extern MapCache *TheMapCache;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
private:
	unsigned char m_prefix[0x3c];
	AsciiString m_mapName;

public:
	int _bfme_getMapIsOfficial() const;
};

int GameInfo::_bfme_getMapIsOfficial() const
{
	if (!TheMapCache)
		return -1;

	AsciiString lowerMap = m_mapName;
	lowerMap.toLower();
	MapCache *cache = TheMapCache;
	MapCacheNode *it = cache->bfmeFind(lowerMap);
	if (it != cache->m_head)
	{
		BfmeMemberB_000C1490 data = it->second;
		int result = data.m_isOfficial;
		((Gen_uw_0002756b *)&data)->~Gen_uw_0002756b();
		return result;
	}

	return -1;
}
