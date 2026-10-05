# WW3D::Movie at VA 0x0133F430

Corrected: one four-byte pointer definition, `?Movie@WW3D@@0PAVFrameGrabClass@@A`, owned by `game/Libraries/Source/WWVegas/WW3D2/ww3d.cpp`. The prior view spellings name the same storage, except the explicitly misplaced sort-list spelling at the movie address. No code identity or verified function extent changes.

The FrameGrabClass movie-capture pointer. Retail Stop_Movie_Capture at RVA 008FD370 checks the recording flag, deletes this object through vtable slot 0, and writes zero. Is_Movie_Ready checks this same pointer; Update_Movie_Capture calls FrameGrabClass::GetBuffer on it. Startup stores the result of a frame-grabber construction here. Zero Hour ww3d.cpp defines FrameGrabClass *WW3D::Movie. The competing default-sort-list spelling is misplaced: retail Init and Reset_Current_Static_Sort_Lists_To_Default use VA 0133F444 for the default sort list, not VA 0133F430. No game file currently declares the misplaced spelling. The old DIR32 row is preserved as instructed.

Retail section is `.data`; the four initial bytes are `00 00 00 00`, and no PE base relocation lies in those four bytes. The zero initial value is the null pointer, not a compiler constant. The narrow ledger scans find no data row overlapping this four-byte range and no DIR32 name strictly inside it. Other spellings exactly at its start are listed below. The owner already defines this private static member once. `tools/add_data_match.py` cannot size private static members (raw refusal: `build/rlink/identity-1791181569/add-data-0133F430.txt`), so this datum remains defined without a data row under the run's explicit private-static exception. Every retail access is a four-byte pointer load or store, and the reference declares the same pointer type. Existing canonical DIR32 spellings are kept without duplicate rows.

The receiver contract is the pointer loaded from this datum, passed unchanged as the member receiver or COM receiver; use-site casts retain the already witnessed partial layouts and member-call ABIs. The global has no arguments. Its readers and writers are independently listed from decoded retail memory operands, not from decompiler text.

Readers (RVAs): `0x008FD370`, `0x008FD3D0`, `0x008FD400`, `0x008FD6E0`, `0x008FDE90`, `0x008FDFD0`.

Direct writers (RVAs): `0x008FD370`, `0x008FD6E0`, `0x008FDE90`.

Raw bytes and access contexts: `build/rlink/identity-1791181569/0133F430-retail.txt`. Full containing bodies and every decoded E9 route are in `build/rlink/identity-1791181569/body-<RVA>.txt` and `build/rlink/identity-1791181569/thunks.json`; reader/writer measurements are in `build/rlink/identity-1791181569/accesses.json` and `contracts-summary.txt`. Reference declarations and behavior are recorded in `reference-globals.txt`, `reference-contract-excerpts.txt`, and `data-pointee-interfaces.txt`. Constructor routes are recorded in `constructor-routes-hex.txt`, `volumetric-ctor-retail-correct-target.txt`, and `helper-ctor-retail.txt`.

Source declaration counts before correction (literal pointer declarations, including the owning definition; generated historical spellings with no declaration count zero):

| Spelling | Game files declaring it |
|---|---:|
| `?Movie@WW3D@@0PAVFrameGrabClass@@A` | 3 |
| `?g_WW3D_DefaultStaticSortList@@3PAVDefaultStaticSortListClass@@A` | 0 |

The raw declaration probe is `build/rlink/identity-1791181569/declaration-counts.txt`; its output lists every counted path.

Refutation: A sort-list construction stored at VA 0133F430, or a frame-grabber writer targeting another address, would refute the correction. Any changed verified function byte also refuses the change. Byte gates, the data gate, CSV consistency, pin consistency, declaration coverage, and LINKED previews are recorded in `build/worker-final.md`.
