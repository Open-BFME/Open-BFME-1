# Handoff: 0x00925D10 get_deformed_vertices single-bone normals loop (1634B)

Date: 2026-11-04. Claim held during investigation, released after.
Bank `targets/game/reverse/attempts/0x00925d10.cpp` unchanged at 0.9878
(1634B, 20 non-reloc diffs, first +0x59E). No production/pin/ledger change.

## Retail ground truth (decoded this round, `dis_retail.py 0x00925D10 1634`)

Single-bone normals loop body (+0590..+05E3), ECX = running `in`, EDI = running
`out`, EDX = out-minus-in delta, EAX = matrix row base, EBP = countdown:

- X row: `fld mX; fmul inX; fld inY; fmul mY; faddp; fld inZ; fmul mZ; faddp;
  fstp [edi-0xc]` — term order X,Y,Z; 1st product matrix-first, 2nd/3rd
  input-first.
- Y row (+05af..+05c5): `fld m[1].X; fmul inX; fld inZ; fmul m[1].Z; faddp;
  fld inY; fmul m[1].Y; faddp; fstp [ecx+edx-0x10]` — term order X,Z,Y.
- Z row (+05c9..+05df): same X,Z,Y term order, `fstp [ecx+edx-0xc]`.

So Y/Z rows evaluate the Z product before the Y product; X row keeps Y,Z order.
Store SIB is `[ecx+edx+d]` (ECX base) vs bank's `[edx+ecx+d]`.

## New negative results this round (do not repeat)

1. Mixed operand spelling on all rows
   (`m[0].X * in->X + in->Y * m[0].Y + in->Z * m[0].Z`, etc.): 20 diffs remain,
   but the X row — untouched by the intent — now emits Z,Y term order. The
   compiler does not preserve written FP term order here.
2. Z-before-Y spelling on Y/Z rows only (X row left as bank): identical 20-diff
   output as (1), including the X-row Z,Y swap. Written term order is not
   compositional across the three statements.
3. Together with the prior 156-trial sweep (paren masks, coeff/sample refs,
   volatile, inline contexts) and the opus spelling perms, the whole
   term-order/operand-orientation family is exhausted: no source spelling of
   these three statements sticks to retail's per-row orders simultaneously.

## Suggested next (untried)

- The per-row emission difference under identical statement shapes points at
  x87 stack/addressing context, not statement spelling: investigate what makes
  the X-row 2nd/3rd products input-first while Y/Z-row same-shape products come
  out matrix-first (matrix displacement width? EAX lifetime? EDI vs ECX+EDX
  store form?). A `// shape:`-style minimal two-row probe outside this TU
  could isolate the codegen rule before touching the bank again.
- Do not run another ungrounded local-count/paren/volatile sweep; do not retry
  term reorderings.
