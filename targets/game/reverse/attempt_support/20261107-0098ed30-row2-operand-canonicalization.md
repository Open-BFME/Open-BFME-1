# 0x0098ED30 LineGroupClass::Render (4100 B): partial, x87 operand-order residue

> The best candidate (`build/wf/0098ed30/best.cpp`, untracked scratch) is now banked as `targets/game/reverse/attempts/0x0098ed30.cpp`. Other `build/wf/0098ed30/` paths below are scratch and are not kept.

Symbol: `?Render@LineGroupClass@@QAEXAAVRenderInfoClass@@@Z`. Ledger row: matched, but only through the
naked lift in `game/Libraries/Source/WWVegas/WW3D2/linegrp.cpp`. Extent: complete `ret 4` at +0x1001
(identity_evidence/0098ed30.md).
Compiler: the TU `// cl:` line from the bank (`/DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc` plus includes). The
build adds `-O2 -GR- -EHsc-`. No flag changes were made.

- Best clean candidate: `build/wf/0098ed30/best.cpp`, a copy of the bank. It reproduces as logged:
  4100/4100, 149 relocs, 35 non-reloc bytes at +0x63A..+0x65F.
- Best diagnostic, which must not land because it uses dummy locals: `build/wf/0098ed30/v/G5_28_0.cpp`.
  It uses canonical `Matrix3D::Transform_Vector` plus 28 dead `int dqN = 0; (void)dqN;` locals at the
  end of Render, and gets 7 non-reloc bytes at +0x602..+0x609.
- BFME 2 donor (dbde7dbe) `Code/Libraries/Source/WWVegas/WW3D2/linegrp.cpp` matched its own Render
  with the canonical `Matrix3D::Transform_Vector` call, but on a different toolchain (/arch:SSE /G7).
  That is evidence that the source shape is canonical, not that its bytes carry over.

## The residue: row/product notation
The loop loads X, Y and Z, giving the stack [Z,Y,X]. Each product `A[r][c]*v` takes one of three forms:
- `m` is `fld A; fmul st(v)` (memory operand first).
- `r` is `fld st(v); fmul A` (register copy first).
- `R` is `fxch v; fmul A`, which consumes v.

| | row 0 | row 1 | row 2 |
|---|---|---|---|
| Retail | ZmYrXm | ZmYmXm | YRZmXR (1 final pop) |
| Bank | ZmYrXm | ZmYmXm | (Z product named) 35 diffs |
| Canonical source | ZmYrXm | ZmYmXm | ZmYmXm (3 pops) 248 diffs |

## New finding: a local-symbol count decides the order (docs/shape_levers.md, the Transform_Vector entry)
MSVC 7.1 canonicalizes the commutative x87 operands. Each pair's form (m/r/R) and the product order
flip as the count of local symbols in the function changes.

- Dead int dummies: only the total count matters. Placing them at the start, inside the if, before
  the loop, inside the loop body or at the end gives the same rows. Names and types do not matter.
- Canonical sequence by count N (`v/G2_N_0.cpp`):
  - The row-2 target YRZmXR appears ONLY at N=28.
  - Row 0 X is `r` for N 16..34, and `m` for N 0..2 and 35..38.
  - The two requirements are therefore incompatible: gap = 34-28 = 6 > 0.
- At N=28, dummies before the vertex block add a 4-byte `mov` swap at +0xE88 (11 diffs). Dummies after
  it give 7 diffs.
- Structural edits that move the two thresholds differently. gap = (row-0 X window end) - (N of
  YRZmXR), and exact needs gap < 0 or some other structure:
  - BFME 2 block-local `Vector3 loc = start/end + size * offset[j]` in the prism caps: -1 each.
    a1 (both caps): target N 20, window end 24.
  - Center as a temporary instead of the named local in the inline helper: -1.
  - Direct `rva0093B340(Rva0093B340Center(...), ...)` call without the helper: -1 (vc).
  - Best gap is 2: `y_tc3_a1.cpp` (3-float center temporary + a1) reaches target at N=21 and window
    end at 23. vbc gives the same.
  - Aggregate dummies (`Vector3 d(0,0,0)`) BEFORE or inside the transform raise the gap (S1v: target 14,
    window to 20; S2v: larger). After the transform they act as about 3 int units each and only shift.
- Edits that only shift, with no gap effect:
  - removing `value_255`
  - block-local `idx` in the index buffer (also adds the E88 swap)
  - block-local `point`
  - `end =`/`start =` instead of `.Set`
  - `loc =` instead of `loc.Set`
  - `offset[j]*size` operand order
  - `Matrix3D xform_mat(cam)` or `= cam`
  - a named zero `Vector3`
  - `identity(1)`
  - non-const `sort`
  - Vector4 constructor spellings
  - `offset[k] = offset_a`
  - removing the extra index-buffer braces
  - the `int k` loop variable (+1 shift)
  - renaming `xform_mat`

## Ruled out this session (in addition to the 8 earlier log entries)
- `Matrix3D` as an operator (not declared without ALLOW_TEMPORARIES).
- `Vector3 t` out-of-place transform plus copy-back: 2260 diffs. `Vector3 t = in` copy-in: 2249.
- `mulVector3` into a temporary: 371.
- Explicit scalar x/y/z, `Vector3 t(in)`, or `Set(...)` with three rows: 259..2282.
- `Vector3 &o` alias: 345.
- `const Matrix3D &` or pointer alias of xform_mat: 4086 B (changes rows 1/2).
- `offset + i`: 248.
- Row-2 statement splits (`+=` chains, named Y/YZ partials): 248..400.
- Helper bodies: `Vector3 tmp(in)`, by-value `in`, and scalar copies change the loop's load addressing.
  The member-wise `tmp.X=in.X...` copy gives a different sequence; its target appears with row-0 Xr.
- Small-TU facts: with an indirect matrix (`const Matrix3D &` parameter), VC7.1 consumes X/Y as retail
  does. With a frame or global matrix, the canonical count shows no consumption. The order is not
  fixed by matrix storage alone.

## Next step
Find another legitimate after-transform aggregate structure (the vertex and sorting section) that
lowers the gap by 3 or more. Then reach the needed count with real named locals, as for 0x001C1820.
Check with `build/wf/0098ed30/sweep2.sh LO HI <stem>`, which reports `N:row0X/row2` per count. Tools:
- `multi.py` / `multi2.py`: dummy placement by anchor letter
- `sig.py`: x87 signature
- `dd.py`: diff ranges
- `trials.log`: every trial
No game/, ledger or pin edits were made.
