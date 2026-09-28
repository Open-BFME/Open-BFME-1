# Client update at RVA 0x004329D0

1632 bytes, retail VA 0x008329D0 through 0x00833030 (exclusive).
The original row was `?d_004329d0@@YAXXZ` in `game/gen_asm/d_0042c460.asm`.
The replacement is `?update@ClientUpdate004329D0@@QAEXXZ` in
`game/GameEngine/Source/GameClient/ClientUpdate004329D0.cpp`.

## Identity and structure

The Zero Hour `GeneralsMD/Code/GameEngine/Source/GameClient/GameClient.cpp`
`GameClient::update` (line 513 onward) supplies the order of the input updates,
freeze checks, drawable iteration, shroud handling, and display updates.
BFME adds four startup timed operations, the client-debug freeze check,
additional subsystems, and resolution/shell recreation. These additions were
reconstructed from GhidraSQL `pseudocode` for VA 0x008329D0 and the complete
retail disassembly. No semantic owner was forced: the replacement retains the
RVA in its class name. There is only one replacement ledger row.

`Dispatch004329D0` is explicitly a vtable-slot ABI view, not a claim that all
subsystems share a class. Named callees use already-established ledger names;
unknown callee declarations keep their body addresses. The Shell allocation
is 0x70 bytes, and its constructor and push symbols are the established ones.
The LoadGameFade slot/wrapper/holder model is the exact existing model from
`PostLoadGameFadeSteps.cpp`; vtable 0x010EDB7C was independently checked with
`vtable_lookup.py`. Callback values remain the four retail ILT VAs.

`name_oracle.py --class GameClient --offset 0xc` returned only a ZH hint,
not a BFME witness; offset 0xc5 was unwitnessed. The source therefore keeps
address/offset-qualified storage views rather than declaring a guessed real
GameClient layout. The drawable, player, and logic accessors describe reads
witnessed in this body (+FC/+104/+134, +C/+24, and +3C respectively).

## Call dependency repairs

`callees.py 0x004329D0 1632` was run before writing the body. Each new body
pin below was checked against the separately decoded callee, not inferred
from a desired compiler displacement. The caller loads ECX and passes no
stack arguments at the four zero-argument sites. The callee evidence is
ECX read before write and unqualified RET exits:

| Pin body RVA | Call ILT RVA | Independent callee evidence |
|---|---|---|
| 005B5590 | 0000B7A3 | 1791 bytes; saves ECX in ESI; RET at 005B5C8E |
| 005B4D40 | 0003EC48 | 902 bytes; saves ECX in ESI; RET at 005B506F and 005B50C5 |
| 0041BE60 | 00031C55 | 2437 bytes; ECX read; RET at 0041C263, 0041C6D7, 0041C7E4 |
| 0040DE00 | 0004ADB3 | 502 bytes; saves ECX in ESI; four zero-cleanup RET exits |
| 0042F190 | 0000C676 | Existing matched forEach body; ECX receiver; two stack words; RET 8 at 0042F1CA |

For 0042F190 the second stack word is a boolean whose low byte the callee
uses. The address-qualified scalar call view matches the two retail pushes;
the existing by-value functor reconstruction and its ledger identity are not
renamed or replaced. Passing a locally constructed byte-bearing aggregate
instead introduced an extra stack temporary and did not match this caller.

The sixth pin is a route for the existing private
`HeaderTemplateManager::populateGameFonts` symbol. Its full chain was decoded:
00020243 -> 0048CA80 -> 000065F0 -> 0048C480. The last is the established
85-byte matched font population body. The pin carries `route=0x0048C480`;
`pin_consistency.py --check` independently accepted the route.

No generated source or callee body was modified. The new pins name body RVAs,
letting the existing resolver derive ILT choices, except for the explicitly
validated multi-hop font route.

## What moved the match

The whole body was written before the first probe: 1642 bytes and 0.946
normalized instruction shape. Explicit client offsets and correct evaluation
order for the timer loop brought it to 0.974. Mechanical EH and source-family
searches found no improvement. Inlining the two script-debug checks through
one receiver and using native-style value getters for drawable, logic, and
object reads produced shape 1.000 at 1633 bytes. The player-list
`getLocal()->getIndex()` accessor sequence fixed the final scratch-register
rotation and recovered exactly 1632 bytes. A rotation sweep was run before
that final accessor change; no artificial identity-copy helper is retained.

## Verification

- `probe.py ... --shape`: EXACT modulo relocation slots, 1632/1632 bytes.
- `add_match.py ... --replace-rva 0x004329D0 --model gpt-6-astra`: verified OK.
- Scoped `build.cmd game/GameEngine/Source/GameClient/ClientUpdate004329D0.cpp`:
  Functions OK 1/1; string-ref OK (MainMenu.apt); DIR32 OK (71 references).
- `pin_consistency.py --check`: 0 new or stale violations; all 194 route rows
  accepted, including this route; guarded CRT imports and DIR32 pins OK.
- The address tokens on every new `g_XXXXXXXX` reference were independently
  compared with retail DIR32 operands, rather than relying on first-use
  consistency alone.

VCS and claim ownership are left to the operator. `BFME_CLAIMS=off` was used
for add_match so it did not alter shared claim refs. Final check_csv reports
only that the new source exists but is not yet Git-tracked; the operator must
stage it together with the functions/symbols ledgers and this evidence file.
No full gate or game launch was run.
