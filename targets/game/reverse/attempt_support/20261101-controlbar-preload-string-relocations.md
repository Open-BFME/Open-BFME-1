# ControlBar preload: canonical string cleanup calls

Queue rank 20, key 0xF3E2008C; base BFME 1 66bc687f60. The existing
576-byte body at 0x004A2CB0 is retained without a source-body edit.

BFME 1 facts: the matched GameLogic caller loads TheControlBar and calls
ILT 0x2914. The complete 0x004A2CB0..0x004A2EF0 body calls narrow
StringBase::releaseBuffer at 0x887940 six times: relocation offsets 0x111,
0x143, 0x175, 0x1A9, 0x1DD and 0x229. Before this change all six object
relocations named ??1AsciiString@@QAE@XZ, whose ledger home is 0x5EE90.
That is a real destructor tail-jump, not an ILT stub: equal behavior does
not establish equal link identity. RetailTruth rejected all six references.
The old stringbaseascii shim only declares the destructor out of line.

Use existing WWLib ascii_string.h instead. Its inline empty derived
destructor and inline StringBase destructor call releaseBuffer directly.
The entire 576-byte body remains byte-exact, including constructors,
stack slots and branches. A fresh RetailTruth inspection reports zero body
differences and zero contradictory relocation destinations (wrong -> unknown).
No string header, pin, ledger identity or verifier policy changes.

Donor evidence: official submodule beed8a16790a6812231ac7b05e3e6893e4cb5d1b,
Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarPreloadButtonImages.cpp,
and sibling /home/yannick/projects/Open-BFME-2 at
597434797b5156afb8a4c500c56aea6194b4f434 (preload now merged into
Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp; merge
99c74babe2), both use the canonical ascii_string.h for the same side/radial
asset workflow. Their reference/shims/bfme2_ascii/ascii_string.h distinguishes
inline release from out-of-line destructor calls. These are semantic and
header-strategy leads only: donor +0x484/+0x6C template and +0x58 player
layouts do not apply to BFME 1's independently witnessed +0x38C/+0x28 fields.
No donor body, layout or address was copied. The newer fetched a49cde3c
reference update remains unverified and was not checked out or marked fresh.

Validation: normal scoped build 1/1, five string literals, nine DIR32 refs,
and body guard pass; find_declared_unmatched finds no missing rows. Current
link_check before/after is UNKNOWN, with no linked-byte gain claimed: the
available October 19 e9a5ae5b4c index predates the assigned afbe8bafb6 queue,
and more than 22,000 current ledger objects are unavailable here. fetch-index
cannot run because gh is absent. A current census/complete provider closure
is required to establish linking.
