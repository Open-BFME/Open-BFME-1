# TheW3DVolumetricShadowManager at VA 0x01306F18

Corrected: one four-byte pointer definition, `?TheW3DVolumetricShadowManager@@3PAVW3DVolumetricShadowManager@@A`, owned by `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp`. The prior view spellings name the same storage, except the explicitly misplaced sort-list spelling at the movie address. No code identity or verified function extent changes.

The volumetric-shadow manager owned by W3DShadowManager. Its constructor allocates 12 bytes, calls VA 00433104 (E9 17 84 78 00) to final VA 00BBB520, then stores EAX at VA 01306F18. The final constructor clears its list fields, creates the geometry manager, and stores a newly constructed buffer manager at VA 01306DE8. That matches the Zero Hour W3DVolumetricShadowManager constructor and the existing retail constructor row. Cleanup at RVA 007B7AF0 clears the same pointer. The candidate ReAcquireResources pinharvest name at 0000F9B6 concerns another route and does not establish this global identity.

Retail section is `.data`; the four initial bytes are `00 00 00 00`, and no PE base relocation lies in those four bytes. The zero initial value is the null pointer, not a compiler constant. The narrow ledger scans find no data row overlapping this four-byte range and no DIR32 name strictly inside it. Other spellings exactly at its start are listed below. `tools/add_data_match.py` proves the compiled pointer size and initial bytes before adding its row. Existing canonical DIR32 spellings are kept without duplicate rows.

The receiver contract is the pointer loaded from this datum, passed unchanged as the member receiver or COM receiver; use-site casts retain the already witnessed partial layouts and member-call ABIs. The global has no arguments. Its readers and writers are independently listed from decoded retail memory operands, not from decompiler text.

Readers (RVAs): `0x007110F0`, `0x007B73D0`, `0x007B7500`, `0x007B7580`, `0x007B75C0`, `0x007B7620`, `0x007B7680`, `0x007B76C0`, `0x007B77F0`, `0x007B7880`, `0x007B78C0`, `0x007B7AF0`, `0x007BAA90`, `0x007BF3C0`.

Direct writers (RVAs): `0x007B7900`, `0x007B7AF0`.

Raw bytes and access contexts: `build/rlink/identity-1791181569/01306F18-retail.txt`. Full containing bodies and every decoded E9 route are in `build/rlink/identity-1791181569/body-<RVA>.txt` and `build/rlink/identity-1791181569/thunks.json`; reader/writer measurements are in `build/rlink/identity-1791181569/accesses.json` and `contracts-summary.txt`. Reference declarations and behavior are recorded in `reference-globals.txt`, `reference-contract-excerpts.txt`, and `data-pointee-interfaces.txt`. Constructor routes are recorded in `constructor-routes-hex.txt`, `volumetric-ctor-retail-correct-target.txt`, and `helper-ctor-retail.txt`.

Source declaration counts before correction (literal pointer declarations, including the owning definition; generated historical spellings with no declaration count zero):

| Spelling | Game files declaring it |
|---|---:|
| `?TheAlpha@@3PAVGenAlpha@@A` | 1 |
| `?TheOpen27110F0Flusher@@3PAVOpen27110F0Flusher@@A` | 1 |
| `?TheW3DVolumetricShadowManager@@3PAVW3DVolumetricShadowManager@@A` | 2 |
| `?g_01306F18@@3PAVGen_01306F18@@A` | 2 |
| `?g_bfmeA1062@@3PAVBfmeA1062@@A` | 1 |
| `?g_rva007baa90@@3PAVRva007BAA90G@@A` | 1 |

The raw declaration probe is `build/rlink/identity-1791181569/declaration-counts.txt`; its output lists every counted path.

Refutation: A thunk at VA 00433104 targeting a different constructor, or an initialized object with incompatible list and geometry-manager fields, would refute the correction. Any changed verified function byte also refuses the change. Byte gates, the data gate, CSV consistency, pin consistency, declaration coverage, and LINKED previews are recorded in `build/worker-final.md`.
