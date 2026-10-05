# ThePlayerList at VA 0x012ED748

Corrected and verified. The owning definition has a matched data row whose complete four bytes equal retail and whose target relocation count is zero. Every retained changed source passes its scoped function gate. Raw data-registration, source-gate and link results are recorded in `build/worker-final.md`.

The supported spelling is `?ThePlayerList@@3PAVPlayerList@@A`. This datum is one `PlayerList *` object in retail `.data`, with size 4 byte(s) and initial bytes `00000000`. It is mutable storage, not a compiler constant. It has no initialized pointer relocations: the scalar and shader bits are values, and the pointer and Dict cells start null. Retail has no PE base-relocation directory, so that absence alone is not relocation proof; the owning compiler object and the retail accesses provide the contract.

The reference Common/RTS/PlayerList.cpp defines PlayerList *ThePlayerList=NULL and PlayerList.h declares it. Retail users perform local-player and player-mask lookups through this loaded receiver. The PlayerList destructor at RVA 0x000DF9A0 clears this exact cell after destroying its player entries. The existing named ThePlayerList pin and the destructor lifetime agree with the reference. ThePlayers, address-derived globals and reference-to-manager spellings are competing views of one pointer, not separate identities. The existing source owner is PlayerList.cpp; partial user layouts remain local cast views.

The contract is one mutable cell. Code accesses this cell directly or, for pointer objects, loads its pointed-to receiver before a member dispatch. Scalars accept their shown arithmetic values; shader presets contain one unsigned ShaderBits word; pointer cells accept null or their owner instance. No array element count, terminator table, inheritance, alias identity or additional wrapper is inferred.

No data row or DIR32 name lies strictly inside `[0x012ED748, 0x012ED74C)`; the raw boundary audit is `build/rlink/identity-20261005-114922/retail-objects.log`. The chosen DIR32 spelling is already present beside the competing rows, so it is retained without inserting a duplicate or removing any pin. No functions.csv row is renamed or reordered.

The decoded retail bodies accessing this exact VA have RVAs `0x00079060`, `0x0008A2A0`, `0x0008A690`, `0x0008A720`, `0x0009A580`, `0x000A21F0`, `0x000A2230`, `0x000A2420`, `0x000A2620`, `0x000A5D40`, `0x000C7A30`, `0x000C7F80`, `0x000C8610`, `0x000C8730`, `0x000C96D0`, `0x000C97C0`, `0x000CBDC0`, `0x000CE170`, `0x000D5160`, `0x000D7680`, `0x000D77B0`, `0x000D7E30`, `0x000D8C60`, `0x000D9A80`, `0x000DF9A0`, `0x000DFCD0`, `0x000F4250`, `0x000F6D80`, `0x000F7FA0`, `0x000F8170`, `0x000FB610`, `0x001083D0`, `0x001086C0`, `0x001112D0`, `0x00144AB0`, `0x0014A110`, `0x0014A5A0`, `0x00163C70`, `0x00164130`, `0x001687B0`, `0x00168ED0`, `0x0016D5C0`, `0x001AA5B0`, `0x001B28C0`, `0x001BE570`, `0x001BE5B0`, `0x001BF060`, `0x001C6F10`, `0x001C9490`, `0x001CA6C0`, `0x001CA9C0`, `0x001CABE0`, `0x001CAF20`, `0x001CE530`, `0x001CEAD0`, `0x001CEFC0`, `0x001CF9F0`, `0x001D29A0`, `0x001DC910`, `0x001DD100`, `0x001DF4A0`, `0x001DF930`, `0x001EC8E0`, `0x001F0480`, `0x001FCA90`, `0x00203130`, `0x0020C3B0`, `0x00214F70`, `0x00217E60`, `0x00218320`, `0x0021A100`, `0x0021F9F0`, `0x0022AC00`, `0x002377A0`, `0x00237950`, `0x0023CEC0`, `0x00249140`, `0x0024BA90`, `0x0024ED40`, `0x002503B0`, `0x002505A0`, `0x0025A9D0`, `0x00267D80`, `0x00280EE0`, `0x002810B0`, `0x002861A0`, `0x0028EE30`, `0x0028F2A0`, `0x00290B90`, `0x00290E50`, `0x00299080`, `0x0029E330`, `0x002A1F80`, `0x002A32D0`, `0x002AB690`, `0x002AC5C0`, `0x002AC620`, `0x002AD380`, `0x002AD670`, `0x002B0D40`, `0x002BA240`, `0x002CF2C0`, `0x002ED8F0`, `0x002ED960`, `0x002EE100`, `0x002EE160`, `0x002EE230`, `0x002EE2D0`, `0x002EE330`, `0x002EE390`, `0x002EE3F0`, `0x002EE450`, `0x002EE4B0`, `0x002EE510`, `0x002EE570`, `0x002EE680`, `0x002EE950`, `0x002EEA70`, `0x002EEAF0`, `0x002EEB60`, `0x002EEBE0`, `0x002EEDA0`, `0x002EEE60`, `0x002EEF40`, `0x002EF110`, `0x002EF1C0`, `0x002EF410`, `0x002EF470`, `0x002EF8B0`, `0x002EF930`, `0x002EFC50`, `0x002EFF30`, `0x002EFFA0`, `0x002F0020`, `0x002F00C0`, `0x002F0140`, `0x002F01C0`, `0x002F0260`, `0x002F02C0`, `0x002F0320`, `0x002F0380`, `0x002F06E0`, `0x002F07A0`, `0x002F0BE0`, `0x002F0E50`, `0x002F0EF0`, `0x002F0F60`, `0x002F0FD0`, `0x002F1C10`, `0x002F1D80`, `0x002F1EC0`, `0x002F2000`, `0x002F3710`, `0x002F4360`, `0x002F44E0`, `0x002F48B0`, `0x002F5380`, `0x002F60A0`, `0x002F6550`, `0x002F65E0`, `0x002F66E0`, `0x002F6760`, `0x002F67E0`, `0x002F6920`, `0x002F69B0`, `0x002F7050`, `0x002F7670`, `0x002F7820`, `0x002F81F0`, `0x002F84C0`, `0x002F8540`, `0x002F85C0`, `0x002F8650`, `0x002F9A80`, `0x002FAF10`, `0x002FC800`, `0x002FCA30`, `0x002FCC90`, `0x002FCEA0`, `0x002FD010`, `0x002FD280`, `0x002FE7D0`, `0x003028B0`, `0x00303490`, `0x00322100`, `0x003221B0`, `0x00322530`, `0x00322630`, `0x00322780`, `0x00322810`, `0x00322880`, `0x003229B0`, `0x00322A60`, `0x00322B10`, `0x00322BC0`, `0x00322C70`, `0x00322D10`, `0x00322DA0`, `0x00322E10`, `0x00322E80`, `0x003230C0`, `0x003231E0`, `0x003232D0`, `0x00323550`, `0x00323650`, `0x00323710`, `0x00323780`, `0x003238C0`, `0x00323D50`, `0x00323E50`, `0x00324210`, `0x00324390`, `0x00324D40`, `0x003252A0`, `0x003254B0`, `0x00325700`, `0x003262C0`, `0x00326490`, `0x00326660`, `0x003269C0`, `0x00326C00`, `0x00326DA0`, `0x00326F40`, `0x00327260`, `0x003273A0`, `0x00327940`, `0x00327A00`, `0x00327D30`, `0x00328020`, `0x003283C0`, `0x00328470`, `0x00328590`, `0x00328680`, `0x003287E0`, `0x00328A80`, `0x00328CC0`, `0x00329160`, `0x00329230`, `0x00329400`, `0x003297F0`, `0x00329A80`, `0x00329C20`, `0x0032A550`, `0x0032A710`, `0x0032ABC0`, `0x0032B8D0`, `0x0032BC80`, `0x0032C090`, `0x0032C460`, `0x0032C680`, `0x0032C7F0`, `0x0032C990`, `0x0032CB00`, `0x0032CCC0`, `0x0032CFC0`, `0x0032D300`, `0x0033C290`, `0x00342E40`, `0x00345F80`, `0x0034B9A0`, `0x0034C430`, `0x0034CB60`, `0x0034DB40`, `0x0035F4E0`, `0x0035F920`, `0x00363E30`, `0x00365DF0`, `0x00367010`, `0x00367470`, `0x0036BD50`, `0x0036F4D0`, `0x00370730`, `0x00371650`, `0x003723A0`, `0x00373B30`, `0x00373ED0`, `0x00377060`, `0x00377550`, `0x00382E30`, `0x00382F50`, `0x00383150`, `0x00387A50`, `0x00388C10`, `0x0038C1E0`, `0x0038DA10`, `0x0038F7B0`, `0x003916F0`, `0x00391C40`, `0x00394260`, `0x00397540`, `0x0039B160`, `0x003C29D0`, `0x003C2BD0`, `0x00411CD0`, `0x00414BE0`, `0x00414E40`, `0x004182A0`, `0x00419E40`, `0x00419F00`, `0x0041B8B0`, `0x0041EBD0`, `0x004237E0`, `0x004280D0`, `0x00428180`, `0x00428880`, `0x004329D0`, `0x0043AAF0`, `0x0043DBE0`, `0x0043F2A0`, `0x0043F640`, `0x0043F950`, `0x004410C0`, `0x004422C0`, `0x004445C0`, `0x00445080`, `0x0044C250`, `0x0044C970`, `0x00458C80`, `0x00459200`, `0x00459640`, `0x0046F490`, `0x0049CAE0`, `0x0049CC00`, `0x0049D0B0`, `0x0049DC90`, `0x0049DD20`, `0x0049DF00`, `0x0049E240`, `0x004A07D0`, `0x004A2290`, `0x004A22F0`, `0x004A2500`, `0x004A2CB0`, `0x004A2F80`, `0x004A4240`, `0x004A5950`, `0x004A5E30`, `0x004A6E20`, `0x004A747F`, `0x004A8F10`, `0x004A9CD0`, `0x004AEE00`, `0x004AF3D0`, `0x004AF490`, `0x004AF6A0`, `0x004BFFE0`, `0x004C0560`, `0x004C1C30`, `0x004C3800`, `0x004E59E0`, `0x004E8050`, `0x004E8320`, `0x004E88E0`, `0x004EB2A0`, `0x004ED400`, `0x00511CC0`, `0x00513740`, `0x00513BF0`, `0x00514000`, `0x0052C220`, `0x005655C0`, `0x00575B70`, `0x005770E0`, `0x00589320`, `0x00589420`, `0x00589900`, `0x00589920`, `0x0058BB30`, `0x0058DDD0`, `0x00590480`, `0x005915E0`, `0x005917E0`, `0x00593310`, `0x00594AD0`, `0x00597130`, `0x00597A30`, `0x00598950`, `0x005999B0`, `0x005A75C0`, `0x005A9B50`, `0x005ADE90`, `0x005AFFB0`, `0x005B15A0`, `0x005B8520`, `0x006386F0`, `0x00639190`, `0x00667060`, `0x00675ED0`, `0x006827A0`, `0x00699F30`, `0x0069B220`, `0x006BD6E0`, `0x006C42B0`, `0x006C43F0`, `0x006C4A50`, `0x006DC0D0`, `0x006DF1F0`, `0x006DF420`, `0x006DF730`, `0x006F0300`, `0x006F9380`, `0x00702920`, `0x007143B0`, `0x00714810`, `0x00715340`, `0x00715530`, `0x007158F0`, `0x0071EEC0`, `0x00733580`, `0x00737B70`, `0x0073AED0`, `0x00745370`, `0x0075BE60`, `0x0076CB10`, `0x00795140`, `0x00799DC0`, `0x0079A2C0`, `0x0079A980`, `0x0079AEC0`, `0x0079B7D0`, `0x007ABAA0`. Each access and its bytes are recorded in `retail-objects.log`, with complete bodies and followed E9 chains in `retail-bodies.log`. `supplemental-xrefs.log` preserves packed-address occurrences beyond interrupted linear decodes; those windows are marked as windows, not new boundary or identity claims.

Before correction, the game files declaring each decorated spelling are:

| Spelling | Declaring game files |
|---|---:|
| `?PlayerList005999B0@@3PAUPlayers005999B0@@A` | 1 |
| `?Players00598950@@3PAVBfmeThingRV@@A` | 0 |
| `?Rva002EE330ThePlayers@@3PAUBfmePlayerList@@A` | 0 |
| `?Rva002EE330ThePlayers@@3PAURva002EE330PlayerList@@A` | 0 |
| `?Rva002EE330ThePlayers@@3PAVPlayerList@@A` | 1 |
| `?Rva002EE330ThePlayers@@3PAVRva000DF7F0@@A` | 0 |
| `?Rva002EE330ThePlayers@@3PAVRva002EE330PlayerList@@A` | 0 |
| `?Rva002EE330ThePlayers@@3RAVPlayerList@@A` | 0 |
| `?Rva004A2F80Players@@3PAVBfmeThingRV@@A` | 0 |
| `?TheBfmeGameOverGateA@@3PAVBfmeGameOverGateA@@A` | 0 |
| `?ThePlayerList@@3PAUBFMEPlayerList@@A` | 0 |
| `?ThePlayerList@@3PAUBfmePlayerList@@A` | 0 |
| `?ThePlayerList@@3PAUBfmePlayerList_AppendInsert@@A` | 0 |
| `?ThePlayerList@@3PAVPlayerList@@A` | 232 |
| `?ThePlayerList@@3PAVPlayerListView@@A` | 0 |
| `?ThePlayerList@@3PAVRva004ED400PlayerList@@A` | 0 |
| `?ThePlayerList@@3PAVThePlayerListType@@A` | 0 |
| `?ThePlayers@@3PAVPlayerList@@A` | 0 |
| `?g012ED748@@3PAURva0038DA10PlayerList@@A` | 1 |
| `?g_bfme938GlobA@@3PAVBfmeGlob938A@@A` | 0 |
| `?g_bfmeBEUA@@3PAVBfmeGlobBEUA@@A` | 0 |
| `?g_bfmeD1025@@3PAVBfmeD1025@@A` | 1 |
| `?g_bfmeD1087@@3PAVBfmeD1087@@A` | 0 |
| `?g_bfmeD1088@@3PAVBfmeD1088@@A` | 0 |
| `?g_bfmeD1089@@3PAVBfmeD1089@@A` | 0 |
| `?g_bfmeD1090@@3PAVBfmeD1090@@A` | 0 |
| `?g_bfmeD1091@@3PAVBfmeD1091@@A` | 0 |
| `?g_bfmeD1092@@3PAVBfmeD1092@@A` | 0 |
| `?g_bfmeD1093@@3PAVBfmeD1093@@A` | 0 |
| `?g_bfmeD1094@@3PAVBfmeD1094@@A` | 0 |
| `?g_bfmeD1095@@3PAVBfmeD1095A@@A` | 0 |
| `?g_bfmeD1096@@3PAVBfmeD1096@@A` | 0 |
| `?g_bfmeD1097@@3PAVBfmeD1097@@A` | 0 |
| `?g_bfmeD1098@@3PAVBfmeD1098@@A` | 0 |
| `?g_bfmeDSV@@3PAVBfmeGlobDSV@@A` | 0 |
| `?g_bfmeObjESCa@@3PAVBfmeGlobESC@@A` | 0 |
| `?g_bfmeObjESCb@@3PAVBfmeGlobESC@@A` | 0 |
| `?g_bfmePlayerList6DF1F0@@3PAUBfmePlayerList6DF1F0@@A` | 0 |
| `?g_bfmePlayersERH@@3PAVBfmePlayersERH@@A` | 0 |
| `?g_bfmePlayersERJ@@3PAVBfmePlayersERJ@@A` | 0 |
| `?g_bfmeRva9140GlobalA@@3PAVBfmeRva9140GlobalA@@A` | 0 |
| `?g_bfmeRvaBA90GlobalA@@3PAVBfmeRvaBA90GlobalA@@A` | 0 |
| `?g_mgr12ED748@@3PAVBfmeMgrD74@@A` | 0 |
| `?g_mgr12ED748@@3PAVBfmeMgrD74_Linked@@A` | 0 |
| `?g_mgr12ED748@@3PAVPlayerList@@A` | 0 |
| `?g_rva005655C0PlayerList@@3PAURva005655C0PlayerList@@A` | 0 |
| `?g_rva005655C0PlayerList@@3PAVBfmeD1025@@A` | 0 |
| `?g_rva005655C0PlayerList@@3PAVRva005655C0PlayerList@@A` | 0 |

The source paths behind those declaration counts are in `build/rlink/identity-20261005-114922/declaration-counts-before.log`; historical DIR32 spellings with no current declaration remain listed as zero. The counts do not decide identity. The reference declarations and the retail receiver, value and lifetime operations decide it.

The observation that would refute or settle this decision is: A PlayerList destructor clearing another singleton, a player-mask caller receiving a different object, or any differing byte in a changed function would refute the correction.

Raw evidence: `build/rlink/identity-20261005-114922/retail-objects.log`, `retail-bodies.log`, `supplemental-xrefs.log`, `shader-preset-run.log`, `inspect-candidates.log`, `reference-names.log`, and `reference-singleton-owners.log`. The unresolved private-size probe is in `private-size-probe.log`. Build and linking receipts, including any pre-existing blockers, are recorded in `build/worker-final.md`.
