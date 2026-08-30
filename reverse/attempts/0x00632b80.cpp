// ?markAsStagingRoomJoiner@GameSpyInfo@@UAEXH@Z
// partial score=0.72 date=2026-08-30
void GameSpyInfo::markAsStagingRoomJoiner(Int game)
{
	m_localStagingRoomID = game;
	m_joinedStagingRoom = TRUE;
	m_isHosting = FALSE;
	m_localStagingRoom.reset();
	m_localStagingRoom.enterGame();
	StagingRoomMap::iterator it = m_stagingRooms.find(game);
	if (it != m_stagingRooms.end())
	{
		GameSpyStagingRoom *info = it->second;
		info->cleanUpSlotPointers();
		AsciiString options = GameInfoToAsciiString(info);
		ParseAsciiStringToGameInfo(&m_localStagingRoom, options);
		m_localStagingRoom.setInGame();
		m_localStagingRoom.setLocalName(m_localName);
		m_localStagingRoom.setExeCRC(info->getExeCRC());
		m_localStagingRoom.setIniCRC(info->getIniCRC());
		m_localStagingRoom.setAllowObservers(info->getAllowObservers());
		m_localStagingRoom.setHasPassword(info->getHasPassword());
		m_localStagingRoom.setGameName(info->getGameName());
	}
}
