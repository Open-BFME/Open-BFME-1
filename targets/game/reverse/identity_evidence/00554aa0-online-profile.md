# OnlineProfile population at 0x00554AA0

The independently matched `BfmeOnlineProfileScreen` constructor at 0x00557C00
calls ILT 0x00032849, which jumps directly to this entry. It passes the screen
in ECX. The body reads the base context at +0x34 and has a plain RET; no
explicit argument is consumed. The original method spelling is unknown, so
`BfmeOnlineProfileScreen::rva00554AA0` preserves the address. The context view
agrees with the constructor and matched base destructor's four string vectors.

The complete range is 00554AA0..00556F6C, 9420 bytes. RET is at 00556F58,
followed by three alignment bytes and the four-entry switch table at
00556F5C..00556F6B. INT3 padding follows. The existing generated row already
has this exact range. The read-only Ghidra project against the identical
retail executable confirms the entry, constructor xref and switch. A linear
callee scan of 9401 code bytes is complete; including the switch-table data
makes a generic linear decoder warn at +0x24CB, which is data, not a truncated
instruction. No boundary is shortened to avoid the table.

The body creates 20-byte QuickMatchPreferences, six localized faction/streak
labels, the local player name and a complete 0x1C4 PSPlayerStats snapshot.
The stats view is the independently recovered BFME layout already used by
WOLQuickMatchMenuUpdate.cpp and PopupPlayerInfo_responses.cpp. The reference
Zero Hour stats shim has different map and tail fields and is unsuitable.
GameSpy slot +0x68 returns AsciiString and +0x90 returns the complete stats
value; their hidden-return arguments are visible in the retail calls.
GameText slot +0x28 returns UnicodeString from a narrow label and bool pointer.

The implementation preserves the date parse/fallback, aggregate wins/losses,
overall streaks, favorite faction, ladder games and best ranks, all four level
labels/icons/next-level texts, faction wins/losses and current/best streaks.
It also preserves the preference write and literal `In Progress` disconnect
field. Canonical AsciiString, StringBase, UnicodeString and STLport types are
used. The min helper returns a const reference. SYSTEMTIME is zeroed with
memset before its witnessed field assignments. These details recover retail's
actual lifetimes and allocation, without padding locals or volatile stores.

The inlined STLport map/tree find specialization contains the same native
algorithm as stl/_tree.h. It exposes the real lookup through both wrapper
levels. The first seventeen searches inline; the last three use the small
independently verified helper below. Neither the main body nor helper contains
assembly, naked code, emitted bytes or a retail byte array.

## Bounded dependency repair: 0x005466C0

The final three integer-key searches need an out-of-line native definition.
At caller offsets +0x21DF, +0x2293 and +0x2347, retail calls ILT 0002EFCD.
The actual five-byte thunk jumps to 005466C0, independently decoded before
adding the pin. Its 71-byte body reads the sentinel/root from a 12-byte
STLport tree, compares signed integer keys at node+0x10, and returns an
iterator containing one node pointer. It has no calls. ECX is the tree;
stack arguments are the hidden iterator return address and const int pointer;
RET 8 closes both. It never reads the mapped value.

The existing real-source ledger row `dup_5466c0` in GameSpy/PeerDefs.cpp
already owns these 71 bytes as an integer-key tree-find template alias. Its
source independently corroborates the tree layout and return ABI. A native
`Rva005466C0Tree::find` definition using the canonical map, kept out of line,
compiles to all 71 retail bytes with ZERO relocations. Its address-derived
class does not assert a semantic owner or original template instantiation.

The existing address-derived `dup_5466c0` row is re-homed to this verified
71-byte definition beside its caller. The new name preserves 005466C0 and
its native source proves the ABI directly. This is an ownership and address-
retaining identity change, not a new byte claim. The normal resolver derives
ILT 0002EFCD from the existing body entry. No new symbols.csv pin or baseline
change is needed; one ledger row continues to own the same 71-byte range.
Pin consistency and route checks pass. The helper receives zero new credit.

The context cache call goes to independently matched 0055CD80 via 0003CC54.
That niladic cache routine ignores ECX. The typed address-derived view retains
the caller's observed context load without renaming the cache function.
Rank points (00022976 -> 004DA980) take stats pointer and side. Remaining
points (0000132F -> 005549C0) take a copied 0x1C4 stats value plus side; four
calls independently use PSPlayerStats copy construction at 006577D0. The
legacy Gen_uw declaration merging side into a larger value is not reused.
The image lookup through 000136A1 is used through its witnessed two-word
cdecl contract, without treating its old `void *ctx` spelling as evidence.

## Relocation and coverage audit

Final source: exact 9420-byte strict comparison, 580 relocations, 370 resolved
REL32 calls, zero unresolved calls. All 104 literal references independently
match their retail strings. DIR32 consistency passes for 13 external symbols,
zero whitelisted or new inconsistencies. The local switch labels target
0055513E, 00555144, 0055514B and 00555152 and the table at 00556F5C.

Independent data witnesses are:

- TheGameText VA012F147C, g_theWindowManager VA012F19E8 and TheGameSpyInfo
  VA012F7194 agree with their existing native GUI/network consumers and pins.
- Level icon pointers VA012B7B44/48/4C/50 agree with the matched OnlineProfile
  destructor and its four named component-image keys.
- Rank globals VA012B9660/64 agree with the existing PeerRequest construction
  at 0053AB90. The address-derived existing variable names are retained.
- Rank-band pointer VA012F401C agrees with matched 00553DF0 and the native
  online rank-progress sibling at 005578A0.
- StringBase's null wide character is VA0107388C, its independently established
  local static. sscanf's IAT is VA01359494 and is checked as an import.
- The EH handler and __except_list are compiler runtime references; all
  lifetime-state stores and cleanup call sites agree with retail.

Only the one generated 9420-byte body is converted. The generated ASM file is
left untouched. The helper was already native and adds zero credit.
