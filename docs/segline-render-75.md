# SegLineRendererClass::Render: 69-byte partial checkpoint

As of 2026-09-12, the reconstruction produces **14,081 bytes with 69 actual
resolved byte differences** at RVA `0x00960A30` (VA `0x00D60A30`). This is
99.510% byte similarity, not a completed conversion or a runtime correctness
claim. The `Code/gen_asm/d_00960a30.asm` ledger entry remains unchanged.
The document keeps its original filename so existing links continue to work.

## Saved source and proof

- [Preferred body](../reverse/attempts/0x00960a30.cpp), including the canonical
  class members and subdivision companion needed for integration.
- [TU-local ABI declarations](../reverse/attempt_support/0x00960a30.inc).
  This unchanged declaration prefix retains its upstream license. Splitting
  the prefix keeps the bank below the 64 KiB banking limit.
- [Verification receipt](../reverse/attempt_support/0x00960a30-verification.json):
  source hashes, compiler options, all 69 differing offsets, and 17 sibling checks.
- [Earlier self-contained source archive](../reverse/attempt_history/0x00960a30/655db775d83c3ef215e70d9298cd3a8ebd870fae82fc54296a7ebf00fadf30a2.json).
  Its `source` field contains the complete **75-difference** predecessor before
  the include split. Keep it when retiring the bank: ordinary bank archives
  still depend on the companion include.

The actual bank was freshly compiled with the repository's original MSVC 7.1,
version `13.10.3077.0`. The normal `build.compile_function` resolver reports
69 differences, `unresolved=[]`, and `masked=False`; all 190 relocation tuples
are identical to the previous checkpoint. All 17 canonical owner/sibling
emissions pass from the same object. `tools/probe.py` independently confirms
69 non-relocation differences with no relocation-layout drift.

An independent reviewer also audited all 143 DIR32 operands: seven distinct
float constants, the common `render_state` base `0x01340EC0`, the real floor
IAT at `0x013593B8`, the empty Vector4 constructor callback and both EH cleanup
states. Both matched SegmentedLine and StreakLine wrappers call this exact
14,081-byte body with six stack arguments; its unique terminal `ret 0x18`
ends at VA `0x00D64131`, followed by 15 padding bytes.

Source/support hashes in the receipt use normalized LF text. Render hashes:

- Raw: `6895ee9a13517b68afa6eb6e64c8394d4c09a077cc30e8c3f7d5031fe2d0d851`.
- Resolved: `90deb703963eff60072dccbd672457317183da70577d299ed7bfb5c976363e83`.

## What now matches

The frame is `0x6d84`; the body has 3,787 instructions and 51 calls. All 25
normalization sequences, all four endpoint blocks, three interior Cross
blocks, classifications, signs, plane producers and the full 513-byte matrix
region remain exact. The early body `[+0x700,+0x1800)` is exact.

The new change makes the TOP-only projection use an explicit Y-Z-X dot
expression with a volatile read of `points[pidx].Y`. It removes exactly the
six bytes at `+0x3127`, `+0x3134`, `+0x313d`, `+0x3143`, `+0x315a` and
`+0x315c`; every other raw byte and relocation tuple is unchanged. The ordered
floating-point store/cleanup sequence is identical to the predecessor.

The predecessor's main improvement remains essential: ordinary in-place
`NormalizeMerge(pl)` with its original Dot/Cross consumers keeps the matrix,
endpoint and expansion lifetimes. Its reduction is `(Z*Z + Y*Y) + X*X`.
Replacing it with return-Z scalers previously regressed unrelated regions.

## Remaining differences

Offsets are relative to Render; the receipt lists each differing byte.

| Group | Bytes | Relevant locations |
|---|---:|---|
| Three chunk-loop reloads | 14 | `+0x43b..+0x449` |
| Merge address base/index encodings | 40 | `+0x1f8f..+0x2422`, six regions |
| Merge classification X-product order | 2 | `+0x2147` and `+0x214b` |
| Initial output address encodings | 5 | `+0x2951`, `+0x2a13`, `+0x2a30` regions |
| Expansion TOP-X addition order | 4 | `+0x2d1d`, `+0x2d1e`, `+0x2d23`, `+0x2d24` |
| BOTTOM-only projection | 4 | `+0x2f9a..+0x2ff0` |

Retail reloads `num_points` into ECX, `chidx` into EBX, then `chunk_size`
into EAX; ours loads EBX, EAX, ECX. First entry bypasses those reloads.
Equal-address SIB encodings still count as real differences.

## Resume constraints and failed approaches

Keep the texture hidden-result ABI, canonical vertex-buffer reference call
at RVA `0x00904510`, expansion factor at object offset `+0x1c`, duplicate
`next_factor` calculation, `curr_int->Parallel` test and the retail
uninitialized `new_direction` path. All callees resolve already; no new pins
are needed. Preserve the float rounding stores and live extended-precision
values, especially the first BOTTOM endpoint's nonpop dot store/live Z product.

Useful negative evidence:

- The matching volatile-Y expression also fixes the BOTTOM tail in isolation,
  but combining both fixes changes earlier initial-projection lifetimes and
  creates relocation-layout drift. Local tail equality is insufficient.
- Integer-address/reversed-index spellings and pointer-variable casts leave
  all merge SIB bytes unchanged. Explicitly naming the edge-byte offset can
  change SIB order, but also changes the frame and many earlier instructions.
- Replacing expansion `top += delta` with separate X/Y/Z additions changes
  the merge SIB and X-product encodings, but regresses matrix and other float
  operations. This is a nonlocal compiler effect, not an accepted repair.
- Local ordering, register/const spellings and target-CPU switches did not fix
  the reloads. Bottom-tested loop forms fix the order but alter the final
  matrix temporary and endpoint cleanup lifetimes.
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
