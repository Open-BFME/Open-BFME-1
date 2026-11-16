# Census after the preceding 200 ICoord2D adoptions

Completed measurement: [43852286500](https://github.com/Open-BFME/Open-BFME-1/actions/runs/43852286500),
successful on 2026-11-16 at12:41:56UTC. Artifact input `fe40b725e8` resolves to
`fe40b725e8d66d3581bc908ab3cb41324830be1c`, the preceding200-task completion.
All commits in the current500-task continuation are later inputs and are not
covered by this census.

Against census43711614660 / `7c314a3e6c`:

| Metric | Before | After | Delta |
|---|---:|---:|---:|
| LINKED bytes | 3,088,824 | 3,094,682 | +5,858 |
| Link-clean source files | 15,522 | 15,524 | +2 |
| Link-clean files in the preceding200-source cohort | 152 | 152 | 0 |

Every one of the200 sources is present in the new status artifact. The cohort
has no newly blocked source. Its48 already blocked sources remain blocked;
this is not a claim that all200 now link. The overall byte gain includes
other intervening work and is not attributed to these200 reconciliations.
Retained-byte/layout gates and a full-image census remain different evidence;
neither establishes runtime or memory/crash improvements.

The raw status comparison also finds two old filenames no longer marked yes.
One is a genuine303B linking regression: `Common/Rva003BF010.cpp` now loses
the `?isEmpty@AsciiString@@QBE_NXZ` COMDAT and touches a wrong selected copy.
The other, `W3DDevice/GameClient/Gen_006eab10_Clamp.cpp`, was moved into
`W3DDisplayDraw.cpp` by21724c8ada: the ledger retains the30B clamp at006EAB10.
It is a source-ownership move, not evidence of lost clamp bytes.

The measured AsciiString name has198 copies:126 retail,72 wrong, with the
wrong Object.obj copy selected. The original export1656 identifies the real
StringBase<char>::isEmpty ILT0000C752 ->0005E4C0; its existing matched body is22B
in `game/Libraries/Source/string/StringBase.cpp`. The AsciiString spelling is
a pin-only facade. Earlier commitb3db3462ba already repaired the caller by
exposing the inherited method; the canonical header's own forwarding member
subsequently shadows that repair. This family is the immediate follow-up.

BFME2 reference7209b9e7397e3ed356627a8110e4b7aab234f6e8 was initially reviewed read-only; the tracked reference subsequently advanced to aa505f34c898e6fb7c9a1f1632e75ce232f4829a with these reviewed string/header inputs unchanged:
`Code/.../LogicDispatch/headers/common/asciistring.h` reaches
`reference/shims/bfme2_ascii/ascii_string.h`. That shim implements its boolean
test directly with the null pointer / unsigned-short length at+4. Its
standalone facade, cleanup modes, addresses and source aliases are not imported
into BFME1's inherited4B type. BFME1's original export, matched provider and
earlier native caller repair establish the narrower correction.

Artifacts and the complete source comparison are preserved under
`W:/OpenBFME/diagnostics/continue-20261116-fivehundred/` in
`census-43852286500`, `census-index-43852286500` and `census-comparison.json`.

## Subsequent scoped repair

Commit `4723fed793ffc3dc2c59326b0a672dd79506b5ea` qualifies the original
StringBase<char>::isEmpty member. The303B caller is unchanged in size, physical
layouts and code/EH/data graph, allowing only that original-export-proven
callee binding. Its original export1656 identifies ILT0000C752 ->0005E4C0.
The global AsciiString header and its other forwarding copies are unchanged.

A subsequent native current-provider preview reports LINKS,0 ->303B, at that
commit. It starts from the complete22992-object current inventory at4e7859a7d792,
with no unknown definers or stale selections, and refreshes the intervening
independently audited local source changes. The native result has no unresolved,
duplicate, wrong/unproven COMDAT, address, selected-provider, weak-alias or
preview-unknown blocker. This is scoped prediction against actual current
objects; it is not a new full-image link measurement or runtime proof.
Evidence: `identity_evidence/20261116-fivehundred-adoption-11.md`.
