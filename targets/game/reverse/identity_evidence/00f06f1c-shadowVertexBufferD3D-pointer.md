# shadowVertexBufferD3D at VA 0x01306F1C

Corrected: one four-byte pointer definition, `?shadowVertexBufferD3D@@3PAUIDirect3DVertexBuffer8@@A`, owned by `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp`. The prior view spellings name the same storage, except the explicitly misplaced sort-list spelling at the movie address. No code identity or verified function extent changes.

The dynamic shadow vertex buffer. Retail RVA 007B9810 passes VA 01306F1C as the output pointer to device vtable slot +68h; slot +6Ch receives the index-buffer output. Release at 007B9760 calls the COM Release slot +8 and zeros this dword. Shadow mesh renderers lock and unlock the buffer, then pass it to SetStreamSource. The Zero Hour reference declares LPDIRECT3DVERTEXBUFFER8 shadowVertexBufferD3D and uses it in the same operations. BFME uses the D3D9-shaped device contract, while the established repository interface spelling remains IDirect3DVertexBuffer8. The use-site casts preserve that witnessed BFME ABI.

Retail section is `.data`; the four initial bytes are `00 00 00 00`, and no PE base relocation lies in those four bytes. The zero initial value is the null pointer, not a compiler constant. The narrow ledger scans find no data row overlapping this four-byte range and no DIR32 name strictly inside it. Other spellings exactly at its start are listed below. `tools/add_data_match.py` proves the compiled pointer size and initial bytes before adding its row. Existing canonical DIR32 spellings are kept without duplicate rows.

The receiver contract is the pointer loaded from this datum, passed unchanged as the member receiver or COM receiver; use-site casts retain the already witnessed partial layouts and member-call ABIs. The global has no arguments. Its readers and writers are independently listed from decoded retail memory operands, not from decompiler text.

Readers (RVAs): `0x007B9760`, `0x007B9810`, `0x007BC270`, `0x007BC8B0`, `0x007BF7D0`.

Direct writers (RVAs): `0x007B9760`.

Raw bytes and access contexts: `build/rlink/identity-1791181569/01306F1C-retail.txt`. Full containing bodies and every decoded E9 route are in `build/rlink/identity-1791181569/body-<RVA>.txt` and `build/rlink/identity-1791181569/thunks.json`; reader/writer measurements are in `build/rlink/identity-1791181569/accesses.json` and `contracts-summary.txt`. Reference declarations and behavior are recorded in `reference-globals.txt`, `reference-contract-excerpts.txt`, and `data-pointee-interfaces.txt`. Constructor routes are recorded in `constructor-routes-hex.txt`, `volumetric-ctor-retail-correct-target.txt`, and `helper-ctor-retail.txt`.

Source declaration counts before correction (literal pointer declarations, including the owning definition; generated historical spellings with no declaration count zero):

| Spelling | Game files declaring it |
|---|---:|
| `?TheBfmeComB@@3PAUBfmeComUnknown@@A` | 1 |
| `?shadowVertexBufferD3D@@3PAUIDirect3DVertexBuffer8@@A` | 3 |

The raw declaration probe is `build/rlink/identity-1791181569/declaration-counts.txt`; its output lists every counted path.

Refutation: An output produced by CreateIndexBuffer, or a renderer using this address for SetIndices rather than SetStreamSource, would refute the correction. Any changed verified function byte also refuses the change. Byte gates, the data gate, CSV consistency, pin consistency, declaration coverage, and LINKED previews are recorded in `build/worker-final.md`.
