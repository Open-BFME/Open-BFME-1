# WW3D::CurrentStaticSortLists at VA 0x0133F448

Corrected: one four-byte pointer definition, `?CurrentStaticSortLists@WW3D@@0PAVStaticSortListClass@@A`, owned by `game/Libraries/Source/WWVegas/WW3D2/ww3d.cpp`. The prior view spellings name the same storage, except the explicitly misplaced sort-list spelling at the movie address. No code identity or verified function extent changes.

The private static current-sort-list pointer. Retail Add_To_Static_Sort_List dispatches slot +4 with render object and level; Render_And_Clear_Static_Sort_Lists dispatches slot +8 with RenderInfoClass. Override stores its argument here, and Reset copies the default list pointer from VA 0133F444. Zero Hour declares this private static member with StaticSortListClass * and uses exactly those operations. The owner already defines the private spelling. The two partial WW3D declarations incorrectly exposed it as public, which changes its COFF name; these declarations now keep it private. The existing local flush helper is granted friendship solely to preserve its existing direct access.

Retail section is `.data`; the four initial bytes are `00 00 00 00`, and no PE base relocation lies in those four bytes. The zero initial value is the null pointer, not a compiler constant. The narrow ledger scans find no data row overlapping this four-byte range and no DIR32 name strictly inside it. Other spellings exactly at its start are listed below. The owner already defines this private static member once. `tools/add_data_match.py` cannot size private static members (raw refusal: `build/rlink/identity-1791181569/add-data-private-sort.txt`), so this datum remains defined without a data row under the run's explicit private-static exception. Every retail access is a four-byte pointer load or store, and the reference declares the same pointer type. Existing canonical DIR32 spellings are kept without duplicate rows.

The receiver contract is the pointer loaded from this datum, passed unchanged as the member receiver or COM receiver; use-site casts retain the already witnessed partial layouts and member-call ABIs. The global has no arguments. Its readers and writers are independently listed from decoded retail memory operands, not from decompiler text.

Readers (RVAs): `0x008FD4C0`, `0x008FD4E0`, `0x008FD840`, `0x008FE3C0`, `0x008FE730`.

Direct writers (RVAs): `0x008FD530`, `0x008FD540`, `0x008FD640`.

Raw bytes and access contexts: `build/rlink/identity-1791181569/0133F448-retail.txt`. Full containing bodies and every decoded E9 route are in `build/rlink/identity-1791181569/body-<RVA>.txt` and `build/rlink/identity-1791181569/thunks.json`; reader/writer measurements are in `build/rlink/identity-1791181569/accesses.json` and `contracts-summary.txt`. Reference declarations and behavior are recorded in `reference-globals.txt`, `reference-contract-excerpts.txt`, and `data-pointee-interfaces.txt`. Constructor routes are recorded in `constructor-routes-hex.txt`, `volumetric-ctor-retail-correct-target.txt`, and `helper-ctor-retail.txt`.

Source declaration counts before correction (literal pointer declarations, including the owning definition; generated historical spellings with no declaration count zero):

| Spelling | Game files declaring it |
|---|---:|
| `?CurrentStaticSortLists@WW3D@@0PAVStaticSortListClass@@A` | 2 |
| `?CurrentStaticSortLists@WW3D@@2PAVStaticSortListClass@@A` | 2 |

The raw declaration probe is `build/rlink/identity-1791181569/declaration-counts.txt`; its output lists every counted path.

Refutation: A header establishing this member as public in the reference, or a retail slot contract incompatible with StaticSortListClass, would refute the correction. Any changed verified function byte also refuses the change. Byte gates, the data gate, CSV consistency, pin consistency, declaration coverage, and LINKED previews are recorded in `build/worker-final.md`.
