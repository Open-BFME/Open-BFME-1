# 0x0024EB00 SlaughterHordeContain::onDie (329 B): first real-C++ bank, shape 0.954

Session s552 (2026-11-03), model claude-opus-5-5, VC7.1 `/DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB`, stlport.
Bank: `targets/game/reverse/attempts/0x0024eb00.cpp` (was a planned new TU
`game/GameEngine/Source/GameLogic/Object/Contain/SlaughterHordeContainOnDie.cpp`).

## Identity
- ilt_oracle CONFIRMS `?onDie@SlaughterHordeContain@@UAEXPBVDamageInfo@@@Z` at 0x0024EB00
  (exact); the row is the naked lift `?onDie@Rva0024EB00@@UAEXPBVDamageInfo@@@Z` in
  `SlaughterHordeContainDestructorThunk.cpp` (object-symbol `??1SlaughterHordeContain@@UAE@XZ`).
  Die-interface table 0x010B0F1C at complete +0x28, slot 0 ILT 0x00041B82
  (identity_evidence/0x0024eb00-on-die-slot.md). The 2026 "converted" verdict was a stale
  pruning-pass record.
- BFME 2 donor (59e3f8f825) `CitadelSlaughterHordeContain::onDie` (0x00480821, 199 B) in
  `Code/GameEngine/Source/GameLogic/Object/Contain/CitadelSlaughterHordeContain.cpp` has the
  same algorithm (copy contain list; kind-gated objects; nested contain interface fills a
  member list; each non-null member goes to the +0x20 interface).

## What matches
- Callees by ledger name: list copy ctor `??0?$list@UGen_t_001cb160_p4cd@@...@QAE@ABV01@@Z`
  (0x001CB160, made out of line by a declaration-only specialization), members list dtor
  `??1Rva000CEBD0IntListState@@QAE@XZ` (0x000CEBD0, class deriving `_STL::list<int>`, so its
  ctor inlines retail's node_alloc(12) header), `Overridable::getFinalOverride`,
  `Object::unidentified_001BFE20`; template kind word +0xD4 bit 0x1000; contain slot 60;
  +0x20 interface slot 34 (call it unqualified: a static_cast from this adds a null test).
- 324/329 B, shape 0.954: identical instruction stream except allocation.

## Remaining: register allocation of the outer loop
Retail: this in EBP, the copied list's head node cached in EDI (reloaded after the
members-dtor call), the iterator in a stack slot (frame 0xC). Ours: this in EDI, iterator
in EBP, head reloaded into EDX at each test (frame 8). Inert (all 324 B / 0.954): iterator
declared first, const_iterator, post-increment, element reference, while loop, nested
continues, const objects, explicit end local (worse), STLport defines (_STLP_NO_EXCEPTIONS
/ _STLP_USE_STATIC_LIB / BFME_STLP_NODE_ALLOC), iterator through a pointer. Explicit
`objects.clear()` regresses (361 B).
