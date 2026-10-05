# TheSkirmishGameInfo at VA 0x012F7094

The datum is `SkirmishGameInfo *TheSkirmishGameInfo`, a single four-byte pointer object in `.data`. It initially contains `00 00 00 00`, with no initial relocation. The next distinct DIR32 start is the bool at 0x012F709A; the four-byte size is established by pointer loads and stores and by the compiler's `sizeof`, not by that six-byte gap. `build/rlink/identity-15/retail-probe.log` checks that no data row or distinct DIR32 address lies inside the extent. `retail-extra-complete.log` finds no data-section pointer into that extent.

## Retail facts and contract

At RVA 0x0057BE50, retail tests the pointer loaded from 0x012F7094. When null it allocates 0x27C bytes, puts the returned allocation in ECX and calls the five-byte E9 ILT at VA 0x00403409. Its bytes are `e9 02 28 07 00`, giving final body VA 0x00475C10 (RVA 0x00075C10). After construction the caller stores the returned object in 0x012F7094. The raw owner, constructor and jump chain are in `skirmish-create.log`, `skirmish-constructor.log` and `retail-extra-complete.log`.

The constructor initializes the GameInfo receiver and eight slots beginning at offset 0x5C with stride 0x44. It installs its main vtable at 0x01075E90 and its secondary table at 0x01075E7C. The existing matched constructor source and its contract identify this object as `SkirmishGameInfo`. Secondary-table slot +0x08 holds VA 0x0040489A, whose five-byte E9 thunk jumps to the type-name body at RVA 0x00075CF0. That body returns VA 0x01075ED4, whose raw bytes are `SkirmishGameInfo` followed by NUL. `skirmish-vtables.log` verifies the slot, jump bytes, final body and string. The string, table and constructor are independent of the competing global spellings.

The Zero Hour reference's `GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h` declares `extern SkirmishGameInfo *TheSkirmishGameInfo`. Its `GameClient/GUI/GUICallbacks/Menus/SkirmishGameOptionsMenu.cpp` defines that pointer as null, allocates a `SkirmishGameInfo` when it is null, and uses it for the slot, seed and map operations also present in the retail skirmish start path. The raw reference excerpts are retained in `build/rlink/identity-15/reference-contracts.log`. An existing pin for `SkirmishBattleHonors::write` also records this address as TheSkirmishGameInfo while accessing slot-zero color, player template and map. The snapshot string and actual allocation establish the derived type instead of relying on that pin alone.

The main probe records all direct readers and writers covered by the function ledger, their sources and their ILT chains. The supplementary Ghidra-boundary inventory additionally covers the direct sites in bodies starting at RVAs 0x00079060 and 0x00394260 that have no covering ledger row. It prints raw instructions from those bodies rather than treating their draft names as identity evidence. Shutdown and close paths clear the pointer after releasing the snapshot subobject at receiver offset 0x58. Recorder, preference, skirmish screen and load-screen callers read or test the same pointer. The pointer is not an integer flag, a void-owned object or a second independent singleton. The complete direct-reference inventory is in `retail-probe.log` and `retail-extra-complete.log`; indirect writes are not exhaustively claimed.

Every existing competing decorated spelling and the count of game C++ files explicitly declaring it is recorded with declaration lines in `spelling-census.log`. This includes the four `g_bfmeCurrentCB` pointer types separately. Existing `TheSkirmishGameInfo` GameInfo-pointer declarations are corrected to the reference's SkirmishGameInfo-pointer declaration. Existing correctly typed declarations and the reference-file definition remain. Counts are used to find all declarations, not to choose the name.

## Correction and refutation

The original Zero Hour-derived definition in `SkirmishGameOptionsMenu.cpp` owns the new verified data row. `build/rlink/identity-15/add-data-skirmish.log` proves its size and zero initial bytes. The chosen decorated spelling `?TheSkirmishGameInfo@@3PAVSkirmishGameInfo@@A` is added beside the retained `GameInfo` spelling in `dir32_addresses.csv`. Existing symbols pins are untouched. The old free pointer names are replaced in game C++ callers. Where callers retain a partial ABI view, they explicitly cast the canonical pointer to that view for the existing operation. No view's member or function identity, inheritance, wrapper or forwarder is invented or renamed.

An ILT chain routing the allocation to another constructor, a type-name slot returning another type, a retail store publishing a different class, a non-pointer access, an interior datum, or any changed verified byte would refute this correction. The final source gates, exact per-file LINKED measurements and retained unrelated blockers are in `build/worker-final.md`.

## Spelling census before the correction

Counts below come from the original source snapshots. Template-static counts include the shared game header and owning explicit instantiation, plus files with explicit extern-template declarations. Ordinary pointer counts require the decorated pointer type. For the STLport member, zero means no explicit game declaration; the vendor header and the three known retail numeric-output users are recorded in the raw census. Stale decorated types whose current source already differs are identified in the notes.

| VA | Existing decorated spelling | Game files | Notes |
|---|---|---:|---|
| 0x012F7094 | `?Rva00579160TheCurrent@@3PAURva00579160Current@@A` | 5 | Count requires the decorated pointer type. |
| 0x012F7094 | `?TheSkirmishGameInfo@@3PAVGameInfo@@A` | 3 | Count requires the decorated pointer type. |
| 0x012F7094 | `?g_bfmeCurrentCB@@3PAVBfmeGameInfo@@A` | 1 | Count requires the decorated pointer type. |
| 0x012F7094 | `?g_bfmeCurrentCB@@3PAVGameInfo@@A` | 2 | Count requires the decorated pointer type. |
| 0x012F7094 | `?g_bfmeCurrentCB@@3PAVSkirmishGameInfo@@A` | 2 | Count requires the decorated pointer type. |
| 0x012F7094 | `?g_bfmeCurrentCB@@3PAXA` | 2 |  |
| 0x012F7094 | `?g_bfmeFlagBRA@@3HA` | 0 |  |
| 0x012F7094 | `?g_bfmeObjECD@@3PAVBfmeObjECC@@A` | 1 | Count requires the decorated pointer type. |
