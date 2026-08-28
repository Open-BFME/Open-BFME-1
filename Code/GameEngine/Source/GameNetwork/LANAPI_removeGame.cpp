// cl: /DNDEBUG /MD /EHsc
// readable body of ?removeGame@LANAPI@@IAEXPAVLANGameInfo@@@Z: Code/GameEngine/Source/GameNetwork/lanapi.cpp

// Retail 0x00685180 -- the LANGameInfo half of the pair whose LANPlayer half,
// ?removePlayer@LANAPI@@IAEXPAVLANPlayer@@@Z at 0x00685290, is already ledgered
// in lanapi.cpp. Same unlink, same shape, one guard more: BFME returns early on
// an empty list where Zero Hour walks into the else branch and dereferences a
// null g.
//
// Its own TU rather than lanapi.cpp: retail's LANGameInfo carries its next
// pointer at +0x398 and the vendored Zero Hour header puts it at +0x360, so the
// body compiled there misses by that displacement in six places. Modelling the
// two offsets here keeps the correction out of a shared header.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo
{
public:
	unsigned char m_bfmeHead[0x398];
	LANGameInfo *m_next;			// +0x398
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
class LANAPI
{
protected:
	void removeGame(LANGameInfo *game);

	unsigned char m_bfmeHead[0x0C];
	LANGameInfo *m_games;			// +0x0C
};

// ?removeGame@LANAPI@@IAEXPAVLANGameInfo@@@Z
void LANAPI::removeGame(LANGameInfo *game)
{
	LANGameInfo *g = m_games;
	if (!game || !g)
	{
		return;
	}
	else if (m_games == game)
	{
		m_games = m_games->m_next;
	}
	else
	{
		while (g->m_next && g->m_next != game)
		{
			g = g->m_next;
		}

		if (g->m_next == game)
		{
			g->m_next = game->m_next;
		}
	}
}
