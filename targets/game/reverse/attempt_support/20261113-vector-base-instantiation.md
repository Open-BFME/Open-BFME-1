# Vector base destructor emission

Queue391 names the extra `_Vector_base<int>` constructor emitted by a whole
class instantiation in stlport_vector_base_int_dtor.cpp. The only ledger
owner in this TU is the45-byte destructor at0081D920. Explicitly instantiate
that destructor alone. The normal byte/relocation/body gate passes1/1, with
zero baseline findings; find_declared_unmatched passes. No layout, pin,
identity, flag or ledger change.

BFME2 revision76f0baefa6f285d54bc1ca922397674312a5913f reviewed:
reverse/attempt_support/stl-instantiation-scope-link-20261022/readme.md
and Code/Libraries/Source/WWVegas/WWLib/stlport_vector_bool_reserve.cpp.
They support narrow explicit instantiation. Donor addresses/flags/headers
are not transferred. Local source stays against its existing STLport.

Paired frozen-census previews are in
build/queue10-20261113/vectorbase-{before,after}.log, index90c15cdeca.
Before: constructor COMDAT and selected-provider conflicts, LINKED0.
After is recorded in the attempt log. No current census closure is claimed.
