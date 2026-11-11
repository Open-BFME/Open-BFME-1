# Link task: DynamicVectorClass<VertexMaterial*> vtable (0x0113C614)

Date: 2026-11-11. Queue: `link_check.py next` (census 9ac0d06c54),
`??_7?$DynamicVectorClass@PAVVertexMaterialClass@@@@6B@`, losers,
517 B in MaterialInfoClassCtor.cpp + MaterialInfoCopyCtor.cpp.

## Status: blocked on shared-header research + full gate

Recorded: `re_log` blocked on `??_7?$DynamicVectorClass@PAVVertexMaterialClass@@@@6B@`
@ 0x0113C614. Lease 0xFBD5D165 released.

## Findings (verified in-session)

- The two MaterialInfo* files do NOT emit the vtable; they only store its
  address via `__identifier` DIR32. Emitters are matinfo.obj and
  MeshLoadContextLifecycle.obj (census index 90c15cdeca), both verdict
  `wrong`, same digest `b91e8deb677b`.
- Both emitters' vtable slots reference the same six names:
  `??_E?$DynamicVectorClass@PAVVertexMaterialClass@@`,
  `??8?$VectorClass@PAVVertexMaterialClass@@`,
  `?Resize/?Clear/?ID/?ID?$DynamicVectorClass@PAVVertexMaterialClass@@`.
- Retail bytes at file offset 0xD3C614 (VA 0x0113C614, RVA 0xD3C614) hold
  six DIR32 slots (VAs):
  `0xD305B0, 0xD2F6B0, 0xD30290, 0xD30240, 0xD30210, 0xD30270`.
- NONE of those equals the ledger's matched DynamicVectorClass<VM*> methods
  (Add 0x96E110, Clear 0x94E4F0, Delete_All 0x93CB00, ID 0x93D7E0,
  Resize 0x974500). All six slot bodies are distinct from each other and
  from every ledger method (first-bytes compared in-session).
- Two slots happen to coincide with existing rows: 0x92F6B0 is ledger
  `??8?$VectorClass@PAVRenderObjClass@@` (68 B, agg_def.cpp) and 0x935B0 is
  `?bfmePushBack@Bfme5LinkPusher@@` (46 B). The other four
  (0x93210/0x93240/0x93270/0x93290) are unclaimed; Ghidra inventory has no
  starts there.
- Retail ctor `??0MaterialInfoClass@@QAE@XZ` (file offset 0x931220, 132 B)
  genuinely stores `0x113C614` (+0x42) and `0x113C62C` (+0x69), so the
  ADDRESS is right and the reconstruction is byte-exact; only the emitted
  vtable CONTENTS are wrong.

## Next steps for whoever takes it

1. Disassemble the six retail slot bodies (file offsets 0x935B0, 0x92F6B0,
   0x93290, 0x93240, 0x93210, 0x93270) and establish identities with
   independent evidence (callers push/cleanup, sibling instantiations).
   Unproven ones get address-derived names, never guessed method names.
2. Decide duplicates-vs-dead-code: ledger methods at 0x93CB00+ may be dead
   copies while the vtable points at the live ones (or vice versa); check
   xrefs before rehoming any row.
3. The vtable is emitted from the shared `WWLib/vector.h` template, so the
   wiring fix pays a full gate (build + hooks, 40-60 min). Fix all six
   slots in one commit with the affected providers/consumers verified.
4. Re-verify with `link_check.py --refresh` on both emitter TUs plus the
   two MaterialInfo files (needs clean tree + warm object cache).
