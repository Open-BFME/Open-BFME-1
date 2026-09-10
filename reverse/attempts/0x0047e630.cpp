// ?winProcessMouseEvent@GameWindowManager@@UAE?AW4WinInputReturnCode@@W4GameWindowMessage@@PAUICoord2D@@PAX@Z
// partial score=0.52 date=2026-09-10
WinInputReturnCode GameWindowManager::winProcessMouseEvent( GameWindowMessage msg,
																														ICoord2D *mousePos,
																														void *data )
{
	WinInputReturnCode returnCode = WIN_INPUT_NOT_USED;
	Bool objectTooltip = FALSE;
	UnsignedInt packedMouseCoords;
	GameWindow *window = NULL;
	GameWindow *toolTipWindow = NULL;
	GameWindow *childWindow;
	Int dx, dy;
	Bool clearGrabWindow = FALSE;

	// pack mouse coords into one entity for message passing
	packedMouseCoords = SHORTTOLONG( mousePos->x, mousePos->y );

	// clear tooltip ... it will be reset if necessary
	TheMouse->setCursorTooltip( UnicodeString::TheEmptyString );

	// Check for mouse capture
	if( m_mouseCaptor )
	{

		// no window grabbed as of yet
		m_grabWindow = NULL;

		// what what window within the captured window are we in
		window = m_mouseCaptor->winPointInChild( mousePos->x, mousePos->y );

		//
		// send buttons, drags, wheels to the windows, we don't continually
		// send mouse positions
		//
		if( sendMousePosMessages == TRUE || msg != GWM_MOUSE_POS )
		{
			GameWindow *win = window;

			if( win )
			{
				while( win != NULL )
				{

					if( winSendInputMsg( win, msg, packedMouseCoords, 0 ) == MSG_HANDLED )
					{

						// if used clear the event
						returnCode = WIN_INPUT_USED;
						break;

					}

					// if we just tested mouseCaptor don't go any higher in the chain
					if( win == m_mouseCaptor )
						break;

					win = win->winGetParent();

				}  // end while

			}  // end if
			else
			{

				// if used clear the event
				if(	winSendInputMsg( m_mouseCaptor, msg, packedMouseCoords, 0 ) == MSG_HANDLED )
					returnCode = WIN_INPUT_USED;

			}  // end else

		}  // end if

	}  // end if, mouse captor window present
	else
	{

		if( m_grabWindow )
		{
			GameWindow *parent;

			switch( msg )
			{

				// --------------------------------------------------------------------
				case GWM_LEFT_UP:
				{
					//Play a beep sound if the window is disabled.
					m_grabWindow->winPointInChild( mousePos->x, mousePos->y, FALSE, TRUE );

					BitClear( m_grabWindow->m_status, WIN_STATUS_ACTIVE );
					if( m_grabWindow->winPointInWindow( mousePos->x, mousePos->y ) )
						winSendInputMsg( m_grabWindow, GWM_LEFT_UP, packedMouseCoords, 0 );
					else if( BitTest( m_grabWindow->m_status, WIN_STATUS_DRAGABLE ))
					{
						winSendInputMsg( m_grabWindow, GWM_LEFT_UP, packedMouseCoords, 0 );
					}

					clearGrabWindow = TRUE;
					break;

				}  // end left up

				// --------------------------------------------------------------------
				case MOUSE_EVENT_NONE:
				case GWM_LEFT_DRAG:
				{

					if( BitTest( m_grabWindow->m_status, WIN_STATUS_DRAGABLE ) )
					{
						ICoord2D *mouseDelta = (ICoord2D *)data;
						dx = mouseDelta->x;
						dy = mouseDelta->y;

						// Clip window to parent
						if( m_grabWindow->winGetParent() )
						{

							parent = m_grabWindow->winGetParent();

							if( m_grabWindow->m_region.lo.x + dx < 0 )
								dx = 0 - m_grabWindow->m_region.lo.x;
							else if( m_grabWindow->m_region.hi.x + dx > parent->m_size.x )
								dx = parent->m_size.x - m_grabWindow->m_region.hi.x;

							if( m_grabWindow->m_region.lo.y + dy < 0 )
								dy = 0 - m_grabWindow->m_region.lo.y;
							else if( m_grabWindow->m_region.hi.y + dy > parent->m_size.y )
								dy = parent->m_size.y - m_grabWindow->m_region.hi.y;
						}

						// Move the window, but keep it completely visible within screen boundaries
						IRegion2D newRegion;
						ICoord2D grabSize;

						m_grabWindow->winGetPosition( &newRegion.lo.x, &newRegion.lo.y );
						m_grabWindow->winGetSize( &grabSize.x, &grabSize.y );

						newRegion.lo.x += dx;
						newRegion.lo.y += dy;
						if( newRegion.lo.x < 0 )
							newRegion.lo.x = 0;
						if( newRegion.lo.y < 0 )
							newRegion.lo.y = 0;
						
						newRegion.hi.x = newRegion.lo.x + grabSize.x;
						newRegion.hi.y = newRegion.lo.y + grabSize.y;
						if( newRegion.hi.x > (Int)TheDisplay->getWidth() )
							newRegion.hi.x = (Int)TheDisplay->getWidth();
						if( newRegion.hi.y > (Int)TheDisplay->getHeight() )
							newRegion.hi.y = (Int)TheDisplay->getHeight();
						
						newRegion.lo.x = newRegion.hi.x - grabSize.x;
						newRegion.lo.y = newRegion.hi.y - grabSize.y;

						m_grabWindow->winSetPosition( newRegion.lo.x, newRegion.lo.y );

					}  // end if, draggable window

					// Send mouse drag message
					winSendInputMsg( m_grabWindow, msg, packedMouseCoords, 0 );
					break;

				}  // end mouse event none or left drag

			}  // end switch

			// mark event handled
			returnCode = WIN_INPUT_USED;

		}  // end if, m_grabWindow
		else
		{

			if( m_modalHead && m_modalHead->window )
			{
				window = m_modalHead->window->winPointInChild( mousePos->x, mousePos->y );
			}
			else
			{
			
				/**@todo Colin, there are 3 cases here that are nearly identical code,
				break them up into functions with parameters */

				// search for top-level window which contains pointer
				for( window = m_windowList; window; window = window->m_next )
				{

					if( BitTest( window->m_status, WIN_STATUS_ABOVE ) &&
							!BitTest( window->m_status, WIN_STATUS_HIDDEN ) &&
							mousePos->x >= window->m_region.lo.x &&
							mousePos->x <= window->m_region.hi.x &&
							mousePos->y >= window->m_region.lo.y &&
							mousePos->y <= window->m_region.hi.y)
					{

						childWindow = window->winPointInAnyChild( mousePos->x, mousePos->y, TRUE, TRUE );
						if( toolTipWindow == NULL )
						{
							if( childWindow->m_tooltip || 
									childWindow->m_instData.getTooltipTextLength() )
							{
								toolTipWindow = childWindow;
							}
						}
						if( BitTest( window->m_status, WIN_STATUS_ENABLED ) )
						{
							// determine which child window the mouse is in
							window = window->winPointInChild( mousePos->x, mousePos->y );
							break;  // exit for
						}
						
					}  // end if

				}  // end for window

				// check !above, below and hidden
				if( window == NULL )
				{

					for( window = m_windowList; window; window = window->m_next )
					{

						if( !BitTest( window->m_status, WIN_STATUS_ABOVE | 
																						WIN_STATUS_BELOW | 
																						WIN_STATUS_HIDDEN ) &&
								mousePos->x >= window->m_region.lo.x &&
								mousePos->x <= window->m_region.hi.x &&
								mousePos->y >= window->m_region.lo.y &&
								mousePos->y <= window->m_region.hi.y)
						{

							childWindow = window->winPointInAnyChild( mousePos->x, mousePos->y, TRUE, TRUE );
							if( toolTipWindow == NULL )
							{
								if( childWindow->m_tooltip || 
										childWindow->m_instData.getTooltipTextLength() )
								{
									toolTipWindow = childWindow;
								}
							}
							if( BitTest( window->m_status, WIN_STATUS_ENABLED ))
							{								
								// determine which child window the mouse is in
								window = window->winPointInChild( mousePos->x, mousePos->y );
								break;  // exit for
							}
						}
					}
				}  // end if, window == NULL

				// check below and !hidden
				if( window == NULL )
				{

					for( window = m_windowList; window; window = window->m_next )
					{

						if( BitTest( window->m_status, WIN_STATUS_BELOW ) &&
								!BitTest( window->m_status, WIN_STATUS_HIDDEN ) &&
								mousePos->x >= window->m_region.lo.x &&
								mousePos->x <= window->m_region.hi.x &&
								mousePos->y >= window->m_region.lo.y &&
								mousePos->y <= window->m_region.hi.y)
						{

							childWindow = window->winPointInAnyChild( mousePos->x, mousePos->y, TRUE, TRUE );
							if( toolTipWindow == NULL )
							{
								if( childWindow->m_tooltip || 
										childWindow->m_instData.getTooltipTextLength() )
								{
									toolTipWindow = childWindow;
								}
							}
							if( BitTest( window->m_status, WIN_STATUS_ENABLED ))
							{
								// determine which child window the mouse is in
								window = window->winPointInChild( mousePos->x, mousePos->y );
								break;  // exit for
							}
						}
					}
				}  // end if

			}  // end else, no modal head

			if( window )
				if( BitTest( window->m_status, WIN_STATUS_NO_INPUT ) )
				{
					if(window->winGetParent() && BitTest( window->winGetParent()->winGetInstanceData()->getStyle(), GWS_COMBO_BOX ))
						window = window->winGetParent();
					else
						window = NULL;
				}

			if( window )
			{
				GameWindow *tempWin;

				//
				// only send messages for button states, wheel states, we do not
				// continually send messages for mouse positions
				//
				if( sendMousePosMessages == TRUE || msg != GWM_MOUSE_POS )
				{

					tempWin = window;
	
					// Give everyone a chance to do something with the clicks
					GameWindow *oldLoneWindow = m_loneWindow;
					while( winSendInputMsg( tempWin, msg, packedMouseCoords, 0 ) == MSG_IGNORED )
					{

						tempWin = tempWin->m_parent;
						if( tempWin == NULL )
							break;

					}  // end while

						
					// First check to see if m_loneWindow is set if so, close the window
					if( m_loneWindow && m_loneWindow == oldLoneWindow 
					&&( msg == GWM_LEFT_UP || msg == GWM_MIDDLE_UP || msg == GWM_RIGHT_UP || tempWin))
					{
						if(!m_loneWindow->winIsChild(tempWin))
							winSetLoneWindow( NULL );
						/*
								ComboBoxData *cData = (ComboBoxData *)m_comboBoxOpen->winGetUserData();
															// verify that the window that ate the message wasn't one of our own
															if(cData->dropDownButton != tempWin &&
																cData->editBox != tempWin &&
																cData->listBox != tempWin &&
																cData->listboxData->upButton != tempWin &&
																cData->listboxData->downButton != tempWin &&
																cData->listboxData->slider != tempWin &&
																cData->listboxData->slider != tempWin->winGetParent())
																	winSetOpenComboBoxWindow( NULL );*/
								
					}
					if( tempWin )
					{
					
						//
						// Someone cares, if this is a left button down event
						// it should get "grabbed"
						/// @todo should allow for left handed mouse configs here?
						//
						if( msg == GWM_LEFT_DOWN )
						{

//						if( tempWin != windowList ) 
//							WinActivate( tempWin );
							m_grabWindow = tempWin;

						}  // end if

						// event is used
						returnCode = WIN_INPUT_USED;

					}  // end if, tempWin

				}  // end if

			}  // end if( window ) 

			if( toolTipWindow == NULL )
			{

				if( isHidden( window ) == FALSE )
					toolTipWindow = window;

			}  // end if

			// if tooltips are on set them into the window
			Bool tooltipsOn = TRUE;
			if( tooltipsOn )
			{
//				if( toolTipWindow && toolTipWindow->winGetParent() && BitTest( toolTipWindow->winGetParent()->winGetInstanceData()->getStyle(), GWS_COMBO_BOX ))
//					toolTipWindow = toolTipWindow->winGetParent();
				if( toolTipWindow )
				{
					// do we have a callback to call for the tooltip
					if( toolTipWindow->m_tooltip )
						toolTipWindow->m_tooltip( toolTipWindow, 
																			&toolTipWindow->m_instData, 
																			packedMouseCoords );

					// else, do we have a normal tooltip to set
					else if( toolTipWindow->m_instData.getTooltipTextLength() )
						TheMouse->setCursorTooltip( toolTipWindow->m_instData.getTooltipText(), toolTipWindow->m_instData.m_tooltipDelay );

				}  // end if
				else
				{

					//
					// not pointing at a window... perhaps we are pointing at a valid
					// tooltip-able object in the game world ... let's set a flag so 
					// during the object testing we can set the tooltip, we can do
					// whatever we like now that we know no other tooltip was set from
					// a window
					//
					objectTooltip = TRUE;

				}  // end else

			}  // end if

		}  // end if grabWindow not present

	}  // end else (mouseCaptor) 

	//
	// check if new current window is different from the last
	// but only if both windows fall within the mouseCaptor if one exists
	//
	if( (m_grabWindow == NULL) && (window != m_currMouseRgn) )
	{
		if( m_mouseCaptor )
		{
			if( m_mouseCaptor->winIsChild( m_currMouseRgn ) )
				winSendInputMsg( m_currMouseRgn, GWM_MOUSE_LEAVING, packedMouseCoords, 0 );
		}
		else if( m_currMouseRgn )
			winSendInputMsg( m_currMouseRgn, GWM_MOUSE_LEAVING, packedMouseCoords, 0 );

		if( window )
			winSendInputMsg( window, GWM_MOUSE_ENTERING, packedMouseCoords, 0 );

		m_currMouseRgn = window;

	}  // end if

	// clear grabWindow if necessary
	if( clearGrabWindow == TRUE )
	{

		m_grabWindow = NULL;
		clearGrabWindow = FALSE;

	}  // end if

	return returnCode;

}  // end winProcessMouseEvent
