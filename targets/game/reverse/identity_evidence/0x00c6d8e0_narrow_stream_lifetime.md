# Narrow STLport stream lifetimes

The existing `game/stlport/X4Iostream.cpp` definitions own `_STL::cin`
(VA0x0130BED8) and `_STL::cout` (VA0x0130BDA0). Their native compiler
initializers `_$E1` and `_$E4` match retail RVAs0x00C6D8E0 and0x00C6D900;
initializer pointers reside at RVAs0x00F5E000 and0x00F5E004
in the `STLPORT_` section. RET+0x19 and INT3+0x1A establish26 bytes each.
Both pass null streambuf and hidden complete-object flag1 to the constructor,
then register their cleanup with atexit.

Constructor routes are independently decoded E9 thunks:

- Input ILT0x0000E340 -> existing native basic_istream<char> ctor0x0053FA20.
- Output ILT0x00041E5C -> existing native basic_ostream<char> ctor0x005CC230.

The registered cleanup bodies0x00C70D50 and0x00C70D70 match native compiler
`_$E2` and `_$E5`. Each ends with tailJMP+0x17 then INT3+0x1C (28 bytes).
Input cleanup installs vtableVA0x0112F2F4 and passes global+8; output cleanup
installsVA0x0112F304 and passes global+4. Both tail-call ILT0x000414BB,
which independently routes to matched narrow basic_ios destructor0x00538210.
These typed constructors/destructor and the canonical stream globals already
have verified ledger/DIR32 bindings. No new pin, header or type view is needed.

All four rows pass strict source, complete bytes and call/global/vtable
relocations. The final X4Iostream gate passes23/23, and the legacy wrapper
TU's remaining bodies pass2/2 after removing its cout wrapper. Address-derived
ledger names select the initializer/cin-cleanup compiler-local symbols;
the existing cout-cleanup ledger name is retained through `object-symbol=`.
The two initializer dumps and cin cleanup dump contribute80 conversion bytes;
the previously matched cout cleanup replacement contributes zero.
