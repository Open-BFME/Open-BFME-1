// ?d_004cd820@@YAXXZ
// partial score=0.949 date=2026-09-26
// Partial reconstruction bank for retail 0x004CD820.
// The declarations and caller live in LanGameOptionsMenu.cpp.
static void rva004CD820(register int index)
{
	GameWindow *combo = comboBoxPlayerTemplate[index];
	register Int playerTemplate;
	Int selIndex;
	GadgetComboBoxGetSelectedPos(combo, &selIndex);
	playerTemplate = (Int)GadgetComboBoxGetItemData(combo, selIndex);
	LANGameInfo *myGame = ((BfmePlayerTemplateLANAPI *)TheLAN)->GetMyGame();

	if (myGame)
	{
		Rva0068D3E0Slot *slot = ((Rva0068D3E0Arr *)myGame)->at(index);
		if (playerTemplate == slot->getPlayerTemplate())
			return;

		Int oldTemplate = slot->getPlayerTemplate();
		slot->setPlayerTemplate(playerTemplate);

		if (oldTemplate == PLAYERTEMPLATE_OBSERVER)
		{
			GadgetComboBoxSetSelectedPos(comboBoxColor[index], 0);
			GadgetComboBoxSetSelectedPos(comboBoxTeam[index], 0);
			slot->setStartPos(-1);
		}
		else if (playerTemplate == PLAYERTEMPLATE_OBSERVER)
		{
			GadgetComboBoxSetSelectedPos(comboBoxColor[index], 0);
			GadgetComboBoxSetSelectedPos(comboBoxTeam[index], 0);
			slot->setStartPos(-1);
		}

		((BfmePlayerTemplateGameInfo *)myGame)->resetAccepted();
		if (((BfmeThing935B *)myGame)->bfmeGo935B())
		{
			if (!s_isIniting)
			{
				BfmePlayerTemplateAddress address;
				((BfmePlayerTemplateLANAPI *)TheLAN)->requestSerializedGameInfo(TRUE, &address);
				rva004CAF70();
			}
		}
		else if (AreSlotListUpdatesEnabled())
		{
			BFMERetailAsciiString options;
			((AsciiString *)&options)->format(AsciiString("PlayerTemplate=%d"), playerTemplate);
			((BfmePlayerTemplateLANAPI *)TheLAN)->RequestGameOptions(options, TRUE);
		}

		if (slot->getStartPos() >= 0 &&
			!((Rva004CD5F0GameInfo *)myGame)->rva004CD5F0(index))
			rva004CB810StartPosition(index, -1);
	}
}
