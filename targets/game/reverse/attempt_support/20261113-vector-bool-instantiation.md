# vector<bool> emission repair

Local owner has exactly two ledger rows: assignment00646340/283 and
reserve009D6BA0/225. Replace whole-class instantiation with those members.
The visible native _Bvector_base deallocation body stays identical but is
imported forceinline, suppressing its unused standalone copy. Normal scoped
byte/relocation/body gate verifies2/2 rows, zero baselined findings.
find_declared_unmatched passes. No header, flag, type, pin or ledger change.

Donor reviewed76f0baefa6f285d54bc1ca922397674312a5913f:
Code/Libraries/Source/WWVegas/WWLib/stlport_vector_bool_reserve.cpp and
reverse/attempt_support/stl-instantiation-scope-link-20261022/readme.md.
The local existing STLport _bvector.h body is independently identical to
the specialization. No donor path, address or compiler setting is imported.

Before: frozen-census preview90c15cdeca has7 selected-provider findings.
Narrow instantiation reduces this to3; suppressing the surplus deallocator
is then checked separately. Assignment and reserve ownership conflicts
remain. LINKED remains0; no current executable closure or recovered bytes
are claimed. Logs: build/queue10-20261113/vectorbool-{before,after,final}.log.
