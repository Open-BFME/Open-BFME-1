# Apt Palantir and Living World state bytes

Retail proves six independent one-byte state variables. The canonical spellings below describe their witnessed roles; none claims to recover EA's original data identifier. `g_aptPalantirInitialized`, `g_aptPalantirJewelBrightened`, and `g_aptLivingWorldClosing` describe the wrong roles at their pinned addresses. Existing pins and DIR32 entries remain additive historical candidates. No function identity or function extent changes.

The baseline is `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`, SHA-256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`. All six bytes belong to writable `.data` (section RVA `0x00EA5000`, virtual size `0x000B3000`, raw size `0x00049000`, characteristics `0xC0000040`). The Palantir closed byte is file-backed and initially `01`. The other five are in the section's zero-filled virtual tail and initially `00`. Every direct instruction referencing one of these addresses has a one-byte memory operand. Each is written at runtime, so none is a compiler constant. There is no existing data-row overlap and no DIR32 address strictly inside any proposed one-byte extent.

| VA | Canonical role spelling | Initial byte | Reader body RVAs | Writer body RVAs |
|---|---|---|---|---|
| `0x012B7D84` | `g_aptPalantirClosed` | `01` | `0x00563940`, `0x00563970`, `0x00565000`, `0x00565070` | `0x00563980`, `0x00565000`, `0x00565070`, `0x00565100`, `0x00565F30` |
| `0x012F499C` | `g_aptLivingWorldVisible` | `00` | `0x0051A6D0`, `0x0051AF30`, `0x0051AF70` | `0x0051AB40`, `0x0051AF30`, `0x0051AF70` |
| `0x012F499D` | `g_aptLivingWorldInitialized` | `00` | `0x0051A6C0`, `0x0051AB40` | `0x0051A6E0`, `0x0051AB40`, `0x0051AF70` |
| `0x012F4AFC` | `g_aptPalantirCallbacksRegistered` | `00` | `0x00563910`, `0x00565F30` | `0x00565F30` |
| `0x012F4AFD` | `g_aptPalantirShowRequested` | `00` | `0x00563940`, `0x00565000` | `0x00565000`, `0x00565100`, `0x00565F30` |
| `0x012F4AFE` | `g_aptPalantirCloseRequested` | `00` | `0x00563940`, `0x00565000`, `0x00565070` | `0x00563980`, `0x00565000`, `0x00565070`, `0x00565F30` |

## Retail state transitions and contracts

Palantir registration at RVA `0x00565F30` returns when the WindowManager singleton is absent or the callbacks-registered byte is nonzero. Its successful path resolves the APT window index, binds the EA strings `AptPalantir::OnInitialized` and `AptPalantir::OnClosed` to callback pointers, and registers the remaining Palantir callbacks. At the end it clears show requested and close requested, sets closed, and sets callbacks registered. The callback pointers are VA `0x0041F62C` (bytes `e9 cf 5a 54 00`, target RVA `0x00565100`) and VA `0x00434022` (bytes `e9 59 f9 52 00`, target RVA `0x00563980`). Each is a complete five-byte ILT `E9` ending at the corresponding body, with no further jump at that body's entry.

The `OnInitialized` body clears closed and show requested before calling the Palantir singleton's virtual slot `0x2C`. It then invokes the APT script `BrightenJewel` through WindowManager. This script name does not identify the show-requested byte: the byte was already cleared, and its only writer of one is the show-window path. The `OnClosed` body hides the indexed APT window, sets closed to one, and clears close requested. This refutes an ordinary initialized-state interpretation of the closed byte.

RVA `0x00565000` hides the window when close requested is nonzero, sets closed, and clears close requested. If close requested was zero and closed was also zero, it returns. Otherwise, if show requested is zero, it calls the indexed show-window method and sets show requested to one. The flag therefore latches a request to show until `OnInitialized` clears it; it is not a jewel-brightness state or a persistent visibility flag. RVA `0x00565070` takes one byte in its first stack argument. A nonzero argument immediately hides an open Palantir, surrounding the call with close-requested writes of one and zero and setting closed. A zero argument, when neither closed nor close requested is set, invokes the APT script literal `Close` and sets close requested. The EA callback and script strings together establish the two distinct close states.

The show call in RVA `0x00565000` goes through VA `0x00412733` (bytes `e9 18 35 45 00`) to RVA `0x00465C50`, the existing `WindowManager::showAptWindow(int)` body. The hide calls go through VA `0x0042144A` (bytes `e9 11 60 44 00`) to RVA `0x00467460`, the existing `WindowManager::hideAptWindow(int)` body. The APT script call goes through VA `0x00415235` (bytes `e9 b6 23 45 00`) to RVA `0x004675F0`. At each call ECX receives WindowManager from VA `0x012F19E8`, and the first stack argument is the integer window index from VA `0x012B7D80`. The flag bodies are free functions, with no flag receiver, and the three leaf getters return the byte in AL without normalizing it. RVA `0x00563940` returns one only when closed, show requested, and close requested are all zero.

The show-method identity is independently documented in `targets/game/reverse/identity_evidence/00465c50-WindowManager-showAptWindow.md`, including the matched BannerUI caller. The current raw callee probes confirm the indexed receiver layout at `ECX + 0xA8 + index * 20`, the show method's write of slot bit zero and receiver byte `0x1AD`, and the hide method's test of slot bit one before its internal hide call. Both return in AL with `ret 4`. These probes support the existing show and hide pins rather than relying on their spellings alone.

The matched `AptPalantir::hide(bool)` caller at RVA `0x00592CD0` sends zero to the RVA `0x00565070` helper when hiding. Its opposite branch calls RVA `0x00565000`. The retail call at VA `0x00992CE7` encodes ILT VA `0x00415CA3` (bytes `e9 c8 f3 54 00`, target RVA `0x00565070`); the call at VA `0x00992D2D` encodes ILT VA `0x00440386` (bytes `e9 75 4c 52 00`, target RVA `0x00565000`). This independently supports interpreting the script `Close` path as a pending close request.

Living World registration at RVA `0x0051AB40` is skipped when the initialized byte is nonzero or WindowManager is absent. Before resolving the Living World window it clears both flags. Its `AptLivingWorldUI::OnInitialized` literal is bound to VA `0x0040EA5C` (bytes `e9 7f bc 50 00`, final target RVA `0x0051A6E0`). That body unconditionally sets the initialized byte to one, then tests the singleton at VA `0x012F4B78`. If present it tail-jumps through VA `0x004271FB` (bytes `e9 50 0a 56 00`, final target RVA `0x00587C50`), passing the singleton as ECX. The callback takes no stack arguments. There is no close operation before the flag write, which refutes `g_aptLivingWorldClosing`.

The Living World show body at RVA `0x0051AF30` tests visible, shows the indexed window only when visible is zero, and then sets visible to one. The hide body at RVA `0x0051AF70` tests visible, hides only when visible is nonzero, and then clears both visible and initialized. Both call the same proven WindowManager show and hide ILT routes described above, using the Living World index at VA `0x012F49A8`. The visible getter at RVA `0x0051A6D0` is called through VA `0x0042C82C` (bytes `e9 9f de 4e 00`); the caller at RVA `0x00584D60` shows the Living World UI when that getter returns zero. The initialized getter at RVA `0x0051A6C0` is called through VA `0x0041B6FD` (bytes `e9 be ef 4f 00`); the caller at RVA `0x005880C0`, after ensuring visibility, skips its update path until initialized is nonzero.

## Competing spellings before the correction

Counts are numbers of distinct game files declaring the base identifier, regardless of its declared type. The raw inventory also lists the exact decorated DIR32 spellings. Declaration count does not prove identity.

| VA | Spelling | Declaring game files |
|---|---|---|
| `0x012B7D84` | `g_aptPalantirInitialized` | 2 |
| `0x012B7D84` | `g_bfmeC1020` | 1 |
| `0x012B7D84` | `g_bfmeF1071` | 1 |
| `0x012B7D84` | `g_bfmeF1085` | 1 |
| `0x012B7D84` | `g_bfmeFlagDMa` | 1 |
| `0x012B7D84` | `g_Va012B7D84` | 1 |
| `0x012F499C` | `g_aptLivingWorldVisible` | 1 |
| `0x012F499C` | `g_aptLivingWorldGuardB` | 1 |
| `0x012F499C` | `g_Va012F499C` | 1 |
| `0x012F499D` | `g_aptLivingWorldClosing` | 1 |
| `0x012F499D` | `g_aptLivingWorldGuardA` | 1 |
| `0x012F499D` | `g_Va012F499D` | 2 |
| `0x012F4AFC` | `g_bfmeFlagMD` | 2 |
| `0x012F4AFD` | `g_aptPalantirJewelBrightened` | 2 |
| `0x012F4AFD` | `g_bfmeFlagDMb` | 1 |
| `0x012F4AFD` | `g_bfmeG1085` | 1 |
| `0x012F4AFE` | `g_bfmeD1020` | 1 |
| `0x012F4AFE` | `g_bfmeFlagDMc` | 2 |
| `0x012F4AFE` | `g_bfmeH1071` | 1 |
| `0x012F4AFE` | `g_bfmeH1085` | 1 |

## Correction, raw evidence, and refutation

The four Palantir globals are defined in the existing Palantir data owner `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptPalantir.cpp`. The two Living World globals are defined in `game/GameEngine/Source/GameClient/GUI/AptLivingWorldUIVisibility.cpp`. All declarations use unsigned one-byte storage so every file refers to the owner's exact COFF symbol and the raw-byte getters retain their contract. This type choice is justified only if the scoped gate reproduces every instruction of every affected row. Six data rows verify the scalar sizes and initial bytes separately. New DIR32 spellings are added beside the old ones; no existing symbol pin is rewritten or deleted.

Raw local probes are `build/rlink/retail-flags.log`, `build/rlink/retail-flags-concise.log`, and `build/rlink/retail-contracts.log`. They include section and byte reads, every absolute reference in `.text`, operand-width and read/write validation, complete owner disassemblies, exact ILT bytes, callback strings and bound pointers, callers, existing data-row range checks, and spelling counts. `build/rlink/ledger-spellings.log` captures the existing pin and DIR32 entries, and `build/rlink/range-neighbours.log` captures neighbouring names. `build/rlink/window-method-pins.log`, `build/rlink/retail-show-method.log`, and `build/rlink/retail-hide-method.log` capture the supporting callee pins and bytes. Gate outputs and before/after LINKED measurements are listed in `build/worker-final.md`.

A retail access wider than one byte, another datum spanning one of these addresses, a different callback pointer in the EA-string binding, an ILT jump to a different final body, or a writer inconsistent with the described transitions would refute the corresponding correction. A different proven EA identifier would supersede its role spelling. Any changed instruction in a scoped verification refutes acceptance of the declaration type or respelling. The current evidence establishes roles and storage, not original EA variable identifiers or runtime success of a requested window operation.
