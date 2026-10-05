# TheVideoPlayer at VA 0x0130B190

Corrected: one four-byte pointer definition, `?TheVideoPlayer@@3PAVVideoPlayerInterface@@A`, owned by `game/GameEngine/Source/GameClient/VideoPlayer.cpp`. The prior view spellings name the same storage, except the explicitly misplaced sort-list spelling at the movie address. No code identity or verified function extent changes.

The video-player subsystem interface singleton. GameClient init stores the result of the virtual video-player factory in this dword; GameClient cleanup and VideoPlayer destructor clear it. Retail readers dispatch update/reset/open and subtitle-management virtual methods through it. The Zero Hour VideoPlayer.cpp defines VideoPlayerInterface *TheVideoPlayer, and its header declares the open and subsystem contracts. Existing VideoPlayer and MovieFactory views describe the same physical object, so their declarations use the interface pointer and their former views remain use-site casts.

Retail section is `.data`; the four initial bytes are `00 00 00 00`, and no PE base relocation lies in those four bytes. The zero initial value is the null pointer, not a compiler constant. The narrow ledger scans find no data row overlapping this four-byte range and no DIR32 name strictly inside it. Other spellings exactly at its start are listed below. `tools/add_data_match.py` proves the compiled pointer size and initial bytes before adding its row. Existing canonical DIR32 spellings are kept without duplicate rows.

The receiver contract is the pointer loaded from this datum, passed unchanged as the member receiver or COM receiver; use-site casts retain the already witnessed partial layouts and member-call ABIs. The global has no arguments. Its readers and writers are independently listed from decoded retail memory operands, not from decompiler text.

Readers (RVAs): `0x000C3480`, `0x001109CF`, `0x0040E3B0`, `0x0042F5A0`, `0x00431380`, `0x00431900`, `0x004329D0`, `0x00441AF0`, `0x00494FA0`, `0x004991D0`, `0x004E2D50`, `0x0051D1E0`, `0x0069AB70`, `0x006A9910`, `0x0081C590`, `0x0081D600`, `0x0081D7C0`, `0x0081DE40`.

Direct writers (RVAs): `0x0042F5A0`, `0x00431380`, `0x0081C590`.

Raw bytes and access contexts: `build/rlink/identity-1791181569/0130B190-retail.txt`. Full containing bodies and every decoded E9 route are in `build/rlink/identity-1791181569/body-<RVA>.txt` and `build/rlink/identity-1791181569/thunks.json`; reader/writer measurements are in `build/rlink/identity-1791181569/accesses.json` and `contracts-summary.txt`. Reference declarations and behavior are recorded in `reference-globals.txt`, `reference-contract-excerpts.txt`, and `data-pointee-interfaces.txt`. Constructor routes are recorded in `constructor-routes-hex.txt`, `volumetric-ctor-retail-correct-target.txt`, and `helper-ctor-retail.txt`.

Source declaration counts before correction (literal pointer declarations, including the owning definition; generated historical spellings with no declaration count zero):

| Spelling | Game files declaring it |
|---|---:|
| `?MovieFactoryGlobal0040E3B0@@3PAUMovieFactory0040E3B0@@A` | 2 |
| `?TheVideoPlayer@@3PAVVideoPlayer@@A` | 3 |
| `?TheVideoPlayer@@3PAVVideoPlayerInterface@@A` | 8 |

The raw declaration probe is `build/rlink/identity-1791181569/declaration-counts.txt`; its output lists every counted path.

Refutation: A writer returning a separate movie factory object instead of the video player, or an open/subtitle vtable contract belonging to another singleton, would refute the correction. Any changed verified function byte also refuses the change. Byte gates, the data gate, CSV consistency, pin consistency, declaration coverage, and LINKED previews are recorded in `build/worker-final.md`.
