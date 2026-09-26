// stlport
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

#include "StringInline.h"

// Partial view of the embedded preview: only its first four bytes are
// represented here, not its total extent. AptMapPreview.cpp
// witnesses the receiver of ILT 0x0003EC57 as AptMapPreview, not AsciiString.
// Raw storage avoids introducing construction/destruction obligations.
class AptMapPreview
{
public:
	void rva005217A0(const AsciiString &value);
private:
	unsigned char m_unmodelled00[4];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	AsciiString getMap(void) const;
};

class MpGameSetup
{
public:
	void bfmeSetSecondGame(GameInfo *game);
private:
	unsigned char m_unmodelled[0x0c];
	GameInfo *m_second;
	unsigned char m_unmodelled10[0x18];
	AptMapPreview m_preview; // +0x28; partial embedded-object view
};

// Cache the secondary game and pass its map name to the embedded preview.
// ?bfmeSetSecondGame@MpGameSetup@@QAEXPAVGameInfo@@@Z
void MpGameSetup::bfmeSetSecondGame(GameInfo *game)
{
	m_second = game;
	if (game)
		m_preview.rva005217A0(game->getMap());
	else
	{
		AsciiString empty("");
		m_preview.rva005217A0(empty);
	}
}
