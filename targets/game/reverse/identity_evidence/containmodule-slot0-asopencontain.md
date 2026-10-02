# ContainModuleInterface slot 0: asOpenContain

All facts below are direct pefile/Capstone reads of the retail lotrbfme.exe
baseline, SHA-256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Addresses are RVAs unless marked VA.

## OpenContain introduces the shared slot

The registered OpenContain instance factory 00115960 calls ILT 00036E49 ->
constructor 002277A0. At 0022782B this constructor installs Contain interface
table VA 010AC038 at object +0x20; the same constructor's primary table
VA 010AC2B8 slot 2 is ILT 00022FCF -> getter 00226440 returning the registered
literal VA 01090BA4 `OpenContain`. Owner proof is independent of the proposed
method name. The full constructor inheritance census is also recorded in
`damagemodule-slots0-1-callbacks.md`.

Whole-image searches find ILT VA 00419533 exactly fourteen times, always once
in slot 0 of these constructor-installed contain tables:

| Owner | Constructor RVA | Contain table VA |
|---|---|---|
| AODHordeContain | 0x00230580 | 010AE520 |
| ContestableContain | 0x0021BEE0 | 010AB140 |
| GarrisonContain | 0x0021D820 | 010AB598 |
| HealContain | 0x00220190 | 010AB9F8 |
| HordeContain | 0x0023EAF0 | 010AF048 |
| HordeGarrisonContain | 0x00248F90 | 010AFB40 |
| HordeSiegeEngineContain | 0x0024A560 | 010B0028 |
| HordeTransportContain | 0x0024B6F0 | 010B0408 |
| HorseHordeContain | 0x0024D220 | 010B0AD0 |
| OpenContain | 0x002277A0 | 010AC038 |
| RiderChangeContain | 0x00229FB0 | 010AC870 |
| SiegeEngineContain | 0x0022BC50 | 010ACE08 |
| SlaughterHordeContain | 0x0024E7A0 | 010B0F40 |
| TransportContain | 0x0022D010 | 010AD268 |

The constructor routes all lead to OpenContain, which itself installs this
concrete slot after abstract ContainModuleInterface initialization. CaveContain
and TunnelContain have different slot-0 bodies and are excluded from this shared
claim. GeneralsMD OpenContain.h:122 defines the introducing public virtual
non-const `OpenContain *asOpenContain() { return this; }`; its base
ContainModuleInterface declares that method first. The derived classes listed
above inherit this one body, so it belongs to OpenContain alone.

## Direct BFME caller and exact ABI

Matched `ControlBar::doTransportInventoryUI` at 004A3E90 (401 bytes), in
ControlBarContextUI.cpp, loads the object's contain pointer from +0x1FC at
004A3EB4, then at **004A3EC6** calls `dword ptr [eax]`, slot 0. Its matched
source names that operation `contain->asOpenContain()` and uses the returned
OpenContain pointer (tested for null, then byte +0xB6 is inspected). This is a
direct BFME call anchoring the slot name independently of declaration order.

ILT 00019533 is E9 directly to 0021B830. That body is exactly
`8D 41 E0 C3`: `lea eax,[ecx-20h]; ret`, followed by INT3 at 0021B834.
ECX points to the contain subobject installed at +0x20, so this returns its
full OpenContain owner. The witnessed ZH declaration supplies return type,
non-const/public/virtual qualifiers and no arguments. The mangling is
`?asOpenContain@OpenContain@@UAEPAV1@XZ`.

Replace the four-byte const void-pointer placeholder
`?owner@Rva0021B830Part@@QBEPAXXZ` with the inline method emitted by
OpenContain.cpp. The prior container-of arithmetic was byte-correct, but
neither its return type nor constness established the method identity.

## TunnelContain's distinct override

TunnelContain's registered factory 00116530 calls ILT 00002450 -> constructor
0022EE70. That constructor first calls OpenContain's constructor through
00036E49, then at 0022EE98 replaces the contain table at +0x20 with
VA 010ADB38. Primary table VA 010ADDB8 (store 0022EE84) slot 2 is ILT
00033168 -> getter 0022EEF0, returning registered literal VA 01090A68,
`TunnelContain`.

Its contain slot 0 is ILT 0002B5C1 -> 0022EF20. Searching the complete mapped
image for this ILT VA yields exactly VA 010ADB38. The body is again exactly
8D 41 E0 C3, followed by INT3 at 0022EF24. Unlike the fourteen shared
OpenContain uses, TunnelContain explicitly supplies a distinct override:
GeneralsMD TunnelContain.h:92 declares public virtual non-const
`OpenContain *asOpenContain() { return this; }`. This exact ZH twin, the
registered derived constructor's replacement table, and the matched BFME
slot-0 caller above prove the method and ABI. The return type remains the
base OpenContain*, so the full mangling is
`?asOpenContain@TunnelContain@@UAEPAVOpenContain@@XZ`.
Replace `?method@Rva0022EF20PointerAdjust@@QBEPADXZ` at the same four-byte
extent and remove its obsolete pointer-adjustment placeholder.

TunnelContain.cpp under game/ contains only the scatter method and does not
emit the inline virtual. The verified provider is the **untouched** vendored
GeneralsMD `Code/GameEngine/Source/GameLogic/Object/Contain/TunnelContain.cpp`,
whose constructor emits it. That original source passes the exact four-byte
check; no custom declaration or emission workaround is used.
