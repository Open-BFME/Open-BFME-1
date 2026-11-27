# Existing owning-handle forwarder: one link repair

One native link-near source task in `game/GameEngine/Source/Common/BfmeConv1993.cpp`: existing 133B main at 0x008931A0 plus
its existing 25B returned-object cleanup at 0x00C56D28. Both original ranges remain
unchanged. No new exact body bytes, library coverage or game-runtime result.

The obsolete sixteen-byte return stand-in forced an undefined destructor and
builder spelling. The independently owned 274B builder writes a single counted
pointer into hidden return storage and uses RET8. Its 115B lookup context and
the existing 35B destructor establish the reused one-pointer owner model. The
parent passes its hidden result unchanged; its cleanup tests/clears mask `1`
(bit0), loads [EBP+4], and jumps via ILT0x000463AD to 0x00784A70. The tracked identity
evidence records the complete targets and both old/new decorated identities.
Existing provider constructor prototypes are declarations only; no EA class or
method name, unused ABI contract or additional constructor body is recovered.
No canonical RefHandle header exists here; the current provider view is reused.

The previously recorded typedef attempt failed because it preserved the wrong
main identity. This session did not repeat it. A prerequisite from the already
reviewed isolated writer commit was integrated as 5ffd60c384: only tools/tests/
tracked evidence, no parked Node13/game sources. Its baseline was byte-identical
to this checkout. All 74 direct identity/parent/refusal regression tests pass
freshly, including exact-token exclusion, wrong source/range, ambiguity,
nonfunclets, no-verify refusal and full rollback. The normal admission then
retired the wrong main identity and atomically retargeted exactly one existing
funclet parent. Compiler label $L368 remains genuinely proven unique; no manual
label or ledger edit, guard override, alias or new pin was used.

Normal whole-source byte gate: 2/2, all 158 existing target bytes retained, 2 DIR32
references, no body findings. FDU is clear. Both unchanged real providers also
pass their existing current normal rows (35B destructor; 274B builder plus 25B
cleanup). The actual normal control/after objects have identical complete
runtime and FPO bytes, section sizes/flags, relocation offsets/kinds, weak and
COMDAT facts, CRT/SafeSEH/default libraries and defined/undefined graph except
the corrected parent identity and its two independently proved callee names.
No new helper, constructor/destructor or vtable is emitted. Native compiler
command fingerprint and include dependencies are identical. Comparison-only
name mapping never enters the native resolver or a gate.

Before, normal link_check reported only the two absent old names, UNLINKED0→0.
After, normal link_check reports LINKS0→133B, 1/1 clean. This is a current per-file
preview using local index 42237e2367, not a new full-image census. Official
Nov23 game LINKING remains 3,022,503B/35.57% at 470a2979bf until a new census.

Historical BFME2 donor was safely refreshed from 1e864b34e0 to official archived
master e2e9995995, with the previous checkout/history preserved. Its selected
Bfme5ThirtyFour.cpp and recipes are unchanged. The one regular native refresh
scanned 53,315 bodies and 790,847 placements; all native input fingerprints were
validated before admission. No source from the active BFME2-Rebuild successor,
donor address, 28B payload layout, nested include or compiler override was
imported. BFME1 target evidence selects the existing 24B payload and four-byte
handle model. The verified donor pointer is included in this commit.
The later intended target-ledger identity change invalidates that discovery
cache for future transfers; it was not reused stale to admit this repair.

Source baseline is 83661bbe3aedea497f83968cbb6ba7de1329401f; master was merged normally as bb4ab07283, preserving
published PR history and the unrelated parked local 048592 branch. A native
incidental hatch-baseline sort was undone only after exact line-byte multiset
equality was proved; no allowance/count changed. Diagnostic evidence includes
the original normal objects, complete target decodes, input/claim fences and
reproducible drivers under W:/OpenBFME/diagnostics/one-per-project-20261124/bfme1.

Recheck with normal build.cmd on this source, eh_state_pins.py --source,
find_declared_unmatched.py and link_check.py. Direct writer regressions are
tools/tests/test_add_match_supersede.py. Compact immutable proof/hashes are in
targets/game/reverse/attempt_support/20261124-owning-handle-forwarder-proof.json. Progress against origin/master and the session baseline is recorded
after the normal commit. One source task; the writer prerequisite is zero
additional body credit. No crash/memory/FPS/runtime improvement is claimed.
