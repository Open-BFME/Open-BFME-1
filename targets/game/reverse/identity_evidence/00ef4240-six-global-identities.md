# Six retail scalar globals

The six addresses below are independent mutable scalar objects. The notification pair and frame duration have matching Zero Hour declarations and uses. The command-line flags, forced CRC frame and horde draw count retain established role-describing names; these three names do not occur in the Zero Hour reference, so they are not asserted to be EA's original spellings.

## Retail storage and source ownership

| VA | Name | Type | Size | Section | Initial bytes | Definition owner |
|---|---|---|---|---|---|---|
| 0x012F4240 | lastNotificationWasStatus | bool | 1 | .data | 00 | GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyOverlay.cpp |
| 0x012F4244 | numOnlineInNotification | int | 4 | .data | 00000000 | GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyOverlay.cpp |
| 0x012BB1CC | TheW3DFrameLengthInMsec | int | 4 | .data | 21000000 | GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp |
| 0x012A6FA0 | TheCommandLineFlags | unsigned int | 4 | .data | 00000000 | GameEngine/Source/Common/T3CommandLineParsers.cpp |
| 0x012A6F38 | forcedCRCFrame | int | 4 | .data | ffffffff | GameEngine/Source/Common/T3CommandLineParsers.cpp |
| 0x01304B60 | TheW3DHordeModelDrawCount | int | 4 | .data | 00000000 | GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DHordeModelDrawConstructor.cpp |

`build/rlink/globals-1791159203/retail-probe-utf8.txt` records the PE section bounds, exact initial bytes, surrounding bytes, every existing DIR32 spelling at these starts, and the check for a data-row overlap or a DIR32 name strictly inside each extent. There are no such overlaps or interior names. Each address is written by executable instructions, so none is a compiler constant. The canonical DIR32 spellings already exist and are retained beside all alternative spellings. No existing pin is removed or rewritten.

The command-line table ends with a zero pair at VA 0x012A6FA0. Its first zero dword is also the mutable flags object written by option handlers. `retail-strings-callers.txt` records the table bytes and each handler's actual E9 chain. This storage coincidence does not establish a distinct datum or permit claiming the adjacent second dword.

## Notification pair

Zero Hour defines `static Bool lastNotificationWasStatus = FALSE` and `static Int numOnlineInNotification = 0` in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyOverlay.cpp:112`. The status cases assign true and increment the count only for a non-offline status (624 through 634). Ordinary messages, disconnects and buddy additions reset both (510, 564 and 585). Its notification display tests the boolean and whether the count exceeds one, then fetches `Buddy:MultipleOnlineNotification` (671 through 673). Deletion and the buddy-add request reset both (694 and 1233). The reference excerpts are in `reference-WOLBuddyOverlay.txt`.

Retail RVA 0x004EA5F0 reads the byte at VA 0x012F4240 and compares the signed dword at VA 0x012F4244 with one, then fetches the exact `Buddy:MultipleOnlineNotification` string at VA 0x01102058. RVA 0x004EE510 resets the pair for ordinary notifications and writes true while incrementing the count for status notifications. Its shipped `Buddy:MessageDisconnected`, `Buddy:AddNotification`, `Buddy:%lsNotification` and `Buddy:OnlineNotification` strings independently identify those branches. RVAs 0x004E9CF0, 0x004ECD10 and 0x004EDAD0 reset the pair. These are all direct retail references found by the probe. `body-004ea5f0.txt`, `body-004ee510.txt`, `body-004e9cf0.txt`, `body-004ecd10.txt` and `body-004edad0.txt` hold the original instruction bytes. `retail-strings-callers.txt` holds the strings and callers routed through the byte-verified ILT chains.

These globals have no receiver or arguments. Their users are notification functions and the buddy-response dispatcher. Their one shared definition must retain bool and int storage. Splitting the recovered reference TU into several game TUs requires external declarations in the other files, rather than private copies. A different byte width, an increment unrelated to online status, or a display comparison selecting a different notification would refute the identities.

## Frame duration

Zero Hour defines `Int TheW3DFrameLengthInMsec = 1000/LOGICFRAMES_PER_SECOND` in `GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp:108`. Its camera operations divide millisecond durations by this signed integer to count frames. `GameEngineDevice/Include/W3DDevice/GameClient/W3DGameClient.h:122` defines `setFrameRate(Real msecsPerFrame)` by assigning this global. The checked excerpts are `reference-W3DView.txt` and `reference-W3DGameClient.txt` under the raw evidence folder.

Retail RVA 0x006FB9C0 loads its sole float argument, calls the float-to-integer conversion machinery, stores EAX into VA 0x012BB1CC, and returns while popping four argument bytes (`body-006fb9c0.txt`). Retail camera methods divide durations by that address, including `rotateCamera` at RVA 0x0073BDD0 and `zoomCamera` at RVA 0x0073FC40. Camera final-zoom and final-pitch operations multiply frame counts by it. The game already defines the correct initialized scalar in W3DView.cpp; the placeholder setter's separate zero-initialized global is replaced by an external declaration. This does not rename or reclassify that setter function.

The scalar has no receiver or arguments. The writer consumes one float argument; the readers use signed integer arithmetic for milliseconds per frame. A different initialized value, a setter targeting another address, or division of a quantity unrelated to camera timing would refute this identity. All reader and writer RVAs and instructions are enumerated in `accesses.json` and `retail-probe-utf8.txt`.

## Command-line flags

Zero Hour contains no `TheCommandLineFlags` spelling (`reference-search-TheCommandLineFlags.txt`, exit 1 recorded in `inventory.txt`). Retail option handlers at RVAs 0x000608C0, 0x00060A00, 0x00060A60, 0x00061180, 0x000611A0, 0x000611C0, 0x000611E0, 0x00061200, 0x00061220, 0x00061240, 0x00061260, 0x000612B0, 0x00061300, 0x00061380, 0x00061430, 0x00061470 and 0x00061490 read or update VA 0x012A6FA0 using one option bit per handler. The `-noaudio` retail table entry follows its five-byte thunk to RVA 0x00060A60, whose body updates this mask and audio-option state. The CRC option handlers contain the shipped warning about specifying both `-deepCRC` and `-liteCRC`. Exact table bytes, strings and routes are in `retail-strings-callers.txt`; all access instructions are in `retail-probe-utf8.txt`.

This scalar has no receiver or arguments; handlers use the ordinary argument-array and count contract or the already recovered no-argument contract. The mask's name describes its proven role, without asserting a Zero Hour identity. A writer assigning a non-mask quantity, an access of another width, or a table route to a different handler would refute this role.

## Forced CRC frame

Zero Hour contains no `forcedCRCFrame` spelling (`reference-search-forcedCRCFrame.txt`, exit 1 recorded in `inventory.txt`). Retail RVA 0x000613F0 converts the second command-line argument with the imported integer parser, accepts only a positive signed result, and stores it to VA 0x012A6F38 and the adjacent diagnostic configuration at VA 0x012A6FB4 (`body-000613f0.txt`). Retail RVA 0x0038DA10 compares the scalar with -1 and enables diagnostic generation from the selected frame minus network slack minus two through that frame, using unsigned frame comparisons. RVA 0x0038B430 compares it with the current logic frame to force checksum mismatch reporting. RVA 0x00388C10 is the remaining direct reader. Their complete original instructions are in the corresponding `body-*.txt` files.

The scalar has no receiver or arguments. The writer consumes the command-line array and count; logic readers compare its value with the frame counter at receiver offset 0x3C. The existing descriptive spelling states this role. Its signed definition preserves the negative disabled sentinel; unsigned comparisons against the logic frame retain their emitted instructions only if the source gates verify them. A disabled sentinel other than -1, a writer accepting a non-frame quantity, or readers comparing against another field would refute this role.

## Horde draw count

Zero Hour contains no `TheW3DHordeModelDrawCount` spelling (`reference-search-TheW3DHordeModelDrawCount.txt`, exit 1 recorded in `inventory.txt`). The existing constructor pin `??0W3DHordeModelDraw@@QAE@PAVThing@@PBVModuleData@@@Z` points at RVA 0x00008378. Its retail bytes `e973997400` jump to RVA 0x00751CF0. The existing destructor pin at RVA 0x000305F3 has bytes `e988187200` and jumps to RVA 0x00751E80. The constructor installs vtables VA 0x01122470 and VA 0x011223A0 and increments VA 0x01304B60. The destructor installs those same vtables and decrements the same dword. RVA 0x00751F30 returns the dword. The scalar is therefore the live horde-model-draw instance count. No body identity is changed by this correction.

`body-00751cf0.txt`, `body-00751e80.txt`, `body-00751f30.txt`, `thunks.json` and `retail-strings-callers.txt` record these facts, the existing pins and the factory and destructor-wrapper callers through the verified thunks. The scalar has no receiver or arguments; its writers operate on the pinned horde constructor and destructor receivers. A thunk ending at a different body, different installed vtables between the writers, or a counter increment outside construction would refute this role.

## Competing spellings and verification

`inventory.txt` records each spelling's number of declaring game files and the exact declaration locations before correction. Notification boolean counts are 3 for the real spelling and 1 for each alternative; notification integer counts are also 3, 1 and 1. Frame duration counts are 10 for the real spelling, 2 for g_006fb9c0 and 0 for g_bfmeDivGT. Command-line mask counts are 2, 1 and 1. Forced CRC frame and horde draw count each have 1 file for each spelling. Evidence, rather than the declaration count, determines the selected spelling.

Every direct four-byte target occurrence in retail .text was decoded from a ledger or Ghidra body boundary, with no uncovered occurrence. Memory access widths and access modes are saved in `accesses.json`. The probe also searches other image sections for pointers to these scalar starts. The function gates, data gates, pin-consistency check, ledger-integrity check, declared-unmatched check and before/after link checks are recorded in `build/worker-final.md`, with current gate outputs under `build/rlink/globals-reapply-1791160903/` and the original identity measurements under `build/rlink/globals-1791159203/`. These gates establish byte preservation separately from the identity evidence above.

## Notification declaration exception

The external notification definitions and data rows are retained in WOLBuddyOverlay.cpp. WOLBuddyResponses.cpp retains its original private declarations because each tested external declaration shape failed the HandleBuddyResponses byte comparison while its other rows passed. The tested shapes were bool with int at file scope, volatile bool with volatile int at file scope, unsigned char with int at file scope, and bool with int at block scope inside HandleBuddyResponses. Temporary DIR32 entries for the qualified type spellings were removed with the failed probes. The original source was restored byte for byte and its complete function gate passed again. No notification body was rewritten.

The raw probe outputs are `build/rlink/globals-reapply-1791160903/probe-notification-00-extern-bool-int.log`, `probe-notification-01-extern-volatile-pair.log`, `probe-notification-02-extern-unsigned-char-int.log` and `probe-notification-03-block-extern-bool-int.log` in the same folder. `notification-byte-measurements.log` derives their byte differences from the full target and compiled byte arrays. `notification-restored-baseline.log` records the restored source gate. This is a declaration code-generation blocker rather than uncertainty about the two retail identities. An external declaration shape passing every WOLBuddyResponses.cpp row would settle the remaining consolidation.
