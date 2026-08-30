// ?markAsStagingRoomHost@GameSpyInfo@@UAEXXZ
// partial score=0.86 date=2026-08-30
void GameSpyInfo::markAsStagingRoomHost(void)
{
	class BfmeStagingRoomResetView
	{
	public:
		virtual void unused0() = 0;
		virtual void unused1() = 0;
		virtual void reset() = 0;
	};

	m_localStagingRoomID = 0;
	m_joinedStagingRoom = FALSE;
	m_isHosting = TRUE;
	reinterpret_cast<BfmeStagingRoomResetView *>(&m_localStagingRoom)->reset();
	m_localStagingRoom.enterGame();
	m_localStagingRoom.setSeed(GetTickCount());

	GameSlot newSlot;
	UnicodeString uName;
	uName.translate(m_localName);
	GameSlotConnectInfo connectInfo = {
		FirewallHelperClass::FIREWALL_TYPE_UNKNOWN, 0
	};
	newSlot.setState(SLOT_PLAYER, uName, &connectInfo);

	m_localStagingRoom.setLocalIP(m_externalIP);
	*reinterpret_cast<Int *>(reinterpret_cast<char *>(&m_localStagingRoom) + 0x38) = NETWORK_BASE_PORT_NUMBER;
	newSlot.setIP(m_externalIP);
	newSlot.setPort(NETWORK_BASE_PORT_NUMBER);
	m_localStagingRoom.setSlot(0, newSlot);
	m_localStagingRoom.setLocalName(m_localName);

	TheMapCache->updateCache();
	m_localStagingRoom.setMap(getDefaultMap(TRUE));
	m_localStagingRoom.adjustSlotsForMap();
}
