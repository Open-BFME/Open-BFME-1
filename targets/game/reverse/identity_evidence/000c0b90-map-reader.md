# MapMetaDataReader destructor C0B90 and action BF8EA6

The Zero Hour INIMapCache.cpp defines MapMetaDataReader at line48 and
constructs its local reader in parseMapCacheDefinition at line126. BFME's
matched C1E50 parseMapCacheDefinition likewise constructs the reader through
C0EA0, reads the same fields and destroys it through ILT3404F -> C0B90.
Its existing native source Rva000C1E50MapCacheDefinition.cpp gives this
last call an address-derived derived-class view; the Zero Hour twin and
matched constructor establish the underlying owner independently.

Raw C0B90 decodes to RET C0C2D, then INT3 from C0C2E (158 bytes).
Its actual prologue names handler BF8ED8 -> FuncInfo DE678C -> unwind
map DE6764. State2 selects BF8EA6. That complete22-byte action destroys
eight12-byte Coord3D elements at this+3C through callback ILT1364C,
returns BF8EBB, then the next action starts BF8EBC. The normal destructor
independently uses the same address/count/stride/callback. Ghidra agrees.

The destructor uses actual native member destruction in the existing
constructor TU. Grouping the trailing eight20-byte player records fixes
the old bank's nine non-relocation differences; this is the same lifetime
grouping used in the matched MapMetaData destructor. No new callback alias
is introduced. Both list destructors outline to the callee printed by
callees.py: ILT344F0 ->76B00, canonical STLport _List_base<Coord3D>.

The existing canonical Coord3D header spells its class-key `class`, whereas
retail's list specialization uses MSVC's `UCoord3D` struct encoding. A
TU-local class-key view includes that same header with `class` changed to
`struct`. coord2d.h is included first and the macro is immediately removed;
no other type is affected. Coord3D's base and all members are explicitly
public, so its layout, access and methods remain identical. This binds
the independently identified canonical list destructor without a duplicate
layout, fallback alias, extra pin or shared-header edit.

The complete constructor remains334 exact bytes; the destructor is158
exact bytes including all independently resolved relocations. The native
cleanup must be selected from this destructor's own EH section and pass
the normal scoped gate, not merely a relocation-masked comparison.

Name-regression alignment audit: PlayerPosition remains the exact same declared
20-byte element class and callbacks; Rva000C0B90PlayerArray is a new containing
array lifetime, not a rename of that element. The bank's BFMERetailAsciiString
is replaced by canonical AsciiString for the same +20/+24 members; the new
array wrapper is at+B0 and cannot be that string type. The checker pairs
these unrelated declarations positionally. Exact snapshot corrections cover
only those two false name pairs.
