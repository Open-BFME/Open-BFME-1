# 007C7FD0 origin-getters bank — NON-MATCHING

Banked at the user's request, without further matching. The supplied source
was `Open-BFME-1-manual-008bf100/build/manual-007c7fd0/`
`origin-getters-20260927-041050-95fa10/origin-getters.cpp`, from source checkout
`c60bb1bfcacb008073710a0abd009536bb5564d6`.

The complete original195805-byte TU is preserved byte-for-byte in
`../attempt_support/007c7fd0/origin-getters.inc`; SHA256:
`6fd3b206ca2fc0d411614d96b7476409e8b8d1e772169a0538ab53885b5682be`.
The small bank entry includes that companion, preserving all matrix-copy,
constant-buffer, dimension/origin getter, state-cache and owning-handle
helpers and their compiler visibility. This follows the existing companion
pattern used by00960A30 and keeps the bank entry within re_log's size limit.
All22 emitted-code reference headers inspected by an independent agent are
identical to the supplied checkout. Only include prefixes are migrated:
`reference/` to `inputs/reference/`, and leading `Code/` to `game/`.
The compiler settings and `stlport` marker are retained; the diagnostic
assembly output goes to ignored `build/007c7fd0-reproduction.asm`.

Fresh compilation reproduces the saved main machine-code listing **byte for
byte**:12153 bytes,912 relocations, frame320h. All549 separately emitted
cleanup/handler bytes also reproduce the original saved listing. Neither
comparison establishes a match to retail. Against the12130-byte retail
body there are6361 masked positional differences, first at+30h, and a23-byte
length penalty. The banking score is
`1 - (6361 + 23) / 12153 = 0.4746976055294989`.
The normalized instruction score0.995 is not a byte-match score. Probe exit0
means the experiment ran; this body is explicitly **not matched**.

The existing preferred bank scored0.0425 and remains in immutable history.
The banking tool selects this stronger complete attempt; it does not erase
the old source or overwrite a better-scoring attempt. No production source,
function ownership, pin, baseline or matched coverage is changed.

Remaining blockers include local StringClass temporary placement (+84h versus
+88h), unwind-state ordering, instruction/block placement and relocation-site
alignment. The supplied analysis has six origin-first x87 sequences and six
dimension spill/FILD sequences, but that does not establish whole-function
floating-point, relocation, ABI or unwind equivalence. No runtime claim is
made. The original full TU is retained so a later investigation starts from
the exact experiment rather than a function excerpt with missing helpers.

From the repository root, reproduce with the normal configured VC7.1/Wine
toolchain and Python environment:

```sh
python3 tools/probe.py targets/game/reverse/attempts/0x007c7fd0.cpp '?set@FlatTerrainShaderPixelShader@@UAEHH@Z' 0x007C7FD0 --size 12130
```

`verification.json` in the companion directory records hashes, the compiler invocation
and measured result; `probe.txt` retains the concise comparison. The main raw
code hash is `a2b1b380dcf50669781e231bc4888a6270e142065a3e1c721a0a6048e08cbaaf`.
