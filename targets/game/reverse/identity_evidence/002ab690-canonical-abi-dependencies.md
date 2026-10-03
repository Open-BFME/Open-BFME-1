# StealthDetectorUpdate::update canonical ABI dependencies

Audit of retail RVA `0x002AB690`, 1,954 bytes, on 2026-10-03, against
repository base `d70815a1e3` (before later concurrent corrections).
The preferred bank is unchanged at `targets/game/reverse/attempts/0x002ab690.cpp`.

## What was reproduced

- MSVC 7.1 (13.10.3077) `finish_measure.py --one 0x002AB690` reproduced
  1,954 / 1,954 bytes, zero non-relocation differences, quality 1.0.
  This is diagnostic equivalence, not a passed relocation-binding gate.
- Ghidra 12.1.2, through `pyghidra-mcp` 0.2.7, independently decompiled
  VA `0x006AB690`. The epilogue returns at VA `0x006ABE31` (RVA
  `0x002ABE31`), confirming the bank's final byte at offset `0x7A1`.
  Ghidra's invented types and names are not identity evidence.
- `tools/callees.py 0x002AB690 1954` reports 29 distinct direct call targets.
  The existing while-next loop and single function-local module key should
  be preserved; the bank records why other shapes failed.

## Canonical contracts that must be reconciled

1. **Filters and query results.** The reference `GameLogic/PartitionManager.h`
   declares the ZH `PartitionFilter` interface, without the BFME next link,
   destructor/getPlayerMask slots, or `link` member. BFME matched callers and
   `PartitionFilterRelationshipCtor.cpp` instead establish a three-slot base,
   next at +4, object at +8, flags at +0xC, and bool at +0x10. The reference
   query returns `SimpleObjectIterator *`; the bank requires a reference-counted
   vector result. `BfmeWideResultForward.cpp` is the existing result/forwarder
   provider; its five-int signature differs from the bank's typed spelling.
2. **Stealth.** `StealthUpdate_markAsDetected.cpp` proves the BFME
   `(unsigned int, bool)` method at `0x002AD380`. The reference
   `StealthUpdate.h` still declares the one-argument ZH interface. The separate
   `0x002AD250` call has no proven semantic name; retain its address identity.
3. **Object and particles.** Reference inline Object accessors do not express
   this body's virtual +0x28 drawable call and cached-name module lookup.
   The reference particle manager returns a pointer, while this body uses a
   12-byte tracked handle. The existing provider `Rva005C3A30.cpp` is still
   represented with a `BfmeVec3` return. Changing only the caller's spelling
   cannot settle the return lifetime, hidden argument, and cleanup contracts.
4. **Audio constructor route.** The matched ledger places
   `??0AudioEventRTS@@QAE@ABVAsciiString@@H@Z` at `0x000B2CC0` (159 bytes,
   `AudioEventRTSCopyAndLifetime.cpp`). This detector calls it through ILT
   `0x00025306`. The same name's current symbols.csv pin instead routes through
   `0x0001EC13` to the thin body at `0x000B2D90`. Do not add a second speculative
   alias to silence the discrepancy.
5. **Audio destructor route and layout.** The reference AudioEventRTS layout
   is 0x64 bytes; the turretai shim is 0x70 but lacks the extra constructor and
   setPlayerIndex declarations. Retail here destroys through ILT `0x00026F35`
   to `0x000B31F0` (162 bytes). Its row is QAE with an UAE object-symbol override.
   The canonical UAE row instead names `0x000CFA40` (77 bytes), pinned through
   `0x0002671F`. Those latter two addresses were actively owned by an audio
   identity-correction worker at audit time. Their correction must be preserved.

## Bounded independent dependency

`PartitionFilter::link` at `0x009F2AE0` remains a 46-byte generated body.
Its existing canonical pin and independently matched callers, including
`ObjectCountNearbyEnemies.cpp` and
`ScriptActions_doMoveUnitTowardsNearest_Thunk.cpp`, provide stronger naming
and ABI evidence than the detector bank alone. Recovering that nonvirtual
next-chain operation can proceed separately without changing filter layouts,
query lifetime rules, or another worker's audio identities.

The detector bank must not land until canonical integration and strict
relocation verification pass. Mass-casting all bank-specific calls through
ILT aliases would conceal the unresolved type/lifetime contracts. No detector
source, bank, or ledger row was changed by this audit.
