# Datum identity at VA 0x012B4D44

Corrected the standalone `Distance004092A0` spelling to the field in `TheAnimationSoundClientBehaviorGlobalSetting` and defined the single four-byte setting object with initial float value 50.0. The selected existing struct spelling has one `Real` field named `m_minMicrophoneDistanceToDirty`.

Retail RVA `0x004093C0` passes VA `0x012B4D44` as the instance and VA `0x010F03E8` as its `FieldParse` table. The first entry contains the EA string `MinMicrophoneDistanceToDirty`, the callback VA `0x00C52B20`, a zero user pointer and offset zero. The next 16-byte entry is entirely zero. `symbols.csv` and the matched ledger independently identify callback RVA `0x00852B20` as `INI::parseReal`. Its retail tail executes `FSTP dword ptr [eax]` through the store argument. The parser throws on map overrides using the EA string `Cannot override AnimationSoundClientBehaviorGlobalSetting in map.ini`.

Retail RVA `0x004092A0` reads the same four-byte value twice with x87 floating operations and compares the squared microphone displacement against its square. Thus the distance spelling is a field access to the parsed setting, rather than an independent datum. The parser writes it indirectly through the proven real callback; the spatial-list updater reads it. No other direct absolute user was found.

The parser takes INI as its only stack argument and passes the global address and field table to `INI::initFromINI`. The updater uses an ECX receiver for its list state; the global is a one-field tuning object and has no receiver or separate arguments. The source definitions retain both contracts. This setting is BFME-specific; no exact Zero Hour declaration was found.

The object is defined once in `game/GameEngine/Source/GameClient/Drawable/Behavior/AnimationSoundClientBehaviorGlobalSetting.cpp`. `SpatialList004092A0.cpp` now names its field. The initializer has no relocations and equals retail byte for byte. A non-real field callback, a different offset, a second field extending the object, a datum inside its four bytes, or a changed verified instruction would refute the correction.

The inspected extent is VA `0x012B4D44` through exclusive `0x012B4D48` in `.data`. Initial bytes are `00 00 48 42`. The extent and declaration audit is in `build/rlink/extent-and-declarations.log`. No other DIR32 name lies strictly inside any corrected extent; the only data-row overlap after correction is its own owner.

| Existing decorated spelling | Game files declaring it before correction |
|---|---:|
| `?Distance004092A0@@3MA` | 1 |
| `?TheAnimationSoundClientBehaviorGlobalSetting@@3UAnimationSoundClientBehaviorGlobalSetting@@A` | 1 |

Counts use direct game-source declarations and declaration-producing macro invocations, count a file once, and exclude comment-only mentions. The raw search and exact declaring lines are in `build/rlink/declarations-rg.jsonl` and `build/rlink/extent-and-declarations.log`. These counts do not decide the preferred identity.

| Retail user RVA | Ledger spelling | Absolute references |
|---|---|---|
| `0x004092A0` | `?update@SpatialList004092A0@@QAEXXZ` | VA 0x8092e7: `fld dword ptr [0x12b4d44]`; VA 0x8092ed: `fmul dword ptr [0x12b4d44]` |
| `0x004093C0` | `?parseAnimationSoundClientBehaviorGlobalSetting@@YAXPAVINI@@@Z` | VA 0x8093f7: `push 0x12b4d44` |

Raw retail data, complete user disassembly, all five-byte E9 routes to these users and callers through the routes are retained in `build/rlink/retail-probe.log` and `build/rlink/focused-retail.log`. The latter rejects raw byte coincidences that are not data operands, but any remaining instruction-shaped references need their enclosing body context. The parse-real callback is independently disassembled in `build/rlink/parse-real-retail-full.log`.

For corrected addresses, `build/rlink/add-data-012b4d44.log` records the byte, sizeof and relocation gate. Relevant per-source gates are `build/rlink/after-<source-stem>.log`; all changed sources are listed in `build/rlink/changed-sources.json`. Ledger, pin and declaration gates are `check-csv-after.log`, `pin-consistency-after.log`, and `declared-unmatched-after.log` in that folder. Per-file LINKED results and remaining unrelated blockers are in `link-before.log` and `link-after.log`.
