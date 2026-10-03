# Four native member-array actions

All addresses in the table are RVAs. Each action is22 bytes, ending at its
own RET (action+15 hex), immediately before another action or its handler.
Ownership is established by parent prologue -> handler -> FuncInfo -> indexed
unwind-map entry, read from retail and cross-checked through Ghidra.

| Action | Parent | Handler | FuncInfo | Map | State -> previous | Count x stride | Offset |
|---|---|---|---|---|---|---|---|
| C46488 | 686CD0 | C4649E | E35F30 | E35F20 | 1 -> 0 | 8 x 104 | +58 |
| C48110 | 6ABC60 | C48134 | E37BA4 | E37B94 | 0 -> -1 | 6 x 12 | +4C |
| C4CCD6 | 71EA00 | C4CD0D | E3C8E4 | E3C8BC | 1 -> 0 | 2 x 8 | +34 |
| C4D948 | 73A230 | C4D95E | E3D4D0 | E3D4C0 | 1 -> 0 | 1 x 20 | +2C |

All load the receiver from EBP-10. Their existing callbacks route as follows:
29A69 -> 6858A0 (LANPlayer); 33A0A -> 69FC60 (Rva006ABC60VectorElement);
3EAB8 -> 5BD90 (Coord2D); 145BF -> 739F00 (Rva00739C70State). The shared
helper is CRT EH vector destructor iterator9F6D76. These are existing bindings,
not newly inferred semantic names or alias pins.

The unchanged native parent declarations already contain these arrays. In
particular the video-buffer state is an array of ONE element, and C4CCD6 is
a Coord2D member-array action rather than the Xfer callback old records called
it. No source or headers change. New cleanup entries remain opaque.

Each native action has14 concrete bytes plus its two relocations. The strict
per-source gate checks the parent and new row together; executable-COFF audits
confirm code-section flags, tracked sources and exactly one row per address.
Specific compiler labels and gate results are recorded through re_log.py.
