# 008B2F50 base native-property dispatcher

Extent: 008B2F50..008B386A (RET 8 at +0x918), then a 16-entry DWORD jump table
at +0x91C (ids 1..16, `dec eax; cmp eax,0xf; ja; jmp [eax*4+table]`), 2396 B.

Owner: vtable 0x011369F0 slot 10 points at VA 0x00CB2F50. That vtable is
installed by the matched constructor `??0Rva008B2EF0@@QAE@II@Z` (0x008B2EF0),
which stores the native object at +0x20. The matched derived dispatcher
`?lookup@NativeProperties008B3C40@@...` (0x008B3C40, vtable 0x01136A40 slot 10)
calls this body first with (owner, key) as a two-argument `__thiscall` returning
a value pointer, which is the pinned ABI view
`?lookup@PropertyLookup008B2F50@@QAEPAURva00899560Value@@PAVNativeProperties008B3C40@@PAUString008B3C40@@@Z`.
No original class or method name is asserted; the names keep the address.

Body: returns 0 for a null owner, hashes the key through 0x008D5DC0 and
switches on ids 1..16. Ids 1 4 6 7 15 16 build lazy native-function singletons
in 0x01338360..0x01338374 (callbacks 0x008B2DB0 2DC0 2E60 2DD0 2DE0 2EA0);
the others wrap values returned by the native object's virtual slots (0x08/0x0C
name-value iteration, 0x14/0x18 list iteration, 0x20 0x2C 0x30 0x48 0x4C
objects, 0x34 0x40 strings, 0x3C integer) or return the fallback value
0x013379BC when the native object is absent.

The earlier stash used a raw `typedef unsigned int Word` for DWORD reads; it
was a storage spelling, not an identity, and the rewrite replaces it with the
typed value classes shared with the 0x008B3C40 sibling.
