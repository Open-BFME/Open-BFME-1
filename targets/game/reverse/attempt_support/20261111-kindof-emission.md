# ThingTemplate kind-of emission repair

BFME 1 base: 5b20831e90fbddd5c36783f0351633977c0cef86. Donor: 76f0baefa6f285d54bc1ca922397674312a5913f. Reviewed donor `reverse/attempt_support/kindof-emission-link-20261015/readme.md` and `Code/GameEngine/Include/Common/ThingTemplate.h`, plus its path history. The donor supplies only the imported-forceinline emission technique; no donor offsets, types, body or address are imported. The donor provider at 0x456AC is not BFME 1's provider.

BFME 1 census 9ac0d06c54 identifies five wrong copies of `?isKindOf@ThingTemplate@@QBE_NW4KindOfType@@@Z`: Object, GameLogic (shared sweep shim), Player_canBuild, BuildAssistant_isRemovableForConstruction and ObjectFields. The retained retail copy is in Thing_isKindOf.cpp, row 0xA2CB0+41. Private constant-specialized bodies and the shared shim retain their original expressions and layouts; only emission attributes change. No names, globals, pins or ledger ownership change.

Scoped normal builds pass all 266 rows across Object, GameLogic, Player_canBuild, BuildAssistant_isRemovableForConstruction and ObjectFields, and all 18 rows in the latter two after their private changes. This verifies existing callers, not inferred general class layouts.

Before: census-only ActionManagerCanEnterObject reports selected isKindOf blocker, LINKED 0 -> 0 (847 own bytes). Live linking remains subject to current provider/dependency availability; no census estimate is claimed as actual linked gain. Original sources are reproducible from the base revision.

The first global shim suppression removed 13 ledger-required nested bitset helpers in AcademyStats and W3DModelDraw (plain imported inline behaved the same). Rejected that broad application. `BFME_KINDOF_INLINE_ONLY` now opts in only Object and GameLogic via their existing compiler directives. Other shim consumers retain ordinary inline emission. The four-unit regression check passes 426/426 rows, including all 13 previously missing helpers. Object inspection finds no isKindOf provider or new reference in the five repaired emitters. Live link_check reports UNKNOWN because 711 changed/new ledger objects cannot be read; no linked-byte gain asserted.
