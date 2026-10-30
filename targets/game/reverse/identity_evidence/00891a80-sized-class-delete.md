# 0x00891A80: sized class operator delete through TheBfmeFree

Retail 0x00891A80 is `jmp dword ptr [0x01337830]` followed by int3 padding
(6 B). VA 0x01337830 is ?TheBfmeFree@@3P6AXPAXI@ZA (data_rows, matched), the
sized-deallocation hook the matched installer fills.

The gen_small row `?ji_00891a80@@YAXXZ` (imports_000.cpp) treats it as an
import thunk, but it is a code body called by REL32: a byte scan of retail
.text finds 43 `call 0x00891A80` sites, all in EH unwind funclets between
0x00C56C86 and 0x00C5A54C, each preceded by `push 0x10; mov eax,[ebp+x];
push eax`. That is the cleanup of a class-scope `new` of a 16-byte object
whose class declares `operator delete(void *, size_t)`; the funclet passes
sizeof = 16 and pops 8 itself (cdecl static member).

Rva00891A70Alloc (0x00891A70, `jmp [0x01337828]`, the paired allocator hook)
sits directly before it, as a class's operator new/delete pair.

Which class (or common base) owns the pair is NOT recovered: the 43 funclets
belong to many parents, so the existing ??3Rva008A9B00 pin is only one
consumer's view. The address-derived name ??3Gen_uws16_00891a80@@SAXPAXI@Z
(existing gen-uw pin read from the funclet bytes; called by
Rva008CDC00TargetPath.cpp) is used.

C++: `static void operator delete(void *, unsigned int) { TheBfmeFree(p, n); }`
compiles (/O2) to the same `jmp [TheBfmeFree]`.
