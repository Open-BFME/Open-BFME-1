// ?winRepaint@GameWindowManager@@UAEXXZ
// partial score=0.56 date=2026-09-10
// Best semantic reconstruction of GameWindowManager::winRepaint.
// Retail boundary: 0x0047CCE0..0x0047CDB7 (215 bytes), selected through
// GameWindowManager vtable slot 36.  The failed compile showed that retail
// also filters each window on [window+0x1F4] == [manager+0x38]; the current
// source/header does not yet identify those fields, so this body preserves
// the named source behavior without inventing their identities.
void GameWindowManager::winRepaint( void )
{
	GameWindow *window, *next;

	for( window = m_windowTail; window; window = next )
	{
		next = window->m_prev;
		if( BitTest( window->m_status, WIN_STATUS_BELOW ) )
			drawWindow( window );
	}

	for( window = m_windowTail; window; window = next )
	{
		next = window->m_prev;
		if( BitTest( window->m_status, WIN_STATUS_ABOVE |
																				 WIN_STATUS_BELOW ) == FALSE )
			drawWindow( window );
	}

	for( window = m_windowTail; window; window = next )
	{
		next = window->m_prev;
		if( BitTest( window->m_status, WIN_STATUS_ABOVE ) )
			drawWindow( window );
	}

	if( TheTransitionHandler )
		TheTransitionHandler->draw();
}
