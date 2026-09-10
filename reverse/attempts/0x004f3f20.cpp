// ?handleColorSelection@@YAXH@Z
// partial score=0.82 date=2026-09-10
// Complete C++ body attempted for retail 0x004F3F20.
// Production context: Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp
// The surrounding TU supplies the game types, globals, and BFME layout views.
__declspec(noinline) void handleColorSelection(int index)
{
	GameWindow *combo = comboBoxColor[index];
	Int color, selIndex;
	GadgetComboBoxGetSelectedPos(combo, &selIndex);
	color = (Int)GadgetComboBoxGetItemData(combo, selIndex);

	GameInfo *myGame = ((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->getCurrentStagingRoom();
	if (!myGame)
		return;

	GameSlot * slot = myGame->getSlot(index);
	if (color == slot->getColor())
		return;

	if (color >= -1 && color < ((BfmeMultiplayerSettingsView *)TheMultiplayerSettings)->getNumColors())
	{
		Bool colorAvailable = TRUE;
		if(color != -1 )
		{
			for(Int i=0; i <MAX_SLOTS; i++)
			{
				GameSlot *checkSlot = myGame->getSlot(i);
				if(color == checkSlot->getColor() && slot != checkSlot)
				{
					colorAvailable = FALSE;
					break;
				}
			}
		}
		if(!colorAvailable)
			return;
	}

	slot->setColor(color);

	if (((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->amIHost())
	{
		((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->setGameOptions();
		WOLDisplaySlotList();
	}
	else
	{
		if (!slot->isPlayer(((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->getLocalName()))
			return;

		AsciiString options;
		options.format("Color=%d", color);
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
