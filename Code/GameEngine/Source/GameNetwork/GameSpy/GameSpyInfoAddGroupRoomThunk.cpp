// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// GameSpyInfo::addGroupRoom, retail RVA 0x00636650, full 1238-byte body.
// The PeerDefs.cpp algorithm gains BFME's translation fallback on both paths.
// The room is 32 bytes: its two strings are at +0/+4, followed by six integers.
// Existing exact room-copy (0x004F97B0), map operator[] (0x006357D0), and pair
// destruction (0x00631920) bodies independently establish that member geometry.
// TU-scoped interface prefixes below preserve only this body's used ABI slots.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define __PLACEMENT_VEC_NEW_INLINE
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>
#include <vector>
#include <string.h>
typedef bool Bool;
typedef int Int;
#define TRUE true
#define FALSE false

template<class T> struct StringData { unsigned short refs, capacity, length, pad; T text[1]; };
template<class T> class StringBase {
    friend class AsciiString;
    friend class UnicodeString;
private:
    StringData<T> *data;
    StringBase():data(0) {}
    StringBase(const T*);
    StringBase(const StringBase&);
    ~StringBase();
    void set(const StringBase&);
};
class AsciiString : private StringBase<char> {
public:
    AsciiString() {}
    AsciiString(const char *p):StringBase<char>(p) {}
    AsciiString(const AsciiString &p):StringBase<char>(p) {}
    ~AsciiString() {}
    const char *str() const { return data ? data->text : ""; }
    void __cdecl format(AsciiString, ...);
    AsciiString &operator=(const AsciiString &other) { set(other); return *this; }
};
class UnicodeString : private StringBase<unsigned short> {
public:
    UnicodeString() {}
    UnicodeString(const unsigned short *p):StringBase<unsigned short>(p) {}
    UnicodeString(const UnicodeString &p):StringBase<unsigned short>(p) {}
    ~UnicodeString() {}
    const unsigned short *str() const { return data ? data->text : (const unsigned short *)L""; }
    void __cdecl format(UnicodeString, ...);
    void translate(const AsciiString&);
    UnicodeString &operator=(const UnicodeString &other) { set(other); return *this; }
};
class GameSpyGroupRoom {
public:
    GameSpyGroupRoom();
    GameSpyGroupRoom(const GameSpyGroupRoom&);
    AsciiString m_name;
    UnicodeString m_translatedName;
    Int m_groupID,m_numWaiting,m_maxWaiting,m_numGames,m_numPlaying,m_bfmeExtra;
};
typedef std::map<Int,GameSpyGroupRoom> GroupRoomMap;
class GameSpyInfo {
public:
    virtual ~GameSpyInfo();
    virtual void reset();
    virtual void clearGroupRoomList();
    virtual GroupRoomMap *getGroupRoomList() { return &m_groupRooms; }
    virtual void addGroupRoom(GameSpyGroupRoom);
    char pad04[0x18-4];
    GroupRoomMap m_groupRooms;
    char pad24[0x68-0x24];
    Bool m_gotGroupRoomList;
};
extern GameSpyInfo *TheGameSpyInfo;
// Unused virtual slots are intentionally unnamed; their signatures are not claims.
class GameSpyConfigInterface {
public:
    virtual ~GameSpyConfigInterface();
    virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
    virtual Int getQMChannel();
    virtual void setQMChannel(Int);
};
extern GameSpyConfigInterface *TheGameSpyConfig;
class GameTextInterface {
public:
    virtual ~GameTextInterface();
    virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c(); virtual void slot20();
    virtual UnicodeString fetch(AsciiString, Bool *exists=0);
};
extern GameTextInterface *TheGameText;

void GameSpyInfo::addGroupRoom( GameSpyGroupRoom room )
{
	if (room.m_groupID == 0)
	{
		m_gotGroupRoomList = TRUE;

		GroupRoomMap::iterator iter;

		// figure out how many good strings we've got
		std::vector<UnicodeString> names;
		Int numRooms = 0;
		for (iter = getGroupRoomList()->begin(); iter != getGroupRoomList()->end(); ++iter)
		{
			GameSpyGroupRoom room = iter->second;
			if (room.m_groupID != TheGameSpyConfig->getQMChannel())
			{
				++numRooms;

				AsciiString groupLabel;
				groupLabel.format("GUI:%s", room.m_name.str());

				Bool exists = FALSE;
				UnicodeString groupName = TheGameText->fetch(groupLabel, &exists);
				if (exists)
				{
					names.push_back(groupName);
				}
				else
				{
					// BFME retains rooms whose label has no localized text.
					UnicodeString name;
					name.translate(room.m_name);
					names.push_back(name);
				}
			}
		}

		if (!names.empty() && names.size() != numRooms)
		{
			// didn't get all names.  fix up
			Int nameIndex = 0;
			Int timesThrough = 1; // start with USA Lobby 1
			for (iter = TheGameSpyInfo->getGroupRoomList()->begin(); iter != TheGameSpyInfo->getGroupRoomList()->end(); ++iter)
			{
				GameSpyGroupRoom room = iter->second;
				if (room.m_groupID != TheGameSpyConfig->getQMChannel())
				{
					room.m_translatedName.format(L"%ls %d", names[nameIndex].str(), timesThrough);
					nameIndex = (nameIndex+1)%names.size();
					m_groupRooms[room.m_groupID] = room;
					if (!nameIndex)
					{
						// we've looped through the name list already.  increment the timesThrough counter
						++timesThrough;
					}
				}
			}
		}
	}
	else
	{
		AsciiString groupLabel;
		groupLabel.format("GUI:%s", room.m_name.str());
		Bool exists = FALSE;
		room.m_translatedName = TheGameText->fetch(groupLabel, &exists);
		if (!exists) room.m_translatedName.translate(room.m_name);
		m_groupRooms[room.m_groupID] = room;
		if ( !stricmp("quickmatch", room.m_name.str()) )
		{
			TheGameSpyConfig->setQMChannel(room.m_groupID);
		}
	}
}
