# 0x004781A0 is GameWindow::winGetCursorPosition

## Caller proof

`?openCandidateList@IMEManager@@IAEXH@Z` (0x0048DCA0, matched,
`game/GameEngine/Source/GameClient/GUI/IMEManager_openCandidateList.cpp`) is the
Zero Hour IMEManager::openCandidateList, whose source calls
`m_window->winGetCursorPosition(&wcursorx, &wcursory)` and then
`m_window->winGetFont()`. Its retail call at that site goes to ILT 0x0003FB11
(`tools/callees.py 0x48DCA0 303`), pinned in symbols.csv to
`?winGetCursorPosition@GameWindow@@QAEHPAH0@Z`.

## Stub proof

Retail bytes at 0x0003FB11 (`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`):
`E9 8A864300` -> 0x0003FB16 + 0x0043868A = 0x004781A0.

## Body proof

0x004781A0 (31 bytes) stores two Int fields (+0x24, +0x28) through optional
out pointers and returns 0 (WIN_ERR_OK): the ZH GameWindow::winGetCursorPosition
body (m_cursorX, m_cursorY). The previous row name `?get@Rva004781A0@@QAEHPAH0@Z`
was an opaque address-derived placeholder with no other references.
