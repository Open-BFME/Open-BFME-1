# RVA 009441D0 native recursive-body identity

The legacy Gen_009431F0::recurse declaration and candidate pin were a behavior
label, not independent evidence for the original C++ member spelling. Its
matched caller Gen_00944360.cpp used /alternatename to generated d_009441d0,
which asserts ABI/receiver compatibility but cannot establish a semantic name.
The naming oracle has no witness for that address-derived owner. The new
Rva009441D0::method identity retains the actual target address and asserts
only the independently proved thiscall/ten-DWORD calling convention. The
caller now names that opaque body directly without a linker alias.

Retail begins at 009441D0, ends with RET 28h at 00944355, excludes INT3 from
00944358 through the next body at 00944360. Thus the complete extent is 392
bytes. Three self calls are at +CD/+10D/+155, and the allocator call at +43
uses canonical STLport __node_alloc<true,0>::_M_allocate at 0082E540.
The independently verified native provider is STL_new_alloc_allocateThunk.cpp.

Canonical MultiList size 24 plus one opaque DWORD gives each node stride28;
the polymorphic list starts at +4, sentinel at +8, and canonical RenderObj
MultiListObject base is +8. Native slist push_front preserves the eight-byte
allocation, placement-copy/null check and head linking. The first opaque
DWORD gates descent. Signed count division by two preserves odd/negative
truncation; node_count shifts right as unsigned. Mutating the original count
and nodes arguments reproduces retail EBX/EBP lifetimes across recursive
calls, with the fourth call naturally optimized as a tail loop.

No original semantic class/member name, vtable slot, or funclet parent is
claimed. Byte-exact code, self/allocator relocations, true boundary and ABI
are verified separately from this honest address-derived identity.
