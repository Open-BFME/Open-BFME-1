# Object position: use the rowed terrain-layer provider

Control: 9c06ecec2472268c7236096489ff7f968f017a22, 2026-10-29.
The edited caller at RVA 0x001C86B0 was claimed before work.

## Target evidence and repair

The existing 302-byte Object::bfmeGetPosition421AE body calls at +0x83
through ILT 0x0001C675 to the 245-byte TerrainLogic body at 0x001A7C20.
The previously recorded complete decodes establish an unadjusted terrain
receiver, Object* then const Coord3D*, a four-byte result, and ret 8.
See [the original recovery evidence](../identity_evidence/001c86b0-native-status.md).

That recovery deliberately used a declaration-only address view when the
canonical name's oracle evidence was disputed. Current functions.csv owns
the independently matched target as TerrainLogic::getLayerForDestination;
the already included native TerrainLogic.h declares its two-argument overload.
Call that declaration directly and remove the unused Rva001A7C20TerrainLogic
view. This reconciles the caller with the current row; it adds no claim about
the original EA spelling, class layout or a new function identity.

No header, global, pin, alias or ledger row changes. Both caller and provider
pass the normal build before and after: 2/2 rows, 547 function bytes and six
DIR32 references. The caller's 302 COFF code bytes are identical
(SHA-256 ad2b8db373f5e4c5a5ee9cd2f1316651fe5f8b8ec77439ce8b3501b429f2c3ab).
Of five relocations, only the symbol at +0x84 changes, from the address view
to the rowed TerrainLogic declaration. The normal gate separately verifies
the native call destination.

## BFME 2 reference and related callers

Reviewed BFME 2 b5a7b8290a0c4c20b03a3664609d434904e228eb,
Code/GameEngine/Source/GameLogic/Map/
TerrainLogicBridges_GetHighestLayerForDestination_GetHighestLayerForDestination.cpp.
Its getLayerForDestination(Object*, const Coord3D*) at RVA 0x002802FE is
251 bytes. The declared receiver and arguments corroborate the existing
interface; no donor body, field offsets, virtual slots or addresses are imported.
BFME 1's own caller, provider and header establish the repair independently.

The related-name sweep also finds the private view in AI/Rva001752A0.cpp;
that separate 943-byte path helper is not modified or claimed here.
TerrainLogicNewMap's recorded canonical-data/legacy-DIR32 prerequisite
(re_attempts.log, RVA 0x001AE190) is unchanged and is not retried.

## Linking boundary

Index: census 58bb4b32e5, 2026-10-29 12:14. Before, the old view is unresolved;
the current-selection preview is UNKNOWN because 22,718 other ledger objects
cannot be read in this checkout. After, the explicitly census-only preview
reports LINKS, 0 -> 299 authored nonpadding bytes, against that saved selection.
This is a historical-selection prediction, not a new census or a proven
current-master closure. Carry the changed caller and its provider into the
next normal census; no headline LINKED increase is claimed.
