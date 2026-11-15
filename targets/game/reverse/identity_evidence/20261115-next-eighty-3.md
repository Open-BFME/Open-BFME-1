# BFME 1 continuation: tasks 43-62 of 80

Immediate baseline `2aceffe11beccac75df31c6ffee8a48c0d2c0fd4`.
The complete selection begins at `3ec594ba25a3edd51d90306bb517d53af2bacfbb`.
These are existing source binding and function-identity metadata repairs.
No new function reconstruction, authored-byte, runtime or crash-fix gain is claimed.

## Retail unwind-state identity corrections

The native eh_state_pins.py writer alone updates the object-symbol notes.
For each row the original parent's retail handler -> FuncInfo -> unwind map identifies
the action at the same state index in the native compiled object. maxState and all
toState entries agree; all ledgered parents that constrain the action agree on one label.
Byte-equal twins are distinguished by this state evidence, never by choosing the first
matching body or by adjacency. Existing semantic names and parent assignments are retained.
Prior attempts and landing evidence were reviewed for all 60 selected funclet RVAs.
Four preliminary stale candidates became proven after a normal cache-refresh build and
were excluded. Only still-wrong or stale uniquely state-proven bindings are repaired.
The remaining unprovable and unrelated/missing-object rows are not modified.

| Task | Retail action | Source | Previous -> proven object label | Retail parent states |
|---|---|---|---|---|
| 43 | `0x00BF5FCB` `?Rva00BF5FCBCleanup@@YAXXZ` (31B) | `game/GameEngine/Source/Common/System/recorder_strings.cpp` | `$L2486` -> `$L2487`; wrong | `?readAsciiString@RecorderClass@@IAE?AVAsciiString@@XZ: [0]` |
| 44 | `0x00BF6048` `?Rva00BF6048Cleanup@@YAXXZ` (25B) | `game/GameEngine/Source/Common/Recorder.cpp` | `$L1278` -> `$L1295`; stale | `?getReplayDir@RecorderClass@@SA?AVAsciiString@@XZ: [0]` |
| 45 | `0x00C08051` `?Rva00C08051Cleanup@@YAXXZ` (25B) | `game/GameEngine/Source/GameLogic/Map/TerrainLogicNameLookups.cpp` | `$L1108` -> `$L1109`; wrong | `?getWaypointByPath@TerrainLogic@@UAEPAVWaypoint@@VAsciiString@@@Z: [2]` |
| 46 | `0x00C08038` `?dup_00C08038@@YAXXZ` (25B) | `game/GameEngine/Source/GameLogic/Map/TerrainLogicNameLookups.cpp` | `$L1106` -> `$L1107`; stale | `?getWaypointByPath@TerrainLogic@@UAEPAVWaypoint@@VAsciiString@@@Z: [1]` |
| 47 | `0x00C460E9` `?dup_00C460E9@@YAXXZ` (25B) | `game/GameEngine/Source/GameNetwork/Network.cpp` | `$L60358` -> `$L61811`; stale | `?getPlayerName@Network@@UAE?AVUnicodeString@@H@Z: [0]` |
| 48 | `0x00BF2B00` `uw_00bf2b00` (11B) | `game/GameEngine/Source/Common/GameEngine.cpp` | `$L94043` -> `$L96451`; stale; twin-proven | `?createMessageStream@GameEngine@@MAEPAVMessageStream@@XZ: [0]` |
| 49 | `0x00BF5FC0` `uw_00bf5fc0` (11B) | `game/GameEngine/Source/Common/System/recorder_strings.cpp` | `$L2485` -> `$L2486`; stale | `?readAsciiString@RecorderClass@@IAE?AVAsciiString@@XZ: [1]` |
| 50 | `0x00BF6010` `uw_00bf6010` (11B) | `game/GameEngine/Source/Common/System/recorder_strings.cpp` | `$L2354` -> `$L2355`; stale | `?appendNextCommand@RecorderClass@@IAEXXZ: [0]` |
| 51 | `0x00BF601B` `uw_00bf601b` (11B) | `game/GameEngine/Source/Common/System/recorder_strings.cpp` | `$L2355` -> `$L2356`; wrong | `?appendNextCommand@RecorderClass@@IAEXXZ: [1]` |
| 52 | `0x00BF6040` `uw_00bf6040` (8B) | `game/GameEngine/Source/Common/Recorder.cpp` | `$L1277` -> `$L1294`; stale | `?getReplayDir@RecorderClass@@SA?AVAsciiString@@XZ: [1]` |
| 53 | `0x00C0A5E0` `uw_00c0a5e0` (8B) | `game/GameEngine/Source/GameLogic/Object/Weapon.cpp` | `$L94047` -> `$L94764`; stale; twin-proven | `?newWeaponTemplate@WeaponStore@@IAEPAVWeaponTemplate@@VAsciiString@@@Z: [0]` |
| 54 | `0x00C0A650` `uw_00c0a650` (8B) | `game/GameEngine/Source/GameLogic/Object/Weapon.cpp` | `$L94511` -> `$L95228`; stale | `?parseWeaponTemplateDefinition@WeaponStore@@SAXPAVINI@@@Z: [0]` |
| 55 | `0x00C222A0` `uw_00c222a0` (8B) | `game/GameEngine/Source/GameClient/GameText.cpp` | `$L36609` -> `$L36210`; stale | `??1GameTextManager@@UAE@XZ: [0]` |
| 56 | `0x00C222A8` `uw_00c222a8` (14B) | `game/GameEngine/Source/GameClient/GameText.cpp` | `$L36610` -> `$L36211`; stale | `??1GameTextManager@@UAE@XZ: [1]` |
| 57 | `0x00C222B6` `uw_00c222b6` (14B) | `game/GameEngine/Source/GameClient/GameText.cpp` | `$L36611` -> `$L36212`; stale | `??1GameTextManager@@UAE@XZ: [2]` |
| 58 | `0x00C222E0` `uw_00c222e0` (11B) | `game/GameEngine/Source/GameClient/GameText.cpp` | `$L35574` -> `$L35139`; wrong | `?CreateGameTextInterface@@YAPAVGameTextInterface@@XZ: [0]` |
| 59 | `0x00C43860` `uw_00c43860` (11B) | `game/GameEngine/Source/GameNetwork/Network.cpp` | `$L60256` -> `$L61723`; stale | `?createNetwork@NetworkInterface@@SAPAV1@XZ: [0]` |
| 60 | `0x00C49580` `uw_00c49580` (11B) | `game/GameEngine/Source/Common/GameEngine.cpp` | `$L94056` -> `$L96464`; stale; twin-proven | `?createFileSystem@GameEngine@@MAEPAVFileSystem@@XZ: [0]` |
| 61 | `0x00C08638` `?dup_00C08638@@YAXXZ` (17B) | `game/GameEngine/Source/GameLogic/Map/TerrainLogicBuildBeacons.cpp` | `$L6425` -> `$L6426`; stale | `?buildBeacons@TerrainLogic@@IAEXXZ: [1]` |
| 62 | `0x00C088D0` `?dup_00C088D0@@YAXXZ` (11B) | `game/GameEngine/Source/GameLogic/System/BfmeCellGrid.cpp` | `$L607` -> `$L608`; stale | `??0CellGrid@@QAE@HHMM@Z: [0]` |

This batch repairs 20 bindings covering 296 existing function bytes; 4 labels still named another object label and 3 actions have byte-equal twins.
These are metadata identity repairs, not newly recovered byte counts.

## Native verification and limits

The combined ordinary gate passes 769/769 functions across 9 sources,
10 data rows, 116 DIR32 references and the body guard.
Staged current-provider preview: 9/9 UNKNOWN, 0/9 LINKS, 0/9 blocked. The 120-second deadline expired before a current-provider verdict.

Latest complete census observed remains [43590726489](https://github.com/Open-BFME/Open-BFME-1/actions/runs/43590726489),
input 1a248a7b476727c19e37a16744c71686fa8f3f5e, snapshot 2026-11-14 12:41 UTC:
3,086,248 LINKED bytes in 15,516 files. It predates both the earlier predicted +515B
and the previous eighty-task batch's +1,492B frozen-index previews; neither is a new
full-census result. Bounded previews establish neither a full-image link nor a game start,
FPS, memory, leak or crash fix.

Detailed original/final objects and proof records remain in `W:/OpenBFME/diagnostics/continue-20261115-eighty-next/batch-3/`
and `build/codex-20261115-eighty-next/`. Shared native objects were produced only by the
ordinary build; isolated compiler experiments never wrote its cache.

All source hashes and every compiled-object byte are retained, excluding only
the four-byte COFF creation-time field at file offsets 4..7. Every changed object
is compared byte-for-byte after removing exactly that field; no section, relocation,
symbol-table or debug byte is excluded.
The normal build regenerated its creation timestamp for: `game/GameEngine/Source/GameLogic/Object/Weapon.cpp`.
Weapon.cpp is deliberately not dependency-cached because a macro/parent-traversing
include lies outside the snapshotted search roots; its normal recompile is retained.

Publication follow-up: the normal pre-push gate for the last 58 cleanup repairs
passed at `e1e3445b84`. It recorded 56 successful verification receipts; the two
Weapon actions `uw_00c0a5e0` and `uw_00c0a650` were not recordable because their
evidence cannot be keyed with the existing unsnapshotted include paths. Direct
normal compilation, complete-object comparison excluding only the COFF timestamp,
byte checks and retail unwind-state checks passed for both. Automatic receipt
coverage remains incomplete for these two actions; this is not a complete cached
receipt package or a full-link/runtime result.
