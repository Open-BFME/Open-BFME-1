# 0x000BE090 is `_M_fill_insert@vector<vector<W4ScienceType>>`, not `@vector<vector<UICoord2D>>`

The name on this row arrived with the 2026-08-11 Open-BFME5
`VectorVectorICoord2DFillInsertThunk.cpp` lift (the old note read
"Open-BFME5 exact C++ __emit thunk converted from MASM dump"), and it is
wrong. The real body is the STLport `vector<vector<ScienceType>>` element
instantiation, which is what `symbols.csv` already pins at this address
(harvested by hand, "independent BE090 decode checks count and capacity in
12-byte records then copies ScienceVec via ILT12C1").

## The bytes cannot decide this, so three independent things do

Both candidate element types are 12-byte STLport vectors -- three
pointers -- whose element is a class with a copy constructor and an
assignment operator, so the *shape* of `_M_fill_insert` is identical
either way and the byte-match is blind to the spelling. What separates
them:

1. **The only caller is a matched caller that names the type.**
   `?j_0000fc86@@YAXXZ` (0x0000FC86) jumps to 0x000BE090, and its one
   call site is the grow branch of `?resizeGroups@Rva000BE440Store@@` at
   0x000BE300, which pushes `(finish, count - size, &value)`. That body
   is `matched` from
   `game/GameEngine/Source/Common/INI/Rva000BE440ScienceGroups.cpp`, whose
   source types the receiver `vector<ScienceVec>` and whose ledger note
   already reads "native nested ScienceVec resize ... fill-insert".

2. **The element this body copies is 4 bytes wide.** The copy constructor
   reached through ILT 0x000012C1 (0x000BB890) loops `mov esi,[eax];
   mov [ecx],esi; add eax,4; add ecx,4` and derives its element count with
   `sar ecx,2`; its two callees are `operator new[]` for a 4-byte class
   (0x0001E2A4 -> 0x000B9800) and `_Vector_base(count, allocator)` over a
   4-byte const-data element (0x0001E579 -> 0x000BB4E0). `ICoord2D` is
   `{long x, long y}`, 8 bytes, so an `ICoord2D` copy constructor could not
   produce those 4-byte strides.

3. **The whole walk family bottoms out in 4-byte element code.** `fill`
   (0x000BCC50) and `__copy_backward` (0x000BCCE0) stride 12 and assign
   through 0x00018A70 -> 0x000BC4B0; `__uninitialized_copy` (0x000BC3C0)
   and `uninitialized_fill_n` (0x000BC460) construct through
   0x0000E705 -> 0x000BC360. Both terminals divide their *inner* element
   count by four -- `sar ecx,2` at 0x000BC4B0:0x25, the same shape at
   0x000BB890:0x1A -- so the 12-byte element is a vector over a 4-byte
   type. `ICoord2D` is `{long x, long y}`: 8 bytes, `sar 3`. The 0x00018A70
   pin already reads `??4?$vector@W4ScienceType@...`
   ("PlayerTemplate science-vector assignment callee").

## The compiler agrees

Writing the specialization as
`_STL::vector<_STL::vector<ScienceType> >::_M_fill_insert` over
`enum ScienceType` mangles to exactly the pinned decoration at
`symbols.csv:13931`, outer-allocator `@2@` rebind included, and compiles
to 421 bytes that match retail's boundary exactly. The lift's ICoord2D
name is therefore retired here; the byte coverage is unchanged, and the
address keeps its only identity.

The four walk helpers this body calls had no ScienceType name, so the
landing adds four pins, each at the address its own call site proves:
`__copy_backward` 0x000BCCE0, `__uninitialized_copy` 0x000BC3C0, `fill`
0x000BCC50, `uninitialized_fill_n` 0x000BC460. The element type of those
names is the one proven above, and each terminal already carries a
ScienceType pin (0x000BC4B0 / 0x000BB890), so this completes a pinned
family rather than guessing one.

## Not this lane's rows

The ledger names on 0x000BCCE0 and 0x000BCC50
(`??$__copy_backward@...UICoord2D...`, `??$fill@...UICoord2D...`) and the
`pair`/`Elem12` placeholder names at 0x000BC360, 0x000BC3C0 and 0x000BC460
are the same lift-inherited spelling error over the same bytes, but they
are separate bodies with their own rows; no new identity is asserted for
them here, and retiring their names is their own lane's work.
