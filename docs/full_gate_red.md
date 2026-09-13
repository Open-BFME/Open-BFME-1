# The full gate is red, and what each red actually is

`./build.sh` with no arguments is the only check that compiles the whole tree.
Nothing else runs it on purpose, so rows rot unseen — the scoped gate a commit
runs verifies only the sources that commit touched.

**This blocks more than it looks.** `.githooks/pre-commit` gives any staged `.h`
or `reference/shims/*` the full gate with **no baseline tolerance**
(`wide_change=1` then `./build.sh || fail`). While the full gate is red, *nobody
can commit a header*. Verified: no `Code/` header landed from any author in the
three days before this was written. Every structural lane that touches a header —
including all of `docs/header_adoption.md` — is parked behind this.

The dir32 whitelist's last commit (2026-08-20) says "gate red is down from 7 to
1". This is roughly three weeks of drift, not years of debt.

## State

    FULL GATE: FAIL — 3 red: functions, dir32 consistency, no-op patch (unrunnable)
    Functions: FAIL 147/161889
    DIR32 consistency: FAIL 97 NEW inconsistent symbol(s)

`no-op patch` is not independent: it needs the patch set `verify_functions`
produces, so it cannot run until `functions` is green. Two reds were cleared
(`source claims`, `null relocs`) — see the commit "Clear two of the full gate's
five reds".

## The 147, by what is actually wrong

| count | cause | note |
|---|---|---|
| 75 | call-target identity | is the folded body the ledger knows under an invented name the SAME function as ours? |
| 24 | generator-written funclet | one bug, in a file with no generator — see below |
| 16 | byte mismatch, no candidate list | per-function reverse engineering |
| 12 | named symbol absent from its object | the compiler stopped emitting an out-of-line body |
| 9 | orphaned compiler-local label | byte-ambiguous; see below |

74 distinct files. 101 failures sit in ordinary `Code/` sources, 25 in
generator-written files, 21 in the vendored ZH reference tree.

## The trap that governs this whole campaign

`reverse/symbols.csv` is an **additive candidate list**: the resolver keeps the
first pinned address that reproduces retail. So **a pin naming the wrong function
still byte-matches, and a green gate proves nothing about it.** The dir32
whitelist carries the same warning from experience — 18 entries once got in
without a human reading them, 8 hiding placements that very check had proved
wrong.

Every shortcut through these 147 is that trap. Adding `??3@YAXPAX@Z,0x00881EF0`
would turn 24 rows green in one line and would be a lie: `0x00881EF0` is
`operator delete[]`, a distinct 21-byte body from `operator delete` at
`0x00881EB0`.

## The 24 generator-written ones need a decision, not a fix

All 24 are in `Code/gen_small/uw_gen_010.cpp` and are one bug: retail's funclet
calls `operator delete[]` and the generated C++ emits `operator delete`.

`tools/gen_uw.py` was **deleted on purpose** in 2d4dab0ad5 (2026-09-07, "retire
the C++ generators"), whose message is explicit: *"there is no generator left to
regenerate those files, so an edit to one is permanent and nothing will ever
cross-check it."* AGENTS.md still bans hand-editing them.

**The generator is nevertheless back in the tree**, restored as a side effect of
`f43040e9c5` ("Open-BFME6: fleet harvest 09-10 14:05"). A harvest resurrected a
file that was removed deliberately; that is worth fixing independently of this.

Three options, all of them somebody's call: regenerate (`gen_uw.py land` — 4,327
units over 19 files), hand-edit (banned), or retire the rows.

## Two lanes that were tried and returned nothing

**Re-pointing orphaned labels.** A row can name a compiler-local symbol
(`object-symbol=_$E14`); those numbers are assigned per compile, so editing
anything earlier in the TU renumbers them. `pointgr.cpp` asks for
`_$E14,17,20,23,26,38,41,44` and its object now holds
`_$E10,12,13,15,16,18,19,21,22,24,25,33,34,36,37,39`.

It cannot be repaired by bytes: all nine of its funclets are byte-identical under
the gate's own masked comparison, so every orphan has nine equal candidates. And
a tool that scanned every row with a missing symbol found 304 "unambiguous"
re-points, **none of which is a gate failure** — the gate already locates those
funclets by bytes without the exact label. Re-pointing them is churn.

The same tool, before it was scoped to compiler-local labels only, proposed
moving a `Matrix4D` CONSTRUCTOR row onto `Matrix4D::Set`, because two small
bodies tie once relocation sites are masked. **A byte match on a small body is
not an identity.**

**Adding the retail-called address as a pin.** Covered above: it is the
wrong-name trap, and it is what the additive candidate list will happily accept.

## What one identity judgement costs

`ModuleInfoNuggetVector.cpp` calls `ModuleInfo::Nugget::~Nugget`; retail's call
site reaches `0x0013B8F0`, which the ledger claims as `??1BfmeOwnVUG@@QAE@XZ`
from `BfmeConv1637.cpp`. `BfmeOwnVUG` is `pad[0xc]; BfmeStrVUG; BfmeRefVUG*` and
its destructor releases a refcount. `ModuleInfo::Nugget` is twenty bytes with an
`AsciiString` at +0, and its own comment says "Not the reference's Nugget". Those
are different objects, so the likely defect is the element type in the source
rather than the pin.

Ten minutes of reading produced a hypothesis, not a settled answer. Seventy-five
of those is the shape of this campaign.

## Where to start

1. Settle the `gen_uw.py` question — biggest single cluster, 24 rows, one bug.
2. `tools/red_rows.py` runs the whole gate and reports every rotted row; it exists
   because "every red row found so far was found by accident".
3. For an identity, the oracles are `tools/callers_of.py`, `tools/multi_name.py`,
   `tools/ctor_vtable.py`, `tools/size_outlier.py`, `tools/find_emitter.py` and
   `tools/audit_ret_arity.py`. See the memory note "Image oracles for identity".
4. Never settle a row by editing a baseline or adding a pin to go green. Both
   files say so in their own headers, and both have been burned before.
