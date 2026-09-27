// ?gameTooltip@@YAXPAVGameWindow@@PAVWinInstanceData@@I@Z
// partial score=0.8 date=2026-09-27
// Replaces the ZH-text gameTooltip in game/GameEngine/Source/GameNetwork/GameSpy/LobbyUtils.cpp
// (insert in place of that function; the rest of the TU unchanged). Built and probed in that TU.

// The BFME GameSpyStagingRoom fields gameTooltip reads. BFME's GameInfo is
// larger than Zero Hour's, so these sit past the header's layout; the ladder
// IP accessor is the out-of-line body at 0x004D7AC0.
class BFMETooltipRoom
{
public:
	AsciiString getLadderIP( void ) const;

	unsigned char m_pad000[0x428];
	Bool m_hasPassword;										// +0x428
	unsigned char m_pad429[0x430 - 0x429];
	UnsignedInt m_exeCRC;									// +0x430
	UnsignedInt m_iniCRC;									// +0x434
	UnsignedInt m_bfme438;								// +0x438
	unsigned char m_pad43c[0x450 - 0x43c];
	UnsignedShort m_ladderPort;						// +0x450
};

// BFME's UnicodeString::concat(WideChar) is inline over the length-taking
// StringBase<WideChar>::concat at 0x00888600.
template <class T> class StringBase
{
public:
	void concat( const T *s, int len );
};

static __forceinline void bfmeConcatChar( UnicodeString &s, WideChar c )
{
	UnsignedInt tmp = c;	// the character and its terminator in one dword
	((StringBase<unsigned short> *)&s)->concat( (const unsigned short *)&tmp, 1 );
}

// BFME de-obfuscates the expected executable CRC through this hook.
Int Rva0009B4B0( Int a, Int b );

static void gameTooltip(GameWindow *window,
													WinInstanceData *instData,
													UnsignedInt mouse)
{
	Int x, y, row, col;
	x = LOLONGTOSHORT(mouse);
	y = HILONGTOSHORT(mouse);

	GadgetListBoxGetEntryBasedOnXY(window, x, y, row, col);

	if (row == -1 || col == -1)
	{
		TheMouse->setCursorTooltip( UnicodeString::TheEmptyString);//TheGameText->fetch("TOOLTIP:GamesBeingFormed") );
		return;
	}

	Int gameID = (Int)GadgetListBoxGetItemData(window, row, 0);
	GameSpyStagingRoom *room = TheGameSpyInfo->findStagingRoomByID(gameID);
	if (!room)
	{
		TheMouse->setCursorTooltip( TheGameText->fetch("TOOLTIP:UnknownGame") );
		return;
	}

	if (col == COLUMN_PING)
	{
#if 0 //def DEBUG_LOGGING
		UnicodeString s;
		s.format(L"Ping is %d ms (cutoffs are %d ms and %d ms\n%hs local pings\n%hs remote pings",
			room->getPingAsInt(), TheGameSpyConfig->getPingCutoffGood(), TheGameSpyConfig->getPingCutoffBad(),
			TheGameSpyInfo->getPingString().str(), room->getPingString().str()
		);
		TheMouse->setCursorTooltip( s, 10, NULL, 2.0f ); // the text and width are the only params used.  the others are the default values.
#else
		TheMouse->setCursorTooltip( TheGameText->fetch("TOOLTIP:PingInfo"), 10, NULL, 2.0f ); // the text and width are the only params used.  the others are the default values.
#endif
		return;
	}
	if (col == COLUMN_NUMPLAYERS)
	{
		TheMouse->setCursorTooltip( TheGameText->fetch("TOOLTIP:NumberOfPlayers"), 10, NULL, 2.0f ); // the text and width are the only params used.  the others are the default values.
		return;
	}
	if (col == COLUMN_PASSWORD)
	{
		if (((const BFMETooltipRoom *)room)->m_hasPassword)
		{
			UnicodeString checkTooltip =TheGameText->fetch("TOOTIP:Password");
			if(!checkTooltip.compare(L"Password required to joing game"))
				checkTooltip.set(L"Password required to join game");
			TheMouse->setCursorTooltip( checkTooltip, 10, NULL, 2.0f ); // the text and width are the only params used.  the others are the default values.
		}
		else
			TheMouse->setCursorTooltip( UnicodeString::TheEmptyString );
		return;
	}
	// BFME has no use-stats tooltip column.

	UnicodeString tooltip;

	UnicodeString mapName;
	const MapMetaData *md = TheMapCache->findMap(room->getMap());
	if (md)
	{
		mapName = md->m_displayName;
	}
	else
	{
		const char *start = room->getMap().reverseFind('\\');
		if (start)
		{
			++start;
		}
		else
		{
			start = room->getMap().str();
		}
		mapName.translate( start );
	}
	UnicodeString tmp;
	tooltip.format(TheGameText->fetch("TOOLTIP:GameInfoGameName"), room->getGameName().str());
	const BFMETooltipRoom *bfmeRoom = (const BFMETooltipRoom *)room;
	if (bfmeRoom->m_ladderPort != 0)
	{
		const LadderInfo *linfo = TheLadderList->findLadder(bfmeRoom->getLadderIP(), bfmeRoom->m_ladderPort);
		if (linfo)
		{
			tmp.format(TheGameText->fetch("TOOLTIP:GameInfoLadderName"), linfo->name.str());
			tooltip.concat(tmp);
		}
	}
	// BFME GlobalData words: +0xBD0 feeds the CRC hook, +0xBC8 and +0xBD4 are
	// compared directly.
	const UnsignedInt *globals = (const UnsignedInt *)TheGlobalData;
	if (bfmeRoom->m_exeCRC != (UnsignedInt)Rva0009B4B0(globals[0xbd0/4], globals[0xbd0/4]) ||
			bfmeRoom->m_iniCRC != globals[0xbc8/4] ||
			bfmeRoom->m_bfme438 != globals[0xbd4/4])
	{
		tmp.format(TheGameText->fetch("TOOLTIP:InvalidGameVersion"), mapName.str());
		tooltip.concat(tmp);
	}
	tmp.format(TheGameText->fetch("TOOLTIP:GameInfoMap"), mapName.str());
	tooltip.concat(tmp);

	AsciiString aPlayer;
	UnicodeString player;
	Int numPlayers = 0;
	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		GameSpyGameSlot *slot = room->getGameSpySlot(i);
		if (i == 0 && (!slot || !slot->isHuman()))
		{
			DEBUG_CRASH(("About to tooltip a non-hosted game!\n"));
		}
		if (slot && slot->isHuman())
		{
			tmp.format(TheGameText->fetch("TOOLTIP:GameInfoPlayer"), slot->getName().str(), slot->getWins(), slot->getLosses());
			tooltip.concat(tmp);
			++numPlayers;
		}
		else if (slot && slot->isAI())
		{
			++numPlayers;
			switch(slot->getState())
			{
			case SLOT_EASY_AI:
				bfmeConcatChar(tooltip, L'\n');
				tooltip.concat(TheGameText->fetch("GUI:EasyAI"));
				break;
			case SLOT_MED_AI:
				bfmeConcatChar(tooltip, L'\n');
				tooltip.concat(TheGameText->fetch("GUI:MediumAI"));
				break;
			case SLOT_BRUTAL_AI:
				bfmeConcatChar(tooltip, L'\n');
				tooltip.concat(TheGameText->fetch("GUI:HardAI"));
				break;
			}
		}
	}
	DEBUG_ASSERTCRASH(numPlayers, ("Tooltipping a 0-player game!\n"));

	TheMouse->setCursorTooltip( tooltip, 10, NULL, 2.0f ); // the text and width are the only params used.  the others are the default values.
}
