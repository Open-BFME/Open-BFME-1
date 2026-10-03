# RVA 0x009F7084: CRT vector-copy constructor finally action

The 24-byte retail body ends at RET 0x009F709B. The next bytes at
0x009F709C are an import jump, not padding or part of this action.
Ghidra's direct caller at VA 0x00DF7077 belongs to the 78-byte parent at
RVA 0x009F7036. The parent's existing archive identity is
`??__C@YGXPAX0IHP6EX00@ZP6EX0@Z@Z` in
`inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/lib/libc.lib`,
member `..\build\intel\st_obj\ehvccctr.obj`.

The unmodified member SHA-256 is
`a5c205fb211b86d53df5dcae61b59a930c060957d27daf4b72200aa3a6402f02`.
Its executable section 2 holds the parent at offset zero and `$L323`,
`$L325`, and `$L336` at the same offset 78. These are three labels for
one body, not alternative owners. `$L323` is the independently anchored
label: the member's `$T330` scope-table record has a DIR32 relocation at
offset 8 to `$L323`. Retail's parent pushes VA 0x011458A0, whose 12-byte
record is `{ -1, 0, 0x00DF7084 }`. The normal parent path also calls the
same action at RVA 0x009F7077.

The archive action bytes are:

```
83 7d e0 00 75 11 ff 75 1c ff 75 e4 ff 75 10 ff 75 08
e8 00 00 00 00 c3
```

The sole relocation, REL32 at action offset 19, names the original CRT
`?__ArrayUnwind@@YGXPAXIHP6EX0@Z@Z`. Retail's call at 0x009F7096 resolves
directly to its existing 47-byte body at 0x009F6D18. All twenty other bytes
match. This supplies independent binding evidence beyond the archive gate's
relocation masking.

The action checks the parent's completion flag at EBP-0x20, then supplies
the destructor, completed element count, stride, and array pointer to
`__ArrayUnwind`. Its frame-relative ABI is a compiler action, not a standalone
C++ callable. Preserve an opaque RVA identity and point to the unchanged
original archive member; no assembly lift, fabricated C++ owner, or new pin
is involved.
