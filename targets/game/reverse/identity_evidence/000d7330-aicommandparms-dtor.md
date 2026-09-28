# 0x000D7330 is AICommandParms::~AICommandParms

Retail body: 65 bytes, `thiscall`, no arguments. It reads `[ecx+0x20]`
(vector begin), returns when null, otherwise computes
`(end_of_storage - begin) / 12 * 12` with the divide-by-12 magic multiply
(`imul 0x2aaaaaab`), frees through `operator delete` when the byte size is
over 0x80 and through `__node_alloc::_M_deallocate` otherwise. That is the
STLport `_Vector_base<Coord3D>` destructor inlined into an otherwise empty
destructor: `Coord3D` is 12 bytes and the vector sits at `AICommandParms+0x20`,
the layout the matched `AICommandParmsStorage::store` (0x000D5C50 family,
`AICommandParmsStorage.cpp`) and `reconstitute` bodies witness.

Caller evidence: the matched `DeployStyleAIUpdate::setMyState` at 0x002B5800
(`DeployStyleAIUpdate_setMyState_BFME.cpp`, exact) builds a local
`AICommandParms(AICMD_NO_COMMAND, CMD_FROM_AI)`, passes it to `aiDoCommand`,
then calls ILT 0x00017C2E with ECX = the address of that whole local, exactly
where Zero Hour's `setMyState` lets the local go out of scope. ILT 0x00017C2E
jumps to 0x000D7330. Every other member of `AICommandParms` (enums, pointers,
`Coord3D`, the 0x5C-byte `DamageInfo`) is trivially destructible, so the only
work of the implicit destructor is that vector release, which is the whole
retail body.

The previous row name `?bfmeClear@Gen_000D7330@@QAEXXZ` (in
`Bfme5VectorReleases.cpp`) was a placeholder describing the byte shape, not an
identity; the placeholder body is removed from that TU with this landing.
