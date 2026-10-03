# Address-qualified allocation helper at0090E330

The complete46B native STLport allocator COMDAT emitted by the existing
ShroudManagerImpl008FBA40.cpp is byte-identical, including both relocation
positions, to retail0090E330..0090E35E. Its native symbol is
`?allocate@?$allocator@PAUGen_t_008fb350_p12pod@@@_STL@@QBEPAPAUGen_t_008fb350_p12pod@@IPBX@Z`.
It starts at section offset0 and has precisely46 bytes. This original
header implementation independently establishes an unsigned element count,
a const-void hint and a const thiscall receiver, with RET8. The concrete
retail element specialization and owning caller are not established;
therefore the new entry is fully address-qualified, not that native name.

The preceding predicate has its own RET at0090E32F. All three allocator
paths end in RET8, the final at0090E35B; two INT3 bytes follow0090E35D.
Thus the older126B predicate-plus-allocator aggregate is not one function.
Ghidra read_memory from00D0E32F reproduces the full boundary and all46B.
Neither Ghidra nor the earlier raw call/table-reference survey found an
incoming reference to this allocator. The independent start evidence is
its complete native code COMDAT/prototype, not an invented caller.

The source uses canonical STLport allocator<unsigned> only as a four-byte
allocation-unit view. It does not claim that retail payload values were
unsigned. Native _alloc.h:354 proves zero count returns null, other counts
multiply by sizeof(value_type), and the default node allocator routes
requests above128 bytes to operator new. The unused hint remains in the
signature. No object fields are introduced or accessed.

Both REL32 operands use existing bindings from that native header:
operator new at00881F30 and __node_alloc<false,0>::_M_allocate at0082E540.
The latter pin passes pin_consistency and the full native COMDAT calls it
at+1E (relocation+1F); it is not the competing __new_alloc alias printed by
the callee inventory. No new pin or callee declaration is introduced.
Strict verification checks all46B and both resolved calls.
