# WOLLoginMenuInit — 00500A20

The retail function lexicon at RVA 00EA99E4 contains
`{0, VA01086C38, VA0040CAEA}`. The string is `WOLLoginMenuInit`, and
ILT0000CAEA (`E9 31 3F 4F 00`) reaches RVA00500A20. The reference
FunctionLexicon and WOLLoginMenu callback agree with this independent name.
The full 3164-byte body ends at RET +C5B, before INT3 padding.

The native body uses the canonical AsciiString and UnicodeString owners.
The independently verified GameSpyLoginPreferences constructor at 00082970
allocates the three maps within the 38-byte object and loads GameSpyLogin.ini
itself; the Zero Hour caller's extra load is absent from retail and omitted.
Its existing source documents the +14/+20/+2C map fields and 14-byte base.
No new callee declaration or pin is used for the constructor.

The pointer tab list reproduces the eleven 12-byte node allocations and
registerTabList/clearTabList operations. The mechanical EH search establishes
`_STLP_NO_EXCEPTIONS` for the STLport node-building path. The original TU's
`less<AsciiString>` specialization uses the native, visible comparison body;
its comparator visibility also removes the two spurious key-temporary unwind
states around map find. Email/nickname comparisons use that same canonical
`compare(...) == 0`, reproducing retail's inline length comparison and
REP CMPSB sequence. These are source-level comparisons, with no byte emits.

WindowLayout hide is virtual at +10 in retail. This is independent of the
new body: vtable VA010F7514 installs the slot at ILT00008F1C -> 00497A00,
and the existing `window_layout.h` and `window_layout.cpp` describe and match
that implementation. The legacy private shim visible through GameWindow
omits hide, so a TU-scoped address-derived interface supplies just this slot;
there is no shared-header edit or speculative member layout.

The original WOLLoginMenu.cpp is retained unchanged as the existing emitter
of legacy generated cleanup helpers and other claimed siblings. Its reference
Init is not credited as a second main body. Only the naked InitThunk file is
removed, and one main-body ledger row points to the native TU.

Verification: 3164/3164 bytes; 292 aligned relocation sites; scoped gate 1/1;
24 nonempty and 4 empty string references verified. Every call resolves
against existing identities. No symbols.csv pin or identity baseline changes.
Model: GPT-6. Work began 2026-09-26 21:40 UTC; exact at 21:46 UTC.
