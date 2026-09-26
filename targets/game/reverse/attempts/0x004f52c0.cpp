// ?WOLGameSetupMenuInit@@YAXPAVWindowLayout@@PAX@Z
// partial score=0.9933365064255116 date=2026-09-26
// ?WOLGameSetupMenuInit@@YAXPAVWindowLayout@@PAX@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/psplayerstats /Iinputs/reference/shims/nat /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retains the menu TU declarations; the candidate body is explicitly banked below.
#define WOLGameSetupMenuInit WOLGameSetupMenuInit_PreFinisherBank
#include "../../../../game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp"
#undef WOLGameSetupMenuInit
void WOLGameSetupMenuInit( WindowLayout *layout, void *userData )
{
	if (TheGameSpyGame && TheGameSpyGame->isGameInProgress())
	{
		TheGameSpyGame->setGameInProgress(FALSE);

		// check if we were disconnected
		Int disconReason;
		if (((BfmeWolInitInfo *)TheGameSpyInfo)->isDisconnectedAfterGameStart(&disconReason))
		{
			AsciiString disconMunkee;
			disconMunkee.format("GUI:GSDisconReason%d", disconReason);
			UnicodeString title, body;
			title = TheGameText->fetch( "GUI:GSErrorTitle" );
			body = TheGameText->fetch( disconMunkee );
			GameSpyCloseAllOverlays();
			GSMessageBoxOk( title, body );
			((BfmeWolInitInfo *)TheGameSpyInfo)->reset();
			DEBUG_LOG(("WOLGameSetupMenuInit() - game was in progress, and we were disconnected, so pop immediate back to main menu\n"));
			TheShell->popImmediate();
			return;
		}

		// If we init while the game is in progress, we are really returning to the menu
		// after the game.  So, we pop the menu and go back to the lobby.  Whee!
		DEBUG_LOG(("WOLGameSetupMenuInit() - game was in progress, so pop immediate back to lobby\n"));
		TheShell->popImmediate();
		if (TheGameSpyPeerMessageQueue && TheGameSpyPeerMessageQueue->isConnected())
		{
			DEBUG_LOG(("We're still connected, so pushing back on the lobby\n"));
			TheShell->push("Menus/WOLCustomLobby.wnd", TRUE);
		}
		return;
	}
	((BfmeWolInitInfo *)TheGameSpyInfo)->setCurrentGroupRoom(0);

	if (TheNAT != NULL) {
		delete TheNAT;
		TheNAT = NULL;
	}

	nextScreen = NULL;
	buttonPushed = false;
	isShuttingDown = false;
	launchGameNext = FALSE;

	//initialize the gadgets
	EnableSlotListUpdates(FALSE);
	InitWOLGameGadgets();
	EnableSlotListUpdates(TRUE);
	((BfmeWolInitInfo *)TheGameSpyInfo)->registerTextWindow(listboxGameSetupChat);

	//The dialog needs to react differently depending on whether it's the host or not.
	TheMapCache->updateCache();
	GameSpyStagingRoom *game = ((BfmeWolInitInfo *)TheGameSpyInfo)->getCurrentStagingRoom();
	GameSpyGameSlot *hostSlot = game->getGameSpySlot(0);
	hostSlot->setAccept();
switch (((BfmeWolInitInfo *)TheGameSpyInfo)->amIHost()) { case FALSE: {
		OptionPreferences natPref;
		CustomMatchPreferences customPref;
		AsciiString options;
		PeerRequest req;
		UnicodeString uName = hostSlot->getName();
		AsciiString aName;
		aName.translate(uName);
		req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
		req.UTM.isStagingRoom = TRUE;
		req.id = "REQ/";
		req.nick = aName.str();
		options.format("PlayerTemplate=%d", customPref.getPreferredFaction());
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
		options.format("Color=%d", customPref.getPreferredColor());
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
		options.format("NAT=%d", natPref.getFirewallBehavior());
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
		options.format("Ping=%s", ((BfmeWolInitInfo *)TheGameSpyInfo)->getPingString().str());
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
   
		game->setMapCRC( game->getMapCRC() );		// force a recheck
		game->setMapSize( game->getMapSize() ); // of if we have the map

		for (Int i = 0; i < MAX_SLOTS; ++i)
		{
			//I'm a client, disable the controls I can't touch.
			comboBoxPlayer[i]->winEnable(FALSE);

			comboBoxColor[i]->winEnable(FALSE);
			comboBoxPlayerTemplate[i]->winEnable(FALSE);
			comboBoxTeam[i]->winEnable(FALSE);
//			buttonStartPosition[i]->winEnable(FALSE);
			buttonMapStartPosition[i]->winEnable(FALSE);

		}
		buttonStart->GameWindow::winSetText(TheGameText->fetch("GUI:Accept"));
		buttonStart->winEnable( FALSE );
		buttonSelectMap->winEnable( FALSE );
		initialAcceptEnable = FALSE;
	} break; default: {
		OptionPreferences natPref;
		CustomMatchPreferences customPref;
		hostSlot->setColor( customPref.getPreferredColor() );
		hostSlot->setPlayerTemplate( customPref.getPreferredFaction() );
		hostSlot->setNATBehavior((FirewallHelperClass::FirewallBehaviorType)natPref.getFirewallBehavior());
		hostSlot->setPingString(((BfmeWolInitInfo *)TheGameSpyInfo)->getPingString());
		game->setMap(customPref.getPreferredMap());

		for (Int i=1; i<MAX_SLOTS; ++i)
		{
			GameSpyGameSlot *slot = game->getGameSpySlot(i);
			GameSlotConnectInfo connect;
			connect.m_nat = (FirewallHelperClass::FirewallBehaviorType)0;
			connect.m_port = 0;
			slot->setState( SLOT_OPEN, UnicodeString::TheEmptyString, &connect );
		}

		AsciiString lowerMap = customPref.getPreferredMap();
		lowerMap.toLower();
		std::map<AsciiString, MapMetaData>::iterator it = TheMapCache->find(lowerMap);
		if (it != TheMapCache->end())
		{
			hostSlot->setMapAvailability(TRUE);
			game->setMapCRC( it->second.m_CRC );
			game->setMapSize( it->second.m_filesize );

			game->adjustSlotsForMap(); // BGC- adjust the slots for the new map.
		}


		WOLDisplaySlotList();
		WOLDisplayGameOptions();
	} break; }

	// Show the Menu
	((BfmeVirtualHideLayout *)layout)->hide( FALSE );
	
	// Make sure the text fields are clear
	GadgetListBoxReset( listboxGameSetupChat );
	GadgetTextEntrySetText(textEntryChat, UnicodeString::TheEmptyString);	

	initDone = true;
	((BfmeWolInitInfo *)TheGameSpyInfo)->setGameOptions();
	//TheShell->registerWithAnimateManager(parentWOLGameSetup, WIN_ANIMATION_SLIDE_TOP, TRUE);
	WOLPositionStartSpots();

	lastSlotlistTime = 0;
	enterTime = timeGetTime();

	// Set Keyboard to chat entry
	TheWindowManager->winSetFocus( textEntryChat );
	raiseMessageBoxes = true;
	TheTransitionHandler->setGroup("GameSpyGameOptionsMenuFade");
}
