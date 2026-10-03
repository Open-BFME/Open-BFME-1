# Shell::push: canonical string declaration

RVA `0x00580080`, 164 bytes, `?push@Shell@@QAEXVAsciiString@@_N@Z`.
The old TU redefined AsciiString and its header despite the canonical
`game/Libraries/Source/WWVegas/WWLib/ascii_string.h`. AGENTS.md requires
“never redeclare a type a header already covers: #include it”.

The GeneralsMD twin is GameClient/GUI/Shell/Shell.cpp:264: the empty-name
check, optional GameSpy overlay shutdown, 16-screen limit, pending push
assignment, and top-layout shutdown match the existing BFME reconstruction.
This is header hygiene, not a new identity or a blanket claim that every
inherited type view or signature is canonical. No owner/member name changes.

Ghidra MCP VA `0x00980080` and the unpacked retail PE independently agree on
all 168 inspected bytes: the 164-byte body ends in RET8 at RVA `0x00580121`
through `0x00580123`, followed by INT3. The null-name guard at `0x0058009C`
and WORD length compare at `0x005800A8` witness the inlined string test.
Reuse StringBase.cpp's real `m_data == 0 || m_data->length == 0` definition
as a TU-local inline specialization. This is the same canonical-header
pattern already verified in isValidMap, not an invented pure callee.

`tools/callees.py` confirms the direct assignment and destructor calls:
`0x005800CF` -> StringBase<char>::set `0x00887C90`, and `0x0058010D` ->
releaseBuffer `0x00887940`. The unchanged other calls route through ILTs
`0x0000F5AB` -> `0x00627B90` and `0x00002F1D` -> `0x0057FD80`.
No new callee declaration or pin was introduced.

Fresh origin/master still contains the same row and old local declaration;
the bounded 12-second pickaxe scan expired without an output, so no exact
introduction date is asserted. The row survives in the August 1 cohort.
Before/after scoped gates pass 1/1 function and the one recorded DIR32
reference. No source body, byte extent, ledger, shared header, baseline or
coverage change beyond this verified declaration substitution.
Logs: `build/audit_v3/s6_shell_before.log`, `s6_shell_after.log`.
