# Address-derived codec caller and physical quantizer contract

No JPEG, vendor release, original class, or native formal parameter count is claimed.

## Caller boundary and address identity

The retail body at RVA `0x009A6B40` is exactly 93 bytes: its `ret` is at
`0x009A6B9C`, followed by INT3 padding. It accepts two stack words under cdecl:
entry ESP+4 is an opaque object pointer and entry ESP+8 is a word forwarded to
both existing codec bodies. Its receiver owner is unproved, so its name remains
`Rva009A6B40(void *, int)`.

The body compares words at byte offsets +0x38 and +0x3C+4*index, with index
read at +0; on inequality it copies +4 to +0x38, initializes the inverse map,
and calls RVA `0x009A6780` at `0x009A6B8B` and RVA `0x009A6630` at
`0x009A6B92`. Both calls push the same two words. The caller cleans 16 bytes
once, after both calls. The source uses memcpy to read object representation;
it introduces no guessed owner layout or aliasing promise.

## Independently existing initializer and data

The matched 37-byte `Rva009A6600InitBlocks` at RVA `0x009A6600` in
`Rva009A4D00TableInit.cpp` already performs the same initialization: the pointer
at +0x13C receives `g_rva01142408`, and bytes at +0x140 are indexed through
`g_rva01142308`. The new caller reuses that visible body and its existing data
symbols. Its DIR32 operands are +0x1C -> VA `0x01142408` and +0x33 -> VA
`0x01142308`. There are no new globals or pins.

Retail `g_rva01142308` is the verified 64-dword permutation of 0..63
(SHA256 `477a41fa6d9fd843864600082cefe2f3ccc83da572a45c14efe90b579d2cec0f`).
Retail `g_rva01142408` begins with the 64-dword identity map 0..63
(SHA256 `fea7b32778ecbdd7adee1941e98c89cf96bbc762f5f1beb0be24e36a456fbbc5`).
No new data extent is claimed.

## Quantizer ABI correction, with native formal count unknown

The complete existing quantizer is `[0x009A6780,0x009A6B31)`, 945 bytes,
ending in `ret` at `0x009A6B30`. Exhaustive E8/E9 operand scanning of retail's
.text finds exactly one direct route, the call at `0x009A6B8B`, and no ILT
routes. Disassembly from the independently proven caller start confirms that
site is an instruction boundary, not an operand coincidence. A tracked-source
search finds only the quantizer's original definition, before this caller was
added; there is no old symbols.csv pin.

The callee pushes EBX, EBP, ESI, then reads `[esp+0x10]` into ESI: entry ESP+4.
After pushing EDI it reuses `[esp+0x14]`, the same first-word home, as x87
conversion scratch. It never reads the second incoming word at entry ESP+8.
ECX is defined before being read. This is an ordinary cdecl stack-pointer
contract, not a private ECX receiver contract. The automatically inferred
thiscall/zero-stack-slots result is contradicted by these instructions.

The old one-word declaration was an emission view. The new declaration keeps
the actual caller's two-word contract and deliberately ignores its second
word. This does **not** prove how many parameters the original native source
formally declared. The change retires the old one-argument mangled row at this
address and retains exactly one caller-compatible identity:
`?Rva009A6780BuildQuantizers@@YAXPAURva009A6780State@@H@Z`.

The existing 945-byte implementation is unchanged apart from that unused
parameter; its 40 relocation sites and byte body remain exact. The existing
500-byte `Rva009A6BA0QuantizeBlock` sibling remains exact with all four of its
relocations. Existing `bfmeApply1040(BfmeS1040 *, int)` at RVA `0x009A6630` is
retained; no callee alias, pin, or new helper body is introduced.

## Verification and accounting

Before edits, the three source units passed 11/11 scoped rows, including
10 floating constants and 67 DIR32 references. Scratch probes separately
matched the new 93-byte body, the 945-byte caller-compatible definition, and
the unchanged 500-byte sibling. Official add_match and final three-source
gates verify all rows and operands before publication.

The new recovery is **93 bytes**. The existing 945-byte body receives an ABI
code-view correction and earns zero additional recovered bytes. No native
vendor identity is inferred from the codec algorithm.

Build-only audit and probe receipts are under `build/codec_9a6b40/` in the
owning `convert_prime_fifteenth_36h` checkout. The immutable retail image hash
and complete callee/caller disassemblies are recorded in its `audit.json`.
