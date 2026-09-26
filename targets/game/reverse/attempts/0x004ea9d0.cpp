// ?InitBuddyControls@@YAXH@Z
// partial score=0.58 date=2026-09-09
void InitBuddyControls( Int type )
{
	if(!TheGameSpyInfo)
	{
		buddyControls.textEntryEditID = NAMEKEY_INVALID;
		buddyControls.textEntryEdit = NULL;
		buddyControls.listboxBuddiesID = NAMEKEY_INVALID;
		buddyControls.listboxChatID = NAMEKEY_INVALID;
		buddyControls.listboxBuddies = NULL;
		buddyControls.listboxChat = NULL;
		buddyControls.isInit = FALSE;
		return;
	}
	switch (type)
	{
	case BUDDY_RESETALL_CRAP:
		buddyControls.textEntryEditID = NAMEKEY_INVALID;
		buddyControls.textEntryEdit = NULL;
		buddyControls.listboxBuddiesID = NAMEKEY_INVALID;
		buddyControls.listboxChatID = NAMEKEY_INVALID;
		buddyControls.listboxBuddies = NULL;
		buddyControls.listboxChat = NULL;
		buddyControls.isInit = FALSE;
		break;
	case BUDDY_WINDOW_BUDDIES:
		buddyControls.textEntryEditID = TheNameKeyGenerator->nameToKey( AsciiString( "WOLBuddyOverlay.wnd:TextEntryChat" ) );
		buddyControls.textEntryEdit = TheWindowManager->winGetWindowFromId(NULL, buddyControls.textEntryEditID);
		buddyControls.listboxBuddiesID = TheNameKeyGenerator->nameToKey( AsciiString( "WOLBuddyOverlay.wnd:ListboxBuddies" ) );
		buddyControls.listboxChatID = TheNameKeyGenerator->nameToKey( AsciiString( "WOLBuddyOverlay.wnd:ListboxBuddyChat" ) );
		buddyControls.listboxBuddies = TheWindowManager->winGetWindowFromId(NULL, buddyControls.listboxBuddiesID);
		buddyControls.listboxChat = TheWindowManager->winGetWindowFromId(NULL, buddyControls.listboxChatID);
		GadgetTextEntrySetText(buddyControls.textEntryEdit, UnicodeString::TheEmptyString);
		buddyControls.isInit = TRUE;
		break;
	case BUDDY_WINDOW_DIPLOMACY:
		buddyControls.textEntryEditID = TheNameKeyGenerator->nameToKey( AsciiString( "Diplomacy.wnd:TextEntryChat" ) );
		buddyControls.textEntryEdit = TheWindowManager->winGetWindowFromId(NULL, buddyControls.textEntryEditID);
		buddyControls.listboxBuddiesID = TheNameKeyGenerator->nameToKey( AsciiString( "Diplomacy.wnd:ListboxBuddies" ) );
		buddyControls.listboxChatID = TheNameKeyGenerator->nameToKey( AsciiString( "Diplomacy.wnd:ListboxBuddyChat" ) );
		buddyControls.listboxBuddies = TheWindowManager->winGetWindowFromId(NULL, buddyControls.listboxBuddiesID);
		buddyControls.listboxChat = TheWindowManager->winGetWindowFromId(NULL, buddyControls.listboxChatID);
		GadgetTextEntrySetText(buddyControls.textEntryEdit, UnicodeString::TheEmptyString);
		buddyControls.isInit = TRUE;
		break;
	case BUDDY_WINDOW_WELCOME_SCREEN:
		break;
	default:
		DEBUG_ASSERTCRASH(FALSE, ("Well, you really shouldn't have gotten here, if you really care about GUI Bugs, search for this string, you you don't care, call chris (who probably doesn't care either"));
	}
}
