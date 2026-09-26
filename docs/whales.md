# Large-function investigations

## Publication on main

Published as a partial on top of `main` at
`21d1669b178744fda0653049e22a8f0a7a083d88`, at the user's explicit request.
The investigation and fresh compiler measurements used the newer checkout
`4ba0bd9db8db94ad1cd0d69b256b72b96f55a506`; its local banking commit is
`c60bb1bfcacb008073710a0abd009536bb5564d6`. This older `main` does not yet
contain `tools/probe.py`. Reproduction commands below refer to the investigation
checkout's tooling. Only this bank, its prior/current source archives, the
experiment index and APT notes are carried here; no unrelated code, tool or
ledger changes are included. The bank source is identical to the measured one.

## 0x008BF100 — APT route-key registry initializer

Status: banked partial, refreshed 2026-09-26; no exact clean-C++ reconstruction.
Start from `reverse/attempts/0x008bf100.cpp`, not the earlier 0.2615 bank.

### Callee table

| Retail target | Count | Proven identity | Evidence |
| --- | ---: | --- | --- |
| `0x0089E680` | 178 | `?bfmeSetVKI@BfmeStrVKI@@QAEXPBD@Z` | `tools/callees.py 0x008BF100 18655`; every string block calls the same `thiscall` setter |
| callback cell at VA `0x01337828` | 1 | `Rva008C5D70Alloc` | indirect cdecl allocation of `hashCount * 4` bytes; the historical symbol names a callback cell, not a call to the body at RVA `0x008C5D70` |
| `0x00891B80` through EH cleanup funclets | 178 | `?release@Rva00891B80@@QAEXXZ` | retail cleanup funclets at `0x00C593C0` onward jump to the matched release body |

The ledger currently carries the generated placeholder as a no-argument
symbol, but the retail caller at `0x00894800` pushes `[edi+0x38]` before the
call. The clean reconstruction therefore uses `void d_008bf100(int hashCount)`;
that ABI correction is evidence, not a semantic name claim.

### Layout

- `g_bfmeRouteKeys1282` is 178 consecutive 4-byte string handles at
  `0x01338480..0x0133874b`; the first initialization loop fills two null
  handles per iteration from `g_bfmeDefaultString1284` at `0x012D5298`.
- The handle points at a short string header containing 16-bit reference
  count, length, capacity, and flags. The shared pool at `0x01337A30` releases
  the header when the count reaches zero.
- The 178 literals are the exact `reverse/string_xrefs.tsv` order from
  `__proto__` through `yMin`; each assignment constructs a temporary, calls
  `bfmeSetVKI`, retains the new handle, releases the old table handle, then
  releases the temporary.
- Retail reserves `0x2c8` bytes after the EH registration frame and has 178
  distinct cleanup states/temporary stack slots. The final three operations
  allocate, zero, and publish the hash array and count.

### Current checkpoint and remaining mismatch

VC7.1 13.10.3077 with `/O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc`
emits 18,655 bytes and 1,080 relocations. The probe reports 15 non-relocation
byte differences and one relocation-layout discrepancy. Its ranking score is
`0.9991959260251944` (1 - 15/18655); this masked positional score is not
relocation verification or an exact-match claim.

The residual is the first temporary cleanup. Retail stores the destination at
`+0x9A`, resets the EH state at `+0x9F` using `[esp+0x2D8]`, decrements and
compares the refcount, then saves EDI at `+0xAD`. Ours saves EDI at `+0x9A`,
shifting those operations by one byte and using `[esp+0x2DC]`. Both streams
realign at `+0xAE`. EDI's first working use is in the zeroing tail at `+0x48AB`.
The compiler cause remains unresolved; do not patch the object or add pushes.

Keep the corrected signed bound at table + `(0xB3 * 4)`, all 178 assignments
from `__proto__` through `yMin`, the constant fallthrough switch, forced-inline
assignment/destruction, and the release and initialization barriers. These
source forms reproduce the frame and scheduling; they do not identify the
original source. Every temporary still ends immediately after its assignment.

Fresh COFF/retail inspection reproduces the 0x2C8 allocation, all 178 distinct
temporary offsets in cleanup-state order, all 178 predecessors of -1, all 356
state writes before decrement/comparison, and 178 direct setter calls without
normal-path assignment/destructor helpers or runtime barrier calls. The tail
starts at `+0x488F` and spans 80 bytes. All retail unwind actions reach the
release at `0x00891B80`; the separate 22-byte destructor was independently
compared with that retail body, including its pool operand at VA `0x01337A30`.
Full relocation/string/global/import, EH-state-path and integration validation
remain required after fixing the instruction shape. No source ownership,
ledger or pin change is justified by this partial.

### Reproduction and tested alternatives

```sh
python3 tools/probe.py reverse/attempts/0x008bf100.cpp '?d_008bf100@@YAXH@Z' 0x008BF100 --size 18655 --all
```

The bank has no hard-coded listing path. For a listing, use a fresh scratch
copy with unique `/FAcs /Fa<path>.asm` options; preserve existing checkpoints.
The compact experiment index is
`reverse/attempt_history/0x008bf100/2026-09-26-index.md`. Full local sources,
diffs, logs, objects and COFF measurements remain under
`build/manual-008bf100/`, including `continue-20260926-033132/`.

Many tail, helper, inheritance, scope, branch, intrinsic and compiler-option
variants reproduce the identical 15-byte residue. Volatile refcount operations,
named Boolean conditions, asynchronous EH and exposed setter definitions
regress other requirements. The eight-assignment control reproduces the same
barrier/EH-store/save-order interaction. Read each experiment's parent and
fingerprint before retrying it; no attempted alternative improved the checkpoint.

No rows were added to `reverse/unlocked.txt`: this partial establishes the
callee/layout hypothesis for this body, but does not land a shared shim or a
byte-verified source body that would unlock a neighbour.
