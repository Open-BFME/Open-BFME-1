# Tasks117-119 /500: remove unreferenced incompatible legacy isEmpty copies

Each existing source uses its already-present public str()[0] ==0 predicate at supported AsciiString call sites. This is specific to the legacy character-based implementation; it is not a substitution for canonical Base length semantics. Mixed Ascii/Unicode receivers were distinguished through isolated compiler-selected overload witnesses. Preprocessor-controlled source and ambiguous receivers are excluded. No witness declaration is in shipped source.

Actual ordinary objects preserve178 rows (row extents summed:8731B, not a new/unique coverage claim), plus all2931 other runtime sections. Only the independently wrong22B legacy predicate is removed per unit. It has no original runtime reference; no runtime symbol binding change or new definition is permitted. All other bytes, extents, flags, relocations, local targets, SafeSEH targets, external definitions and weak/alias contracts match exactly. Combined native source/provider gate:396/396 across10 sources. EH-unmaintainable members are restored, rebuilt and uncounted; reports remain in eh-refused-members.json. Compiler-local locator maintenance, if needed, uses only eh_state_pins.py with state-index proof.

Headers, physical declarations, compiler flags, identity pins, aliases, verifiers and baselines are unchanged. These are existing bodies, not new functions/authored coverage. Frozen previews are not a fresh whole-image result; no runtime or crash-fix improvement is claimed.

BFME2 reference0630f0ef47d0a818bb2e97583b43cfb1ecd35491 was refreshed and its strings providers/headers/consumers reviewed. No donor address, private heap representation or compiler setting is imported. BFME1 original export1656 identifies the existing Base word predicate at5E4C0, while these unused shared copies use a byte at+4. Source-local inline code is preserved; no uniform heap-layout claim. This follows task116's ordinary GameAudio proof and the source-context constraints documented in docs/shape_levers.md.

| Source | Retained rows | Summed row bytes | Preserved runtime sections |
|---|---:|---:|---:|
| game/GameEngine/Source/Common/INI/INIMapCache.cpp | 59 | 2447 | 795 |
| game/GameEngine/Source/GameLogic/Object/Locomotor.cpp | 42 | 2587 | 1024 |
| game/GameEngine/Source/GameClient/MapUtil.cpp | 77 | 3697 | 1112 |

Local evidence: diagnostics/continue-20261116-fivehundred/batch-20 and legacy-empty-probes. Useful rejected candidates and compiler type witnesses remain isolated under build/codex-20261116-fivehundred/legacy-empty-probes.

Native eh_state_pins.py --fix repoints 3 compiler-local object-symbol locators from original unwind-map/state-index evidence; all touched sources reverified. These notes-only ledger updates do not change callable identity, extent or ownership.
