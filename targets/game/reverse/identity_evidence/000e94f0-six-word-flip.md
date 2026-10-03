# Refute the 117-bit identity and restore the complete body

Old row: ?flip@?$bitset@$0HF@@_STL@@QAEAAV12@XZ at RVA000E94F0/23B,
backed by Drawable.cpp. Its end cuts NOT ECX atE9506. Sequential retail
instructions continue through RET atE952B thenINT3 atE952C:60 contiguous
bytes. Ghidra create_function independently reports the complete60B body.

Retail writes all six dwords at offsets00,04,08,0C,10,14 and then masks
word14 with001FFFFF. A bitset<117> contains four32-bit words; it cannot
perform these accesses or this final21-bit mask. The named template width
is contradicted by retail storage span and behavior, independently of
compiler agreement. The complete width represented by this algorithm is
5*32+21=181. The original23B match merely stopped before the width became
observable.

A scan of retail E8/E9 destinations finds only ILT218B4 referring to this
entry and no direct caller to that ILT. This does not independently prove
a retail class/template identity. Replace the false full name with
Rva000E94F0::method, preserving the address and known no-argument thiscall
ABI returning the same pointer in EAX. No guessed semantic owner is added.

The new implementation uses the canonical STLport bitset<181> as private
storage in an explicitly address-qualified view. That is an implementation
choice for the independently observed six-word complement/mask algorithm,
not a claim that the retail symbol was that template. Its source comes from
inputs/vendor/stlport/stl/_bitset.h (_M_do_flip and flip); no duplicate library
class is declared. name_oracle has no witnessed Rva000E94F0 layout.

The native C++ view emits exactly60 bytes with zero relocations. Keep
Drawable.cpp's existing117-bit code, which belongs to its other source
users; retire only this contradictory function claim. No new callee pin,
shared-header change, generated-source edit, or assembly is required.
