# BFME 1 continuation: tasks 63-80 of 80

Immediate baseline `f22544b103aeefb3ac93c33742d8ade982c0bd1a`.
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
| 63 | `0x00C14188` `?Rva00C14188Cleanup@@YAXXZ` (24B) | `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate_ctor_Thunk.cpp` | `$L570` -> `$L571`; wrong | `??0WorkerAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z: [1]` |
| 64 | `0x00C17688` `?Rva00C17688Cleanup@@YAXXZ` (25B) | `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine.cpp` | `$L666` -> `$L672`; stale | `?getStats@ScriptEngine@@QAE?AVAsciiString@@PAM00@Z: [0]` |
| 65 | `0x00C185CD` `?Rva00C185CDCleanup@@YAXXZ` (24B) | `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineRva00347E60.cpp` | `$L19222` -> `$L17197`; stale | `??0ScriptEngine@@QAE@XZ: [21]` |
| 66 | `0x00C185E5` `?Rva00C185E5Cleanup@@YAXXZ` (24B) | `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineRva00347E60.cpp` | `$L18327` -> `$L17198`; stale | `??0ScriptEngine@@QAE@XZ: [22]` |
| 67 | `0x00C21FD1` `?Rva00C21FD1Cleanup@@YAXXZ` (24B) | `game/GameEngine/Source/GameClient/GameClientConstructor00433340.cpp` | `$L9947` -> `$L9946`; wrong | `??0GameClient@@QAE@XZ: [8]` |
| 68 | `0x00C31A80` `?Rva00C31A80Cleanup@@YAXXZ` (34B) | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineCustomMatchRva0053E870.cpp` | `$L11326` -> `$L11329`; wrong | `?rva0053E870@BfmeAptScreenOnlineCustomMatch@@QAEXXZ: [1]` |
| 69 | `0x00C134B6` `?dup_00C134B6@@YAXXZ` (24B) | `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdateCtorThunk.cpp` | `$L541` -> `$L543`; wrong | `??0DozerAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z: [2]` |
| 70 | `0x00C1848E` `?dup_00C1848E@@YAXXZ` (25B) | `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineRva00347E60.cpp` | `$L18308` -> `$L17179`; stale | `??0ScriptEngine@@QAE@XZ: [3]` |
| 71 | `0x00C184A7` `?dup_00C184A7@@YAXXZ` (27B) | `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineRva00347E60.cpp` | `$L17179` -> `$L17180`; wrong | `??0ScriptEngine@@QAE@XZ: [4]` |
| 72 | `0x00C18508` `?dup_00C18508@@YAXXZ` (27B) | `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineRva00347E60.cpp` | `$L18315` -> `$L17186`; stale | `??0ScriptEngine@@QAE@XZ: [10]` |
| 73 | `0x00C1853F` `?dup_00C1853F@@YAXXZ` (24B) | `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineRva00347E60.cpp` | `$L18318` -> `$L17189`; stale | `??0ScriptEngine@@QAE@XZ: [13]` |
| 74 | `0x00C1859D` `?dup_00C1859D@@YAXXZ` (24B) | `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineRva00347E60.cpp` | `$L17194` -> `$L17195`; wrong | `??0ScriptEngine@@QAE@XZ: [19]` |
| 75 | `0x00C185B5` `?dup_00C185B5@@YAXXZ` (24B) | `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineRva00347E60.cpp` | `$L18325` -> `$L17196`; stale | `??0ScriptEngine@@QAE@XZ: [20]` |
| 76 | `0x00C185FD` `?dup_00C185FD@@YAXXZ` (24B) | `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineRva00347E60.cpp` | `$L18328` -> `$L17199`; stale | `??0ScriptEngine@@QAE@XZ: [23]` |
| 77 | `0x00C49F90` `?dup_00C49F90@@YAXXZ` (8B) | `game/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadar_buildTerrainTexture.cpp` | `$L1310` -> `$L1311`; wrong | `?buildTerrainTexture@W3DRadar@@IAEXPAVTerrainLogic@@@Z: [2]` |
| 78 | `0x00C4B518` `?dup_00C4B518@@YAXXZ` (11B) | `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayCreate.cpp` | `$L620` -> `$L621`; wrong | `?createVideoBuffer@W3DDisplay@@UAEPAVVideoBuffer@@_N@Z: [1]` |
| 79 | `0x00C49560` `uw_00c49560` (11B) | `game/GameEngine/Source/GameLogic/System/GameLogic.cpp` | `$L120613` -> `$L123359`; stale; twin-proven | `?createTerrainLogic@GameLogic@@EAEPAVTerrainLogic@@XZ: [0]` |
| 80 | `0x00C0990C` `?Rva00C0990CCleanup@@YAXXZ` (20B) | `game/GameEngine/Source/GameLogic/Object/Rva001D48A0Xfer.cpp` | `$L12196` -> `$L12200`; stale | `?DoXfer@Object@@MAEXAAVXfer@@@Z: [4]` |

This batch repairs 18 bindings covering 404 existing function bytes; 8 labels still named another object label and 1 actions have byte-equal twins.
These are metadata identity repairs, not newly recovered byte counts.

## Native verification and limits

The combined ordinary gate passes 96/96 functions across 10 sources,
4 data rows, 185 DIR32 references and the body guard.
Staged current-provider preview: 10/10 UNKNOWN, 0/10 LINKS, 0/10 blocked. The 120-second deadline expired before a current-provider verdict.

Latest complete census observed remains [43590726489](https://github.com/Open-BFME/Open-BFME-1/actions/runs/43590726489),
input 1a248a7b476727c19e37a16744c71686fa8f3f5e, snapshot 2026-11-14 12:41 UTC:
3,086,248 LINKED bytes in 15,516 files. It predates both the earlier predicted +515B
and the previous eighty-task batch's +1,492B frozen-index previews; neither is a new
full-census result. Bounded previews establish neither a full-image link nor a game start,
FPS, memory, leak or crash fix.

Detailed original/final objects and proof records remain in `W:/OpenBFME/diagnostics/continue-20261115-eighty-next/batch-4/`
and `build/codex-20261115-eighty-next/`. Shared native objects were produced only by the
ordinary build; isolated compiler experiments never wrote its cache.

All source hashes and every compiled-object byte are retained, excluding only
the four-byte COFF creation-time field at file offsets 4..7. Every changed object
is compared byte-for-byte after removing exactly that field; no section, relocation,
symbol-table or debug byte is excluded.
