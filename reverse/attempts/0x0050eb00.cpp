// attempt stash for ?removePlayer@DisconnectMenu@@QAEXHVUnicodeString@@@Z at 0x0050EB00
// partial score=0.8 date=2026-09-09
//
// This body lands in Code/GameEngine/Source/GameClient/AptScreenFactories.cpp,
// which already models DisconnectMenu (removePlayer forward-declared but never
// defined), WindowManager::bfme_setAptText (== the Rva00579160Manager/palantir
// bfmeStore family, singleton at 0x012F19E8), unidentified_00015235 (the "fire"
// 8-arg APT reporter), GadgetListBoxAddEntryText (already matched elsewhere at
// 0x004BB4B0 with the SAME 6-arg by-value-UnicodeString signature used here),
// and DisconnectMenu::setPlayerName (already matched, 292B, at 0x0050F6D0 --
// its body is >90% the same shape as this one and was the template).
//
// TWO required additions to that file, applied at the point noted:
//
// (1) UnicodeString needs a str() accessor (it doesn't have one yet); add
//     right after isEmpty() in the UnicodeString class body:
//
//         const unsigned short *str() const
//         {
//             return m_data ? (const unsigned short *)((char *)m_data + 8)
//                 : (const unsigned short *)0x0107388C;
//         }
//
//     (mirrors AsciiString::str() already in the file; 0x0107388C is
//     g_bfmeEmptyUnicode, read directly off retail at +0x00bd.)
//
// (2) A NEW global pin is needed and was added to reverse/symbols.csv:
//         ?g_bfmeChatColor@@3HA,0x00EB73F8,...
//     ZH's chatNormalColor is a file-static const (GameMakeColor(255,0,0,255))
//     that would compile to an immediate; retail instead reads a real global
//     dword at VA 0x012B73F8 (mov edx,[0x12b73f8]) for the listbox color, so
//     ZH's local const was promoted to a genuine BFME global.
//
// Then this definition, placed right before DisconnectMenu::setPlayerName:

extern int g_bfmeChatColor;			// retail 0x012B73F8

// ?removePlayer@DisconnectMenu@@QAEXHVUnicodeString@@@Z
// upstream: ZH DisconnectMenu::removePlayer calls hidePlayerControls(slot) then
// posts a "Network:PlayerLeftGame" chat line; BFME folds hidePlayerControls
// into the blank/non-blank halves of setPlayerName's shape (this+0x250 movie,
// this+0x258 ChatBox listbox, this+0x262 kick-button flags) and additionally
// resets the DisconnectScreen::VotesReceived%d apt property for the slot.
void DisconnectMenu::removePlayer( int slot, UnicodeString playerName )
{
	AsciiString variableName;
	char slotText[ 28 ];
	variableName.format( (AsciiString)"DisconnectScreen::PlayerName%d", slot );

	if( playerName.isEmpty() )
	{
		UnicodeString blank( L" " );
		g_theWindowManager->bfme_setAptText( variableName, blank );
	}
	else
	{
		g_theWindowManager->bfme_setAptText( variableName, playerName );

		if( *(GameWindow **)( (char *)this + 0x258 ) )
		{
			UnicodeString text;
			text.format( TheGameText->fetch( "Network:PlayerLeftGame" ), playerName.str() );
			GadgetListBoxAddEntryText( *(GameWindow **)( (char *)this + 0x258 ),
				text, g_bfmeChatColor, -1, -1, true );
		}
	}

	sprintf( slotText, "%d", slot );

	int movie = *(int *)( (char *)this + 0x250 );
	g_theWindowManager->unidentified_00015235(
		movie, "HideKickButton", 1, slotText,
		reinterpret_cast< const void * >( 0 ), 0, 0, 0 );
	*(char *)( (char *)this + 0x262 + slot ) = 0;

	variableName.format( (AsciiString)"DisconnectScreen::VotesReceived%d", slot );
	UnicodeString blank2( L" " );
	g_theWindowManager->bfme_setAptText( variableName, blank2 );
}

// STATUS: compiles clean and hits the EXACT target size (488/488 bytes).
// explain_mismatch shows only 8 diff lines left, ALL small (4-0x34 byte)
// stack-offset differences confined to the compiler-generated variadic
// argument-marker scratch slots that AsciiString::format(fmt, ...) and
// UnicodeString::format(fmt, ...) build internally (offsets 0x14-0x4c) --
// every call target, branch, and instruction COUNT already matches; this is
// pure stack-slot coloring, not a control-flow or identity problem.
//
// Specifically: retail allocates a genuinely separate 4-byte marker slot for
// the SECOND format() call's variadic arg-list (at retail-relative +0x1c,
// distinct from the first call's +0x18 -- see raw dump around VA 0x0050EC5C),
// while this version's second format() call (on the reused `variableName`)
// collapses onto the SAME slot as the first call's marker. Levers tried
// without success: reusing vs. NOT reusing `variableName` for the second
// format() key (NOT reusing costs 3 extra bytes elsewhere -- an explicit
// ~UnicodeString call appears instead of inlined releaseBuffer, needing a
// 491B target); wrapping the votes block in its own nested { } scope
// (regresses to the same 491B problem); varying char slotText[] from 16 to
// 32 (16..28 changes the GLOBAL frame size linearly and only 28 hits the
// exact prologue `sub esp,0x1c` retail uses -- confirmed necessary, not
// sufficient); inlining `int movie` at its use site (no effect on the gap).
//
// Next lever to try: the two format() calls likely need to be split across
// TWO distinct (but still same-named-type) locals whose live ranges the
// compiler is convinced do NOT overlap and do NOT need a shared destructor
// state slot -- e.g. giving the SECOND call's key its own throwaway block
// scope that ends before slotText/movie are used, rather than after (this
// attempt's failed nested-scope try put the block at the very end, after the
// fire()/mark-hidden work; try scoping tighter, immediately around just the
// second format()+bfmeStore pair with nothing else inside). t=110min model=sonnet-5.1
