// ?handleColorSelection@@YAXH@Z
// partial score=0.82 date=2026-09-11
// Complete C++ body for retail 0x004F3F20, meant to replace the placeholder
// static handleColorSelection() already sitting (unclaimed) in
// Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp
// at its real production location. Drop this body in, in place, and add
// class BfmeMultiplayerSettingsView (below) plus name three existing
// BfmeVirtualGameSpyInfo placeholder slots (see notes).
//
// CONFIRMED FIXES over the previous 0.82 stash:
// - The function must NOT be `static`. Retail loads `index` from the
//   caller-pushed stack slot ([esp+0x1bc] at entry); marking it static in
//   this TU (single call site) makes MSVC 7.1 apply its private
//   register-passing convention for single-caller static functions (index
//   arrives in ECX, whole body reshuffles, body shrinks to 536B). Dropping
//   `static` recovers the correct stack-based ABI and reaches 541B, matching
//   this stash's ancestor. Confirmed by direct A/B probe.
// - BfmeMultiplayerSettingsView (below) reproduces retail's lazy getNumColors
//   layout exactly (fields at +0x34 / +0x3C), confirmed byte-exact against
//   the `mov ecx,[TheMultiplayerSettings]; mov edx,[ecx+0x3c]; test edx,edx;
//   lea eax,[ecx+0x3c]; jne ...; mov ecx,[ecx+0x34]; mov [eax],ecx` sequence.
//   Reuses the same layout already proven in
//   Code/GameEngine/Source/Common/promoted__getPreferredColor_CustomMatchPreferences_QAEHXZ_000AC2A0.cpp.
// - BfmeVirtualGameSpyInfo vtable slots confirmed by direct disassembly:
//   slot 0x68 = getLocalName() (AsciiString by value), slot 0xC0 = amIHost(),
//   slot 0xC4 = getCurrentStagingRoom() (already named), slot 0xCC =
//   setGameOptions(). Name these three placeholders in the TU-local class.
//
// RULED OUT / remaining gap (register-allocation shape wall, not semantic):
// After the `static` fix the body is byte-identical in shape to retail for
// every call, branch and callee (all 7 callees, all control flow, both early
// returns, the loop-with-break, the amIHost/else split) but is 19 bytes short
// (541 vs 560) purely from one register-role swap:
//   - Retail puts the `index` PARAMETER in EBP, and reuses EBP for the loop
//     counter `i` after index's last use (the first myGame->getSlot(index)
//     call). EBX is a single-purpose register holding only `slot`.
//   - Our compile puts `index` in EBX (reused for `slot` immediately after,
//     following the natural index-dies/slot-is-born dataflow edge instead),
//     and gives the loop counter `i` a *separate*, early-materialized EBP
//     (MSVC hoists `xor ebp,ebp` up to the null-check site and reuses it
//     there as a zero comparand instead of retail's plain `test edi,edi`).
//   This one swap cascades into every later byte: the null-check idiom
//   (`test reg,reg` vs `xor+cmp`), the SEH prologue's push/mov-fs order
//   (`push -1; mov eax,fs:[0]` in retail vs the reverse here), and a later
//   `push 0` (retail, 2 bytes) becoming `push ebp` (ours, 1 byte, since ebp
//   is wrongly known-zero on every path here, whereas retail's ebp is only
//   zero on the path that ran the loop).
// Tried and did not change the register assignment: reordering the local
// declarations of color/selIndex ahead of myGame/slot (declaration order
// already matches retail's evaluation order, so this lever from
// docs/shape_levers.md does not apply -- there is nothing left to reorder
// without changing statement order itself, which would move real
// instructions and diverge further). No missing statement, callee, or type
// was found; this is a plain MSVC 7.1 graph-coloring choice for which
// physical register absorbs `index`'s dead value once `slot` is born.
//
// callees confirmed: GadgetComboBoxGetSelectedPos, GadgetComboBoxGetItemData,
// TheGameSpyInfo->getCurrentStagingRoom (0xC4), GameSlot::getSlot(index)
// (thunk 0x0001EC18, called from GameInfo), GameSlot::getColor/setColor
// (inline field access at +0xC), TheMultiplayerSettings->getNumColors
// (BfmeMultiplayerSettingsView, fields +0x34/+0x3C), TheGameSpyInfo->amIHost
// (0xC0), TheGameSpyInfo->setGameOptions (0xCC), WOLDisplaySlotList (thunk
// 0x00006942), GameSlot::isPlayer(AsciiString) (thunk 0x0001F0EB),
// TheGameSpyInfo->getLocalName (0x68), AsciiString::format/translate/str,
// PeerRequest/TheGameSpyPeerMessageQueue->addRequest (thunk 0x0003A20B path).

void handleColorSelection(int index)
{
	GameWindow *combo = comboBoxColor[index];
	Int color, selIndex;
	GadgetComboBoxGetSelectedPos(combo, &selIndex);
	color = (Int)GadgetComboBoxGetItemData(combo, selIndex);

	GameInfo *myGame = ((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->getCurrentStagingRoom();
	if (!myGame)
		return;

	GameSlot *slot = myGame->getSlot(index);
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
		// send around a new slotlist
		((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->setGameOptions();
		WOLDisplaySlotList();
	}
	else
	{
		// request the color from the host
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

// class BfmeMultiplayerSettingsView (add near the file's other Bfme* view
// classes):
//
// class BfmeMultiplayerSettingsView
// {
// public:
// 	Int getNumColors( void )
// 	{
// 		if (m_numColors == 0)
// 			m_numColors = m_colorCount;
// 		return m_numColors;
// 	}
// private:
// 	unsigned char m_unreconstructed_00[0x34];
// 	Int m_colorCount;
// 	unsigned char m_unreconstructed_38[4];
// 	Int m_numColors;
// };
