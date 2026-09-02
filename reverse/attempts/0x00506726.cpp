// ?WOLQuickMatchMenuUpdate@@YAXPAVWindowLayout@@PAX@Z
// partial score=0.43 date=2026-09-02
// Banked partial for retail 0x00506726.
// Transplant into WOLQuickMatchMenu.cpp with that TU's existing includes and globals.
// Object-form wrapper is required because retail receives WindowLayout in ecx and returns with ret 4.

class BfmeWOLQuickMatchMenuUpdateBody
{
public:
	void update(void *userData);
};

// The BFME queue record is 0x330 bytes; the Zero Hour declaration included by
// this source is 0x1c0.  Its shared prefix contains every field used below.
class BfmeQuickMatchPeerResponse : public PeerResponse
{
private:
	unsigned char m_bfmeTail[0x170];
};

void BfmeWOLQuickMatchMenuUpdateBody::update(void *userData)
{
	WindowLayout *layout = reinterpret_cast<WindowLayout *>(this);
	// BFME moved GameLogic::m_gameMode to +0x10c.  The surviving Zero Hour
	// header still places it at +0x94, while m_frame remains at +0x3c.
	if (*reinterpret_cast<const Int *>(reinterpret_cast<const char *>(TheGameLogic) + 0x10c) == GAME_SHELL
			&& TheGameLogic->getFrame() == 1)
	{
		SignalUIInteraction(SHELL_SCRIPT_HOOK_GENERALS_ONLINE_ENTERED_FROM_GAME);
	}

	// We'll only be successful if we've requested to 
	if(isShuttingDown && TheShell->isAnimFinished()&& TheTransitionHandler->isFinished())
		shutdownComplete(layout);

	if (raiseMessageBoxes)
	{
		RaiseGSMessageBox();
		raiseMessageBoxes = false;
	}
	
	/// @todo: MDC handle disconnects in-game the same way as Custom Match!

	if (TheShell->isAnimFinished() && !buttonPushed && TheGameSpyPeerMessageQueue)
	{
		HandleBuddyResponses();
		HandlePersistentStorageResponses();

		if (TheGameSpyGame && TheGameSpyGame->isGameInProgress())
		{
			if (TheGameSpyInfo->isDisconnectedAfterGameStart(NULL))
			{
				return; // already been disconnected, so don't worry.
			}

			Int allowedMessages = TheGameSpyInfo->getMaxMessagesPerUpdate();
			Bool sawImportantMessage = FALSE;
			BfmeQuickMatchPeerResponse resp;
			while (allowedMessages-- && !sawImportantMessage && TheGameSpyPeerMessageQueue->getResponse( resp ))
			{
				switch (resp.peerResponseType)
				{
				case PeerResponse::PEERRESPONSE_DISCONNECT:
					{
						sawImportantMessage = TRUE;
						AsciiString disconMunkee;
						disconMunkee.format("GUI:GSDisconReason%d", resp.discon.reason);

						// check for scorescreen
						NameKeyType listboxChatWindowScoreScreenID = NAMEKEY("ScoreScreen.wnd:ListboxChatWindowScoreScreen");
						GameWindow *listboxChatWindowScoreScreen = TheWindowManager->winGetWindowFromId( NULL, listboxChatWindowScoreScreenID );
						if (listboxChatWindowScoreScreen)
						{
							GadgetListBoxAddEntryText(listboxChatWindowScoreScreen, TheGameText->fetch(disconMunkee),
								GameSpyColor[GSCOLOR_DEFAULT], -1);
						}
						else
						{
							// still ingame
							TheInGameUI->message(disconMunkee);
						}
						TheGameSpyInfo->markAsDisconnectedAfterGameStart(resp.discon.reason);
					}
				}
			}

			return; // if we're in game, all we care about is if we've been disconnected from the chat server
		}

		if (TheNAT != NULL) {
			NATStateType NATState = TheNAT->update();
			if (NATState == NATSTATE_DONE)
			{
				TheGameSpyGame->launchGame();
				if (TheGameSpyInfo) // this can be blown away by a disconnect on the map transfer screen
					TheGameSpyInfo->leaveStagingRoom();
				return; // don't do any more processing this frame, in case the screen goes away
			}
			else if (NATState == NATSTATE_FAILED)
			{
				// delete TheNAT, its no good for us anymore.
				delete TheNAT;
				TheNAT = NULL;

				// Just back out.  This cleans up some slot list problems
				buttonPushed = true;
				GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:NATNegotiationFailed"));
				nextScreen = "Menus/WOLWelcomeMenu.wnd";
				TheShell->pop();
				return; // don't do any more processing this frame, in case the screen goes away
			}
		}

#ifdef PERF_TEST
		UnsignedInt start = timeGetTime();
		UnsignedInt end = timeGetTime();
		std::list<Int> responses;
		Int numMessages = 0;
#endif // PERF_TEST

		Int allowedMessages = TheGameSpyInfo->getMaxMessagesPerUpdate();
		Bool sawImportantMessage = FALSE;
		BfmeQuickMatchPeerResponse resp;
		while (allowedMessages-- && !sawImportantMessage && TheGameSpyPeerMessageQueue->getResponse( resp ))
		{
#ifdef PERF_TEST
			++numMessages;
			responses.push_back(resp.peerResponseType);
#endif // PERF_TEST
			switch (resp.peerResponseType)
			{
			case PeerResponse::PEERRESPONSE_PLAYERUTM:
				{
					if (!stricmp(resp.command.c_str(), "STATS"))
					{
						DEBUG_LOG(("Saw STATS from %s, data was '%s'\n", resp.nick.c_str(), resp.commandOptions.c_str()));
						AsciiString data = resp.commandOptions.c_str();
						AsciiString idStr;
						data.nextToken(&idStr, " ");
						Int id = atoi(idStr.str());
						DEBUG_LOG(("data: %d(%s) - '%s'\n", id, idStr.str(), data.str()));

						PSPlayerStats stats = TheGameSpyPSMessageQueue->parsePlayerKVPairs(data.str());
						PSPlayerStats oldStats = TheGameSpyPSMessageQueue->findPlayerStatsByID(id);
						stats.id = id;
						DEBUG_LOG(("Parsed ID is %d, old ID is %d\n", stats.id, oldStats.id));
						if (stats.id && (oldStats.id == 0))
							TheGameSpyPSMessageQueue->trackPlayerStats(stats);

						// now fill in the profileID in the game slot
						AsciiString nick = resp.nick.c_str();
						for (Int i=0; i<MAX_SLOTS; ++i)
						{
							GameSpyGameSlot *slot = TheGameSpyGame->getGameSpySlot(i);
							if (slot && slot->isHuman() && (slot->getLoginName().compareNoCase(nick) == 0))
							{
								slot->setProfileID(id);
								break;
							}
						}
					}
					Int slotNum = TheGameSpyGame->getSlotNum(resp.nick.c_str());
					if ((slotNum >= 0) && (slotNum < MAX_SLOTS) && (!stricmp(resp.command.c_str(), "NAT"))) {
						// this is a command for NAT negotiations, pass if off to TheNAT
						sawImportantMessage = TRUE;
						if (TheNAT != NULL) {
							TheNAT->processGlobalMessage(slotNum, resp.commandOptions.c_str());
						}
					}
					/*
					else if (key == "NAT")
					{
						if ((val >= FirewallHelperClass::FIREWALL_TYPE_SIMPLE) &&
								(val <= FirewallHelperClass::FIREWALL_TYPE_DESTINATION_PORT_DELTA))
						{
							slot->setNATBehavior((FirewallHelperClass::FirewallBehaviorType)val);
							DEBUG_LOG(("Setting NAT behavior to %d for player %d\n", val, slotNum));
							change = true;
						}
						else
						{
							DEBUG_LOG(("Rejecting invalid NAT behavior %d from player %d\n", val, slotNum));
						}
					}
					*/
				}
				break;

			case PeerResponse::PEERRESPONSE_DISCONNECT:
				{
					sawImportantMessage = TRUE;
					UnicodeString title, body;
					AsciiString disconMunkee;
					disconMunkee.format("GUI:GSDisconReason%d", resp.discon.reason);
					title = TheGameText->fetch( "GUI:GSErrorTitle" );
					body = TheGameText->fetch( disconMunkee );
					GameSpyCloseAllOverlays();
					GSMessageBoxOk( title, body );
					TheGameSpyInfo->reset();
					TheShell->pop();
				}
            break; // LORENZEN ADDED. SORRY IF THIS "BREAKS" IT...


			case PeerResponse::PEERRESPONSE_JOINGROUPROOM:
				/*
				if (resp.joinGroupRoom.ok)
				{
					TheGameSpyInfo->addText(UnicodeString(L"Joined group room"), GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
				}
				else
				{
					TheGameSpyInfo->addText(UnicodeString(L"Didn't join group room"), GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
				}
				*/
				break;
			case PeerResponse::PEERRESPONSE_PLAYERJOIN:
				{
					//UnicodeString str;
					//str.format(L"Player %hs joined the room", resp.nick.c_str());
					//TheGameSpyInfo->addText(str, GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
				}
				break;
			case PeerResponse::PEERRESPONSE_PLAYERLEFT:
				{
					//UnicodeString str;
					//str.format(L"Player %hs left the room", resp.nick.c_str());
					//TheGameSpyInfo->addText(str, GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
				}
				break;
			case PeerResponse::PEERRESPONSE_MESSAGE:
				{
					//UnicodeString m;
					//m.format(L"[%hs]: %ls", resp.nick.c_str(), resp.text.c_str());
					//TheGameSpyInfo->addText(m, GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
				}
				break;


// LORENZEN EXPRESSES DOUBT ABOUT THIS ONE, AS IT MAY HAVE SUFFERED MERGE MANGLING... SORRY
            // I THINK THIS IS THE OBSOLETE VERSION... SEE THE NEWER LOOKING ONE ABOVE
/*
  			case PeerResponse::PEERRESPONSE_DISCONNECT:
  				{
  					UnicodeString title, body;
  					AsciiString disconMunkee;
  					disconMunkee.format("GUI:GSDisconReason%d", resp.discon.reason);
   				title = TheGameText->fetch( "GUI:GSErrorTitle" );
  					body = TheGameText->fetch( disconMunkee );
  					GameSpyCloseAllOverlays();
  					GSMessageBoxOk( title, body );
  					TheGameSpyInfo->reset();
  					TheShell->pop();
  				}
*/



			case PeerResponse::PEERRESPONSE_CREATESTAGINGROOM:
				{
					if (resp.createStagingRoom.result == PEERJoinSuccess)
					{
						// Woohoo!  On to our next screen!
						UnicodeString str;
						str.format(L"Created staging room");
						TheGameSpyInfo->addText(str, GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
					}
					else
					{
						UnicodeString s;
						s.format(L"createStagingRoom result: %d", resp.createStagingRoom.result);
						TheGameSpyInfo->addText( s, GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow );
					}
				}
				break;
			case PeerResponse::PEERRESPONSE_JOINSTAGINGROOM:
				{
					if (resp.joinStagingRoom.ok == PEERTrue)
					{
						// Woohoo!  On to our next screen!
						UnicodeString s;
						s.format(L"joinStagingRoom result: %d", resp.joinStagingRoom.ok);
						TheGameSpyInfo->addText( s, GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow );
					}
					else
					{
						UnicodeString s;
						s.format(L"joinStagingRoom result: %d", resp.joinStagingRoom.ok);
						TheGameSpyInfo->addText( s, GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow );
					}
				}
				break;
			case PeerResponse::PEERRESPONSE_STAGINGROOM:
				{
					UnicodeString str;
					str.format(L"Staging room list callback", resp.nick.c_str());
					TheGameSpyInfo->addText(str, GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
				}
				break;
			case PeerResponse::PEERRESPONSE_QUICKMATCHSTATUS:
				{
					sawImportantMessage = TRUE;
					switch( resp.qmStatus.status )
					{
					case QM_IDLE:
						//TheGameSpyInfo->addText(UnicodeString(L"Status: QM_IDLE"), GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
						break;
					case QM_JOININGQMCHANNEL:
						TheGameSpyInfo->addText(TheGameText->fetch("QM:JOININGQMCHANNEL"), GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
						break;
					case QM_LOOKINGFORBOT:
						TheGameSpyInfo->addText(TheGameText->fetch("QM:LOOKINGFORBOT"), GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
						break;
					case QM_SENTINFO:
						TheGameSpyInfo->addText(TheGameText->fetch("QM:SENTINFO"), GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
						break;
					case QM_WORKING:
						{
							UnicodeString s;
							s.format(TheGameText->fetch("QM:WORKING"), resp.qmStatus.poolSize);
							TheGameSpyInfo->addText(s, GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
						}
						buttonWiden->winEnable( TRUE );
						break;
					case QM_POOLSIZE:
						{
							UnicodeString s;
							s.format(TheGameText->fetch("QM:POOLSIZE"), resp.qmStatus.poolSize);
							TheGameSpyInfo->addText(s, GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
						}
						break;
					case QM_WIDENINGSEARCH:
						TheGameSpyInfo->addText(TheGameText->fetch("QM:WIDENINGSEARCH"), GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
						buttonWiden->winEnable( FALSE );
						break;
					case QM_MATCHED:
						{
							TheGameSpyInfo->addText(TheGameText->fetch("QM:MATCHED"), GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
							buttonWiden->winEnable( FALSE );

							TheGameSpyGame->enterGame();
							TheGameSpyGame->setSeed(resp.qmStatus.seed);

							TheGameSpyGame->markGameAsQM();

							const LadderInfo *info = getLadderInfo();
							if (!info)
							{
								TheGameSpyGame->setLadderIP("localhost");
								TheGameSpyGame->setLadderPort(0);
							}
							else
							{
								TheGameSpyGame->setLadderIP(info->address);
								TheGameSpyGame->setLadderPort(info->port);
							}

							Int i;
							Int numPlayers = 0;
							for (i=0; i<MAX_SLOTS; ++i)
							{
								if (!resp.stagingRoomPlayerNames[i].empty())
									++numPlayers;
							}

							std::list<AsciiString> maps = TheGameSpyConfig->getQMMaps();
							for (std::list<AsciiString>::const_iterator it = maps.begin(); it != maps.end(); ++it)
							{
								AsciiString theMap = *it;
								theMap.toLower();
								const MapMetaData *md = TheMapCache->findMap(theMap);
								if (md && md->m_numPlayers >= numPlayers)
								{
									TheGameSpyGame->setMap(*it);
									if (resp.qmStatus.mapIdx-- == 0)
										break;
								}
							}

							Int numPlayersPerTeam = numPlayers/2;
							DEBUG_ASSERTCRASH(numPlayersPerTeam, ("0 players per team???"));
							if (!numPlayersPerTeam)
								numPlayersPerTeam = 1;

							for (i=0; i<MAX_SLOTS; ++i)
							{
								GameSpyGameSlot *slot = TheGameSpyGame->getGameSpySlot(i);
								if (resp.stagingRoomPlayerNames[i].empty())
								{
									slot->setState(SLOT_CLOSED);
								}
								else
								{
									AsciiString aName = resp.stagingRoomPlayerNames[i].c_str();
									UnicodeString uName;
									uName.translate(aName);
									slot->setState(SLOT_PLAYER, uName);
								slot->setIP(resp.qmStatus.IP[i]);
									slot->setColor(resp.qmStatus.color[i]);
									slot->setPlayerTemplate(resp.qmStatus.side[i]);
									//slot->setProfileID(0);
									slot->setNATBehavior((FirewallHelperClass::FirewallBehaviorType)resp.qmStatus.nat[i]);
									slot->setLocale("");
									slot->setTeamNumber( i/numPlayersPerTeam );
									if (i==0)
										TheGameSpyGame->setGameName(uName);
								}
							}

							DEBUG_LOG(("Starting a QM game: options=[%s]\n", GameInfoToAsciiString(TheGameSpyGame).str()));
							SendStatsToOtherPlayers(TheGameSpyGame);
							TheGameSpyGame->startGame(0);
							GameWindow *buttonBuddies = TheWindowManager->winGetWindowFromId(NULL, buttonBuddiesID);
							if (buttonBuddies)
								buttonBuddies->winEnable(FALSE);
							GameSpyCloseOverlay(GSOVERLAY_BUDDY);
						}
						break;
					case QM_INCHANNEL:
						TheGameSpyInfo->addText(TheGameText->fetch("QM:INCHANNEL"), GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
						break;
					case QM_NEGOTIATINGFIREWALLS:
						TheGameSpyInfo->addText(TheGameText->fetch("QM:NEGOTIATINGFIREWALLS"), GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
						break;
					case QM_STARTINGGAME:
						TheGameSpyInfo->addText(TheGameText->fetch("QM:STARTINGGAME"), GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
						break;
					case QM_COULDNOTFINDBOT:
						TheGameSpyInfo->addText(TheGameText->fetch("QM:COULDNOTFINDBOT"), GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
						buttonWiden->winEnable( FALSE );
						buttonStart->winHide( FALSE );
						buttonStop->winHide( TRUE );
						enableOptionsGadgets(TRUE);
						break;
					case QM_COULDNOTFINDCHANNEL:
						TheGameSpyInfo->addText(TheGameText->fetch("QM:COULDNOTFINDCHANNEL"), GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
						buttonWiden->winEnable( FALSE );
						buttonStart->winHide( FALSE );
						buttonStop->winHide( TRUE );
						enableOptionsGadgets(TRUE);
						break;
					case QM_COULDNOTNEGOTIATEFIREWALLS:
						TheGameSpyInfo->addText(TheGameText->fetch("QM:COULDNOTNEGOTIATEFIREWALLS"), GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
						buttonWiden->winEnable( FALSE );
						buttonStart->winHide( FALSE );
						buttonStop->winHide( TRUE );
						enableOptionsGadgets(TRUE);
						break;
					case QM_STOPPED:
						TheGameSpyInfo->addText(TheGameText->fetch("QM:STOPPED"), GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
						buttonWiden->winEnable( FALSE );
						buttonStart->winHide( FALSE );
						buttonStop->winHide( TRUE );
						enableOptionsGadgets(TRUE);
						break;
					}
				}
				break;
			}
		}
#ifdef PERF_TEST
		// check performance
		end = timeGetTime();
		UnsignedInt frameTime = end-start;
		if (frameTime > 100 || responses.size() > 20)
		{
			UnicodeString munkee;
			munkee.format(L"inQM:%d %d ms, %d messages", s_inQM, frameTime, responses.size());
			TheGameSpyInfo->addText(munkee, GameSpyColor[GSCOLOR_DEFAULT], quickmatchTextWindow);
			PERF_LOG(("%ls\n", munkee.str()));

			std::list<Int>::const_iterator it;
			for (it = responses.begin(); it != responses.end(); ++it)
			{
				PERF_LOG(("  %s\n", getMessageString(*it)));
			}
		}
#endif // PERF_TEST
	}
}// WOLQuickMatchMenuUpdate
