# Datum identity at VA 0x012AD678

Corrected `TheRva001ECDC0Names` to the existing `TheWeaponSlotTypeNames` spelling and defined the single 16-byte table. The source contract is `const char *const[4]`: `PRIMARY`, `SECONDARY`, `TERTIARY`, and a null terminator.

The three pointer words target VA `0x010A166C`, `0x010A1660`, and `0x010A1654`. Their entire null-terminated contents equal the corresponding compiler string sections. The definition has three DIR32 relocations, all checked against these exact retail targets; seventeen string pins for this table and the icon table were added additively to `dir32_addresses.csv`. The following table at VA `0x012AD688` begins `FROM_PLAYER`, so it is not included.

The Zero Hour reference declares `static char *TheWeaponSlotTypeNames[]` with these three strings and NULL in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/WeaponSet.h:57`. This proves the identifier and element role, not the original BFME const qualifiers. The correction retains the existing externally declared const-pointer spelling shared by the matched BFME parsers.

Retail parsers at RVA `0x0018C380`, `0x0018C3E0`, `0x0018C420`, `0x001EAC70`, `0x001EACB0`, `0x001ECDC0`, `0x001ECE00`, and `0x007730A0` pass this address as the index-name list. The preferred-against and only-against callbacks scan a weapon slot and use its index times 24 to select an instance bitset. Their four-argument INI callback contract is unchanged. There is no table writer in the typed absolute-reference scan.

The owner is `game/GameEngine/Source/Common/SmallIniParseCallbacks.cpp`, which contains the two previously misnamed direct users. Existing game declarations using the chosen spelling already agree. A different retail string, a parser expecting another enumeration, a writer requiring another element layout, a datum inside these 16 bytes, or a changed verified function would refute the correction.

The inspected extent is VA `0x012AD678` through exclusive `0x012AD688` in `.data`. Initial bytes are `6c 16 0a 01 60 16 0a 01 54 16 0a 01 00 00 00 00`. The extent and declaration audit is in `build/rlink/extent-and-declarations.log`. No other DIR32 name lies strictly inside any corrected extent; the only data-row overlap after correction is its own owner.

| Existing decorated spelling | Game files declaring it before correction |
|---|---:|
| `?TheRva001ECDC0Names@@3QBQBDB` | 1 |
| `?TheWeaponSlotTypeNames@@3QBQBDB` | 1 |

Counts use direct game-source declarations and declaration-producing macro invocations, count a file once, and exclude comment-only mentions. The raw search and exact declaring lines are in `build/rlink/declarations-rg.jsonl` and `build/rlink/extent-and-declarations.log`. These counts do not decide the preferred identity.

| Retail user RVA | Ledger spelling | Absolute references |
|---|---|---|
| `0x0018C380` | `?parseTWS@@YAXPAVINI@@PAX1PBX@Z` | VA 0x58c3a0: `push 0x12ad678` |
| `0x0018C3E0` | `?parseTurretSweep@TurretAIData@@SAXPAVINI@@PAX1PBX@Z` | VA 0x58c3e5: `push 0x12ad678` |
| `0x0018C420` | `?parseTurretSweepSpeed@TurretAIData@@SAXPAVINI@@PAX1PBX@Z` | VA 0x58c425: `push 0x12ad678` |
| `0x001EAC70` | `?parseWeapon@WeaponTemplateSet@@CAXPAVINI@@PAX1PBX@Z` | VA 0x5eac75: `push 0x12ad678` |
| `0x001EACB0` | `?parseAutoChoose@WeaponTemplateSet@@CAXPAVINI@@PAX1PBX@Z` | VA 0x5eacb5: `push 0x12ad678` |
| `0x001ECDC0` | `?parsePreferredAgainst@@YAXPAVINI@@PAX1PBX@Z` | VA 0x5ecdc5: `push 0x12ad678` |
| `0x001ECE00` | `?parseOnlyAgainst@@YAXPAVINI@@PAX1PBX@Z` | VA 0x5ece05: `push 0x12ad678` |
| `0x006F2CC0` | `?d_006f2cc0@@YAXXZ` | VA 0xaf31a8: `mov ecx, dword ptr [eax*4 + 0x12ad678]` |
| `0x007730A0` | `?parseWeaponBoneName@@YAXPAVINI@@PAX1PBX@Z` | VA 0xb730bc: `push 0x12ad678` |

Raw retail data, complete user disassembly, all five-byte E9 routes to these users and callers through the routes are retained in `build/rlink/retail-probe.log` and `build/rlink/focused-retail.log`. The latter rejects raw byte coincidences that are not data operands, but any remaining instruction-shaped references need their enclosing body context. The parse-real callback is independently disassembled in `build/rlink/parse-real-retail-full.log`.

For corrected addresses, `build/rlink/add-data-012ad678.log` records the byte, sizeof and relocation gate. Relevant per-source gates are `build/rlink/after-<source-stem>.log`; all changed sources are listed in `build/rlink/changed-sources.json`. Ledger, pin and declaration gates are `check-csv-after.log`, `pin-consistency-after.log`, and `declared-unmatched-after.log` in that folder. Per-file LINKED results and remaining unrelated blockers are in `link-before.log` and `link-after.log`.
