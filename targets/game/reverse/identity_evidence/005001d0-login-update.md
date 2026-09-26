# WOLLoginMenuUpdate — 005001D0

Retail function lexicon RVA00EA9B70 contains
`{0, VA010868F8, VA0042CF07}`. The string is `WOLLoginMenuUpdate`, and
ILT0002CF07 (`E9 C4 32 4D 00`) reaches RVA005001D0. This independently
names the callback described in the reference FunctionLexicon and menu source.
The full 1693-byte body ends at RET +69C, followed by INT3 padding.

The caller uses the verified canonical AsciiString/UnicodeString bodies.
PeerResponse's 20-string prefix and 0x330 extent are independently proved by
PeerResponseCopies.cpp (copy426/assignment537) and the matched queue getResponse.
Its union begins at +F4. This body's accesses agree with the reference group-room
and player fields; player internal/external IP are at +118/+11C. No meanings
are assigned to the unrecovered remainder. PingResponse retains the reference
string and two integers, independently checked against its 20-byte stack slot.

The 32-byte GameSpyGroupRoom is independently proved by record copy004F97B0
and the matched GameSpyInfo addGroupRoom/map body006357D0. Name/translatedName
occupy +0/+4, followed by the five witnessed counters. The final +1C word
stays address-derived. The caller copies the full32-byte record by value.

The verified shutdownCompleteWOLLoginMenu helper is visible with its existing
native body from WOLLoginMenuShutdownThunk.cpp. This naturally emits the
private ESI parameter ABI observed in retail, without inline assembly or
an invented callable convention. Its existing ledger owner is unchanged.
WindowLayout hide at vtable+10 is independently established by VA010F7514,
ILT00008F1C and matched hide00497A00; a scoped view supplies the slot omitted
by the legacy GameWindow shim. Existing Shell, transition and preferences
headers supply their established declarations.

The original WOLLoginMenu.cpp remains unchanged as the existing owner of
verified response constructors/destructors, cleanup helpers and other siblings.
Only the naked UpdateThunk is removed. One main-body ledger row claims this
new native TU, with no new pin, shared header or identity baseline changes.

Verification: 1693/1693 bytes;108 aligned relocation sites;scoped gate1/1;
5 literals plus4 empty-string references verified, every direct callee resolved.
The first native experiment matched immediately after reading the verified
helper and response layouts. Model GPT-6; t=4 minutes (21:48–21:52 UTC).
