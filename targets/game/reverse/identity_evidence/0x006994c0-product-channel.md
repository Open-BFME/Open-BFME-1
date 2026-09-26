# 0x006994C0 product-channel refresh

Retail's complete 34-byte body starts with `push esi; push edi`, reads one
stack argument into EDI, and ends with `ret 4`. At +0x07 it calls ILT
0x00018359, whose jump resolves to the already matched 111-byte
`Rva00699430Owner::productClamp` body at 0x00699430. It then calls ILT
0x00019E6B twice, with argument pairs `(index, 0)` and `(index, 1)`; that
thunk resolves to the already matched 450-byte
`Rva00699180Owner::refreshPair` body at 0x00699180. Both callees use ECX
as their receiver. The clamping body's +0x34 product slot is the same
offset as `m_product` in the refresh body's witnessed layout.

No independently named caller establishes the enclosing class. The new
entry therefore keeps its own address in `Rva006994C0Owner` and describes
only the behavior proved by the body. The productClamp pin is a routing
claim for the observed ILT, not a second physical body; `pin_consistency
--routes` re-derives its jump to 0x00699430.

External-only C++ declarations emit a 38-byte body with receiver reloads.
Putting the two already matched helper definitions in the same translation
unit as this method lets MSVC 7.1 retain ECX, and the clean method probes
34/34 bytes with two aligned call relocations. The strict scoped build
verifies all five matched functions in that translation unit, including
the repointed productClamp body.
