# TheW3DShadowManager at VA 0x01306EEC

Corrected: one four-byte pointer definition, `?TheW3DShadowManager@@3PAVW3DShadowManager@@A`, owned by `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadow.cpp`. The prior view spellings name the same storage, except the explicitly misplaced sort-list spelling at the movie address. No code identity or verified function extent changes.

The shadow-system singleton. Retail W3DTerrainVisual init at RVA 00730590 constructs and stores it; cleanup at 00731050 destroys and clears it. Readers use its shadow-color dword at +4, its scene flag, and its add/remove-shadow calls. The Zero Hour W3DShadow.cpp declares W3DShadowManager *TheW3DShadowManager, and the retail writers and named W3DDefaultDraw/W3DDebrisDraw callers have that contract.

Retail section is `.data`; the four initial bytes are `00 00 00 00`, and no PE base relocation lies in those four bytes. The zero initial value is the null pointer, not a compiler constant. The narrow ledger scans find no data row overlapping this four-byte range and no DIR32 name strictly inside it. Other spellings exactly at its start are listed below. `tools/add_data_match.py` proves the compiled pointer size and initial bytes before adding its row. Existing canonical DIR32 spellings are kept without duplicate rows.

The receiver contract is the pointer loaded from this datum, passed unchanged as the member receiver or COM receiver; use-site casts retain the already witnessed partial layouts and member-call ABIs. The global has no arguments. Its readers and writers are independently listed from decoded retail memory operands, not from decompiler text.

Readers (RVAs): `0x006C5FC0`, `0x006C6190`, `0x006E2540`, `0x006E6A80`, `0x006FBCB0`, `0x006FCE10`, `0x006FD4B0`, `0x006FD4E0`, `0x006FE140`, `0x006FEB10`, `0x006FF160`, `0x007110B0`, `0x007110F0`, `0x00711600`, `0x007143B0`, `0x00714810`, `0x007308F0`, `0x00730960`, `0x00731050`, `0x00747FF0`, `0x00748860`, `0x00750730`, `0x00750CC0`, `0x007510D0`, `0x007513C0`, `0x00755F70`, `0x007626F0`, `0x00778590`, `0x007B0250`, `0x007B73D0`, `0x007B9280`, `0x007BA590`, `0x007BBF80`, `0x007BC270`, `0x007BE000`, `0x007BFB90`, `0x007C1760`, `0x007C19F0`.

Direct writers (RVAs): `0x00730590`, `0x00731050`.

Raw bytes and access contexts: `build/rlink/identity-1791181569/01306EEC-retail.txt`. Full containing bodies and every decoded E9 route are in `build/rlink/identity-1791181569/body-<RVA>.txt` and `build/rlink/identity-1791181569/thunks.json`; reader/writer measurements are in `build/rlink/identity-1791181569/accesses.json` and `contracts-summary.txt`. Reference declarations and behavior are recorded in `reference-globals.txt`, `reference-contract-excerpts.txt`, and `data-pointee-interfaces.txt`. Constructor routes are recorded in `constructor-routes-hex.txt`, `volumetric-ctor-retail-correct-target.txt`, and `helper-ctor-retail.txt`.

Source declaration counts before correction (literal pointer declarations, including the owning definition; generated historical spellings with no declaration count zero):

| Spelling | Game files declaring it |
|---|---:|
| `?R2Ptr01306EEC@@3PAVGen0003AC38@@A` | 1 |
| `?ShadowManager01306EEC@@3PAUShadowData00747FF0@@A` | 1 |
| `?TheOpen27110B0Source@@3PAVOpen27110B0Source@@A` | 2 |
| `?TheOpen27110F0Sink@@3PAVOpen27110F0Sink@@A` | 1 |
| `?TheTacticalView@@3PAUTacticalViewLike@@A` | 0 |
| `?TheTacticalView@@3PAVTacticalViewLike@@A` | 0 |
| `?TheW3DShadowManager@@3PAVW3DShadowManager@@A` | 14 |
| `?g_bfmeGlobQE@@3PAVBfmeGlobQE@@A` | 2 |
| `?g_bfmeObjEMHa@@3PAVBfmeGlobEMHa@@A` | 1 |
| `?g_bfmeObjEMHb@@3PAVBfmeGlobEMHb@@A` | 1 |
| `?g_shadowManager@@3PAVGen0003AC38@@A` | 1 |

The raw declaration probe is `build/rlink/identity-1791181569/declaration-counts.txt`; its output lists every counted path.

Refutation: A writer constructing a tactical view, or a retail addShadow/removeShadow route to a different class, would refute the correction. Any changed verified function byte also refuses the change. Byte gates, the data gate, CSV consistency, pin consistency, declaration coverage, and LINKED previews are recorded in `build/worker-final.md`.
