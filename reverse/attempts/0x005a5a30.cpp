// ?setCursor@Mouse@@UAEXW4MouseCursor@1@@Z
// partial score=0.98 date=2026-09-01
// BFME layout correction for Mouse::setCursor.  The body is otherwise the
// upstream implementation; only the two cursor-state fields moved in BFME.
struct BfmeMouseCursorState
{
	UnsignedByte pad[0x4da8];
	Mouse::MouseCursor currentCursor;
	DisplayString *cursorTextDisplayString;
};

void Mouse::setCursor( MouseCursor cursor )
{
	BfmeMouseCursorState *self = (BfmeMouseCursorState *)this;

	if( self->currentCursor == cursor )
		return;

	if( self->cursorTextDisplayString != NULL )
	{
		CursorInfo *cursorInfo = &m_cursorInfo[ cursor ];
		if( cursorInfo->cursorText.isEmpty() == FALSE )
			setMouseText( TheGameText->fetch( cursorInfo->cursorText.str() ),
										 &(cursorInfo->cursorTextColor),
										 &(cursorInfo->cursorTextDropColor) );
		else
			setMouseText( UnicodeString( L"" ), NULL, NULL );
	}
}
