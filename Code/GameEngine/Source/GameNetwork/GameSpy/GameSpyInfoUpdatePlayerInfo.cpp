// ?updatePlayerInfo@GameSpyInfo@@UAEXVPlayerInfo@@VAsciiString@@@Z
// BFME adds a third AsciiString to PlayerInfo, so this body keeps its ABI
// layout local instead of inheriting the Zero Hour layout from PeerDefs.cpp.

#include <map>
#include "../../../../../reference/shims/stringinline/StringInline.h"

typedef int Int;
typedef bool Bool;

class PlayerInfo
{
public:
	AsciiString m_name;
	AsciiString m_locale;
	AsciiString m_bfmeExtraString;
	Int m_wins;
	Int m_losses;
	Int m_profileID;
	Int m_flags;
	Int m_rankPoints;
	Int m_side;
	Int m_bfmeExtra0;
	Int m_bfmeExtra1;
	Int m_bfmeExtra2;
	Int m_preorder;

	PlayerInfo &operator=(const PlayerInfo &other);
};

struct AsciiComparator
{
	Bool operator()(AsciiString first, AsciiString second) const;
};

typedef std::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;

class GameSpyInfoVtable
{
public:
	virtual void slot_000();
	virtual void slot_004();
	virtual void slot_008();
	virtual void slot_00c();
	virtual void slot_010();
	virtual void slot_014();
	virtual void slot_018();
	virtual void slot_01c();
	virtual void slot_020();
	virtual void slot_024();
	virtual void slot_028();
	virtual void slot_02c();
	virtual void slot_030();
	virtual void slot_034();
	virtual void slot_038();
	virtual void slot_03c();
	virtual void slot_040();
	virtual void playerLeftGroupRoom(AsciiString nick);
	virtual void slot_048();
	virtual void slot_04c();
	virtual void slot_050();
	virtual void slot_054();
	virtual void slot_058();
	virtual void slot_05c();
	virtual void slot_060();
	virtual void slot_064();
	virtual void slot_068();
	virtual void slot_06c();
	virtual void slot_070();
	virtual void slot_074();
	virtual void slot_078();
	virtual void slot_07c();
	virtual void slot_080();
	virtual void slot_084();
	virtual void slot_088();
	virtual void slot_08c();
	virtual void slot_090();
	virtual void slot_094();
	virtual void slot_098();
	virtual void slot_09c();
	virtual void slot_0a0();
	virtual void slot_0a4();
	virtual void slot_0a8();
	virtual void slot_0ac();
	virtual void slot_0b0();
	virtual void slot_0b4();
	virtual void slot_0b8();
	virtual void slot_0bc();
	virtual void slot_0c0();
	virtual void slot_0c4();
	virtual void slot_0c8();
	virtual void slot_0cc();
	virtual void slot_0d0();
	virtual void slot_0d4();
	virtual void slot_0d8();
	virtual void slot_0dc();
	virtual void slot_0e0();
	virtual void slot_0e4();
	virtual void slot_0e8();
	virtual void slot_0ec();
	virtual void slot_0f0();
	virtual void slot_0f4();
	virtual void slot_0f8();
	virtual void slot_0fc();
	virtual void slot_100();
	virtual void slot_104();
	virtual void slot_108();
	virtual void slot_10c();
	virtual void slot_110();
	virtual void slot_114();
	virtual void slot_118();
	virtual void slot_11c();
	virtual void slot_120();
	virtual void slot_124();
	virtual void slot_128();
	virtual void slot_12c();
	virtual void slot_130();
	virtual void slot_134();
	virtual void slot_138();
	virtual void slot_13c();
	virtual void slot_140();
	virtual void slot_144();
	virtual void slot_148();
	virtual void slot_14c();
	virtual void slot_150();
	virtual void slot_154();
	virtual void slot_158();
	virtual void slot_15c();
	virtual void slot_160();
	virtual void markPlayerAsPreorder(Int profileID);
};

class GameSpyInfo : public GameSpyInfoVtable
{
public:
	virtual void updatePlayerInfo(PlayerInfo pi, AsciiString oldNick);

private:
	char m_bfmePad[0x48];
	PlayerInfoMap m_playerInfoMap;
};

void GameSpyInfo::updatePlayerInfo(PlayerInfo pi, AsciiString oldNick)
{
	char *oldNickData = *reinterpret_cast<char *const *>(&oldNick);
	if (oldNickData != 0
		&& *reinterpret_cast<const unsigned short *>(oldNickData + 4) != 0)
		playerLeftGroupRoom(oldNick);

	m_playerInfoMap[pi.m_name] = pi;

	if (pi.m_preorder != 0)
		markPlayerAsPreorder(pi.m_profileID);
}
