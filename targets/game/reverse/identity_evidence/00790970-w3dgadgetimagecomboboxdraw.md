# RVA 0x00790970 is W3DGadgetImageComboBoxDraw

Retail directly names this callback in the W3D draw FunctionLexicon table.
Facts were read from `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`
with pefile and Capstone, image base 0x00400000, and cross-checked with
GhidraMCP read_memory.

The table begins at VA 0x012BA454 and has a 12-byte stride: string pointer,
draw callback pointer, zero. Nearby rows are:

| Row VA | String VA and contents | Callback VA |
| --- | --- | --- |
| 0x012BA4C0 | 0x0111D604 `W3DGadgetListBoxImageDraw` | 0x0043BB15 |
| 0x012BA4CC | 0x0111D5E8 `W3DGadgetComboBoxDraw` | 0x0040C036 |
| **0x012BA4D8** | **0x0111D5C8 `W3DGadgetImageComboBoxDraw`** | **0x00446083** |
| 0x012BA4E4 | 0x0111D5A8 `W3DGadgetComboBoxImageDraw` | 0x00416C02 |

The callback at VA 0x00446083 is the five-byte E9 ILT stub at RVA 0x00046083.
Its bytes are `E9 E8 A8 74 00`, targeting VA 0x00B90970, i.e. this body.
The full function starts at RVA 0x00790970, and its final `ret` is at
0x00790AFC followed by INT3: 397 bytes. It takes two cdecl stack arguments,
in the same callback table role as its named siblings.

The body obtains GameWindow position and size, uses a selection RAII adapter,
finds a selected list-entry image, and draws through the window manager.
That agrees with the registered image-combo callback and rules out the
formerly proposed list-box callbacks. The exact literal in retail, rather
than a Zero Hour fuzzy twin or adjacency, proves the name.

The selection helper constructor and destructor at RVAs 0x004B5A50 and
0x004B5A70 still have unrelated address-era owners in the ledger. This
session records identity only; it does not guess that adapter's type or
change a pin, source body or progress row.
