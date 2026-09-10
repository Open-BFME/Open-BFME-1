// ?showNotificationBox@@YAXVAsciiString@@VUnicodeString@@@Z
// partial score=0.2 date=2026-09-10
// Focused research bank for the failed clean-C++ repoint of 0x004ECD10.
// This is the complete function body copied from the canonical
// WOLBuddyOverlay.cpp definition; its surrounding TU supplies the declarations.
// It is not a production source file and defines no fallback helpers.

void showNotificationBox( AsciiString nick, UnicodeString message)
{
	// if(!GameSpyIsOverlayOpen(GSOVERLAY_BUDDY))
	// 	return;
	if( !noticeLayout )
		noticeLayout = TheWindowManager->winCreateLayout( "Menus/PopupBuddyListNotification.wnd" );
	((BfmeVirtualHideLayout *)noticeLayout)->hide( FALSE );
	if (buttonNotificationID == NAMEKEY_INVALID)
	{
		buttonNotificationID = TheNameKeyGenerator->nameToKey("PopupBuddyListNotification.wnd:ButtonNotification");
	}
	GameWindow *win = TheWindowManager->winGetWindowFromId(NULL,buttonNotificationID);
	if(!win)
	{
		deleteNotificationBox();
		return;
	}

	if (lastNotificationWasStatus && numOnlineInNotification > 1)
	{
		message = TheGameText->fetch("Buddy:MultipleOnlineNotification");
	}

	if (nick.isNotEmpty())
		message.format(message, nick.str());
	GadgetButtonSetText(win, message);
	// GadgetStaticTextSetText(win, message);
	noticeExpires = timeGetTime() + NOTIFICATION_EXPIRES;
	noticeLayout->bringForward();

	AudioEventRTS buttonClick("GUICommunicatorIncoming");

	if( TheAudio )
	{
		TheAudio->addAudioEvent( &buttonClick );
	}
}
