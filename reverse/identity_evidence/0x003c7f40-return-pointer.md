# 0x003C7F40 returns an opaque pointer

The generated row at 0x003C8030 is an independent physical caller of the
184-byte body. Its call at +0x10 targets ILT 0x00029B31, which jumps to
0x003C7F40. The caller pushes three stack words and the callee returns with
`ret 0x0c`, so the callback takes three stack arguments.

The caller moves the returned EAX to ESI at +0x15, tests ESI at +0x17, loads a
vtable from `[esi]` at +0x1b, invokes vslot +0x190 at +0x2a, and decrements a
reference count at `[esi+4]` at +0x31. Thus EAX is a pointer to an object,
not an integer status. The vslot +0x7c call inside 0x003C7F40 returns EAX;
the body preserves it through `StringBase<char>::releaseBuffer` and returns
that same value. Both the virtual slot declaration and the free function must
return a pointer. `void *` preserves the proved ABI without inventing the
object's class.

The original 2026-09-24 conversion at `a99b617101` was byte-exact but used
`int` for both declarations because the return was not then checked against
this caller. Its exact 184-byte shape survives the pointer correction; the
symbol's MSVC return encoding changes from `H` to `PAX`. No semantic owner is
claimed: `Rva003C7F40` remains in the exported name.
