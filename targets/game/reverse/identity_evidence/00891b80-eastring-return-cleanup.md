# EAStringC destructor at RVA 00891B80

The existing `Rva00891B80::release` row describes the 22-byte operation but
keeps the owner opaque. The matched native `EAStringC::Mid(int) const`
(0089F1B0, 207 bytes) returns EAStringC by value. Its prologue pushes handler
VA 01057B81, which loads FuncInfo VA 01246F2C. State 0 has predecessor -1
and action 00C57B60. This action guards bit 1 at EBP-10, loads the hidden
result pointer at EBP+4, and jumps directly to 00891B80. The RET at C57B78
ends exactly 25 bytes before the independent state-1 action.

Both native predecessor states agree. The corresponding native action
`$L572` names `??1EAStringC@@QAE@XZ`; its out-of-line destructor is emitted by
the same unchanged EAStringCMid.cpp translation unit. This matched caller
lifetime identifies the exact retail copy independently of generic release
byte equality. The existing matched Mid spelling and return type are reused;
no public-name claim is inferred solely from the matching destructor bytes.

Raw 00891B80 loads the single data pointer, decrements its unsigned-short
reference count, and calls the free callback at pool VA 01337A30 + 4 only
when the count reaches zero. RET at 00891B95 and INT3 at 00891B96 prove the
complete 22-byte extent. This agrees with the native EAStringC destructor.

The correction preserves one identity and the exact extent, replacing the
opaque operation/provider with the native returned-string destructor. It
adds no new pin and no new coverage for the already matched 22-byte body.
The old source also supplies other independent addresses and is retained.
