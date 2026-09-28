# SIB base/index experiments on the two-register `lea` residue

Follow-up to "The two-register lea operand order is not a spelling" in
`docs/shape_levers.md`. That section gives up on four one-byte-residue
bodies (0x0078D410, 0x007901F0, 0x005A0450, 0x0045C2F0) after roughly a
dozen source respellings each, across five separate sessions (opus5-xhigh,
gpt-5, astra, codex, luna). This session ran controlled micro-experiments
outside those four bodies to find the general rule, then tested the one
promising lever against a real body. No exact match resulted. Recorded here
so nobody repeats the same dead end.

## Harness

`build/sib_experiment/` (untracked, gitignored under `build/`): a scratch
`.cpp` with many `__declspec(noinline)` functions, compiled with
`-O2 -GR- -EHsc- -DNDEBUG -MD` (the flags every one of the four bodies'
stashes uses) plus `-FAcs` to get a `.cod` assembly-with-source listing.
`build/sib_experiment/compile.py` wraps `tools/build.py`'s
`compiler_command`/`compiler_environment` so the same wine/cl.exe path and
env setup applies, and just inserts the listing flag before the
`-Fo/source` tail. No retail bytes exist for the scratch functions; read the
`.cod` listing directly instead of using `tools/probe.py` diffing (there's
nothing to diff against).

## Experiment 1: does source shape/type/operand-order steer the SIB base?

One `.cpp` (`probe1.cpp`) with paired variants, each forcing MSVC to fold
`a + b` into `lea dst,[x+y]` by keeping both `a` and `b` alive afterward
(passed to an undefined extern `use3(a,b,sum)` — the TU is never linked,
just compiled to `.obj`, so the missing definition is fine).

| Variant | Shape | SIB base |
|---|---|---|
| A1/A2 | two params, `a+b` vs `b+a` | base = first PARAM (a), unaffected by textual order |
| B1/B2 | param + global-backed local, both orders | base = whichever is loaded first in the emitted stream (the global, since it's read before the param) |
| C1/C2 | two locals from `volatile` globals, declaration order swapped, expression always `a+b` | base = **second**-loaded value in BOTH C1 and C2 (i.e. innsensitive to local declaration order, but opposite polarity from A/B) |
| D1/D2 | member load (`p->x`) + param, both orders | base = member load (loaded first in the stream) |
| D3 | member load + a value returned from a call (`sink(c)`) | base = the member load, which here is the **second**-loaded value (the call result sits in eax first) |
| E/F/G | pointer-cast forms (`(const char*)base + b`, `(unsigned)((const char*)0+a)+b`, `a - (0-b)`) | all collapse to the same `lea eax,[base_of_two_plain_loads]` shape as A; base = first-loaded in every case |
| H | one addend also used as an array index (`p[a]` vs `p[b]`) elsewhere | MSVC folds the whole thing into two-operand `add` chains instead of a 3-register lea (CSE with the index computation) — not comparable |
| I | addend is a loop induction variable | compiles to scaled-index addressing (`lea ecx,[esi+ecx*4]`) baked once before the loop, not a plain two-register lea — not comparable |
| J | `int`/`unsigned`/`long` addends | identical machine code to the `int` case in all three |
| K | `__forceinline` helper vs inline expression | identical machine code either way |

Textual/expression operand order (`a+b` vs `b+a`) **never** changed anything,
confirming shape_levers.md's "MSVC commutes the addition before it picks
the base." Declaration order of the two locals also never changed anything
(C1 and C2 are identical). The one property that DID change something: the
first group (A, B, D1/D2, E, F, G, K — all "plain load, no other event in
between load and combine") consistently picked the FIRST value materialized
in the instruction stream as the SIB base. The second group (C1/C2, D3 —
where the eventual "index" operand's load has some structural difference:
two same-shape global reads with no register-pressure tiebreak in C, a
call-result operand in D3) instead picked the SECOND value materialized.

## Experiment 2: isolating "first vs second materialized" with an intervening touch

`probe3.cpp`, group P: reproduces the closest realistic shape to the actual
residual bodies — two `ICoord2D`-style locals filled by out-parameter calls
(`getPointOut(&origin.x, &origin.y)`), then combined through a
`__forceinline int addCoords(int base, int offset){ return base+offset; }`,
matching `drawTypeText`'s real `addCoords(origin.x, width)` call at
`0x005A0450+0xDE` almost verbatim. Both operands again kept alive via
`use3(...)` afterward to force a genuine 3-register lea.

- P1 (no intervening use of either operand between the two calls and the
  add): SIB base = **first**-loaded operand (`origin.x`) — `8d 14 08`.
- P7 (`g_sink1 = origin.x;` inserted between the two calls and the add,
  touching the FIRST operand): SIB base flips to the **second**-loaded
  operand (`width`) — `8d 14 01`. The flip happens even though the
  preceding `mov eax,[...]; mov ecx,[...]` pair is byte-identical to P1 and
  the g_sink1 store itself gets scheduled AFTER the lea in the final
  instruction stream (interleaved with the `use3` argument pushes). The
  compiler's *source-order* placement of that extra use is what flips the
  choice, not its position in the final schedule.
- P8 (same touch, but on the SECOND operand, `width`, instead): same flip,
  identical bytes to P7. So it's not "which operand gets touched," just
  "does ANY intervening use of either operand exist between definition and
  combination."
- P2–P6, P9, P10 (reversed helper-argument order, swapped call order, no
  helper, no named `width` local, values from the same struct): all give
  the SAME `8d 14 08` as P1. None of the "obvious" respellings matter here
  either — only the intervening touch does.

This is a real, reproducible, minimal lever: **an intervening use of either
addend between its definition and the point where it is combined with the
other addend flips which one becomes the SIB base**, independent of
register assignment (which stays identical) and independent of which of
the two operands is touched.

## Applying it to a real body: negative result

`drawTypeText` at `0x005A0450` has EXACTLY the P7 shape in its real source
(`targets/game/reverse/attempts/0x005a0450.cpp`): `clipRegion.lo.x = origin.x;` and
`clipRegion.lo.y = origin.y;` sit between `origin`/`size` being filled and
the `addCoords(origin.x, width)` call at the residual `+0xDE`. Per the
micro-experiment, REMOVING that intervening touch (moving the `lo.x`/`lo.y`
stores to after the `hi.x`/`hi.y` computation — semantically safe, nothing
reads `clipRegion.lo` in between) should un-flip the base back to
`origin.x`, matching retail.

Tested directly against the real RVA with `tools/probe.py`
(`build/sib_experiment/test_005a0450.cpp`, reordered):

```
diffs    7 non-reloc byte(s); first at +224
!!00de  lea edx, [ecx + ebx]     <- UNCHANGED, still wrong
!!00ec/00f0/00f4  three store instructions now also mismatch (order swapped)
```

The `lea` SIB byte at `+0xDE` did **not** change at all — identical bytes
before and after the reorder — and the reorder additionally broke three
more bytes by changing the store order of `hi.x`/`hi.y`/`lo.x`/`lo.y`
(retail keeps `lo` before `hi` in the store stream even though it computes
`hi` from untouched values; matching that store order needs the touch
present). So in the full function (many more live locals — `textColor`,
`textDropColor`, `tData`, `text`, `font`, `wordWrap`, register pressure
across `ebx`/`ebp`/`esi`/`edi`) the P7/P8 "intervening touch" lever from the
isolated two-variable case has no effect: something about the larger
function's register allocation already fixes the base/index choice before
that local property can matter. Reverted; the stash source is unchanged.

## Conclusion

The isolated lever (intervening touch of either addend flips SIB base) is
real and reproducible in a minimal function, but does not transfer to any
of the four documented residues once tried against the actual body. This
matches the existing shape_levers.md conclusion for this symptom: bank the
body and move on, this byte is not reachable from clean C++ under this
toolchain and codebase context. Do not re-run the "intervening touch"
respelling against 0x0078D410, 0x007901F0, or 0x0045C2F0 — the same
register-pressure argument applies to all three (all are ~220-560 byte
bodies with several other live locals around the residual `lea`).

No new bodies landed this session. All four RVAs remain at their prior
`blocked`/`partial` state in `targets/game/reverse/re_attempts.log`; no new re_log entry
was needed since nothing changed about them (this session worked entirely
in the untracked `build/sib_experiment/` scratch harness plus one revert-only
probe against the existing stash).

## Addendum, 2026-09-20 (orchestrator): flag and spelling sweep on 0x0045C2F0

Against the 229-byte `View::getScreenCornerWorldPointsAtZ` witness (one byte:
retail `lea edx,[edi+eax]`, ours `[eax+edi]`, `edi` = `viewWidth` from the
earlier `getWidth()` call, `eax` = `origin.x` just reloaded), every variant
below left the byte unchanged and the other 228 exact:

- declaration order: `origin` before or after `viewWidth`/`viewHeight`, and
  all six locals declared after both calls;
- operand types: `unsigned viewWidth`, `(unsigned)` / `(long)` casts on
  either addend, an all-unsigned sum cast back to `Int`; `(short)` changed
  the body shape (231 B, 139 diffs) without touching the SIB;
- receiving `getOrigin` into two scalar locals instead of an `ICoord2D`,
  declared before or after the width/height locals;
- a named `Int right = origin.x + viewWidth` computed once and stored twice;
- holding width/height in an `ICoord2D dims` aggregate instead of scalars;
- flags appended to the `// cl:` line: `/Zi`, `/Z7`, `/Ob0`, `/Ob1`, `/Ot`,
  `/Oi`, `/Op`, `/Oa`, `/Ow`, `/GF`, `/Gy`, `/Gs`, `/Zp1`, `/Zp4`, `/Zp8`,
  `/Zp16`, `/J`, `/GS-`, `/Og`, `/Ox`, `/Gr`, `/Zc:forScope-`, `/Gm`, `/Gi`,
  `/GX-`, `/GT`, `/GA`, `/EHa`, `/EHs` all reproduce the same 229 bytes;
  `/Oy-`, `/Os`, `/O1`, `/Od`, `/Ge` change the whole body and `/GL` breaks
  the object reader.

Retail's choice here is "the OLDER value is the base" (`viewWidth` was
materialized first); ours is the opposite, and in the isolated probes of the
first section ours also picked the older value as base. So the ranking is
not a property of the source at all in this body. The remaining untested
hypothesis is a different `c2.dll` build (retail may not be 13.10.3077 RTM
for every TU); nothing else reachable from this toolchain moves the byte.
