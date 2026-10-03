# Four native 22-byte member-array actions

Each entry keeps an opaque RVA identity. No source, header, alias or pin is
changed. Parent ownership comes from the retail prologue's handler immediate,
its FuncInfo and the indexed unwind-map entry, not neighboring function order.
Ghidra read_memory cross-checks the bytes against the unpacked retail image.
All table addresses below are RVAs (image base 00400000).

| Action | Parent | Handler | FuncInfo | Unwind map | State -> previous |
|---|---|---|---|---|---|
| BF8F36 | C0EA0 | BF8F68 | DE6800 | DE67D8 | 2 -> 1 |
| BFCF33 | 107FE0 | BFCF49 | DEA52C | DEA514 | 2 -> 1 |
| C037DC | 13C3F0 | C03876 | DF1E00 | DF1DA0 | 4 -> 3 |
| C04091 | 147600 | C0420B | DF26C4 | DF258C | 12 -> 11 |

Every action loads the saved receiver from EBP-10 and calls the existing
CRT EH vector destructor iterator at RVA 9F6D76. Each has 14 concrete bytes
plus a DIR32 callback and REL32 helper relocation. The native parents already
model the following member lifetimes:

| Action | Count x stride | Member offset | Callback route | Final RET |
|---|---|---|---|---|
| BF8F36 | 8 x 12 | +3C | 1364C -> 5BC40, Coord3D destructor | BF8F4B |
| BFCF33 | 64 x 80 | +28 | 25D15 -> 1075F0, RadarEvent destructor | BFCF48 |
| C037DC | 4 x 4 | +4C | D828 -> 5EE90, AsciiString destructor | C037F1 |
| C04091 | 5 x 4 | +38 | D828 -> 5EE90, AsciiString destructor | C040A6 |

The byte immediately after each RET begins another action or the handler;
none of these ranges includes INT3 padding. The source declarations and
callback bindings predate these promotions. Their inherited owner/member
spellings are not new identity claims made by this work.

The strict per-source gate verifies each parent and proposed action, including
relocation targets. The pre-commit audit checks one row per address, tracked
native sources, selected compiler labels, nonrelocation equality and executable
COFF section flags. Per-action emitted labels and gate results are recorded
with re_log.py; masked equality alone is not the promotion criterion.
