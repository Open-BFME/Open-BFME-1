# 0x000BDF20 is `_M_insert_overflow@vector<vector<W4ScienceType>>`, not `@vector<vector<UICoord2D>>`

The name on this row arrived with the 2026-08-11 Open-BFME5
`VectorVectorICoord2DInsertOverflowThunk.cpp` lift, a naked `__emit` copy of
the 284 retail bytes, and it is wrong. This is the same lift-inherited
spelling error already retired on the sibling `0x000BE090`
(`000be090-science-type-fill-insert.md`); the body is the STLport
`vector<vector<ScienceType> >` element instantiation, and `symbols.csv:14726`
already pins that name at this address.

## The bytes cannot decide this, so the callers and the callees do

Both candidate element types are 12-byte STLport vectors -- three pointers --
over a class with a copy constructor and a destructor, and the *shape* of
`_M_insert_overflow` is identical either way. The stride is fixed
(`add esi,0xc` / `add edi,0xc` in all four copy loops, `lea ecx,[ecx+ecx*2];
shl eax,2` for `12*(oldSize+growth)` at the allocation). What separates them:

1. **Two matched callers name the type, and they are the science parser.**
   `python3 tools/callers_of.py 0x000BDF20` gives three call sites:

   - `0x000BE090` `?_M_fill_insert@?$vector@V?$vector@W4ScienceType@@...`,
     `matched` from
     `game/GameEngine/Source/Common/INI/ScienceGroupVectorFillInsert.cpp`,
     whose receiver is `vector<ScienceVec>` and whose only out-of-line call is
     `this->_M_insert_overflow(position, value, _IsPODType(), count)`;
   - `0x000BE440` `?Rva000BE440@@YAXPAVINI@@PAX1PBX@Z`, `matched` from
     `game/GameEngine/Source/Common/INI/Rva000BE440ScienceGroups.cpp`, which
     declares `typedef _STL::vector<ScienceType> ScienceVec` and
     `typedef _STL::vector<ScienceVec> ScienceGroupVec`;
   - `0x000BE2A0` `?push_back@?$vector@UGen_t_000be2a0_p12cd@@...`, a
     gen-tgrid payload member whose element is also 12 bytes.

   The third caller cannot separate the two spellings -- a 12-byte element
   generates identical code for either -- but the two matched sources that
   share this INI home both name `vector<ScienceVec>`.

2. **The element is a vector over a four-byte type.** Every copy of one
   element goes through 0x0000E705 -> 0x000BC360, and that body calls
   0x000BB890 through `?j_000012c1@@YAXXZ`. 0x000BB890 derives its inner count
   with `sar ecx,2` and copies `mov esi,[eax]; mov [ecx],esi; add eax,4;
   add ecx,4`. `ICoord2D` is `{long x, long y}`: eight bytes, `sar 3`, so an
   `ICoord2D` copy constructor cannot produce those strides. The teardown
   0x0002211F -> 0x000BDCA0 closes the same 12-byte loop and calls the
   matching destructor per element. The same four-byte terminal sits under the
   `fill` / `__copy_backward` pair of the 0x000BE090 family (0x000BC4B0:0x25
   `sar ecx,2`).

3. **The 12-byte element is a vector, not a plain record.** The element is
   constructed and destroyed through helpers, never copied inline, and both
   helpers are the vector copy constructor / vector destructor of a 12-byte
   record. `vector<ICoord2D>` is also 12 bytes, so this is consistent with
   either name; point 1 is what decides it.

## The compiler agrees

`game/GameEngine/Source/Common/INI/ScienceGroupVectorInsertOverflow.cpp`
declares the instantiation over `enum ScienceType` and
`_STL::vector<ScienceType, _STL::allocator<ScienceType> >`, exactly as
`ScienceGroupVectorFillInsert.cpp` does for the sibling `0x000BE090`, and
explicitly instantiates `vector<ScienceVec, allocator<ScienceVec> >`. The
mangled name is character-for-character the decoration `symbols.csv:14726`
already pins, and `tools/probe.py` reports `EXACT (modulo relocation slots)`
on 284 bytes, with no /EHsc: retail built this instantiation without an SEH
frame, the same as the other 12-byte-element bodies in the
`RvaVectorInsertOverflowInlineCopy.cpp` family.

The lift's ICoord2D name is retired here. The naked `__emit` copy and its
`bfme_VectorVectorICoord2DInsertOverflow_0BDF20` object symbol are deleted;
`?b_000bdf20@@YAXXZ` and the `Gen_t_000be2a0_p12cd` payload pin stay as the
address aliases they are.

## Two pins travel with the body

The body calls two helpers whose names are its own, so the landing adds one
pin for each, at the address the call site proves, exactly as
`RvaVectorAllocateAndCopy.cpp` documents for its own ILTs:

- `??$BfmeElementConstruct<V?$vector@W4ScienceType@@...>` at 0x0000E705, the
  ILT all four copy sites of this body call, routing to 0x000BC360;
- `?_M_clear@?$vector@V?$vector@W4ScienceType@@...>` at 0x0002211F, the ILT
  the teardown call reaches, routing to 0x000BDCA0.

Neither disturbs an existing pin: 0x0000E705 and 0x0002211F each already carry
one alias for a different element spelling, and build.py treats a name at
several addresses as a resolution candidate.

## Not this lane's rows

0x000BCC50 (`??$fill@...UICoord2D...`), 0x000BCCE0
(`??$__copy_backward@...UICoord2D...`) and the `pair`/`Elem12` placeholders at
0x000BC360, 0x000BC3C0 and 0x000BC460 carry the same lift-inherited spelling
error over the same bytes. They are separate bodies with their own rows, and
retiring their names is another lane's work.
