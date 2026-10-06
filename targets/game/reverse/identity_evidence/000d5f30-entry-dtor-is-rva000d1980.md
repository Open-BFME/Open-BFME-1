# 0x000D5F30 destroys its entry with the matched ??1Rva000D1980

`Gen_000D5E90::bfmeRemove` (0x000D5F30, 198 B, Bfme5EntryRemove.cpp) called
the entry destructor as `??1Gen_dtor_000d4030@@QAE@XZ`, a symbols.csv pin on
ILT 0x00023218 that no source defines (link census: unresolved,
pinned-elsewhere).

`tools/callees.py 0x000D5F30 198`: `0x23218 -> 0xd1980`. The ILT slot's body
is 0x000D1980, matched as `??1Rva000D1980@@QAE@XZ`
(R3VectorOwnerDestructors.cpp, `BFME_VECTOR_OWNER(Rva000D1980, 0x04,
GenElem4)`): `tools/dis_retail.py 0x000D1980 46` frees the vector at
this+0x04 (finish of storage at +0x0C) through `operator delete` or the node
pool, thiscall with no arguments and no `this` adjustment. That is the
three-pointer vector copy the removal's entries own at +0x04..+0x0C.

The `Gen_dtor_000d4030` spelling names 0x000D4030, a different address that
this call never reaches, so it is not this body's identity. The caller now
calls `Rva000D1980::~Rva000D1980()`, the matched name at the call's retail
target, with the same ABI; its bytes are unchanged (1/1).
