// ?handleStartPositionSelection@@YAXHH@Z
// partial score=0.35 date=2026-09-07
// ?handleStartPositionSelection@@YAXHH@Z
// Partial source attempt for retail RVA 0x004F44E0 (497 bytes).
// The surrounding WOLGameSetupMenu.cpp declarations provide these BFME
// virtual layouts; this body is intentionally banked as a source hint, not a
// generated or inline-assembly lift.
// BFME's WOL update body keeps the map position in ECX and the player index
// as its one caller-cleaned stack argument.
__declspec(noinline) inline static void handleStartPositionSelection(int startPos, Int player)
{
	GameSpyStagingRoom *myGame = ((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->getCurrentStagingRoom();
	if (myGame)
	{
		GameSpyGameSlot *slot = myGame->getGameSpySlot(player);
		if (!slot)
			return;
		if (startPos == slot->getStartPos())
			return;
		Bool skip = FALSE;
		if (startPos < 0)
			skip = TRUE;
		if (!skip)
		{
			Bool isAvailable = TRUE;
			for (Int i = 0; i < MAX_SLOTS; ++i)
			{
				if (i != player && myGame->getSlot(i)->getStartPos() == startPos)
				{
					isAvailable = FALSE;
					break;
				}
			}
			if (!isAvailable)
				return;
		}
		slot->setStartPos(startPos);
		if (((BfmeVirtualStagingRoom *)myGame)->amIHost())
		{
			((BfmeVirtualStagingRoom *)myGame)->resetAccepted();
			((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->setGameOptions();
			WOLDisplaySlotList();
		}
		else if (AreSlotListUpdatesEnabled())
		{
			AsciiString options;
			options.format("StartPos=%d", slot->getStartPos());
			AsciiString hostName;
			hostName.translate(myGame->getSlot(0)->getName());
			PeerRequest req;
			req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
			req.UTM.isStagingRoom = TRUE;
			req.id = "REQ/";
			req.nick = hostName.str();
			req.options = options.str();
			TheGameSpyPeerMessageQueue->addRequest(req);
		}
	}
}
