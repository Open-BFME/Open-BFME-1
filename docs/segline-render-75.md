# SegLineRendererClass::Render: 75-byte partial checkpoint

As of 2026-09-11, the reconstruction produces **14,081 bytes with 75 actual
resolved byte differences** at RVA `0x00960A30` (VA `0x00D60A30`). This is
99.467% byte similarity, not a completed conversion or a runtime correctness
claim. The user requested saving this checkpoint for a later session.
The existing `Code/gen_asm/d_00960a30.asm` ledger entry remains unchanged.

## Saved source and proof

- [Preferred body](../reverse/attempts/0x00960a30.cpp), including the existing
  canonical class members and subdivision companion needed for integration.
- [TU-local ABI declarations](../reverse/attempt_support/0x00960a30.inc).
  These are the unchanged 32,489-byte declaration prefix, with its license.
  Splitting this prefix keeps the banked body below the bank tool's 64 KiB
  limit without renaming helpers, deleting definitions, or changing gates.
- [Verification receipt](../reverse/attempt_support/0x00960a30-verification.json):
  hashes, compiler options, all 75 differing offsets, and 17 sibling checks.
- [Self-contained source archive](../reverse/attempt_history/0x00960a30/655db775d83c3ef215e70d9298cd3a8ebd870fae82fc54296a7ebf00fadf30a2.json).
  Its `source` field contains the entire TU before the include split. Keep
  this archive when retiring the preferred bank; the ordinary bank archive
  alone still depends on the companion include.

The actual banked source was freshly compiled with the repository's original
MSVC 7.1 compiler, version `13.10.3077.0`, after updating to master
`467265486735e46b3408866131fb58f4b91cd0d2`. Its Render bytes and all 190
relocation records exactly equal the separately compiled, unsplit candidate.
The normal `build.compile_function` resolver reports 75 differences,
`unresolved=[]`, and `masked=False`. All 17 existing owner/sibling emissions
pass from that same object. `tools/probe.py` independently reports the same
size and 75 non-relocation differences, with no relocation-layout drift.

Raw Render SHA256:
`a233061ecdd0f3a12fc73b616b5b0bc7b7dfc2f34ec749ad13def90c94bea6cb`.
Resolved Render SHA256:
`3276d5b880d5cef9bfbd173f98e809fb13c47cc7cf9caea02fcfe6dcb242edbb`.

## What now matches

The frame is `0x6d84`; the function has 3,787 instructions and 51 calls.
All 25 complete normalization sequences match, including their length
reductions, zero tests, inverse calls, scaling and cleanup. All four endpoint
blocks, three interior Cross blocks, classifications, signs, plane producers
and projections match. The full 513-byte matrix region and the early body
`[+0x700,+0x1800)` are exact. Initial and paired projection blocks of 177 and
169 bytes are exact.

The ordered sequence of 425 floating-point stores and cleanup operations
matches after canonicalizing proven equal-address base/index encodings:
324 floating-result memory stores, 28 integer-result stores, and 73 register
cleanups. This comparison checks operation order and stack homes, not just
counts. Equal-address encodings still count toward the 75 actual differences.

The decisive final change replaced a return-Z scaler and volatile-reference
merge consumers with ordinary in-place `NormalizeMerge(pl)` and the original
Dot_Product/Cross_Product consumers. Its length reduction remains
`(Z*Z + Y*Y) + X*X`. This restored 28 matrix bytes, 12 expansion Y/Z bytes and
two final output-address bytes while reversing two TOP-only X-product bytes:
115 differences became 75. The previously original-verified best was 103.
The full 580-byte merge block still contains 18 differing SIB bytes; its
arithmetic and lifetimes match, but that block is not literally byte-exact.

## Remaining differences

Offsets are relative to the start of Render. Exact individual byte offsets
are recorded in the verification JSON.

| Group | Bytes | Relevant locations |
|---|---:|---|
| Three chunk-loop reloads | 14 | `+0x43b..+0x449` |
| Merge address base/index encodings | 40 | `+0x1f8f..+0x2422`, six separated regions |
| Merge classification X-product order | 2 | instructions at `+0x2147` and `+0x214b` |
| Initial output address encodings | 5 | `+0x2951`, `+0x2a13`, `+0x2a30` regions |
| Expansion TOP-X addition order | 4 | `+0x2d1d`, `+0x2d1e`, `+0x2d23`, `+0x2d24` |
| BOTTOM-only projection | 4 | `+0x2f9a..+0x2ff0` |
| TOP-only projection | 6 | `+0x3121..+0x317a` |

Retail reloads `num_points` into ECX, `chidx` into EBX, then `chunk_size`
into EAX. The candidate loads EBX, EAX, ECX instead. The first iteration
bypasses these reloads. Both versions reach the same clamp instructions at
`+0x44a`; a fix must preserve that first-entry path and the frame.

## Resume constraints and failed approaches

Keep the texture hidden-result ABI, canonical vertex-buffer reference call
at RVA `0x00904510`, expansion factor at object offset `+0x1c`, duplicate
`next_factor` computation, `curr_int->Parallel` test and the retail
uninitialized `new_direction` path. Do not fix apparent source oddities
without checking the original instructions. The bank already resolves every
callee; no new alias pins are required for this checkpoint.

Preserve float rounding stores and live extended-precision values. In the
first BOTTOM endpoint, the dot is consumed by X scaling while Z remains live;
an extra cleanup at the old `+0x10a2` location is a regression. In the
asymmetric projections, the nonpop dot store and live Z product matter.
The expansion keeps three factor reads, rounded scaled deltas, and its
original output homes. All 25 normalization sequences must remain exact.

Useful negative evidence for choosing the next experiment:

- The documented integer-address SIB lever was tested on all 11 merge field
  accesses of an earlier canonical-layout candidate. Both offset-first and
  pointer-first forms produced identical bytes and relocations. Changing only
  pointer producers was also inert.
- Loop-local declaration orders, scalar helper boundaries, register/const
  spellings, G5/G6/G7 controls and peeled volatile forms failed to reproduce
  the reload order without other changes. A combined subtraction/clamp helper
  still reloaded index, capacity, total in that order in the miniature.
- Return-Z merge helpers caused the matrix operand regression. Local matrix
  multiplication rewrites did not repair it reliably; restoring the original
  merge lifetime structure did. This compiler's changes can propagate far
  beyond the edited block.
- The double-accumulator asymmetric helper was finally retested on this
  75-byte source. Both asymmetric tails and expansion became locally exact,
  but the function grew to 14,097 bytes, with 107 relocation-layout drifts,
  an extra first-BOTTOM dot cleanup and 28 matrix differences. It was rejected.
- A direct paired-TOP lifetime formulation fixed expansion X in an earlier
  context but introduced endpoint cleanup. Transferring that unit to this
  75-byte source remains untested; do not treat it as a known improvement.

Copy the bank and its support include together, or extract the complete
archive to a scratch TU. Start by reproducing the checkpoint:

```sh
python3 tools/probe.py reverse/attempts/0x00960a30.cpp \
  '?Render@SegLineRendererClass@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@ABVSphereClass@@PAVVector4@@@Z' \
  0x00960A30 --size 14081
```

Probe is diagnostic; use the normal resolver to verify all actual relocated
bytes before accepting an improvement. Keep experiments under ignored
`build/`, check complete function size and all 190 relocation tuples, and
recheck the 17 sibling rows when integrating. Only a fully exact result may
replace the generated ledger entry. Retire the preferred bank and its ABI
support together when the function eventually lands.
