// stlport
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

class AsciiStringTarget
{
public:
	void assign(const AsciiString &other);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	AsciiString getMap(void) const;
};

class Gen_00525EE0
{
public:
	void bfmeSetSecondGame(GameInfo *game);
private:
	unsigned char m_unmodelled[0x0c];
	GameInfo *m_second;
	unsigned char m_unmodelled10[0x18];
	AsciiString m_mapName;
};

// Cache the secondary game and mirror its map name into the controller.
// ?bfmeSetSecondGame@Gen_00525EE0@@QAEXPAVGameInfo@@@Z
void Gen_00525EE0::bfmeSetSecondGame(GameInfo *game)
{
	m_second = game;
	if (game)
		reinterpret_cast<AsciiStringTarget *>(&m_mapName)->assign(game->getMap());
	else
	{
		AsciiString empty("");
		reinterpret_cast<AsciiStringTarget *>(&m_mapName)->assign(empty);
	}
}
