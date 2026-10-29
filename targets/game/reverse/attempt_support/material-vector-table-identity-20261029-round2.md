# Material-vector table identity prerequisite

Inspected BFME 1 98199b2d on 2026-10-29. No source edit is retained.
All 39 matched rows across matinfo.cpp, MeshLoadContextLifecycle.cpp and the
two MaterialInfo constructor units pass the normal build. Their claims were
released after this inspection.

At index ea2916a82d, both constructor consumers are blocked by the selected
??_7?$DynamicVectorClass@PAVVertexMaterialClass@@@@6B@ table (517 authored
bytes together). Both emitted copies, in matinfo.cpp and
MeshLoadContextLifecycle.cpp, have digest b91e8deb677b and verdict wrong.
No retail-approved copy is recorded.

The native 24-byte table at VA 0x0113C614 contains these six pointer values:
0x00D305B0, 0x00D2F6B0, 0x00D30290, 0x00D30240, 0x00D30210, 0x00D30270.
Current code rows label them respectively VectorClass<ShaderClass>'s deleting
destructor, VectorClass<RenderObjClass*>::operator==, two Prototype-family
DynamicVector methods, its reference ID and a Render2D pointer-ID alias.
Those are current ledger labels, not independent proof of the native table's
C++ class. dir32_addresses.csv also gives both PrototypeClass and
VertexMaterialClass vector table spellings the same VA 0x0113C614.

The emitted tables instead name six VertexMaterialClass instantiations.
Their exact bodies/relocations and the competing table identities need a
coherent ownership investigation before another specialization, pin or alias
can be justified. A current caller byte match alone cannot decide the class
names or selected method owners.

Reviewed donor b5a7b829 material-helper-link-20261018/README.md and the donor
MaterialInfo constructor/matinfo sources. That donor repair changes inline
RefCountClass/helper size settings; it does not establish BFME 1's table's
six method identities, so it is not adapted here. Native target fields and
current ledger ambiguity above are separate from that donor evidence.

Next: reconcile those six method identities with the constructor writes and
existing owners, then recheck provider and consumer objects together. No new
alias, guessed class identity, provider edit or linking gain is claimed.
