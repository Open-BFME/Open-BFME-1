# 0x003C8030 partial: physical callee and opaque identities

The 64-byte retail body calls ILT 0x00029B31 at +0x10. That thunk reaches the
matched 0x003C7F40 callback, whose independently checked ABI and pointer
return are recorded in `0x003c7f40-return-pointer.md`. The old bank declared
this target `bfmeFindYU`, but the callee joins two strings with `"."` and
dispatches through receiver vslot +0x7c. The finder name did not describe a
proved function and cannot be kept as a callee identity.

The caller tests the returned pointer, calls its vslot +0x190 with
`flag == 0`, decrements the reference count at +4, and invokes slot zero if
it reaches zero. This proves the two slot offsets and the reference-count
offset, not the result object's class. The old `BfmeThingYU` type and
`bfmeReleaseYU` function were synthetic bank labels; earlier verdicts say
the owning class and method are unknown. `Rva003C8030Result` and
`Rva003C8030ReleaseResult` retain the address token.

The corrected C++ remains partial: 64/64 bytes, one relocation, 16
non-relocation byte differences versus the previous bank's 17. VC7.1
preloads all three callback arguments before saving ESI, while retail saves
ESI and then reloads argument one after pushing argument three. The rotated
registers carry into the flag and virtual call. An alternate typed-parameter
spelling made 18 differences. No exact byte match or live source claim is
made for 0x003C8030.
