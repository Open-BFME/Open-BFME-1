# Final read-only terrain data review

Verdict: GO for the applied source/data representation. No source-level finding was found in this scoped independent comparison. Publication remains dependent on Root/Transport's normal DataWriter, AFTER link proof and hooks; this review itself grants none of those results.

Reviewed source SHA256: `fd0e3d9b4ef4ea31d0831932bddbe144c72b2d1cd99b4b49b83b012836319a1b`.

Source: `game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawSetTerrainDecal.cpp`.

The only byte-level source change relative to `TERRAIN.before.cpp.txt` is the six explicit character definitions and one table-definition block, including its explanatory comment. Restoring that block to the old extern declaration yields the original source byte for byte. Original compiler flags, includes, function bodies and line endings are retained.

## Independent original-byte comparison

Each explicit `extern const char[]` was parsed from the actual source, checked against the original baseline at its address-derived label, and checked again against the corresponding bytes of one actual normal COFF snapshot:

|Symbol|Original VA|NUL-inclusive bytes|
|---|---|---|
|g_011236E8|011236E8|35|
|g_011236DC|011236DC|8|
|g_011236CC|011236CC|11|
|g_011236C0|011236C0|9|
|g_011236B0|011236B0|12|
|g_011236A0|011236A0|12|

All six source strings, their single NUL termination and their original bytes match. Their total typed payload is87B; no adjacent original alignment bytes are claimed as string content.

The table at original VA012BB604/RVA00EBB604 is exactly28B with seven DIR32 relocations at offsets0,4,8,12,16,20,24. The actual normal COFF referents are, in order: g_011236E8, g_011236DC, g_011236CC, g_011236C0, g_011236B0, g_011236A0, g_011236B0. This reproduces the original seven pointer values. Entries4 and6 reference the identical explicit symbol, guaranteeing the required pointer identity rather than merely equal text. Together the seven typed datums carry115B. The new COFF.rdata section is120B because it also contains alignment; this is not120B of admitted payload.

All added objects have explicit external linkage and the existing pointer/character constness. Their identifiers remain address-derived and the source comment explicitly disclaims EA C++ name recovery. Asset text is copied as target data, not presented as a recovered C++ entity name. No pointer literal, alias, cast, second duplicate string object for entry6, helper function, runtime initialization or custom compiler/section control was added. The actual normal object has the same five external function definitions as the original control and no.CRT initializer section.

The prior original bounds proof remains applicable: physical294B setTerrainDecal ends with RET4; CMP index,7 and signed JGE precede the four-byte indexed load at VA012BB604. LINKED293 is a separate filtered metric. This source review does not add a negative-index guard or treat adjacent zero padding as an eighth element.

## Proof currency boundary

Read `TERRAIN-WHOLE-OBJECT-PROOF.json` at SHA256 `fdfb8cf1bf82b399b8fb2e931757b121efe3ef49befb756fd55ace7c6a7ecc20`. Its source hash matches exactly, and it records the full preexisting runtime/FPO/COMDAT/directive graph and its historical whole-host-environment limitation explicitly.

During the ongoing normal data admissions, build/match's actual normal object is now SHA256 `3180d53ce02126451962778a0eb0275498802e52559a872b554d3b5a45186424`, whereas that proof binds earlier normal object `d1d425021e5fc6f5b4a519512ad906085672d4d350d23c19bed9c377c545cb02`. Therefore the old report is not asserted to be a current whole-object receipt for the later object. The seven relocations, all six complete byte payloads, unchanged function-definition set and absence of CRT initialization were independently checked on one captured byte snapshot of the later object. Root was notified; normal final AFTER/hooks must supply their own current whole-object/link currency before publication. The SHA change alone is not reported as a source defect or unexplained runtime regression, and no unsupported cause is asserted.

No compiler/preprocessor/link/DataWriter/claims/Git/source/header action was performed in this review. Only this review file was written. No new function-byte or runtime/full-image claim. PC remains on.

Rating: source/original data correspondence and pointer alias identity are **sicher**. Successful final native admission/publication is outside this read-only review and remains pending its normal gates.
