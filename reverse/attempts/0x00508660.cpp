// ?PopulateQMLadderListBox@BfmeAptScreenQuickMatchMenu@@QAEXPAVGameWindow@@@Z
// partial score=0.62 date=2026-09-10
// Candidate source excerpt for
// ?PopulateQMLadderListBox@BfmeAptScreenQuickMatchMenu@@QAEXPAVGameWindow@@@Z
// Retail boundary: 0x00508660..0x00508B56 (1254 bytes).
// This is the complete readable candidate body from
// Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenu.cpp.
// It is bank evidence, not a second production definition.

class BfmeAptScreenQuickMatchMenu
{
public:
	void PopulateQMLadderListBox( GameWindow *win );

private:
	char m_unmodelled[ 0x218 ];
	bool m_isMatching;
	char m_pad219[ 3 ];
	int m_matchingLevel;
	bool m_isStopping;
	char m_pad221[ 3 ];
	int m_selectedMap;
	NameKeyType m_parentOptionsKey;
	GameWindow *m_parentOptions;
	NameKeyType m_maxPingKey;
	GameWindow *m_maxPing;
	NameKeyType m_numPlayersKey;
	GameWindow *m_numPlayers;
	NameKeyType m_ladderKey;
	GameWindow *m_ladder;
	NameKeyType m_maxDisconnectsKey;
	GameWindow *m_maxDisconnects;
	NameKeyType m_sideKey;
	GameWindow *m_side;
	NameKeyType m_colorKey;
	GameWindow *m_color;
	NameKeyType m_backKey;
	GameWindow *m_back;
	NameKeyType m_startKey;
	GameWindow *m_start;
	NameKeyType m_currentMatchingLevelKey;
	GameWindow *m_currentMatchingLevel;
	NameKeyType m_personalInfoKey;
	GameWindow *m_personalInfo;
	NameKeyType m_mapSelectKey;
	GameWindow *m_mapSelect;
	NameKeyType m_parentProgressKey;
	GameWindow *m_parentProgress;
	NameKeyType m_quickMatchListKey;
	GameWindow *m_quickMatchList;
	NameKeyType m_widenKey;
	GameWindow *m_widen;
	NameKeyType m_stopKey;
	GameWindow *m_stop;
	NameKeyType m_parentStatsKey;
	GameWindow *m_parentStats;
};

void BfmeAptScreenQuickMatchMenu::PopulateQMLadderListBox( GameWindow *win )
{
	if (!m_ladder)
		return;

	isPopulatingLadderBox = true;

	QuickMatchPreferences pref;
	AsciiString userPrefFilename;
	Int localProfile = ((BfmeAptGameSpyInfo *)TheGameSpyInfo)->getLocalProfileID();

	Color specialColor = GameSpyColor[GSCOLOR_MAP_SELECTED];
	Color normalColor = GameSpyColor[GSCOLOR_MAP_UNSELECTED];
	Color favoriteColor = GameSpyColor[GSCOLOR_MAP_UNSELECTED];
	Int index;
	GadgetListBoxReset( win );

	std::set<const LadderInfo *> usedLadders;

	// start with "No Ladder"
	index = GadgetListBoxAddEntryText( win, TheGameText->fetch("GUI:NoLadder"), normalColor, -1 );
	GadgetListBoxSetItemData( win, 0, index );

	// add the last ladder
	Int selectedPos = 0;
	AsciiString lastLadderAddr = pref.getLastLadderAddr();
	UnsignedShort lastLadderPort = pref.getLastLadderPort();
	const LadderInfo *info = TheLadderList->findLadder( lastLadderAddr, lastLadderPort );
	if (isValidLadder(info))
	{
		usedLadders.insert(info);
		index = GadgetListBoxAddEntryText( win, info->name, favoriteColor, -1 );
		GadgetListBoxSetItemData( win, (void *)(info->index), index );
		selectedPos = index;
	}

	// our recent ladders
	LadderPreferences ladPref;
	ladPref.loadProfile( localProfile );
	const LadderPrefMap recentLadders = ladPref.getRecentLadders();
	for (LadderPrefMap::const_iterator cit = recentLadders.begin(); cit != recentLadders.end(); ++cit)
	{
		AsciiString addr = cit->second.address;
		UnsignedShort port = cit->second.port;
		if (addr == lastLadderAddr && port == lastLadderPort)
			continue;
		const LadderInfo *info = TheLadderList->findLadder( addr, port );
		if (isValidLadder(info) && usedLadders.find(info) == usedLadders.end())
		{
			usedLadders.insert(info);
			index = GadgetListBoxAddEntryText( win, info->name, favoriteColor, -1 );
			GadgetListBoxSetItemData( win, (void *)(info->index), index );
		}
	}

	// special ladders
	const LadderInfoList *lil = TheLadderList->getSpecialLadders();
	LadderInfoList::const_iterator lit;
	for (lit = lil->begin(); lit != lil->end(); ++lit)
	{
		const LadderInfo *info = *lit;
		if (isValidLadder(info) && usedLadders.find(info) == usedLadders.end())
		{
			usedLadders.insert(info);
			index = GadgetListBoxAddEntryText( win, info->name, specialColor, -1 );
			GadgetListBoxSetItemData( win, (void *)(info->index), index );
		}
	}

	// standard ladders
	lil = TheLadderList->getStandardLadders();
	for (lit = lil->begin(); lit != lil->end(); ++lit)
	{
		const LadderInfo *info = *lit;
		if (isValidLadder(info) && usedLadders.find(info) == usedLadders.end())
		{
			usedLadders.insert(info);
			index = GadgetListBoxAddEntryText( win, info->name, normalColor, -1 );
			GadgetListBoxSetItemData( win, (void *)(info->index), index );
		}
	}

	GadgetListBoxSetSelected( win, selectedPos );
	isPopulatingLadderBox = false;
}
