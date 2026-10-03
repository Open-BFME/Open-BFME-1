# 0053FC00 staging-room refresh

The full body is 622 bytes: RET at RVA 0053FE6D, followed by INT3.
Ghidra VA 0093FC00 was created and decompiled, then checked against raw retail.
The existing matched caller OnlineCustomMatchRefreshStagingList.cpp
(RVA 00544DD0) names BfmeAptScreenOnlineCustomMatch::applyStagingRoomRefresh
and calls it through ILT 00022999. Retain that existing binding, not a newly
inferred EA spelling. The sibling insertGame binding is already matched at
0053F210, reached through 0002E0FF.

## Shape repair

The served bank emits 637 bytes with 97 non-relocation differences. Retail
branches backward from +1EB to +170 when the two game dwords agree. Invert
that condition in source and place the enable call directly in its arm;
retain the shared disable call. This yields all 622 bytes, including argument
push scheduling and the backward branch. Shared inline setter experiments
(646/665 bytes) regressed and are not used. No barrier, volatile or assembly.

## Existing declarations and actual calls

The final TU includes the existing StagingRoomGameInfo and GameWindowManager
headers. GameSpyStagingRoom and GameWindowManager are not redeclared.
The first four listbox wrappers and the final two setters keep their existing
matched names and signatures. Native STLport owns the map and multiset.

The supplied GameSpy header has the ID at 41C but places the reported fields
elsewhere; it cannot establish semantic names for the raw dwords at 454/458.
The local accessors name offsets, not guessed members. Likewise the supplied
GameSpy interface places getStagingRoomList at an incompatible slot. A local
address-derived dispatch view models only the observed +98 call and its map
pointer result. The global keeps its existing GameSpyInfo pointer binding at
VA 012F7194. No header or shared layout changes are introduced.

The setup call is the already-matched MpGameSetup::bfmeSetSecondGame(GameInfo *)
at 00526040 via 00038951. Its complete139-byte body writes the pointer at
receiver+0C, uses the map accessor, and ends RET4 at 005260C8. The caller
passes its +40 receiver and the game pointer, or null. Replace the bank's
Gen00038951::handle(int) facade with that existing binding.

The bank's WindowManager::add facade also obscures an established contract.
The call through 00015235 reaches the matched BfmeLevelAN::bfmeBuildAN at
004675F0. Its full206-byte body uses an unsigned level, seven further dwords,
returns the shared buffer, and ends RET20 at 004676BB. The result is unused
here. Keep that existing name/signature and cast pointer-valued arguments to
its existing integer ABI. The host's +250 value is an unsigned level, not a
new claimed movie pointer. Its type and the screen's unproved fields retain
addresses or offsets. No new semantic helper/type name is asserted.

The ordinary build configuration inlines global new for the multiset header.
Retail instead calls the pool allocator at 0082E540. Enabling the existing
BFME_STLP_NODE_ALLOC configuration and stlp_nodealloc include shim reproduces
that call with the existing binding; no allocation pin was added. This is a
real relocation difference that the masked probe alone did not establish.

## Lifetimes and validation

The retail handler at C31C48 selects FuncInfo E21B48 and one unwind state:
state0 -> -1 at C31C40, adjusting the local receiver by EBP-18 and jumping
through449DFF to539E50. The native multiset supplies this one cleanup lifetime.
The normal path reaches the existing destructor route471DB ->539970.
No cleanup funclet or helper is newly claimed here.

Read-only standard build verification of the final scratch row passes all622
bytes and every relocation, three literal strings, four DIR32 data references,
and no floating constants. The literal contents are CallChild,
EnableButtonJoinGame and DisableButtonJoinGame. Source ledger promotion is
also checked by the normal add_match gate and commit hook.

## Bank-local names

The seven snapshot corrections are confined to unpromoted bank declarations.
No real ledger method, global binding, or callee identity is retired. In
particular, GameSpyInfo remains the global's existing pointer type: the
checker pairs its removed facade with the separate slot98 dispatch view.
That facade placed a semantic method at a slot contradicted by the supplied
interface header; the view deliberately claims only the actual call contract.
AptMovieHost and m_movie described a pointer-valued movie object, whereas the
actual matched callee accepts an unsigned level and branches on level <12.
The host view and +250 field now expose that independently checked ABI.
The source has no EA witness for the screen member spellings m_host,
m_setup, m_listbox or m_joinEnabled (name_oracle has no screen witness).
Their behavior is preserved, but experimental bank labels are not promoted
into new EA member identities: the source names proven offsets34/40/18C/1D4.
These changes follow the strict promotion rule; the existing matched caller
still supplies the entry and direct-callee names. Exact source hashes limit
all seven corrections to this conversion.
