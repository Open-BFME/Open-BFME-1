# Exported Region2D dimensions and surplus identities

Retail baseline SHA256: `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.

Independent raw PE export parsing (ENGINE audit, reproduced by math) proves:

- Ordinal 1792, `?width@Region2D@@QBEMXZ`: RVA `0x00011CB1`, bytes `E9 6A EE 14 00`, routes to `0x00160B20`. Body `D9 41 08 D8 21 C3` is 6 bytes followed by INT3 padding.
- Ordinal 1642, `?height@Region2D@@QBEMXZ`: RVA `0x00035053`, bytes `E9 D8 BA 12 00`, routes to `0x00160B30`. Body `D9 41 0C D8 61 04 C3` is 7 bytes followed by INT3 padding.

Retail has no identical-COMDAT folding. Its directly exported names establish the owners; legacy `icf-owner` notes cannot establish additional identities at these addresses. Under `docs/naming_evidence.md` (One body, one name), retire exactly these surplus rows with evidence tombstones:

- `?Width@RectClass@@QBEMXZ`, 0x00160B20/6, W3DDisplay.cpp.
- `?Height@RectClass@@QBEMXZ`, 0x00160B30/7, W3DDisplay.cpp.
- `?Width@ViewportClass@@QBEMXZ`, 0x00160B20/6, camera.cpp.
- `?Height@ViewportClass@@QBEMXZ`, 0x00160B30/7, camera.cpp.

These source definitions remain untouched because verified callers need them. Their actual standalone retail addresses are not established here. No replacement identity, alias, pin, shared header, or generated source is added or changed. Existing opaque camera and AIPlayer alias rows remain outside this bounded repair. None of the six exact dimension names has a symbols.csv or dir32_addresses.csv pin.

The two Region2D rows retain their names, export routes, and extents. Existing inline providers in AISkirmishPlayerAcquireEnemy.cpp are used without editing that source; the redundant strong definitions are removed from region.cpp. All four sources passed 117/117 rows before the change, including every caller and helper. The four surplus rows contribute no unique retail byte coverage because the exported Region2D rows already cover the same extents.

Current affected caller targets before the change: AISkirmishPlayerAcquireEnemy 10 blockers, W3DDisplay 148, camera 16; region has 2. Measurements refresh all four providers together against the immutable census without object filtering. No gain from upstream changes is attributed to this patch.

Final verification: 113/113 retained rows match, with 23 literals plus 2 empty-string references, 49 constants and 99 DIR32 references checked. Current joint refresh changes region 2 -> 0 blockers (+1,404 newly linked bytes), AI 10 -> 8, display 148 -> 148, camera 16 -> 16; no new blocker in any category. Independent read-only peer review reproduced the raw exports and checked the exact four tombstones.
