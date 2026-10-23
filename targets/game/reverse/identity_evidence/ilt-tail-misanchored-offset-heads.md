# Misanchored `j_` rows that are the tail jmp of 11-byte offset/adjustor bodies

Thirty-nine generated `?j_XXXXXXXX@@YAXXZ` rows (game/gen_small/gthunks_084.cpp and
gthunks_085.cpp) each claim five bytes that are not an incremental-link thunk. Each is
the `jmp REL32` at +6 of an eleven-byte body:

    81 C1 imm32 / jmp REL32   add ecx,N  -> MemberOffsetTailThunks.cpp family (30 rows)
    81 E9 imm32 / jmp REL32   sub ecx,N  -> AdjustorThunks.cpp family (9 rows)

Boundary evidence, read from the retail image (inputs/baselines/bfme1/retail-1.03-unpacked):

- Start: every head is the target of exactly one ILT `E9` entry (column 3), and the
  byte before every head is one of ['cc'] (int3 padding or a ret).
- End: the byte after the eleven bytes is `cc` in every case.
- Interior: no `E8`/`E9` REL32 anywhere in .text reaches the tail address (column 5),
  so nothing ever entered at +6; the `j_` name was assigned by the thunk generator
  only because the five bytes decode as a lone `jmp`.

Landed (2026-10-23): the twenty-nine add-ecx heads, in MemberOffsetTailThunks.cpp. A head
whose jump target already carries a pinned `Gen` callee uses it; the rest are spelled through
the ILT entry the REL32 names (`BFME_OFFSET_TAIL_THUNK_ILT`), because their target bodies
already carry other ledger names and the pin gate refuses a second identity there.
Not landed: 0x000E9FD0 (its target 0x00019BCD is a body with two names, not an ILT entry)
and the nine sub-ecx adjustor heads, which can only be emitted by declaring the override,
and every override here is a real-named body (`??_G...` deleting destructors,
`WorkerAIUpdate::onDelete`, `W3DView::reset`).

Identity: the bodies take the address-derived names of their families
(`?invoke@RvaXXXXXXXX@@QAEXXZ`, `?handle@RvaXXXXXXXX@@W...@AEXXZ`); no semantic
identity is claimed. The jump target's body is pinned under the family's
address-derived callee/override name.

| head | bytes | ILT entry (E9 to head) | tail row retired | rel32 refs to tail | next byte |
|---|---|---|---|---|---|
| 0x000C3C40 | `81 c1 64 02 00 00 e9 9e 8c f7 ff` | 0x000206F3 | ?j_000c3c46@@YAXXZ @0x000C3C46 | 0 | cc |
| 0x000C8E70 | `81 c1 30 06 00 00 e9 4c cf f7 ff` | 0x000245A5 | ?j_000c8e76@@YAXXZ @0x000C8E76 | 0 | cc |
| 0x000C8E80 | `81 c1 30 06 00 00 e9 6d 6f f4 ff` | 0x00007211 | ?j_000c8e86@@YAXXZ @0x000C8E86 | 0 | cc |
| 0x000CFF30 | `81 c1 8c 00 00 00 e9 53 20 f6 ff` | 0x00044F8F | ?j_000cff36@@YAXXZ @0x000CFF36 | 0 | cc |
| 0x000E9FD0 | `81 c1 c8 00 00 00 e9 f2 fb f2 ff` | 0x0002849D | ?j_000e9fd6@@YAXXZ @0x000E9FD6 | 0 | cc |
| 0x000ED410 | `81 c1 70 02 00 00 e9 75 a8 79 00` | 0x000332D0 | ?j_000ed416@@YAXXZ @0x000ED416 | 0 | cc |
| 0x00132AD0 | `81 c1 c8 00 00 00 e9 f8 6c f1 ff` | 0x000150F0 | ?j_00132ad6@@YAXXZ @0x00132AD6 | 0 | cc |
| 0x0019BE40 | `81 c1 30 06 00 00 e9 3b 79 e8 ff` | 0x0004A02F | ?j_0019be46@@YAXXZ @0x0019BE46 | 0 | cc |
| 0x001AC3C0 | `81 c1 5c 05 00 00 e9 13 92 e9 ff` | 0x0001B48C | ?j_001ac3c6@@YAXXZ @0x001AC3C6 | 0 | cc |
| 0x001BD360 | `81 c1 70 01 00 00 e9 59 2a e7 ff` | 0x00048CED | ?j_001bd366@@YAXXZ @0x001BD366 | 0 | cc |
| 0x001BD640 | `81 c1 b8 02 00 00 e9 60 ea e7 ff` | 0x000053E4 | ?j_001bd646@@YAXXZ @0x001BD646 | 0 | cc |
| 0x001BD650 | `81 c1 b8 02 00 00 e9 11 92 e8 ff` | 0x0001748B | ?j_001bd656@@YAXXZ @0x001BD656 | 0 | cc |
| 0x001C0BB0 | `81 c1 84 00 00 00 e9 d5 70 6c 00` | 0x0000A8C6 | ?j_001c0bb6@@YAXXZ @0x001C0BB6 | 0 | cc |
| 0x001E0AC0 | `81 c1 64 02 00 00 e9 a9 b2 e3 ff` | 0x00041E1B | ?j_001e0ac6@@YAXXZ @0x001E0AC6 | 0 | cc |
| 0x002C9450 | `81 e9 40 03 00 00 e9 f5 d8 d5 ff` | 0x000134B7 | ?j_002c9456@@YAXXZ @0x002C9456 | 0 | cc |
| 0x002D9380 | `81 c1 d4 02 00 00 e9 b5 e5 5a 00` | 0x0001816A | ?j_002d9386@@YAXXZ @0x002D9386 | 0 | cc |
| 0x002D9390 | `81 c1 d8 02 00 00 e9 a5 e5 5a 00` | 0x000208D8 | ?j_002d9396@@YAXXZ @0x002D9396 | 0 | cc |
| 0x002ED3B0 | `81 c1 b8 02 00 00 e9 45 13 d2 ff` | 0x0003030A | ?j_002ed3b6@@YAXXZ @0x002ED3B6 | 0 | cc |
| 0x00360760 | `81 c1 84 06 00 00 e9 84 08 cc ff` | 0x0003BE71 | ?j_00360766@@YAXXZ @0x00360766 | 0 | cc |
| 0x0036B9C0 | `81 c1 00 01 00 00 e9 c5 c2 51 00` | 0x00020699 | ?j_0036b9c6@@YAXXZ @0x0036B9C6 | 0 | cc |
| 0x00383840 | `81 c1 70 01 00 00 e9 19 f6 c7 ff` | 0x00023173 | ?j_00383846@@YAXXZ @0x00383846 | 0 | cc |
| 0x00383900 | `81 c1 70 01 00 00 e9 90 8f c9 ff` | 0x0001ABC2 | ?j_00383906@@YAXXZ @0x00383906 | 0 | cc |
| 0x003C6FE0 | `81 c1 b8 00 00 00 e9 a5 0c 4c 00` | 0x00001889 | ?j_003c6fe6@@YAXXZ @0x003C6FE6 | 0 | cc |
| 0x003C6FF0 | `81 c1 b8 00 00 00 e9 45 09 4c 00` | 0x00031D8B | ?j_003c6ff6@@YAXXZ @0x003C6FF6 | 0 | cc |
| 0x00410680 | `81 c1 b8 02 00 00 e9 40 f6 c0 ff` | 0x000436D0 | ?j_00410686@@YAXXZ @0x00410686 | 0 | cc |
| 0x00466600 | `81 c1 4c 02 00 00 e9 85 16 42 00` | 0x00010028 | ?j_00466606@@YAXXZ @0x00466606 | 0 | cc |
| 0x0049CA20 | `81 c1 88 04 00 00 e9 69 08 ba ff` | 0x000417A9 | ?j_0049ca26@@YAXXZ @0x0049CA26 | 0 | cc |
| 0x004C1130 | `81 c1 88 04 00 00 e9 d8 55 b8 ff` | 0x0000731A | ?j_004c1136@@YAXXZ @0x004C1136 | 0 | cc |
| 0x0050DCA0 | `81 e9 18 02 00 00 e9 fa 28 b0 ff` | 0x00035323 | ?j_0050dca6@@YAXXZ @0x0050DCA6 | 0 | cc |
| 0x00519B90 | `81 e9 18 02 00 00 e9 15 cc b0 ff` | 0x0004809F | ?j_00519b96@@YAXXZ @0x00519B96 | 0 | cc |
| 0x0055CCD0 | `81 e9 18 02 00 00 e9 7a 5e ad ff` | 0x0001ED99 | ?j_0055ccd6@@YAXXZ @0x0055CCD6 | 0 | cc |
| 0x0060A870 | `81 c1 ac 00 00 00 e9 15 d4 27 00` | 0x00043874 | ?j_0060a876@@YAXXZ @0x0060A876 | 0 | cc |
| 0x006B0CA0 | `81 c1 b8 01 00 00 e9 1e a3 95 ff` | 0x0002B70B | ?j_006b0ca6@@YAXXZ @0x006B0CA6 | 0 | cc |
| 0x006D25D0 | `81 e9 cc 00 00 00 e9 54 5c 97 ff` | 0x00019948 | ?j_006d25d6@@YAXXZ @0x006D25D6 | 0 | cc |
| 0x00711ED0 | `81 e9 08 01 00 00 e9 d5 7a 91 ff` | 0x00013F75 | ?j_00711ed6@@YAXXZ @0x00711ED6 | 0 | cc |
| 0x00713500 | `81 e9 08 01 00 00 e9 f2 4b 8f ff` | 0x000206DF | ?j_00713506@@YAXXZ @0x00713506 | 0 | cc |
| 0x0071CD70 | `81 c1 50 14 00 00 e9 95 11 1f 00` | 0x00016A90 | ?j_0071cd76@@YAXXZ @0x0071CD76 | 0 | cc |
| 0x00746170 | `81 e9 fc 00 00 00 e9 16 b0 8f ff` | 0x00036D63 | ?j_00746176@@YAXXZ @0x00746176 | 0 | cc |
| 0x00746180 | `81 e9 fc 00 00 00 e9 ad e8 8c ff` | 0x0003F995 | ?j_00746186@@YAXXZ @0x00746186 | 0 | cc |


## Same defect, longer heads

The scan also found generated `j_` rows that are the final `jmp` of bodies longer than
eleven bytes. Each head is the target of one ILT `E9`, int3 surrounds the body, and no
REL32 reaches the retired tail address.

| head | size | tail row retired | shape |
|---|---|---|---|
| 0x00699BF0 | 12 | ?j_00699bf7@@YAXXZ @0x00699BF7 | `mov byte [0x012BA144],0 / jmp` (twin of matched 0x00699C00) |
| 0x00699C10 | 22 | ?j_00699c21@@YAXXZ @0x00699C21 | store arg to 0x012BA12C, arg slot = 0, jmp ILT 0x00047F3C |
| 0x00699C30 | 22 | ?j_00699c41@@YAXXZ @0x00699C41 | same, 0x012BA130, 1 |
| 0x00699C50 | 22 | ?j_00699c61@@YAXXZ @0x00699C61 | same, 0x012BA134, 2 |
| 0x00699C70 | 22 | ?j_00699c81@@YAXXZ @0x00699C81 | same, 0x012BA13C, 4 |
| 0x00699C90 | 22 | ?j_00699ca1@@YAXXZ @0x00699CA1 | same, 0x012BA138, 3 |
| 0x00505780 | 11 | ?j_00505786@@YAXXZ @0x00505786 | `mov ecx,[ecx+0x2AC] / jmp` ILT 0x00027F2A |
| 0x007AF700 | 11 | ?j_007af706@@YAXXZ @0x007AF706 | `mov ecx,[ecx+0x24C] / jmp` ILT 0x0001E344 |
| 0x0026E460 | 11 | ?j_0026e466@@YAXXZ @0x0026E466 | `fld [ecx+0x18C] / jmp __ftol2` |
| 0x0022F110 | 19 | ?j_0022f11e@@YAXXZ @0x0022F11E | owner at this-0x18, call ILT 0x00020824, `[eax+0x22C]`, jmp ILT 0x00027746 |
| 0x0022F2C0 | 19 | ?j_0022f2ce@@YAXXZ @0x0022F2CE | same, jmp ILT 0x000456E2 |

0x0026EDA0 (22 bytes, tail `?j_0026edb1`) has the same defect but is not landed: every
spelling tried loads the argument into EAX where retail uses EDX (3 bytes).
