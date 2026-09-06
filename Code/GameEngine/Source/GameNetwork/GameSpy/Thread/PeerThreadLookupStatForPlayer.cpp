// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?lookupStatForPlayer@PeerThreadClass@@: Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp
//
// Retail 0x00647DD0 (351 B): PeerThreadClass::lookupStatForPlayer, the ZH
// PeerThread.cpp:371 body line for line (pinned by that name in symbols.csv).
// The tracked PeerThread.cpp compiles it to 231 B because PreRTS.h builds
// STLport on plain operator new/delete (_STLP_USE_NEWALLOC); the retail body
// destroys the packed key with the inline __node_alloc shape (the <= 0x80
// branch deallocates through _M_deallocate, larger through operator delete),
// so this standalone TU keeps STLport's default node allocator. Only the two
// stat maps (group room at +0x94, staging room at +0xA0, the reverse of the ZH
// declaration order) of the thread object are laid out; everything
// before them is opaque padding.

#include <string>
#include <map>

enum RoomType
{
	NoRoom = 0,
	GroupRoom = 1,
	StagingRoom = 2
};

typedef std::map<std::string, int> PlayerStatMap;

class PeerThreadClass
{
public:
	int lookupStatForPlayer(RoomType roomType, const char *nick, const char *key);

private:
	std::string packStatKey(const char *nick, const char *key);

	char m_pad[0x94];
	PlayerStatMap m_groupRoomStats;		// +0x94
	PlayerStatMap m_stagingRoomStats;	// +0xA0
};

int PeerThreadClass::lookupStatForPlayer(RoomType roomType, const char *nick, const char *key)
{
	std::string fullKey = packStatKey(nick, key);
	PlayerStatMap::const_iterator it;
	switch (roomType)
	{
		case GroupRoom:
			it = m_groupRoomStats.find(fullKey);
			if (it != m_groupRoomStats.end())
				return it->second;
			break;
		case StagingRoom:
			it = m_stagingRoomStats.find(fullKey);
			if (it != m_stagingRoomStats.end())
				return it->second;
			break;
	}
	return 0;
}
