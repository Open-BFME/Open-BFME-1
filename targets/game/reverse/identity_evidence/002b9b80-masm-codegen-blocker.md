# 0x002B9B80 DozerAIUpdate::aiDoCommand -- MASM landing with a measured receiver-register blocker

Target: RVA 0x002B9B80..0x002B9CC9, 330 bytes, name
`?aiDoCommand@DozerAIUpdate@@UAEXPBUAICommandParms@@@Z` (real, non-placeholder).
Source: `game/masm_dumps/Rva002B9B80DozerAIDoCommand.asm`, derived from the
gen-dump row `?d_002b9b80@@YAXXZ` in `game/gen_asm/d_002afb20.asm`.

## Identity (proven, not guessed)

- ILT: `python3 tools/ilt_oracle.py check
  '?aiDoCommand@DozerAIUpdate@@UAEXPBUAICommandParms@@@Z' 0x002B9B80` ->
  CONFIRMED (exact; p_false=3.26e-04). The slot is ILT 8532: thunk VA
  0x0040B6A9 = RVA 0x0000B6A9, the row `?j_0000b6a9@@YAXXZ` in functions.csv
  whose notes carry `target=0x002B9B80`.
- Vtable: constructor 0x002B8680 installs vtable VA 0x010C69B4 (RVA
  0x00CC69B4); slot 0 at that RVA holds dword 0x0040B6A9, the ILT thunk above
  (byte-checked in the retail image at file offset 0xCC69B4; same finding in
  `re_attempts.log` line 55761 and in `002b9b80-resume-receiver-bank.md`).
- Twin: GeneralsMD `DozerAIUpdate.cpp:2343` names this method and calls
  `aiIdle(CMD_FROM_AI)` unqualified in both the repair and resume arms.

## Complete body and boundary

- `ret 4` ends the body at +0x147..+0x149 (`c2 04 00`); INT3 padding starts at
  +0x14A (RVA 0x002B9CCA). Frame: `push ebx / mov ebx,ecx`, no SEH frame. The
  next ledger body starts much later (0x002B9E50).

## Why this lands as a MASM dump (measured)

- The reconstructible C++ body (`targets/game/reverse/attempts/0x002b9b80.cpp`,
  bank score 0.997) compiles with `tools/probe.py` to exactly 330 bytes and
  7 relocations with shape 1.000 -- every instruction matches retail once
  registers and constants are normalised. The whole residue is ONE receiver
  byte at +0xF6:

      retail: 6a 02 / 8b cb / call ?j_00024d70   (mov ecx, ebx -> AICommandInterface)
      ours:   6a 02 / 8b cf / call ?j_00024d70   (mov ecx, edi -> complete object)

  The incoming ecx/ebx is the secondary AICommandInterface subobject
  (complete object minus 0x20); the bank's reinterpret_cast of the complete
  `this` passes edi, 0x20 bytes wrong. Retail passes the inherited receiver.
- Roughly 35 spellings were measured across the waves (re_attempts.log lines
  25171, 28253, 29656, 29758, 30084, 30234, 32892, 34155, 38147, 52259,
  53841, 55761, 55772, 56746, 60656, 61045 plus this session): explicit and
  implicit subobject conversion at either or both aiIdle sites, qualified
  `AICommandInterface::aiIdle`, `via AIUpdateInterface`, reference receivers,
  named command/guard/receiver locals, reinterpret/static/void* casts,
  `(char*)this+0x20`, member-pointer forms, case reorderings (n1/n2/n3),
  private-layout twin classes, declaration orders. Every one lands in one of
  three states, none byte-exact:
    * one byte wrong at +0xF6 (retail ebx, ours edi) -- the banked form;
    * one byte wrong at its mirror +0x12B when the conversion sits on the
      repair arm instead;
    * a complete allocator flip when both arms convert: 40 diffs from +0x1
      (edi becomes primary this, esi = this-0x20).
  No spelling makes both aiIdle receivers use the raw incoming ebx while
  keeping the rest of the schedule.
- `tools/probe.py` shape report: 1.000 with the residue classified
  "register/stack-slot ALLOCATION only"; the one differing byte alone decides.
- The dump body is byte-identical to retail outside its relocation slots; the
  only symbolic references are the 7 calls to five ILT thunks
  (0x2191d, 0x23033 x1, 0x24d70 x2, 0x3251f, 0x409b2 x2), all declared as
  EXTERN NEAR and resolved by existing functions.csv rows.

## Relocation sites

call ?j_0002191d (+0x1C, notifyModelConditionChanged), call ?j_00023033 (+0x41,
createMachines), call ?j_000409b2 (+0x8C and +0xD6, AIUpdateInterface::aiDoCommand),
call ?j_0003251f (+0xB6, isKindOf), call ?j_00024d70 (+0xF9 and +0x12E,
AICommandInterface::aiIdle). Offsets other than the calls carry no relocations.

## Why not inline asm

`docs/conversion_gate` blocks `__asm`/`__emit`/`__declspec(naked)` outside
`game/masm_dumps/*.asm`; the banked C++ is the best non-dump artifact and is
retained in this file's history for any future allocator work.

## Resolved (s548, 2026-11-03)

Landed as real C++ in game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdateAiDoCommand.cpp:
a port of the BFME 2 donor DozerAIUpdateCtor.cpp (open-bfme-2 45afcff3) compiled with
BFME 1's flags. The BFME 1 layout, vtable slots and callee spellings were read from this
body. The MASM dump is deleted.
