# TheW3DShadowHelperManager at VA 0x01307178

Corrected: one four-byte pointer definition, `?TheW3DShadowHelperManager@@3PAVW3DShadowHelperManager@@A`, owned by `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadow.cpp`. The prior view spellings name the same storage, except the explicitly misplaced sort-list spelling at the movie address. No code identity or verified function extent changes.

The second BFME shadow submanager. Retail W3DShadowManager constructor allocates 28 bytes and calls VA 00422764 (E9 67 E9 79 00), whose final target VA 00BC10D0 clears exactly seven dwords and returns the receiver. The existing pin names this constructor W3DShadowHelperManager. Cleanup calls its independently pinned destructor at RVA 007C19A0 and clears this pointer. Its users include the second-manager resource and shadow-task paths. W3DShadowHelperManager is the existing BFME stand-in name; the Zero Hour reference does not declare this extra helper. This correction unifies the proven object under its existing definition and does not claim that its original EA class name is recovered.

Retail section is `.data`; the four initial bytes are `00 00 00 00`, and no PE base relocation lies in those four bytes. The zero initial value is the null pointer, not a compiler constant. The narrow ledger scans find no data row overlapping this four-byte range and no DIR32 name strictly inside it. Other spellings exactly at its start are listed below. `tools/add_data_match.py` proves the compiled pointer size and initial bytes before adding its row. Existing canonical DIR32 spellings are kept without duplicate rows.

The receiver contract is the pointer loaded from this datum, passed unchanged as the member receiver or COM receiver; use-site casts retain the already witnessed partial layouts and member-call ABIs. The global has no arguments. Its readers and writers are independently listed from decoded retail memory operands, not from decompiler text.

Readers (RVAs): `0x007B7500`, `0x007B7580`, `0x007B75C0`, `0x007B7620`, `0x007B7680`, `0x007B76C0`, `0x007B7880`, `0x007B78C0`, `0x007B7AF0`, `0x007BFB90`, `0x007C2A00`, `0x007C2B50`.

Direct writers (RVAs): `0x007B7900`, `0x007B7AF0`.

Raw bytes and access contexts: `build/rlink/identity-1791181569/01307178-retail.txt`. Full containing bodies and every decoded E9 route are in `build/rlink/identity-1791181569/body-<RVA>.txt` and `build/rlink/identity-1791181569/thunks.json`; reader/writer measurements are in `build/rlink/identity-1791181569/accesses.json` and `contracts-summary.txt`. Reference declarations and behavior are recorded in `reference-globals.txt`, `reference-contract-excerpts.txt`, and `data-pointee-interfaces.txt`. Constructor routes are recorded in `constructor-routes-hex.txt`, `volumetric-ctor-retail-correct-target.txt`, and `helper-ctor-retail.txt`.

Source declaration counts before correction (literal pointer declarations, including the owning definition; generated historical spellings with no declaration count zero):

| Spelling | Game files declaring it |
|---|---:|
| `?Rva01307178@@3PAVRva007C2CD0Receiver@@A` | 1 |
| `?TheBeta@@3PAVGenBeta@@A` | 0 |
| `?TheW3DShadowHelperManager@@3PAVW3DShadowHelperManager@@A` | 6 |
| `?g_01307178@@3PAVGen_01307178@@A` | 0 |

The raw declaration probe is `build/rlink/identity-1791181569/declaration-counts.txt`; its output lists every counted path.

Refutation: A changed constructor route, a different allocation footprint, or a caller needing a distinct physical global instead of this same object would refute the unification. Any changed verified function byte also refuses the change. Byte gates, the data gate, CSV consistency, pin consistency, declaration coverage, and LINKED previews are recorded in `build/worker-final.md`.
