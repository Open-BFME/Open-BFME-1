// ?updateVotes@DisconnectMenu@@QAEXHH@Z
// partial score=0.98 date=2026-09-02
// Near-miss body for 0x0050EFB0 (198B): DisconnectMenu::updateVotes(int, int).
// Identity is proven: format literal 0x01104E2C "DisconnectScreen::VotesReceived%d",
// wide literals 0x01084C34 L" " and 0x010F9F60 L"%d", callee set
// {AsciiString ctor 0x00888BC0, AsciiString::format 0x00888FF0, UnicodeString ctor
// 0x00888DE0, UnicodeString::format 0x00889190, bfme_setAptText via ILT 0x0000BDCA,
// ~UnicodeString 0x008881D0, ~AsciiString 0x00887940}, and the reference source
// Generals DisconnectMenu::updateVotes(Int slot, Int votes).
//
// Destination: Code/GameEngine/Source/GameClient/AptScreenFactories.cpp (home of
// setPlayerName/setPlayerTimeoutTime).  Needed edits there:
//   - UnicodeString class: add `void format( UnicodeString format, ... );`
//   - DisconnectMenu class: add `void updateVotes( int slot, int votes );`
//   - body below.
//
// 196 of 198 bytes match.  The only diff is the documented EH-temporary
// transposition (docs/lessons.md) at the SECOND by-value call site:
//   retail: 89 64 24 20 8b cc   (mov [esp+0x20],esp ; mov ecx,esp)
//   ours:   8b cc 89 64 24 20
// Both call sites in setPlayerTimeoutTime and the first site here compile in
// retail order because an EH-state store is co-scheduled inside the ctor-call
// sequence; site 2 has no state store (state already 1 before the branch) and
// the toolchain then emits mov-ecx first.  Tried and failed: C-cast /
// functional-cast / static_cast / implicit conversion for the format temp,
// votes!=0 / !!votes / (unsigned)votes / braced / ternary control flow, and
// per-function #pragma optimize "s"/"t"/"a"/"w" ("s" changes the whole shape).

void DisconnectMenu::updateVotes( int slot, int votes )
{
	AsciiString variableName;
	variableName.format( (AsciiString)"DisconnectScreen::VotesReceived%d", slot );

	UnicodeString text( L" " );
	if( votes )
		text.format( (UnicodeString)L"%d", votes );

	g_theWindowManager->bfme_setAptText( variableName, text );
}
