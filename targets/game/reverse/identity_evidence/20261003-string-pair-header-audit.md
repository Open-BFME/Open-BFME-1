# Canonical string members in two existing destructors

Both StringInfo::~StringInfo (RVA004368F0/76B) and
GameSpyGroupRoom::~GameSpyGroupRoom (RVA004F9850/76B) locally redeclared
AsciiString and UnicodeString as opaque four-byte padding arrays. AGENTS.md
requires including a header when that header already covers the type. The
automatic adoption tool skips array-shaped declarations; that skip is a coverage
limit, not permission to retain these known duplicate string types.

Independent Capstone decoding of both complete retail functions shows the
UnicodeString receiver at this+4 calling StringBase<unsigned short>::releaseBuffer
at008881D0, followed by the original receiver calling
StringBase<char>::releaseBuffer at00887940. Ghidra read_memory independently
agrees with the77-byte StringInfo function-plus-padding window. The final RETs
are0043693B and004F989B, followed immediately byCC at0043693C/004F989C.

The cleanup ownership is independently established by the parent prologues:

| Parent | Handler | FuncInfo | State0 -> -1 action |
|---|---|---|---|
| 004368F0 | 00C221A8 | 00E124EC | 00C221A0 |
| 004F9850 | 00C2CEA8 | 00E1D028 | 00C2CEA0 |

Both actions load the saved receiver from EBP-10 and tail-jump through
ILT0000D828 to AsciiString::~AsciiString at0005EE90. No parent is inferred from
adjacency. This witnesses the remaining narrow-string lifetime during the
wide-string destructor call. The canonical headers preserve both normal and
exceptional cleanup paths.

Only the duplicate string declarations are replaced by ascii_string.h and
unicode_string.h; the existing owner declarations, members and names remain.
This is not a new identity claim or a claim that the local owner view describes
its entire object. GeneralsMD PeerDefs.h has the same initial narrow/wide pair;
GeneralsMD GameText.cpp's StringInfo additionally has a third speech member,
which is not present in these two witnessed BFME cleanup sequences. The upstream
layout alone must not be used to infer additional BFME fields.

The strict scoped gate passes all four existing rows: both76-byte destructors
and both8-byte actions. Compiler labels move from$L315 to$L1920, and the canonical
funclet verifier identifies the existing actions by bytes and parent group.
That automatic label healing is byte evidence, not a renamed funclet or added
coverage. No pin, ledger row, shared header or baseline changes.

Artifacts: build/audit_v3/s5_string_pair_build.log and the saved original source
snapshots named StringInfoDestructorThunk.cpp.before and
GameSpyGroupRoomDestructorThunk.cpp.before in that directory.
