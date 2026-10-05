# Unresolved datum ownership at VA 0x012B87AC

The integer interpretation is refuted, and the retail users establish a three-float position sentinel. No source or data-row correction is made because the proposed twelve-byte Coord3D extent contains the independent DIR32 names `?g_bfmeSecondEG@@3HA` at VA 0x012B87B0 and `?g_bfmeThirdEG@@3HA` at VA 0x012B87B4. This run forbids defining a datum with another DIR32 name strictly inside its range and requires retaining existing spellings beside the chosen spelling. The existing declarations and rows are left unchanged.

Retail `.data` at VA 0x012B87AC through exclusive VA 0x012B87B8 contains `ff ff 7f 7f ff ff 7f ff ff ff 7f 7f`. These are the IEEE binary32 words `0x7F7FFFFF`, `0xFF7FFFFF`, and `0x7F7FFFFF` (maximum finite positive, maximum finite negative, maximum finite positive). The image has no PE base-relocation directory; the stored bytes and typed reads provide the evidence, rather than an inferred relocation count. No data row overlaps this extent. The interior component DIR32 names prevent a single owner under the run's rule.

Constructor RVA 0x005A7460 copies the three dwords from these addresses into receiver offsets 0x10, 0x14, and 0x18. It receives its object in ECX and has no stack arguments. Its integer register moves preserve float representations and do not establish integer member types. The ILT entry at RVA 0x0000F164 contains `e9 f7 82 59 00` and jumps to RVA 0x005A7460. Verified callers load the destination address into ECX before calling that actual thunk; examples include RVAs 0x005B1F9F and 0x005B202B.

Retail helper RVA 0x005A8A10 receives the drawable in ESI and nine stack arguments. It reads the information pointer into ECX, tests it for null, then performs `fld dword ptr` at instruction RVAs 0x005A8B85, 0x005A8B97, and 0x005A8BA9. Each value is compared with the corresponding field at information offsets 0x10, 0x14, and 0x18 using `fucompp`. A difference marks a supplied position. This establishes binary32 components and a three-component position sentinel. The absolute-operand scan finds these two read-only users and no static writer; it does not exclude an undiscovered indirect writer.

| Existing decorated spelling | Game files declaring it |
|---|---:|
| `?g_bfmeFirstEG@@3HA` | 1 |
| `?g_va012B87AC@@3VCoord3D@@A` | 1 |
| `?g_bfmeSecondEG@@3HA` (interior at +4) | 1 |
| `?g_bfmeThirdEG@@3HA` (interior at +8) | 1 |

The integer declarations belong to `game/GameEngine/Source/Common/Bfme5SixtyNine.cpp`; the Coord3D declaration belongs to `game/GameEngine/Source/GameClient/MessageStream/CommandXlatVoice.cpp`. The existing Coord3D spelling fits the witnessed position role better than the integer spelling. Zero Hour's PickAndPlayInfo declaration and constructor lack this BFME position addition; the reference does not supply a real global identifier or a membership declaration for the sentinel. No new name, inheritance, or alias is inferred.

A verified membership declaration or retail initialization/consumer that establishes whether these are one Coord3D object or three independent float objects would settle source ownership. A single-object correction also needs a policy-compatible disposition of the interior DIR32 names. An integer arithmetic consumer, incompatible extent, or different instruction route would refute the position-sentinel interpretation. A constructor register move alone cannot refute it.

Raw initial bytes, section, interior DIR32 rows, complete user disassembly and the five-byte ILT route are in `build/rlink/retail-probe-v3.log`. Validated operand accesses and actual caller instructions are in `build/rlink/focused-retail.log`. Declaring source lines are in `build/rlink/coordinate-users.txt`; the Zero Hour constructor and reference search are in `reference-constructor.txt`, `reference-position-search.txt`, and `reference-pick-contract.txt` under that folder. The unchanged sources were included in `build/rlink/link-before.log`: neither linked, each reported LINKED 0 to 0 bytes. No candidate for this address was built or added to the data ledger.
