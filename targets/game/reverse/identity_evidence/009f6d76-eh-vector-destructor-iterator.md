# `??_M@YGXPAXIHP6EX0@Z@Z` at 0x009F6D76 is the MSVC 7.1 CRT array-destruction helper

## The claim under review

`targets/game/reverse/functions.csv` line 13026 held

    ??_M@YGXPAXIHP6EX0@Z@Z,,0x009F6D76,72,game/Libraries/Source/WWVegas/WWLib/ArrayDeleteHelperBodyThunk.cpp,matched,Open-BFME5 exact C++ body;object-symbol=?ArrayDeleteHelperBodyThunk@@YAXXZ

That source is a `__declspec(naked)` / `__emit` transcription of the retail bytes
under the Open-BFME5 name `?ArrayDeleteHelperBodyThunk@@YAXXZ`, so it scores as a
dump, not as a conversion. The task is to recover the real body.

## The name is not a guess: it is the shipped library's own symbol

The toolchain's static CRT is in the tree:

    inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/lib/libc.lib

`tools/coffar.py read_archive` on that archive yields one member named
`..\build\intel\st_obj\ehvecdtr.obj` (8746 bytes). Its string table
(69 symbols, 4-byte length prefix at file offset 8573) contains exactly seven
external names:

    ?ArrayUnwindFilter@@YAHPAU_EXCEPTION_POINTERS@@@Z
    ?terminate@@YAXXZ
    ?__ArrayUnwind@@YGXPAXIHP6EX0@Z@Z
    __SEH_epilog
    __except_handler3
    __SEH_prolog
    ??_M@YGXPAXIHP6EX0@Z@Z

Walking the COFF symbol table (records of 18 bytes from file offset 7331, inline
8-byte names plus string-table offsets) gives the external FUNCTION symbols
(storage class 2, type 0x20):

    section 2  (18 B)  ?ArrayUnwindFilter@@YAHPAU_EXCEPTION_POINTERS@@@Z
    section 5  (94 B)  ?__ArrayUnwind@@YGXPAXIHP6EX0@Z@Z
    section 10 (96 B)  ??_M@YGXPAXIHP6EX0@Z@Z          <-- value 0

The member's three `.text` contributions are 18, 94 and 96 bytes. Section 10 is
the one whose first 72 bytes are our body, and its remaining 24 bytes are the
`__finally` funclet already held separately as `?d_009f6dbe@@YAXXZ` at
0x009F6DBE. 72 + 24 = 96, so the whole retail function, funclet included, is one
CRT function in one CRT object.

## The bytes are the library's bytes

Section 10 of `ehvecdtr.obj`, raw, before any relocation is applied:

    6a0c6800000000e8000000008365e4008b750c8bc60faf45100145088365fc00
    ff4d10780b2975088b4d08ff5514ebf0c745e401000000834dfcffe808000000
    e800000000c21000837de4007511ff7514ff7510ff750cff7508e800000000c3

`python3 tools/dis_retail.py 9f6d76 0x60` on
`inputs/baselines/bfme1/retail-1.03-unpacked` reads, over the same 96 bytes:

    6a 0c 68 80 58 14 01 e8 06 11 00 00 83 65 e4 00 8b 75 0c 8b c6 0f
    af 45 10 01 45 08 83 65 fc 00 ff 4d 10 78 0b 29 75 08 8b 4d 08 ff
    55 14 eb f0 c7 45 e4 01 00 00 00 83 4d fc ff e8 08 00 00 00 e8 08
    11 00 00 c2 10 00 83 7d e4 00 75 11 ff 75 14 ff 75 10 ff 75 0c ff
    75 08 e8 43 ff ff ff c3

Instruction for instruction the same body, with the four differences exactly at
the four relocation sites of section 10 (an imm32 scope-table operand and three
REL32 call displacements), which is the pre-link state any `.lib` member is in.
`tools/build.py` masks those sites for a `.lib`-sourced row, which is how the two
sibling claims on this same member already verify:

    ?ArrayUnwindFilter@@YAHPAU_EXCEPTION_POINTERS@@@Z  0x009F6D06  18 B
    ?__ArrayUnwind@@YGXPAXIHP6EX0@Z@Z                   0x009F6D18  47 B
    ??_M@YGXPAXIHP6EX0@Z@Z                              0x009F6D76  72 B   (this row)

## The signature in the name is the signature in the body

`??_M@YGXPAXIHP6EX0@Z@Z` and `?__ArrayUnwind@@YGXPAXIHP6EX0@Z@Z` carry
character-identical parameter encodings, and both `ret 0x10`, so both are

    void __stdcall f(void *base, unsigned elemSize, int count,
                     void (__thiscall *dtor)(void *));

(`P6EX0@Z` is the MSVC 7.1 mangling of a one-argument `__thiscall` pointer,
which is why only `ecx` is loaded before `call [ebp+0x14]`.) The body uses the
parameters the way that signature says: `imul eax,[ebp+0x10]` and
`dec dword [ebp+0x10]` treat slot 3 as the count, `call [ebp+0x14]` treats slot 4
as the element destructor, and `mov esi,[ebp+0xc]` keeps slot 2 as the element
size. The matched caller
`BfmeThingCDE::bfmeDtorCDE` at 0x008F8340
(`game/Libraries/Source/shroudmanager/shroudmanager_data.cpp`) pushes
`(m_array, 0x10, count, 0x00CF7BD0)` in that order — count in slot 3, element
destructor in slot 4 — so the real parameter order and the real caller agree.

The body destroys the array in reverse, `p = base + elemSize * count` then
`while (count-- >= 0) { p -= elemSize; dtor(p); }`, and the 12-byte scope table
in section 12 (`ff ff ff ff 00 00 00 00 00 00 00 00` = EnclosingLevel -1, no
filter, no handler) plus the 24-byte funclet that calls `__ArrayUnwind` only
when the state word at `[ebp-0x1c]` is still 0, is the standard SEH
array-unwind shape.

## Why this lands as a `vendored=` claim and not as C++ source

`??_M@YGXPAXIHP6EX0@Z@Z` is a reserved MSVC name. It is not the mangling of any
C++ declaration a translation unit can make — the `_M@YG...@Z` form is what the
compiler emits for `__eh_vector_destructor_iterator`, a helper the front end
calls rather than a function the CRT publishes under a source-level name. No
C++ source can therefore carry this decorated name, and no C++ source can be the
honest home for these bytes. The upstream identity IS the library, and the
library is in this tree; the two symbols immediately below this one in the same
`ehvecdtr.obj` are already landed that way
(`vendored=msvc71-crt;member=..\build\intel\st_obj\ehvecdtr.obj`). This row now
joins them, which is a real recovery of the real identity and of the real bytes
rather than a transcription of them.

## The dependency the lift was holding up

`game/Libraries/Source/WWVegas/WWLib/ArrayDeleteHelperBodyThunk.cpp` is the only
definition of `?ArrayDeleteHelperBodyThunk@@YAXXZ`, and
`shroudmanager_data.cpp:72` reaches the address through

    #pragma comment(linker, "/alternatename:?ArrayDeleteHelperBodyThunk@@YGXPAXII0@Z=?ArrayDeleteHelperBodyThunk@@YAXXZ")

so deleting the lift with that pragma unchanged leaves an unresolved external
and breaks two already-matched rows in `shroudmanager_data.cpp`. The alternatename
target is retargeted to the real CRT symbol in the same change. No call site,
argument or body byte in `shroudmanager_data.cpp` changes: the call was already
a `call rel32` to an external with four pushed stack arguments, and it still is.

`?ArrayDeleteHelperBodyThunk@@YGXPAXII0@Z` stays in `symbols.csv` as what it is,
an additive candidate pin whose note already says "callee pin for stdcall
array-delete helper". It is a near-miss on the real parameter types (it types
slots 3 and 4 as `unsigned` and `void *` where the library says `int` and a
`__thiscall` pointer) and it is not the identity; no pin is added or changed here.
