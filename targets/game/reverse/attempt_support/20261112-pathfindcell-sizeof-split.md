# PathfindCell ??_E 0x08-vs-0x10: root cause (2026-11-12)

`??_EPathfindCell@@UAEPAXI@Z` has 5 copies with verdict=retail (4 pass 0x10,
1 — `aipathfind.obj` from `game/GameEngine/Source/GameLogic/AI/AIPathfind.cpp`
— passes 0x08). The immediate bytes differ at exactly one site:

```
common (retail-verdict):  ... 50 6a10 56 e8 <??_M> ...
aipathfind (loser):       ... 50 6a08 56 e8 <??_M> ...
```

`6a10`/`6a08` is the element-size operand the vector-deleting destructor
forwards to the `??_M` array helper: `sizeof(PathfindCell)` as seen by each TU.

- The 4 winning TUs use a TU-local 16-byte view (`unsigned char opaque[8];
  zoneStorageType zone; zoneStorageType nextZone; unsigned char tail[4]`, no
  vptr, ushort zones: 8+2+2+4 = 16). Their functions byte-match, so this view's
  sizeof and used offsets are retail-true.
- `AIPathfind.cpp` uses the shared shim
  (`inputs/reference/shims/bfme/pathfind_cell_shim.h`: `m_info` ptr + packed
  bitfields = 8 bytes). Its functions also byte-match, so the shim's offsets
  for the members it uses are retail-true too.

Reconciliation: retail's `PathfindCell` is 16 bytes; the shim models only the
low 8 bytes (missing the zone/nextZone/tail members at 8..16) while keeping the
used offsets correct. Both views' codegen agrees with retail everywhere except
the one site that materializes `sizeof`.

Fix hypothesis (append-only, safe): append the missing 8 bytes
(zone/nextZone/tail per the TU-local view) to the shim class WITHOUT moving any
existing member. All current user codegen is unchanged (same offsets); only
`sizeof`-dependent sites (the `??_E` copy) change 0x08 -> 0x10 and converge.
Cost: shared-shim edit => full gate (40-60 min) to re-verify every dependent
TU, plus a dir32/name check for the "new" member names. Not attempted here for
lack of a build-lock window; the `??_E` copy itself must NOT be hand-patched
(identity row does not exist; the copy is compiler-generated).
