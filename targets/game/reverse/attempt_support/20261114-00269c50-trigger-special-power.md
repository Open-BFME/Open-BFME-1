# 0x00269C50 (1073 B) handoff, 2026-11-14 workflow session

## Blocking prerequisite on this host: nothing was compiled

`tools/probe.py` stops right away with `wine not found. Install Wine to run MSVC 7.1 on this host.`
(it comes from `tools/build.py` `compiler_command`). This host has no wine binary, no
wine prefix, no apt cache, and nothing usable cached under `build/`. The sandbox rules
forbid network fetches. So this session could not reproduce the bank, and it measured
**no** variant. Every number below comes from the bank's own recorded measurements, not
from a rerun. The next worker needs a host with wine and VC7.1. From the repo root, run
`build/wf/0x00269c50/probe_all.sh`. It probes the two bank forms, the landing-ready
file and five donor-derived variants.

## Prior verdicts (read in full)

- Bank `targets/game/reverse/attempts/0x00269c50.cpp`: score 0.9851, 16 non-relocation diffs.
  This is the **ABI-wrong** by-value `Int key` form. Do not land it.
- `attempt_support/0x00269c50-20261013-formB-constref-abi.inc`: the ABI-correct `const Int &`
  form, 23 diffs, shape 0.997, extent 1073 = retail. Residue as recorded:
  - +0xc7: retail loads TheGameLogic into ECX, ours into EDX. That is 2 bytes, at +0xc8 and +0xce.
  - +0x182..+0x192: the configure() args. Retail allocates value/player in EDX and name/store in ECX.
    Ours allocates them ECX,ECX,EDX,ECX. The recorded "structural insert" at +0x193 is only a
    push-scheduling consequence of that register choice.
  - +0x1eb..+0x215: the Coord3D copy. Retail uses eax/edx, ours mirrors them. This is 14 bytes,
    and it appears only on the const-ref form.
- Roughly 250 spellings were closed across six sessions. They include rotation_sweep,
  eh_levers, shape_search, shape_family_levers and flag_sweep, plus the reference/pointer
  axis and the store/key/kind/fx/hasValue/Coord3D spellings. See both files. Do not re-run them.
- `re_log.py show 0x00269c50` printed only the summary line. It has no extra per-RVA entries
  beyond the banks.

## Retail facts this session added (static analysis, no compiler)

1. **Identity/ABI: the bank's decorated name is contradicted.**
   `tools/ilt_oracle.py check` results:
   - `?finishSpecialPower@SpecialPowerModule@@QAEXI@Z` → **CONTRADICTED** (p_false 3.9e-4)
   - `?triggerSpecialPower@SpecialPowerModule@@IAEXPBVCoord3D@@@Z` → **CONFIRMED (exact)**
   - The same name with QAE or AAE access, or with PBU in place of PBV → CONTRADICTED
   - Siblings: `?createViewObject@SpecialPowerModule@@IAEXPBVCoord3D@@@Z` (0x00269130) is
     CONFIRMED. The ledger's PBU spelling of it is CONTRADICTED.
     `?aboutToDoSpecialPower@…@IAEXPBVCoord3D@@@Z` is already landed as PBV.
   - So EA declared `class Coord3D` in this unit. The function is protected
     `SpecialPowerModule::triggerSpecialPower(const Coord3D *)`. That agrees with the BFME 2
     donor's name and outline at 0x004941F3.
2. Callee ledger bindings the bank got wrong. The probe masks these, but the landing gate
   does not:
   - 0x0042DAA0 is `?bfmeIsBlocked@FXList@@QAE_NXZ` and is non-const. The bank calls `isEmpty() const`.
   - 0x00087A80 is `?getFinalOverride@Overridable@@QBEPBV1@XZ` and is const. The bank declares it non-const.
   - ILT 0x2852E → 0x001BE220 is pinned as `?dispatch@Rva001BE220Receiver@@QAEXHI@Z`
     (receiver+0x1DC tail forward of condition and duration). The bank uses `BfmeItemRY::bfmeDoRY`.
   - Globals by recorded name (dir32_addresses.csv): `?TheBfmeGameLogic@@3PAUGameLogic@@A`
     (0x012F0898), `?g_bfmeModeAZC@@3PAUBfmeModeAZC@@A` (0x012F0FE0) and
     `?ThePartitionManager@@3PAVPartitionManager@@A` (data row, matched). The bank uses
     `TheGameLogic` and `g_bfmeModeGF`.
3. Register-flow reading of +0x15c..+0x1a2: the kind chain uses CL for both byte tests and
   EAX for kind. The value (EDX), name (ECX), player (EDX, reloaded from the [esp+0x10]
   spill) and store (ECX) then follow plain eax/ecx/edx round-robin, skipping live EAX.
   Ours starts that block one step behind (ECX), which agrees with the session-5 phase
   analysis.

## Donor search (BFME 2 at f6c3838e7b58025531e09913bc42b810f1a01216, Zero Hour GeneralsMD)

- **Found a matched BFME 2 donor:** `Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModuleTrigger.cpp`.
  In BFME 2's `reverse/functions.csv` it is the row
  `?triggerSpecialPower@SpecialPowerModule@@QAEXPBUCoord3D@@@Z` at 0x004941F3, 926 B, matched.
  BFME 2's own flags are `/O1 /arch:SSE /EHs`. They are **not** imported, so BFME 1 keeps
  `/DNDEBUG /MD /EHsc`. Its structure is the same lineage:
  - aboutToDo, createViewObject and recharge
  - the controlling player's cost through a `__forceinline lightPointCost(t)` free accessor
  - model condition plus setDisabledUntil(frame + frames)
  - FX at the location or on the object
  - an `if (field2C) { if (field42) A(); else { kind 1/2/3; B(kind, &key, player, &name, …); } … return; }` block
  - hasMask, then `Object *obj`, then a nested block **from `Coord3D pos` to the end** (its
    recorded lever: "if/else pos copy plus nested block from pos on")
  - four filters in the same order, a range query, horde/self append, then the rva helper
  - BFME 2 extras that are absent in BFME 1: the shared-name recharge loop, the weather
    tail and the self-search loop.
  - Verdict: **applicable as a structural lead, not as inherited source**. The BFME 1 body
    already follows this outline. Two donor shapes are not in the bank's closed list and are
    queued as variants: the nested block from pos (H-B), and the forceinline cost accessor (H-E).
- Also reviewed: `docs/recipes.md` (nested-block slot lever, register-mirror and paren
  levers), the `reverse/attempt_support/` listing (no 0x004941F3 handoff) and BFME 2
  `SpecialPowerModule.cpp` / `SpecialPowerModuleDo.cpp` (markSpecialPowerTriggered is a -0x10
  adjustor tail into trigger, the same as BFME 1 Rva0026A190).
- Zero Hour `GeneralsMD/.../SpecialPowerModule.cpp` `triggerSpecialPower` contains only
  aboutToDo, createViewObject and startPowerRecharge. It supplies the name, not the body.

## Hypotheses (status)

| family | change | result |
|---|---|---|
| identity/ABI (d) | function decorated `IAEXPBVCoord3D` (triggerSpecialPower, protected) | ILT oracle CONFIRMED. Bytes expected identical: the bank recorded that a `const Coord3D *` parameter changes only the mangled name. Not probed. |
| callee decls (d) | bfmeIsBlocked non-const, getFinalOverride const, dispatch pin, recorded globals | applied in landing_ready.cpp. These are relocation-only changes. Not probed. |
| scoping (b) | H-B: nested block from `Coord3D pos` to end (BFME 2 lever), with and without the inner result block | variants/hB_*.cpp. NOT MEASURED (no compiler). It targets the +0x1eb Coord3D mirror. Note: the formB "whole tail in its own block" may overlap with it. |
| inline layering (d) | H-E: `__forceinline` free cost accessor like BFME 2 `lightPointCost`, with and without braces | variants/hE_*.cpp. NOT MEASURED. It targets one fewer temp before +0xc7. |
| inline layering (d) | H-G: getTemplate in the matched GrabPassenger sibling's native form (null-first, inline-recursive const getFinalOverride) | variants/hG_native_gettemplate.cpp. NOT MEASURED. |
| flags (e) | matched siblings: createViewObject `/DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS`, aboutToDo `/DNDEBUG /MD /EHsc` | `_STLP_NO_EXCEPTIONS` would be a new flag axis for this body. flag_sweep did not record it. NOT MEASURED. |

## Exact remaining mismatch (recorded on the formB base, 23 bytes)

```
+00c7  retail 8b 0d [TheGameLogic]  mov ecx,[..]   | ours mov edx,[..]
+00cd  retail 8b 41 3c              mov eax,[ecx+3c] | ours mov eax,[edx+3c]
+0181  retail 8b 96 e8 01 00 00     mov edx,[esi+1e8] ; push edx | ours ecx
+0188  retail 8b 54 24 14           mov edx,[esp+14] (player) | ours ecx, and the push lands before the store load
+01ea  retail 8b 45 00 / 8b 55 04   mov eax,[ebp] / mov edx,[ebp+4] | ours edx/eax mirrored through +0x215
```

## Best candidate

`build/wf/0x00269c50/landing_ready.cpp` is the formB const-ref body with these changes:
- the canonical `#include "Lib/Coord3D.h"`, preceded by `class Coord3D;` so the unit
  decorates PBV the way the ILT oracle requires
- ledger-bound callees
- recorded global names
- the ILT-confirmed decorated name

Its expected score is the bank's 23 non-relocation diffs. **Unverified.** Compiler context:
MSVC 7.1 (inputs/toolchains/vs2003), `// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include`,
`// stlport`, with `_STLP_USE_STATIC_LIB` / `BFME_STLP_NODE_ALLOC` defined in the source as
in the bank.

Caveats to verify first:
- (a) That MSVC 7.1 keeps the first-seen `class` key, giving PBV, despite the struct-keyed
  header (C4099). If not, the decorated name, aboutToDo and createViewObject become PBU.
- (b) That the class gate accepts the forward declaration without an allow.

## Landing notes

- **Name to land:** `?triggerSpecialPower@SpecialPowerModule@@IAEXPBVCoord3D@@@Z`.
  `python3 tools/ilt_oracle.py check <that> 0x00269C50` → `CONFIRMED p_false=3.91e-04 (exact)`.
  The bank's `?finishSpecialPower@SpecialPowerModule@@QAEXI@Z` → `CONTRADICTED`.
- **Consumers to reconcile in the same change.** They currently declare and call
  `finishSpecialPower(UnsignedInt)`, and symbols.csv pins it at ILT 0x000251AD:
  - `SpecialPowerModuleDoSpecialPower.cpp`
  - `SpecialPowerModuleDoSpecialPowerAtLocation.cpp`
  - `SpecialPowerModuleDoSpecialPowerAtObject.cpp`
  - `SpecialPowerModuleDoSpecialPowerUsingWaypoints.cpp`
  - `PlayerUpgradeSpecialPowerDoSpecialPower.cpp`
  - `GrabPassengerSpecialPowerDoSpecialPowerAtObject.cpp`

  All six are under `game/GameEngine/Source/GameLogic/Object/SpecialPower/`.
  `SpecialPowerModule.cpp` carries a `present-unmatched` marker for the PBU spelling.
- **Ledger name repairs needed for the callees** (writer: `ilt_repair.py`):
  - `?createViewObject@SpecialPowerModule@@IAEXPBUCoord3D@@@Z` → PBV (CONFIRMED).
  - The doFXPos row at 0x004280D0 is contradicted in both its PBU and PBV 4-argument
    spellings, the 5-argument ZH spelling is contradicted too, and doFXObj (0x00428180),
    bfmeIsBlocked (0x0042DAA0) and configure (0x0039B6D0) are also contradicted. Their true
    names are unresolved. Bind to the current ledger names or fix them first.
- **New pin needed:** the helper at ILT 0x0001F505 → 0x00269780 (gen dump `?d_00269780@@YAXXZ`).
  It is thiscall, takes one `BfmeWideResult *` and ends `ret 4`. Suggested address-derived
  name: `?rva00269780@SpecialPowerModule@@IAEXPAUBfmeWideResult@@@Z`. BFME 2's analogue is
  `rva0049402B`.
- **Helper/inline COMDATs the body emits or uses:**
  - inline friend_getFinalOverride overloads; the out-of-line calls go to
    `?friend_getFinalOverride@Overridable@@QAEPAV1@XZ` (0x97880) and
    `?getFinalOverride@Overridable@@QBEPBV1@XZ` (0x87a80)
  - inline filter ctors/dtors: `??_7Rva00265150RJFilter@@6B@`, `??_7PartitionFilterRelationship@@6B@`,
    `??_7Rva0025ED50RootFilter@@6B@`, `??_7Rva0025ED50ObjectFilter@@6B@`. All are recorded in
    dir32_addresses.csv. The filter dtors and BfmeWideResult::~ inline into the EH tail.
  - STLport `list<Object*>` ctor (0xCFFB0) and `_List_base` dtor (0xCEBD0)
  - `?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z`, `??3@YAXPAX@Z` and `__ftol2`
- **Float constants:** 0x01075350 (0.0f) is recorded as `g_bfmeDefaultBR`/`?g_bfmeDefaultBR@@3MA`,
  and 0x01075344 (5.0f) as `?g_bfmeK1266C@@3MB`. The bank uses the `__real` literals, which
  are proven to produce the matching `fmul`/`fcomp` order. Check how the relocation verifier
  resolves `__real@` symbols before changing them.
- **Home TU:** a new split unit,
  `game/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModule_triggerSpecialPower.cpp`.
  This follows the landed siblings `SpecialPowerModule_aboutToDoSpecialPower.cpp` and
  `SpecialPowerModule_createViewObject.cpp`. The current ledger row is a gen dump
  (`?d_00269c50@@YAXXZ`, `game/gen_asm/d_00266ef0.asm`), so land it with `--replace-rva 0x00269C50`.

## Files

- `bank_byvalue.cpp`: copy of the bank (ABI-wrong, reference only)
- `formB.cpp`: copy of the const-ref handoff
- `landing_ready.cpp`, `make_landing.py`: the best candidate and the script that generates it
- `variants/*.cpp`, `make_variants.py`: H-B, H-E and H-G, not measured
- `probe_all.sh`: runs every probe on a compiler-equipped host

## Measured 2026-11-14 (Wine 11, MSVC 7.1)

- **Bank forms.** `bank_byvalue.cpp` (bank name, by-value ABI) measures 16 diffs. `formB.cpp` (const-ref ABI) and `landing_ready.cpp` each measure 23 diffs, first at +0xC8.
- **Name decoration.** `ilt_oracle` CONFIRMS `?triggerSpecialPower@SpecialPowerModule@@IAEXPBVCoord3D@@@Z` (exact, p_false 3.9e-4). With the PBU spelling it CONTRADICTS.
  - `landing_ready.cpp` puts `class Coord3D;` before `#include "Lib/Coord3D.h"`. MSVC 7.1 still decorates the parameter as `PBUCoord3D` (the header's `struct` wins), so the file defines `...PBUCoord3D...`. Probing it under the PBV name reports NOT IN OBJECT.
  - Landing the confirmed name therefore needs a declaration in which Coord3D is a `class` at first sight, without redeclaring the canonical class. That is a class-gate question to settle first.
- **The +0xC7 phase is not local.** Retail does `mov ecx,[TheGameLogic]` where ours does `mov edx,...`. Five rewrites of the `setDisabledUntil(DISABLED_HELD, frame + delta)` call left the count unchanged at 23: operand order swapped, inline `getFrame()`, both of those together, a frame local, and an `Object*` local. The three ECX/EDX sites probably share an upstream cause.
- **Unmeasured variant.** `hG_native_gettemplate.cpp` regresses to 835 diffs (+0x02).
