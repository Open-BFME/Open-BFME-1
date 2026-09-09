// ?WOLBuddyOverlayInit@@YAXPAVWindowLayout@@PAX@Z
// partial score=0.48 date=2026-09-09
void WOLBuddyOverlayInit( WindowLayout *layout, void *userData )
{
	parentID = TheNameKeyGenerator->nameToKey( AsciiString( "WOLBuddyOverlay.wnd:BuddyMenuParent" ) );
	buttonHideID = TheNameKeyGenerator->nameToKey( AsciiString( "WOLBuddyOverlay.wnd:ButtonHide" ) );
	buttonAddBuddyID = TheNameKeyGenerator->nameToKey( AsciiString( "WOLBuddyOverlay.wnd:ButtonAdd" ) );
	buttonDeleteBuddyID = TheNameKeyGenerator->nameToKey( AsciiString( "WOLBuddyOverlay.wnd:ButtonDelete" ) );
	buttonAcceptBuddyID = TheNameKeyGenerator->nameToKey( AsciiString( "WOLBuddyOverlay.wnd:ButtonYes" ) );
	buttonDenyBuddyID = TheNameKeyGenerator->nameToKey( AsciiString( "WOLBuddyOverlay.wnd:ButtonNo" ) );
	radioButtonBuddiesID = TheNameKeyGenerator->nameToKey( AsciiString( "WOLBuddyOverlay.wnd:RadioButtonBuddies" ) );
	radioButtonIgnoreID = TheNameKeyGenerator->nameToKey( AsciiString( "WOLBuddyOverlay.wnd:RadioButtonIgnore" ) );
	parentBuddiesID = TheNameKeyGenerator->nameToKey( AsciiString( "WOLBuddyOverlay.wnd:BuddiesParent" ) );
	parentIgnoreID = TheNameKeyGenerator->nameToKey( AsciiString( "WOLBuddyOverlay.wnd:IgnoreParent" ) );
	listboxIgnoreID = TheNameKeyGenerator->nameToKey( AsciiString( "WOLBuddyOverlay.wnd:ListboxIgnore" ) );

	parent = TheWindowManager->winGetWindowFromId( NULL, parentID );
	buttonHide = TheWindowManager->winGetWindowFromId( parent, buttonHideID );
	buttonAddBuddy = TheWindowManager->winGetWindowFromId( parent, buttonAddBuddyID );
	buttonDeleteBuddy = TheWindowManager->winGetWindowFromId( parent, buttonDeleteBuddyID );
	buttonAcceptBuddy = TheWindowManager->winGetWindowFromId( parent, buttonAcceptBuddyID );
	buttonDenyBuddy = TheWindowManager->winGetWindowFromId( parent, buttonDenyBuddyID );
	radioButtonBuddies = TheWindowManager->winGetWindowFromId( parent, radioButtonBuddiesID );
	radioButtonIgnore = TheWindowManager->winGetWindowFromId( parent, radioButtonIgnoreID );
	parentBuddies = TheWindowManager->winGetWindowFromId( parent, parentBuddiesID );
	parentIgnore = TheWindowManager->winGetWindowFromId( parent, parentIgnoreID );
	listboxIgnore = TheWindowManager->winGetWindowFromId( parent, listboxIgnoreID );

	InitBuddyControls(BUDDY_WINDOW_BUDDIES);
	GadgetRadioSetSelection(radioButtonBuddies, FALSE);
	parentBuddies->winHide(FALSE);
	parentIgnore->winHide(TRUE);
	PopulateOldBuddyMessages();
	((BfmeVirtualHideLayout *)layout)->hide( FALSE );
	TheWindowManager->winSetFocus( parent );
	isOverlayActive = true;
	updateBuddyInfo();
} // WOLBuddyOverlayInit
