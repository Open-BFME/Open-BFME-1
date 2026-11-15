# BFME 1 continuation: tasks 23-42 of 80

Immediate baseline `306fd57c727f81b4fab796328b93049ab63324b3`.
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
| 23 | `0x00C2A633` `uw_00c2a633` (22B) | `game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp` | `$L85476` -> `$L85396`; stale | `??1PeerRequest@@QAE@XZ: [9]` |
| 24 | `0x00C3D420` `uw_00c3d420` (8B) | `game/GameEngine/Source/GameClient/Drawable/Update/BeaconClientUpdateClientUpdate.cpp` | `$L722` -> `$L723`; stale; twin-proven | `?createParticleSystem@@YA?AVParticleSystemHandle@@PAVDrawable@@@Z: [0]` |
| 25 | `0x00C3D428` `uw_00c3d428` (8B) | `game/GameEngine/Source/GameClient/Drawable/Update/BeaconClientUpdateClientUpdate.cpp` | `$L723` -> `$L724`; wrong | `?createParticleSystem@@YA?AVParticleSystemHandle@@PAVDrawable@@@Z: [1]` |
| 26 | `0x00C3D440` `uw_00c3d440` (8B) | `game/GameEngine/Source/GameClient/Drawable/Update/BeaconClientUpdateClientUpdate.cpp` | `$L811` -> `$L812`; stale; twin-proven | `?hideBeacon@BeaconClientUpdate@@QAEXXZ: [0]` |
| 27 | `0x00C3D448` `uw_00c3d448` (8B) | `game/GameEngine/Source/GameClient/Drawable/Update/BeaconClientUpdateClientUpdate.cpp` | `$L813` -> `$L814`; stale; twin-proven | `?hideBeacon@BeaconClientUpdate@@QAEXXZ: [1]` |
| 28 | `0x00C3D460` `uw_00c3d460` (8B) | `game/GameEngine/Source/GameClient/Drawable/Update/BeaconClientUpdateClientUpdate.cpp` | `$L848` -> `$L849`; stale; twin-proven | `?clientUpdate@BeaconClientUpdate@@UAEXXZ: [0]` |
| 29 | `0x00C40970` `uw_00c40970` (8B) | `game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp` | `$L81468` -> `$L81388`; stale; twin-proven | `?removeStagingRoom@GameSpyInfo@@UAEXVGameSpyStagingRoom@@@Z: [0]` |
| 30 | `0x00C40BE0` `uw_00c40be0` (8B) | `game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp` | `$L89366` -> `$L89267`; stale; twin-proven | `?addStagingRoom@GameSpyInfo@@UAEXVGameSpyStagingRoom@@@Z: [0]` |
| 31 | `0x00C40BE8` `uw_00c40be8` (11B) | `game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp` | `$L89368` -> `$L89269`; stale; twin-proven | `?addStagingRoom@GameSpyInfo@@UAEXVGameSpyStagingRoom@@@Z: [1]` |
| 32 | `0x00C40C70` `uw_00c40c70` (8B) | `game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp` | `$L87819` -> `$L87739`; stale | `?addToSavedIgnoreList@GameSpyInfo@@UAEXHVAsciiString@@@Z: [0]` |
| 33 | `0x00C40C78` `uw_00c40c78` (8B) | `game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp` | `$L87820` -> `$L87740`; stale; twin-proven | `?addToSavedIgnoreList@GameSpyInfo@@UAEXHVAsciiString@@@Z: [1]` |
| 34 | `0x00C40EE8` `uw_00c40ee8` (11B) | `game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp` | `$L89609` -> `$L89510`; stale; twin-proven | `??0GameSpyInfo@@QAE@XZ: [1]` |
| 35 | `0x00C40EF3` `uw_00c40ef3` (11B) | `game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp` | `$L89610` -> `$L89511`; stale; twin-proven | `??0GameSpyInfo@@QAE@XZ: [2]` |
| 36 | `0x00C40EFE` `uw_00c40efe` (11B) | `game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp` | `$L89611` -> `$L89512`; stale; twin-proven | `??0GameSpyInfo@@QAE@XZ: [3]` |
| 37 | `0x00C40F4B` `uw_00c40f4b` (11B) | `game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp` | `$L89618` -> `$L89519`; stale; twin-proven | `??0GameSpyInfo@@QAE@XZ: [10]` |
| 38 | `0x00C40F56` `uw_00c40f56` (11B) | `game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp` | `$L89619` -> `$L89520`; stale; twin-proven | `??0GameSpyInfo@@QAE@XZ: [11]` |
| 39 | `0x00C40F61` `uw_00c40f61` (11B) | `game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp` | `$L89620` -> `$L89521`; stale; twin-proven | `??0GameSpyInfo@@QAE@XZ: [12]` |
| 40 | `0x00C40F6C` `uw_00c40f6c` (11B) | `game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp` | `$L89621` -> `$L89522`; stale; twin-proven | `??0GameSpyInfo@@QAE@XZ: [13]` |
| 41 | `0x00C40F85` `uw_00c40f85` (14B) | `game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp` | `$L89623` -> `$L89524`; stale; twin-proven | `??0GameSpyInfo@@QAE@XZ: [15]` |
| 42 | `0x00C41200` `uw_00c41200` (11B) | `game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp` | `$L91176` -> `$L91077`; stale; twin-proven | `?createNewGameSpyInfoInterface@GameSpyInfoInterface@@SAPAV1@XZ: [0]` |

This batch repairs 20 bindings covering 207 existing function bytes; 1 labels still named another object label and 17 actions have byte-equal twins.
These are metadata identity repairs, not newly recovered byte counts.

## Native verification and limits

The combined ordinary gate passes 192/192 functions across 2 sources,
3 data rows, 22 DIR32 references and the body guard.
Staged current-provider preview: 2/2 UNKNOWN, 0/2 LINKS, 0/2 blocked. The 120-second deadline expired before a current-provider verdict.

Latest complete census observed remains [43590726489](https://github.com/Open-BFME/Open-BFME-1/actions/runs/43590726489),
input 1a248a7b476727c19e37a16744c71686fa8f3f5e, snapshot 2026-11-14 12:41 UTC:
3,086,248 LINKED bytes in 15,516 files. It predates both the earlier predicted +515B
and the previous eighty-task batch's +1,492B frozen-index previews; neither is a new
full-census result. Bounded previews establish neither a full-image link nor a game start,
FPS, memory, leak or crash fix.

Detailed original/final objects and proof records remain in `W:/OpenBFME/diagnostics/continue-20261115-eighty-next/batch-2/`
and `build/codex-20261115-eighty-next/`. Shared native objects were produced only by the
ordinary build; isolated compiler experiments never wrote its cache.

Twin counts describe the corrected action, not twins of a still-defined wrong old label.
