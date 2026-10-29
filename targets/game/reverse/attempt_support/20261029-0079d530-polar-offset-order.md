# 0x0079D530 AptPalantir polar offset: x87 residence trials (session a1/476)

Bank: targets/game/reverse/attempts/0x0079d530.cpp (0.9407, 961 B, 57 diffs).
Probe: `python3 tools/probe.py --all --size 961 <src> '?rva0079D530@AptPalantir@@QAEXXZ' 0x0079D530`.

Retail +0x2FD..+0x345 (after `distance` is stored to [esp+14]):
`fld st0; fcos; fmul d` (cx kept on x87) -> `fxch; fsin; fmul d; fstp [esp+2c]` (sy spilled
into an 8-byte struct slot at esp+28, its x half never stored) -> 544.x+=cx, 544.y+=[2c],
564.x-=cx (st1), pop, 564.y-=[2c]. Frame 0x30.

Observed (not yet a match):

- Replacing the bank's offset block with
  ```
  BfmeVec2CY offset;offset.x=(float)cos(middle)*distance;offset.y=(float)sin(middle)*distance;
  m_coords544[i].x+=(float)cos(middle)*distance;m_coords544[i].y+=offset.y;
  m_coords564[i].x-=(float)cos(middle)*distance;m_coords564[i].y-=offset.y;
  ```
  reproduces the frame (0x30), the dead offset.x store, sy in [esp+2c] and cx kept on the
  stack: 959 B, shape 0.989, 2 structural diffs. Remaining: sin is computed before cos
  (`fld st0; fsin; fmul; fstp [2c]; fcos; fmul`), so the 2-byte fxch is missing, plus the
  minimum slot (esp+10 vs retail esp+14, unchanged from the bank).
- Same 959 B sin-first result: offset fields in either order, BfmeVec2CY(cx,sy) ctor,
  aggregate FloatPairBase init, comma-joined assignments, distance*cos operand order,
  `float ox=cos*d; offset.x=ox`, offset.x reassigned after use.
- Scalarised (frame 0x28, 957 B): ox scalar declared before the struct, offset.x=c copy,
  only offset.y assigned. Scalar ox/oy pairs spill cx instead of sy (957 B).
- 544.x update placed before the offset.y statement: 953 B.

Lead: retail evaluates cos first yet keeps sy memory-bound; whatever forces the cos
evaluation ahead of the sin store while offset.x stays dead is the missing piece.

Follow-up (same session):

- Ordering rule seen in every trial: VC7.1 evaluates cos/sin in the order of their first
  *live* use. Inline-ctor argument temps and dead scalar defs are sunk to their use, so a
  struct store of y that precedes the first live use of cx always computes sin first.
- `BfmeVec2CY offset(cos*d, sin*d)` + `+=`/`-=` (ctor body x then y): cos first, but x is
  stored to [esp+28] and sy is kept on x87 (the exact mirror of retail, 957 B). Reversing
  the ctor body (y=b; x=a) gives sin first again.
- Scalar ox/oy (float or double, either operand order) compute cos first but spill cx and
  drop the struct slot (frame 0x28).
- An unused `float ox=cos*d;` before the struct, `(float)(cos(middle)*distance)` casts,
  reusing firstVector/secondVector as the offset (frame changes, 965-981 B), and a
  forceinline polar helper returning BfmeVec2CY (not inlined: 968-981 B) do not help.
- Late additions: an inline ctor taking `const float &` arguments (either body order, with
  field or CSE'd uses) and placing `544.x += cos*d` before the offset.y store (VC7.1 keeps
  the statement store order, so cx is stored to 544.x before fsin) reproduce the same two
  outcomes; no case computes cos first while keeping sy as the memory-home value.
