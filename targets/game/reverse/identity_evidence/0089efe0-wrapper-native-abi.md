# Ordinary C++ wrapper at RVA 0x0089EFE0

The 35-byte native body at RVA `0x0089EFE0` is recovered in ordinary C++ in
the existing original Apt string TU. Its original class and member identity
are unknown. `Rva0089EFE0::method` is an address-derived emission view and
claims no vendor method name, object size, fields or semantic identity.

## Complete wrapper and boundary

Native bytes:

```
518a442408681c3007018d54240466c74424042a005288442408e8b1f2ffff59c20400
```

The start is independently INT3-delimited. The preceding 16 bytes are
`5f5e5bc20800cccccccccccccccccccc`; the 16 bytes after the final `RET4` are
`cccccccccccccccccccccccccc6aff68`. The original generated row independently
records the same 35-byte carved range and `ret+int3` end. It is replaced at
exactly that extent; no generated source is modified.

Incoming ECX is retained for the direct call at RVA `0x0089EFFA`. The wrapper
reads one stack byte, initializes a two-byte local string from `"*"`,
replaces its first byte with that argument, and passes it together with the
actual empty literal at VA `0x0107301C`. The call targets RVA `0x0089E2B0`.
The wrapper forwards EAX unchanged, restores its local stack space, and ends
with `RET4`. A byte argument and 32-bit integral result are compatible
emission views; original parameter signedness and vendor declarations are
not claimed.

Existing `ea_evidence.csv` attributes the wrapper to
`Libraries/Source/Apt/string/EAString.cpp` via `retail-run` and the callee to
the same file via `wb1`. The authored file already contains an independently
matched 209-byte sibling. That sibling and its declarations are unchanged.
No existing shared header covers the new address-derived view.

## Independently proven callee ABI

The prior attempt stopped because the generated callee name
`?d_0089e2b0@@YAXXZ` is not a usable native ABI declaration. The complete
native callee is 503 bytes at RVA `0x0089E2B0`; its SHA256 is
`020ace16e4deb94b7196d8598d92954d0f4d619d2bd1ac9086cf729c6f243e77`.
Two agents independently read that full native body.

- `MOV EDI,ECX` at `+0x1F` preserves the receiver.
- Two stack pointers are read as NUL-terminated byte strings.
- All three normal exits use `RET8`, at `+0x54`, `+0xB0`, and `+0x1F4`.
- Early exits explicitly set EAX to zero. The success exit at `+0x1E4`
  explicitly moves the accumulated ESI count to EAX.
- The wrapper keeps that result live through its own return.

The new pin is therefore a `__thiscall` method with two `const char*` stack
arguments and a 32-bit integral result:
`?rva0089E2B0@Rva0089EFE0@@QAEHPBD0@Z` at RVA `0x0089E2B0`.
Both wrapper and callee names retain their complete addresses. The receiver
view is reused because the wrapper passes the same incoming ECX unchanged;
no invented layout or original owning class is implied.

An exhaustive raw-backed native E8/E9 scan finds the wrapper's decoded call
as the callee's sole direct reference, with no E9/ILT route and no literal-VA
reference. The wrapper itself has no direct E8/E9 or literal-VA reference.
No existing real-name callee pin, export, correction or independently proven
`EAStringC::Replace` declaration was found. The callee's generated row and
source remain unchanged; it gains no conversion credit.

## Verification and accounting

The first source probe is exactly 35/35 bytes. The official `add_match.py`
replacement and then the final official-source re-verification both pass.
The final whole-file scoped gate verifies both functions, 244 bytes total,
the actual empty-string reference, and both remaining DIR32 data references.
The compiler wrapper has exactly two relocations: the empty literal at
`+0x06` and the independently proven callee REL32 at `+0x1B`.

The new callee pin passes individual consistency checks. The complete
`pin_consistency.py --check` passes with zero new/stale/baselined conflicts;
all route notes are independently re-derived and guarded imports agree.
No header, baseline, generated body, datum or unrelated callee pin changes.

`progress.py origin/master` measures 35 new C++/headline/authored-card bytes.
Retail-text C++ exact coverage increases 35 bytes and ASM-only coverage
decreases 35 bytes; total retail-text exact coverage is unchanged. This is
one recovery, not a new native extent. No physical selected C++ provider
for the still-unconverted 503-byte callee or runtime closure is claimed.

Scratch probe, actual object/native operand evidence and scoped gate logs
are in `build/rva0089efe0/` in the contributing checkout. Original native
wrapper SHA256 is
`07c0e2bc927ce75b2640f1a4ab8f850c9b3aaab59d7a3cf14a56fe3a62a4179f`.
