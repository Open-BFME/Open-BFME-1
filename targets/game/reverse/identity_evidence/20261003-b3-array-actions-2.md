# Native 22-byte array cleanup actions, second batch

Each new entry is opaque; no parent source or callback binding changes.
Ownership follows the parent prologue -> handler -> FuncInfo -> unwind map.
All addresses in this table are RVAs; Ghidra read_memory independently
agrees with the unpacked retail bytes.

| Action | Parent | Handler | FuncInfo | Map | State -> previous | Array | Receiver |
|---|---|---|---|---|---|---|---|
| C07A60 | 19E640 | C07ABA | DF6284 | DF622C | 5 -> 4 | 32 x 24 | [EBP-14]+2C |
| C0C3E0 | 20ED10 | C0C401 | DFAE9C | DFAE8C | 0 -> -1 | 16 x 12 | EBP-CC |
| C106B8 | 27EF60 | C1070E | DFF9A0 | DFF968 | 1 -> 0 | 16 x 12 | [EBP-14]+74 |
| C13700 | 2BC7A0 | C13716 | E02D90 | E02D88 | 0 -> -1 | 10 x 12 | [EBP-10]+2C |

Each complete extent ends in RET at action+15 hex, followed immediately by
another action or its handler. The shared helper is the existing CRT EH
vector destructor iterator at 9F6D76. C07A60 pushes callback25590 -> 19AF30
(existing SidesInfo destructor); the other three push1364C -> 5BC40
(existing Coord3D destructor). Each emitted action has14 concrete bytes and
two independently checked relocation sites.

C106B8 retains the parent's existing AIUpdateArrayElement callback binding.
This does not establish a new semantic element identity. Likewise C13700
retains an existing source provider whose RunwayInfo owner spelling is not
independently re-proved here. Its exact compiler action is owned by parent
2BC7A0 regardless of that inherited spelling. No new semantic owner, alias,
pin or synthetic emitter is introduced.

C0B0B0 is separately blocked: parent1F96E0 -> C0B10B -> DF9A40/mapDF9A08
state0/-1 owns its16x12 local array at EBP-CC, but the979B parent remains a
dump and the full bank has concrete stack/register mismatches. Its RET at
1F9AB2 and INT3 from1F9AB3 were read independently; Ghidra's973-byte body
count is not its contiguous extent. The action itself ends RET C0B0C5.

Strict parent/action gates and executable-COFF audits cover the promotions.
Per-body emitted labels, results and blocked outcome are in re_attempts.log.
