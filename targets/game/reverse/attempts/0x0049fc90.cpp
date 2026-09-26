// ?setControlBarSchemeByPlayerTemplate@ControlBar@@QAEXPBVPlayerTemplate@@@Z
// partial score=0.35 date=2026-09-10
// Complete source-twin body banked after the first BFME ABI/layout probe.
void ControlBar::setControlBarSchemeByPlayerTemplate( const PlayerTemplate *pt)
{
	if(m_controlBarSchemeManager)
		m_controlBarSchemeManager->setControlBarSchemeByPlayerTemplate(pt);

	static NameKeyType buttonPlaceBeaconID = NAMEKEY( "ControlBar.wnd:ButtonPlaceBeacon" );
	static NameKeyType buttonIdleWorkerID = NAMEKEY("ControlBar.wnd:ButtonIdleWorker");
	static NameKeyType buttonGeneralID = NAMEKEY("ControlBar.wnd:ButtonGeneral");
	GameWindow *buttonPlaceBeacon = TheWindowManager->winGetWindowFromId( NULL, buttonPlaceBeaconID );
	GameWindow *buttonIdleWorker = TheWindowManager->winGetWindowFromId( NULL, buttonIdleWorkerID );
	GameWindow *buttonGeneral = TheWindowManager->winGetWindowFromId( NULL, buttonGeneralID );

	if(pt == ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey("FactionObserver")))
	{
		m_isObserverCommandBar = TRUE;
		switchToContext( CB_CONTEXT_OBSERVER_LIST, NULL );
		DEBUG_LOG(("We're loading the Observer Command Bar\n"));

		if (buttonPlaceBeacon)
			buttonPlaceBeacon->winHide(TRUE);
		if (buttonIdleWorker)
			buttonIdleWorker->winHide(TRUE);
		if (buttonGeneral)
			buttonGeneral->winEnable(FALSE);
	}
	else
	{
		switchToContext( CB_CONTEXT_NONE, NULL );
		m_isObserverCommandBar = FALSE;

		if (buttonPlaceBeacon)
			buttonPlaceBeacon->winHide(
			(TheGameLogic->getGameMode() != GAME_LAN && TheGameLogic->getGameMode() != GAME_INTERNET) ||
			!TheGameInfo->isMultiPlayer());
		if (buttonIdleWorker)
			buttonIdleWorker->winHide(FALSE);
		if (buttonGeneral)
		{
			buttonGeneral->winHide(FALSE);
			buttonGeneral->winEnable(TRUE);
		}
	}
	switchControlBarStage(CONTROL_BAR_STAGE_DEFAULT);

	hidePurchaseScience();
}
