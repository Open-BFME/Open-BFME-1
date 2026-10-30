# 0x000AF880 (4 B): AudioEventInfo +0x0C accessor, not GameSpyInfo::getMOTD

Old row: `?a_000af880@@YAXXZ`, a `gen-alias` placeholder whose object symbol is
`?getMOTD@GameSpyInfo@@UAEABVAsciiString@@XZ` from PeerDefs.cpp. That only
says the bytes (`lea eax,[ecx+0xC]; ret`) equal getMOTD's; getMOTD's own retail
body is the matched row at 0x006306B0, and retail has no identical-COMDAT
folding, so 0x000AF880 is a different function.

BFME 1 target evidence: retail AudioEventRTS::generateFilename 0x000B3970
loads `ecx = [esi+8]` (m_eventInfo) and calls ILT 0x00010E0B, which jumps to
0x000AF880, then concatenates the returned string onto m_filenameToLoad on the
music/streaming arm, the arm where Zero Hour's generateFilename appends
`m_eventInfo->m_filename`. It is the +0x0C sibling of the matched
`Rva000AF890::fieldAt40` at 0x000AF890 (weighted sounds at +0x40) called from
the same body. The owner type is not established, so the accessor keeps the
address-derived name `Rva000AF880::fieldAt0C` beside its siblings in
Rva000A33E0To000B51D0CarvedAccessors.cpp. Model: claude-opus-5-5, session 491.
