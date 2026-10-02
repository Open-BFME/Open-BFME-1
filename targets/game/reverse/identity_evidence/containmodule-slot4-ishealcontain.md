# ContainModuleInterface slot 4: isHealContain

All observations are direct pefile/Capstone reads of retail lotrbfme.exe,
SHA-256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Addresses are RVAs unless marked VA.

## Direct BFME call, rather than a guessed ZH slot shift

Matched InGameUI::canSelectedObjectsDoAction at 00447A40 (976 bytes), in
InGameUICanSelectedObjectsDoAction.cpp, loads the target's contain pointer
from +0x1FC at 00447B2F. At **00447B3F** it calls `dword ptr [edx+10h]`,
slot 4, then tests AL. Its matched source and ZH InGameUI.cpp twin identify
this condition as `contain->isHealContain()`. This directly fixes the BFME
slot: ZH's complete interface order differs, so no global slot shift is assumed.

## Independent owners and inherited uses

The complete sixteen-constructor census and base-call chains are in
`damagemodule-slots0-1-callbacks.md`. The OpenContain, GarrisonContain and
TunnelContain registered factory routes, +0x20 contain tables and primary
literal getters are independently detailed in `containmodule-slot0-asopencontain.md`
and `containmodule-slot2-isgarrisonable.md`.

HealContain's registered factory 00115B40 calls ILT 00019899 at 00115B7E ->
constructor 00220190. That constructor calls OpenContain at 0022019F,
then installs primary VA 010ABC78 at 002201A4 and contain VA 010AB9F8 at
+0x20 at 002201B8. Primary slot 2 is ILT 0003E171 -> getter 00220220,
returning literal VA 01090B10 `HealContain`. This independently names the
owner of the single true-returning override.

| Owner | Contain table VA | Slot-4 body RVA |
|---|---|---|
| AODHordeContain | 010AE520 | 00226450 |
| ContestableContain | 010AB140 | 0021B870 |
| GarrisonContain | 010AB598 | 0021B870 |
| HealContain | 010AB9F8 | 00220230 |
| HordeContain | 010AF048 | 00226450 |
| HordeGarrisonContain | 010AFB40 | 0021B870 |
| HordeSiegeEngineContain | 010B0028 | 00226450 |
| HordeTransportContain | 010B0408 | 00226450 |
| HorseHordeContain | 010B0AD0 | 00226450 |
| OpenContain | 010AC038 | 00226450 |
| RiderChangeContain | 010AC870 | 00226450 |
| SiegeEngineContain | 010ACE08 | 00226450 |
| SlaughterHordeContain | 010B0F40 | 0021B870 |
| TransportContain | 010AD268 | 00226450 |
| TunnelContain | 010ADB38 | 0022EF40 |

Whole-image little-endian ILT-VA searches yield exactly 9 uses of 0044A7C8,
4 of 004260CB, 1 of 00442145 and 1 of 00417369, each once in slot 4 of
the corresponding tables above. CaveContain has a distinct override and is
not claimed here. Constructor chains identify OpenContain as the introducer
of the nine-use default, GarrisonContain as the introducer of the four-use
override, and HealContain/TunnelContain as explicit single-table overrides.

## Explicit class twins and ABI

GeneralsMD OpenContain.h:204, GarrisonContain.h:117, HealContain.h:68 and
TunnelContain.h:95 each define a public const virtual `Bool isHealContain() const`.
They return false, false, true and false respectively, precisely as retail:

| Introducing owner | ILT RVA | Body RVA | Complete bytes |
|---|---|---|---|
| OpenContain | 0004A7C8 | 00226450 | 32 C0 C3 |
| GarrisonContain | 000260CB | 0021B870 | 32 C0 C3 |
| HealContain | 00042145 | 00220230 | B0 01 C3 |
| TunnelContain | 00017369 | 0022EF40 | 32 C0 C3 |

Each ILT is an E9 directly to the listed body, and each three-byte body is
immediately followed by INT3. The bool return is in AL, with no stack
arguments; the explicit const/public/virtual declaration gives UBE_NXZ in
all four decorated names. No field names or layouts are invented.
Use existing OpenContain.cpp/GarrisonContain.cpp and the untouched full
vendored HealContain.cpp/TunnelContain.cpp to emit these inline methods.
Remove the four retired address-only definitions after separate byte checks.
