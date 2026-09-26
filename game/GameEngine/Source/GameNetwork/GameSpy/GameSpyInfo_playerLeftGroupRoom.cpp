// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport
// STLport's real map ABI is used here instead of a private tree facade.
//
// GameSpyInfo::playerLeftGroupRoom is the 168-byte body at 0x00633F80.
// The GameSpyInfo constructor at 0x00636D90 installs vtable 0x011188D0;
// slot 17 (+0x44) is ILT j_0002800B, whose body is 0x00633F80.  The named
// WOLLobbyMenu.cpp:982 and WOLGameSetupMenu.cpp:2066 callbacks call this
// virtual after a PEERRESPONSE_PLAYERLEFT.  The map starts at this+0x4c.
//
// The BFME PlayerInfo is 0x34 bytes here.  Keep that small ABI slice local so
// the ZH PeerDefs declarations cannot alter this body's map node size.  The
// prior hand-written _Rb_tree attempt was one byte/register short; this pass
// deliberately uses the authentic STLport map implementation.

#define _STLP_NO_EXCEPTIONS 1
#include "../../../../../inputs/reference/shims/stringinline/StringInline.h"
#include <map>
class GameWindow;

class PlayerInfo
{
public:
	~PlayerInfo();
	PlayerInfo(const PlayerInfo&);

private:
	char m_body[0x34];
};

struct AsciiComparator
{
	bool operator()(AsciiString first, AsciiString second) const;
};

typedef std::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;

class GameSpyInfo
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0a();
	virtual void slot0b();
	virtual void slot0c();
	virtual void slot0d();
	virtual void slot0e();
	virtual void slot0f();
	virtual void slot10();
	virtual void playerLeftGroupRoom(AsciiString nick);
	virtual PlayerInfoMap *getPlayerInfoMap();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void addChat(PlayerInfo p, UnicodeString msg, bool isPublic, bool isAction, GameWindow *win);
	virtual void addChat(AsciiString nick, int profileID, UnicodeString msg, bool isPublic, bool isAction, GameWindow *win);

private:
	char m_head[0x48];
	PlayerInfoMap m_playerInfoMap;
};

void GameSpyInfo::playerLeftGroupRoom(AsciiString nick)
{
	PlayerInfoMap::iterator it = m_playerInfoMap.find(nick);
	if (it != m_playerInfoMap.end())
		m_playerInfoMap.erase(it);
}

// The retail vtable places the 6-argument overload at slot 60 and the
// 5-argument overload at slot 61 (MSVC reverses adjacent overloads).
void GameSpyInfo::addChat(AsciiString nick, int profileID, UnicodeString msg,
	bool isPublic, bool isAction, GameWindow *win)
{
	PlayerInfoMap::iterator it = getPlayerInfoMap()->find(nick);
	if (it != getPlayerInfoMap()->end())
		addChat(it->second, msg, isPublic, isAction, win);
}
