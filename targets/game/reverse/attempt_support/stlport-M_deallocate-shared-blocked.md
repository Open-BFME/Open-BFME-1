# Shared STLport `_M_deallocate` wrong_selected — blocks 3 link files, needs family-owner repair

Link queue #1 (`?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z`,
retail 0x0082E5F0, 85 B) is the SOLE blocker of at least:

- `game/GameEngine/Source/GameLogic/Map/WaypointConstructor.cpp` (1186 B)
- `game/GameEngine/Source/Common/Q3VectorStorageRelease.cpp` (1292 B)
- `game/GameEngine/Source/Common/S4VectorDestructors.cpp` (1295 B)

## Census evidence (index 31c8ddea62)

- 32 COMDAT copies: exactly 1 verdict `retail`
  (`.../WWLib/node_alloc_M_deallocateThunk.obj`, digest `30cdb4b352b5`),
  31 verdict `wrong` (digest `bbf929cae32a`).
- Link order: the retail thunk object sits at position 19435, AFTER the wrong
  emitters (e.g. MoneyPutCharString at 8982) and after the three consumers
  (1871/3985/5262). `link.exe` keeps the first select-any copy, so the kept
  definition is proven not retail's → `wrong_selected` for every consumer.
- The wrong copies come from the real STLport `_alloc.c` template definition,
  pulled in via `_STLP_EXPOSE_GLOBALS_IMPLEMENTATION` (set by
  `inputs/vendor/stlport/src/stlport_prefix.h` when template-export + declspec
  are active) in the locale facet TUs (`MoneyPut*`, `NumGet*`, `NumPut*`,
  stdio/time facets, `Bfme5UnwoundDestructors`). The retail copy comes from the
  thunk's hand-written template (`/Og-`, explicit `__node_alloc<true,0>`
  instantiation with its own RAII lock shape).

## What was proven this pass

- All three consumer files pass their scoped byte gates unchanged
  (4/4, 21/21, 13/13 rows matched). Their bodies are intact; per-file edits
  cannot fix this item and must not be attempted.
- No new emitter was added: the mechanism above was read from the vendored
  headers and the census index, not re-derived per file.

## Why no fix was applied here

- STLport names have a single owner (`next --family stlport`); a 31-file
  suppression or vendored-header change is that lane's work, with full-gate
  costs on every touched facet TU (each carries its own verified bodies).
- Candidate shared repairs (untested, for the family owner): define
  `_STLP_LINK_TIME_INSTANTIATION` in the facet TUs so `_alloc.c` is skipped
  while `_STLP_EXPOSE_STREAM_IMPLEMENTATION` keeps the facet bodies; or give
  the overlay (`inputs/reference/shims/stlport_bfme`) a matching
  `_M_deallocate` inline so every emitter converges on the retail digest
  (then link order stops mattering). Either needs objdump proof that all 32
  copies become identical plus scoped rebuilds of every touched TU.
- Renaming the thunk to sort earlier in link order was considered and
  rejected: fragile, and it would not survive build-order changes.
