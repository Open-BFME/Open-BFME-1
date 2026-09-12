# SegLineRendererClass::Render: 51-byte partial checkpoint

As of 2026-09-12, the reconstruction produces **14,081 bytes with 51 actual
resolved byte differences** at RVA `0x00960A30` (VA `0x00D60A30`). This is
99.638% byte similarity, not a completed conversion or a runtime correctness
claim. The `Code/gen_asm/d_00960a30.asm` ledger entry remains unchanged.
The document keeps its original filename so existing links continue to work.

## Saved source and proof

- [Preferred body](../reverse/attempts/0x00960a30.cpp), including the canonical
  class members and subdivision companion needed for integration.
- [TU-local ABI declarations](../reverse/attempt_support/0x00960a30.inc).
  This unchanged declaration prefix retains its upstream license. Splitting
  the prefix keeps the bank below the 64 KiB banking limit.
- [Verification receipt](../reverse/attempt_support/0x00960a30-verification.json):
  source hashes, compiler options, all 51 differing offsets, and 17 sibling checks.
- [Earlier self-contained source archive](../reverse/attempt_history/0x00960a30/655db775d83c3ef215e70d9298cd3a8ebd870fae82fc54296a7ebf00fadf30a2.json).
  Its `source` field contains the complete **75-difference** predecessor before
  the include split. Keep it when retiring the bank: ordinary bank archives
  still depend on the companion include.

The actual bank was freshly compiled with the repository's original MSVC 7.1,
version `13.10.3077.0`. The normal `build.compile_function` resolver reports
51 differences, `unresolved=[]`, and `masked=False`; all 190 relocation tuples
are identical to the previous checkpoint. All 17 canonical owner/sibling
emissions pass from the same object. `tools/probe.py` independently confirms
51 non-relocation differences with no relocation-layout drift.

An independent reviewer also audited all 143 DIR32 operands: seven distinct
float constants, the common `render_state` base `0x01340EC0`, the real floor
IAT at `0x013593B8`, the empty Vector4 constructor callback and both EH cleanup
states. Both matched SegmentedLine and StreakLine wrappers call this exact
14,081-byte body with six stack arguments; its unique terminal `ret 0x18`
ends at VA `0x00D64131`, followed by 15 padding bytes.

Source/support hashes in the receipt use normalized LF text. Render hashes:

- Raw: `29ee090942e4e4c8dd21616977b5297e69c466f829b1893d9936e25eae6323cd`.
- Resolved: `ebedceb981e1efd684d010c29f25c87fd0545c2c44598a71171dfda41b7858d2`.

## What now matches

The frame is `0x6d84`; the body has 3,787 instructions and 51 calls. All 25
normalization sequences, all four endpoint blocks, three interior Cross
blocks, classifications, signs, plane producers and the full 513-byte matrix
region remain exact. The early body `[+0x700,+0x1800)` is exact.

The previous 69-difference checkpoint made the TOP-only projection use an explicit Y-Z-X dot
expression with a volatile read of `points[pidx].Y`. It removes exactly the
six bytes at `+0x3127`, `+0x3134`, `+0x313d`, `+0x3143`, `+0x315a` and
`+0x315c`; every other raw byte and relocation tuple is unchanged. The ordered
floating-point store/cleanup sequence is identical to the predecessor.

The 55-difference checkpoint included canonical `matrix3d.h` before the
existing TU ABI prefix. This restores all 14 chunk-loop reload bytes, with
every other raw byte and relocation tuple unchanged. Independent verification
confirms the same 17 exact siblings. A copied Matrix3D header and duplicate
multiply helper initially reproduced this result, but isolated experiments
showed that the include order alone is sufficient; neither is part of the bank.

The latest 51-difference checkpoint puts the BOTTOM Y-Z-X dot expression in
`DotSegLineBottomOutput`, an inline helper with a volatile `point.Y` read.
The TOP expression stays directly in Render. This removes exactly four more
bytes (`+0x2f9d`, `+0x2faa`, `+0x2fb0`, `+0x2fb9`) with every other byte and
relocation unchanged; both asymmetric projections now match together. The
helper boundary matters: spelling both dots directly in Render changes the
initial projection's live x87 temporary and was rejected.

The older predecessor's main improvement remains essential: ordinary in-place
`NormalizeMerge(pl)` with its original Dot/Cross consumers keeps the matrix,
endpoint and expansion lifetimes. Its reduction is `(Z*Z + Y*Y) + X*X`.
Replacing it with return-Z scalers previously regressed unrelated regions.

## Remaining differences

Offsets are relative to Render; the receipt lists each differing byte.

| Group | Bytes | Relevant locations |
|---|---:|---|
| Merge address base/index encodings | 40 | `+0x1f8f..+0x2422`, six regions |
| Merge classification X-product order | 2 | `+0x2147` and `+0x214b` |
| Initial output address encodings | 5 | `+0x2951`, `+0x2a13`, `+0x2a30` regions |
| Expansion TOP-X addition order | 4 | `+0x2d1d`, `+0x2d1e`, `+0x2d23`, `+0x2d24` |

The chunk-loop reloads now match retail: `num_points` into ECX, `chidx` into
EBX, then `chunk_size` into EAX. First entry still bypasses those reloads.
Equal-address SIB encodings remain real differences.

## Resume constraints and failed approaches

Keep the texture hidden-result ABI, canonical vertex-buffer reference call
at RVA `0x00904510`, expansion factor at object offset `+0x1c`, duplicate
`next_factor` calculation, `curr_int->Parallel` test and the retail
uninitialized `new_direction` path. All callees resolve already; no new pins
are needed. Preserve the float rounding stores and live extended-precision
values, especially the first BOTTOM endpoint's nonpop dot store/live Z product.

Useful negative evidence:

- Directly spelling both volatile-Y projection expressions in Render changes
  earlier initial-projection lifetimes and creates relocation-layout drift.
  Keep the BOTTOM helper boundary; local tail equality is insufficient.
- Integer-address/reversed-index spellings and pointer-variable casts leave
  all merge SIB bytes unchanged. Explicitly naming the edge-byte offset can
  change SIB order, but also changes the frame and many earlier instructions.
- Replacing expansion `top += delta` with separate X/Y/Z additions changes
  the merge SIB and X-product encodings, but regresses matrix and other float
  operations. This is a nonlocal compiler effect, not an accepted repair.
- Local ordering, register/const spellings and target-CPU switches did not fix
  the reloads. Bottom-tested loop forms changed matrix-temporary and endpoint
  lifetimes. Those CFG rewrites are unnecessary: the canonical matrix include
  order fixes the reloads while preserving the complete body.
- A double-accumulator asymmetric helper tested on the earlier 75-byte body
  fixed local tails/expansion but produced 14,097 bytes and 107 relocation
  drifts. Return-Z merge helpers likewise regressed the matrix.

Copy the bank and support include together. Reproduce it with:

```sh
python tools/probe.py reverse/attempts/0x00960a30.cpp \
  '?Render@SegLineRendererClass@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@ABVSphereClass@@PAVVector4@@@Z' \
  0x00960A30 --size 14081
```

Probe is diagnostic. Use the normal resolver for all actual relocated bytes,
check complete size and all 190 relocation tuples, and recheck the 17 sibling
rows before integration. Only a fully exact result may replace the generated
ledger row. Retire the preferred bank and its ABI support together on landing.
