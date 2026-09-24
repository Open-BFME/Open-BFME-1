# The false Drawable route through 0x0001C8D2

## Confirmed retail evidence

The matched 15-byte row at `0x00527200` is compiled from the Zero Hour
`Drawable::clearModelConditionState` inline wrapper. Its retail bytes push the
incoming argument and `-1`, call ILT `0x0001C8D2`, and return. Those bytes and
the call relocation prove the forwarding *shape*, not the Drawable identity.
The five-byte ILT jumps to `0x00526660`. Its prior C++ source names a Drawable
method and jumps to a locally invented shim pinned to `0x00526660`; the pin
therefore cannot independently corroborate that name.

The `0x00526660` body saves its original `this` in ESI, then at offset `+0x7F`
passes the same receiver in ECX to ILT `0x0003AA67`. Retail decodes that ILT
to the separately matched `MpGameSetup::bfmeGetStartPositionInfo` at
`0x00525F80`. The body also uses `this+4`, `+8`, `+0xC`, the eight-slot arrays
at `+0x88`, `+0xA8`, and `+0xC8`, and the mode flag at `+0x124`. These match
the independently reconstructed multiplayer setup view in
`MpGameSetup.cpp`, not Drawable's witnessed layout. The exact dynamic owner
could still be a derived screen class, so the replacement should retain an
address token in its class and method names. Retail's `ret 8` starts at
`0x00526868` and ends at `0x0052686B`: the complete extent is 523 bytes,
while the Ghidra inventory and derived
`reloc_names.csv` entry report 518. The inventory records the Ghidra-owned
address count, which need not equal a contiguous retail extent; tracked
`reverse/carved.csv` independently records 523 for this body. Keep both facts
distinct. No body at `0x00526660` is claimed as matched by this correction.

The current relocation harvester sees the falsely named 15-byte wrapper as a
byte-true caller, follows its call through the ILT, and publishes a Drawable
candidate for `0x00526660` with `identity=real`. This is a provenance error
propagating from the two matched labels; hiding only the candidate would
leave both labels and the bad pin in place.

## Proposed correction and pre-implementation review gate

Replace the 5-byte claim with an address-derived
`Rva0001C8D2Thunk::forward(int,int)` thiscall thunk, and the 15-byte claim
with `Rva00527200Owner::rva00527200(int)`. Each name retains its own address
token, and the wrapper preserves the same receiver and argument stack across
the ILT. A scratch C++
translation unit probes at 5/5 and 15/15 bytes, each with one aligned
relocation and no non-relocation differences. The 5-byte matched row resolves
the wrapper's call without a second alias pin; pin only the opaque forwarding
shim directly to the observed body at `0x00526660`. Use two
`add_match.py --correct-identity` transactions with this evidence, remove the
old Drawable and shim pins, and regenerate the derived naming file.

This preserves the two verified byte ranges without claiming the 523-byte
body or asserting a semantic class name. A plain `?j_0001c8d2@@YAXXZ` thunk
would require a separately pinned typed method alias at the stub for the
15-byte thiscall wrapper. Pin consistency cannot validate a `route=` for that
alias without a same-name matched body at `0x00526660`, and omitting the route
would hide the fact that the name resolves through a stub. The typed but
address-derived five-byte claim avoids that conflict. Merely deleting the
derived queue row would leave the false matched claims; naming the replacement
`MpGameSetup` would assert more than the same-receiver call proves; deleting
the matched rows would discard valid C++ byte coverage. The expected benefit
is corrected identity provenance and removal of a misleading finish
candidate, not new game-code bytes or measured throughput.

Before implementation, independently challenge whether any other matched
caller uses the old Drawable pin, whether an address-derived thunk/wrapper
can pass strict relocation checks without a hidden fallback, and whether
removing the old pin breaks other scoped matches. Record the decision here
before editing the claims.

Pre-change focused test run: 119 passed, one unrelated failure in
`test_published_rows_are_unambiguous_anonymous_and_sized_by_the_inventory`
because the checked-in derived entry for `0x0014E2B0` says 571 bytes while the
Ghidra inventory says 574. This is a pre-existing derived-file freshness
failure, not evidence about this identity route; it must not be hidden by
weakening the assertion.

## Review decision

The independent review found the Drawable identity refuted, but returned
**revise** for the initial plain-`?j_` design: its typed alias pin could not
carry a valid `route=` without a same-name matched body at `0x00526660`.
The reviewed design above uses a matched address-derived thiscall thunk and
one direct opaque body pin, retaining strict relocation verification. The
independent reviewer further suggested putting the thunk's own RVA in its
name rather than the forwarded body's RVA; the revised scratch source still
probes 5/5 and 15/15 exactly modulo aligned relocations.
The review also found that the old Drawable pin appears only in a cached
`Object.obj` among the available cached objects, and the sole cached matched
caller is the 15-byte wrapper. The object cache is incomplete, so a full
strict build after pin removal remains mandatory. If another matched caller
fails, repair its source and independent identity evidence or defer removal;
never restore the false semantic pin just to make the gate green. Proceed with
the revised transaction and tests; no production claim changed at this
checkpoint.

## Follow-up guard design checkpoint (before changing the guard)

The correction exposed a separate false pairing in `tools/name_regression.py`:
moving the 15-byte ledger row out of the still-unmodified `Object.cpp` links
that whole file to the new wrapper. The token comparison then reports five
unrelated `Object.cpp` identifiers as renamed, even though they remain in the
source. A temporary-Git-repository regression test reproduces this failure
against the production `pairs()` and `check()` entry points.

The smallest proposed guard is to omit a cross-file comparison when its old
`Code/` source is byte-identical in the new snapshot. Keep same-file edits,
deleted-source moves, retained bank-to-source comparisons, and same-RVA ledger
symbol checks. This prevents a retained multirow source from being treated as
if all its declarations moved with one row. The alternative of documenting
the five invented token pairs in `name_corrections.json` would leave a false
audit trail; function-level parsing of arbitrary C++ is out of scope.

The risk is losing a source-token warning when one unchanged file's row is
repointed to a new file. The old source still retains its names, and the
same-RVA ledger check continues to catch owner/method downgrades, but fields
local to the newly extracted body need independent evidence review. The
negative tests must preserve detection for a changed source, a retained bank,
and the ledger-only downgrade. The independent review returned **proceed**
only after a changed-source extraction test was added. It challenged the
remaining blind spot for member/local names in a newly extracted body when
the old TU stays identical; whole-TU alignment is not trustworthy evidence
there, so this correction relies on the explicit identity proof above. The
review also requires removing the five invented `Object.cpp` correction
records, regenerating `reloc_names.csv`, and passing its focused test and the
full strict build before publication. The regeneration requirement was revised
below after the pre-existing full-gate failures were independently reproduced;
the final gate requirement is exact non-regression against that pre-change run.

## Derived-name publication revision (before editing the derived file)

The full strict gate reached function comparison but is red at 44 of 169,271
rows; `build.py` writes `reloc_names.csv` only after **every** function row
passes. Its existing red baseline is documented in `docs/full_gate_red.md`.
The pre-change revision is being run independently to separate existing red
rows from any introduced by this correction. Thus the proposed full
regeneration cannot be used as a publication step unless the entire baseline
is repaired first. An earlier evidence-backed correction at `0x00416FE0`
removed exactly one refuted derived row while the full gate was red
(`abfc4dab91`); that is a relevant precedent, not a general license to edit
derived candidates.

If the independent baseline confirms no new red, the smallest safe repair is
to remove only the proven false Drawable candidate for `0x00526660` from the
checked-in snapshot. Do not synthesize a replacement row: the corrected
address-derived thunk may produce a `generated` candidate on a future green
full gate, and that candidate would not be recovered identity. Preserve the
harvester, the full-gate write rule, and the other snapshot rows. The focused
test must show that neither the published file nor the actual queue serves
the refuted semantic name. On any future green full regeneration the now
corrected caller source should prevent the old symbol from returning.

Review risks before making this deletion: another verified caller might still
emit the old Drawable symbol; a one-row prune could hide such a contradiction;
and an old snapshot with one manually removed row must not be presented as a
fully refreshed harvest. Inspect the full gate comparison and the old symbol's
remaining source/pin uses, then record the independent review decision here.

The independent pre-change full gate at `3a57f38c91` confirms 44 failing
function rows and 86 DIR32 inconsistencies; none of its failure diagnostics
mentions the corrected route. The staged run reported the same totals, but
an exact red-set comparison is still required. The reviewer found exactly one
published candidate at `0x00526660`, with `call-sites=1` from the now-refuted
wrapper and no alternate name, and returned **proceed** for a one-row prune
conditional on that comparison. A stronger regression now fails on any
`identity=real` row or queue assignment at this address. The review rejects
changing the harvester or presenting this prune as a regenerated snapshot.

## Post-implementation gate audit

The independent pre-change full gate and the captured corrected full gate
failed on the **same 44 function labels**, with no extra or missing label.
Their 86 DIR32 inconsistency rows are byte-identical. Pin consistency and
source-claim checks passed in the corrected run, and none of its failures
mentions the corrected route. The strict full gate is still red on that
pre-existing set and cannot regenerate the derived file or run the no-op patch;
this correction does not claim a green full build. The checked-in name file
therefore remains the prior snapshot with only its refuted candidate pruned.

The focused naming tests passed (122 in the guard/identity/transaction group;
the two route-specific harvester/queue tests passed). The full relocation-name
test module had 11 passes and one pre-existing failure: its row for
`0x0014E2B0` says 571 bytes while the Ghidra inventory says 574. No assertion
or baseline was weakened to conceal that independent freshness problem.
