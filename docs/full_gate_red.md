# The full gate is red, and what each red actually is

`./build.sh` with no arguments is the only check that compiles the whole tree.
Nothing else runs it on purpose, so rows rot unseen — the scoped gate a commit
runs verifies only the sources that commit touched.

**This blocks more than it looks.** `.githooks/pre-commit` gives any staged `.h`
or `inputs/reference/shims/*` the full gate with **no baseline tolerance**
(`wide_change=1` then `./build.sh || fail`). While the full gate is red, *nobody
can commit a header*. Verified: no `game/` header landed from any author in the
three days before this was written. Every structural lane that touches a header —
including all of `docs/header_adoption.md` — is parked behind this.

The dir32 whitelist's last commit (2026-08-20) says "gate red is down from 7 to
1". This is roughly three weeks of drift, not years of debt.

## State

    FULL GATE: FAIL — 4 red: functions, dir32 consistency, source claims, no-op patch (unrunnable)
    Functions: FAIL 100/161893
    DIR32 consistency: FAIL 108 NEW inconsistent symbol(s)

String-ref verify, pin consistency, CRT import pins, and null relocs were OK.
Null relocs read 161893 rows and reported 789 unreadable rows. Source claims
had 4 zero-row sources. The no-op patch did not run because verify_functions
did not produce a patch set while functions were red. The raw failing rows are
preserved in docs/full_gate_red_2026-09-15.txt; targets/game/reverse/reloc_names.csv was
unchanged.

After the same day's campaign (three parallel Astra lanes plus Claude):
Functions 90 red (the ini.cpp trio landed through the baseline-tolerant hook,
six more rows went green under it), DIR32 99 live inconsistent symbols after
lane B's nine source fixes, `targets/game/reverse/full_gate_baseline.txt` at 90 rows. The
retired generators are deleted again and guarded (targets/game/reverse/retired_paths.txt).

## The hook now compares against a baseline (2026-09-15)

`.githooks/pre-commit` no longer demands a fully green gate for a header or
shim. It runs `tools/gate_baseline.py --check`, which fails on any row that is
red now and absent from `targets/game/reverse/full_gate_baseline.txt`, and on a gate that
dies before byte comparison. The baseline is recorded once with `--record`
on a stated revision and may only SHRINK: `--validate` refuses a staged
baseline that adds a row, so a red cannot be hidden by writing it down. Rows
that went green are printed so the fixing commit removes them. If the
baseline file were ever absent the hook falls back to strict.

## The 100, by what is actually wrong

| count | cause | note |
|---|---|---|
| 83 | call-target identity | the retail call reaches a body whose ledger identity or emitted callee still needs proof |
| 2 | generator-written funclet | stale compiler-local funclet pins in W3DDisplayString.cpp |
| 1 | byte mismatch, no candidate list | per-function reverse engineering (GiantBirdAIUpdate destructor) |
| 5 | named symbol absent from its object | the compiler stopped emitting an out-of-line body |
| 9 | orphaned compiler-local label | byte-ambiguous; see below |

57 distinct files. 79 failures sit in game/ sources and 21 in the vendored
ZH reference tree.

## The trap that governs this whole campaign

`targets/game/reverse/symbols.csv` is an **additive candidate list**: the resolver keeps the
first pinned address that reproduces retail. So **a pin naming the wrong function
still byte-matches, and a green gate proves nothing about it.** The dir32
whitelist carries the same warning from experience — 18 entries once got in
without a human reading them, 8 hiding placements that very check had proved
wrong.

Every shortcut through these 100 is that trap. Adding
??3@YAXPAX@Z,0x00881EF0 would turn multiple rows green in one line and would
be a lie: 0x00881EF0 is operator delete[], a distinct 21-byte body from
operator delete at 0x00881EB0.

## The 2 generator-written funclets need a decision, not a fix

Both are gen-funclet rows in
game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayString.cpp.
The gate reports stale $L45506 and $L45507 object-symbol pins after the
translation unit was edited; their emitted destructor call also remains a
call-target identity issue. Do not repoint them from bytes alone.

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

Resolved 2026-09-18: the two observed families now have separate address-qualified
owners, `game/GameEngine/Source/Common/Containers/Rva0013B8F0Vector.cpp` and
`game/GameEngine/Source/Common/Containers/Rva007701C0Vector.cpp`. The former
retains the string-at-+0x0C/reference-at-+0x10 records; the latter retains the
string-at-+0/vector-at-+4 records. All 821B and 1048B of their scoped ranges
remain byte-verified. Their original class names are still unknown; unrelated
legacy `ModuleInfo` candidate pins were preserved. The example below records
the earlier investigation, not an outstanding failure of the corrected clear.

Ten minutes of reading produced a hypothesis, not a settled answer. Seventy-five
of those is the shape of this campaign.

## Where to start

1. Review the two stale generated-funclet pins in W3DDisplayString.cpp.
2. `tools/red_rows.py` runs the whole gate and reports every rotted row; it exists
   because "every red row found so far was found by accident".
3. For an identity, the oracles are `tools/callers_of.py`, `tools/multi_name.py`,
   `tools/ctor_vtable.py`, `tools/size_outlier.py`, `tools/find_emitter.py` and
   `tools/audit_ret_arity.py`. See the memory note "Image oracles for identity".
4. Never settle a row by editing a baseline or adding a pin to go green. Both
   files say so in their own headers, and both have been burned before.

## The gate is partly self-blocking

Three failures in `WWLib/ini.cpp` — `~BufferPipe`, `~BufferStraw`, `~CacheStraw` —
share one cause. At +0x29 each calls `~Buffer` out of line, while retail calls
`Buffer::Reset` at 0x009E1E60 directly. That is not a wrong candidate: retail
INLINED `~Buffer`, whose entire body is

    Buffer::~Buffer(void) { Reset(); }          buff.cpp:82

so the inlined call goes straight to Reset. Our `buff.h` declares
`~Buffer(void);` out of line, so MSVC emits a call to the destructor instead.

**The fix is a one-line header change and it cannot be committed.** Tested:
inlining the body in `buff.h` clears all three. It then costs four — `~Buffer`
loses the out-of-line body its own row at 0x009E1E30 claims, and three `uw_*`
unwind funclets in ini.cpp shift because inlining changes the EH structure. So
the real change is "inline it AND keep a COMDAT AND re-land the funclets", which
is conversion work rather than a one-liner.

Either way it edits a `.h`, and `.githooks/pre-commit` gives any staged header the
FULL gate with no baseline tolerance. **The full gate is red partly because of
these three, and fixing them requires the full gate to be green.**

That circularity is worth a decision rather than more attempts. The obvious
resolution is the one every other check here already uses: compare a header
change against a BASELINE of known reds -- the way `targets/game/reverse/identity_baseline.txt`
works -- instead of demanding zero. A header edit would then have to not make
things WORSE, which is the property that actually matters, rather than having to
fix everything first. That is a policy change to the hook and belongs to whoever
owns it, not to a tool.

## Leads that look like a pin and are not — verified, do not re-chase

Each of these has the shape "retail calls a body our ledger already names", which
reads like a missing candidate. In every case the sizes settle it: **ICF twins are
the same length, because they are the same code.** Different lengths mean
different functions, and a pin would be a lie.

| our source calls | retail calls | verdict |
|---|---|---|
| `~Snapshot` 7B @0x0005C520 | `~SubsystemInterface` 14B @0x009A1A40 | different; our hierarchy is one base short |
| `~Buffer` 40B @0x009E1E30 | `Buffer::Reset` 40B @0x009E1E60 | same size, still different: retail INLINED `~Buffer`, whose body IS `Reset()` |
| `Free_Definitions` 50B @0x009CB880 | `bfmeGo920F` 27B @0x00160E70 | different |
| `freeSockets` 64B @0x0008FCE0 | `bfmeGo920F` 27B @0x00160E70 | different |

The `~SubsystemInterface` case is worth reading twice. Its 14 bytes are
`mov [ecx],vptr; add ecx,4; jmp <next base dtor>` -- a base-chain destructor --
and FOUR invented names are already pinned to it as aliases (`BannerSubsystemBase`,
`BfmeBase1134`, `BfmeBaseAA`, `BfmeBaseP`). The tree keeps meeting this body and
naming it locally instead of modelling the base class. That is the same disease as
a TU-local `BFMEFindAsciiStringView`, one level up the hierarchy.

`tools/wrong_callee.py` splits the whole family by whether each side is a matched
row, so the 28 with a possible source fix can be told from the 54 waiting on the
conversion lane.
