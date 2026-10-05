# shadowIndexBufferD3D at VA 0x01306F20

Corrected: one four-byte pointer definition, `?shadowIndexBufferD3D@@3PAUIDirect3DIndexBuffer8@@A`, owned by `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp`. The prior view spellings name the same storage, except the explicitly misplaced sort-list spelling at the movie address. No code identity or verified function extent changes.

The dynamic shadow index buffer. Retail RVA 007B9810 passes VA 01306F20 as the output pointer to device vtable slot +6Ch; the create call specifies index format 65h. Release at 007B9760 invokes COM Release at +8 and clears the pointer. Shadow mesh renderers lock and unlock it, then pass it to SetIndices. The Zero Hour reference declares LPDIRECT3DINDEXBUFFER8 shadowIndexBufferD3D and uses it in the same operations. BFME uses the D3D9-shaped device contract; the repository retains the established IDirect3DIndexBuffer8 spelling and casts where its partial ABI views differ.

Retail section is `.data`; the four initial bytes are `00 00 00 00`, and no PE base relocation lies in those four bytes. The zero initial value is the null pointer, not a compiler constant. The narrow ledger scans find no data row overlapping this four-byte range and no DIR32 name strictly inside it. Other spellings exactly at its start are listed below. `tools/add_data_match.py` proves the compiled pointer size and initial bytes before adding its row. Existing canonical DIR32 spellings are kept without duplicate rows.

The receiver contract is the pointer loaded from this datum, passed unchanged as the member receiver or COM receiver; use-site casts retain the already witnessed partial layouts and member-call ABIs. The global has no arguments. Its readers and writers are independently listed from decoded retail memory operands, not from decompiler text.

Readers (RVAs): `0x007B9760`, `0x007BC270`, `0x007BC8B0`, `0x007BF7D0`.

Direct writers (RVAs): `0x007B9760`.

Raw bytes and access contexts: `build/rlink/identity-1791181569/01306F20-retail.txt`. Full containing bodies and every decoded E9 route are in `build/rlink/identity-1791181569/body-<RVA>.txt` and `build/rlink/identity-1791181569/thunks.json`; reader/writer measurements are in `build/rlink/identity-1791181569/accesses.json` and `contracts-summary.txt`. Reference declarations and behavior are recorded in `reference-globals.txt`, `reference-contract-excerpts.txt`, and `data-pointee-interfaces.txt`. Constructor routes are recorded in `constructor-routes-hex.txt`, `volumetric-ctor-retail-correct-target.txt`, and `helper-ctor-retail.txt`.

Source declaration counts before correction (literal pointer declarations, including the owning definition; generated historical spellings with no declaration count zero):

| Spelling | Game files declaring it |
|---|---:|
| `?TheBfmeComA@@3PAUBfmeComUnknown@@A` | 1 |
| `?shadowIndexBufferD3D@@3PAUIDirect3DIndexBuffer8@@A` | 3 |

The raw declaration probe is `build/rlink/identity-1791181569/declaration-counts.txt`; its output lists every counted path.

Refutation: A vertex-buffer create output at this address, or use of this pointer as the stream-source buffer, would refute the correction. Any changed verified function byte also refuses the change. Byte gates, the data gate, CSV consistency, pin consistency, declaration coverage, and LINKED previews are recorded in `build/worker-final.md`.
