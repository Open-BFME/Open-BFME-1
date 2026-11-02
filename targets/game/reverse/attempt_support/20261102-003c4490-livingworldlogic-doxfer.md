# 0x003C4490 LivingWorldLogic::DoXfer (542 B): bank at 20 diffs

Session a1/532, 2026-11-02. Bank: targets/game/reverse/attempts/0x003c4490.cpp
(compiles to 542/542 B, 18 relocations; every instruction through +0x1E9 matches).

## Identity (BFME 1 evidence)
- LivingWorldLogic Snapshot vtable 0x010EDBC8 (second table, installed at +0x08
  by the matched ctor 0x003C2FC0), slot 3 -> ILT 0x0000FDBC -> this body.
- `ilt_oracle.py check ?DoXfer@LivingWorldLogic@@UAEXAAVXfer@@@Z 0x3C4490`
  CONFIRMS; every ?xfer@...PAVXfer spelling is CONTRADICTED. The receiver is the
  Snapshot subobject (whole = this-8), so the bank declares the class with an
  8-byte primary base and a Snapshot base introducing DoXfer at slot 3.
- [BFME 2 donor] Open-BFME-2 45afcff3 LivingWorldLogic_xfer.cpp (0x002BC653)
  supplied the overall shape only. BFME 1 is version 3 and differs in detail;
  the bank is written from the retail listing.

## Callees and globals
transfer/load003C4160 (Transfer003C3D90 view on the whole object),
BfmeOneAQA::bfmeStopAQA on g_rva012F7048LivingWorld, Gen_003C0F70/Gen_003C1190
bfmeClear, BfmeThingEN::bfmeGoEN on TheGameLogic, slot-3 transfer through
TheLivingWorldCampaignManager+8 and TheLivingWorldManager+8, malloc/free.
0x003C0610 is ledgered as the free function postLoadGameFadeSteps(), but retail
loads ECX with the whole object first; a single-inheritance PMF union call
(Transfer003C3D90::*) reproduces that direct call.

## Remaining mismatch (+0x1CD..+0x21B, save tail)
Retail:  ver>=2: mode==8||mode==4 ? `xor eax,eax` : `mov eax,1`; jmp join
         ver<2:  `cmp [edx+0x10C],8; setne al`
         join:   `mov edx,[esi]; movzx ecx,al; ...; mov [esp+0x14],ecx; call [edx+0x78]`
The bank (`int state = ver>=2 ? intHelper(mode) : (int)(bool)(mode != 8)`) gets
the true arm exact but zero-extends inside the else arm (setne dl; movzx eax,dl).
Tried and worse or same: bool ternary/if-else with &&, ||, `? 0 : 1`; bool and
int helpers (if/return, switch, local flag), __forceinline helper taking the
version, GameLogic inline member, function-scope state shared with the load
branch (frame changes, 456 diffs). The join wants a byte value whose true arm
is materialised as 32-bit constants; not found yet.

## Update (same session): 16 diffs
`unsigned char active; if (ver >= 2) active = intHelper(mode); else active =
mode != 8; int state = active;` (intHelper: `if (mode == 8 || mode == 4) return 0;
return 1;`) reproduces retail's instruction shape exactly: 32-bit constants in
the true arm, setne al in the else arm, movzx at the join. Only the register
tie remains: retail loads TheGameLogic into EDX in the else arm and zero-extends
into ECX after loading the Xfer vtable into EDX; ours uses ECX / EDX / EAX.
Inert there: separate `int state; state = active;`, xferInt(&state),
operator== call spelling, Xfer* local, swapped if/else polarity (48 diffs),
initialise-then-override (532 B), GameLogic pointer local, (unsigned) cast;
bool/char join types and a function-scope shared state are worse.
