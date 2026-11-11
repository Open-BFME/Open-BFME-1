# Repair: MilesAudioManagerConstructor dir32 ILT debts (6 lines + 1 unbaselined)

Date: 2026-11-11. File: `game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManagerConstructor.cpp`
(20 matched rows). Baseline lines (body_guard_baseline.csv): six
"name encodes X but retail reads Y" items plus one un-baselined
`??0Rva00478100 @ 0x422FA7` hard failure (pre-existing at HEAD).

## Status: blocked (record here; no tree change kept)

All seven slots are DIR32 arguments to compiler-generated `ehvec_ctor`
array-construction helpers (paired `push dtor / push ctor` at +0/+5, e.g.
`??1Rva006ABC60@0x132 + ??0Rva006ABC60@0x137`, `??1Rva00478100@0x282 +
??0Rva00478100@0x287`), verified by disassembling the built object.
Retail's slots hold ILT-thunk addresses because retail linked with
incremental linking; all seven thunks verified E9 in the image:

| slot (VA) | name in TU | thunk -> body (VA) |
|---|---|---|
| 0x4046F6 | ??1Rva006967A0 | -> 0x96870 = ??1PlayingAudioRef (35B row) |
| 0x431EDF | ??0Rva006967A0 | -> 0x967A0 (10B const-store ctor, unrowed) |
| 0x41E6F0 | ??1Rva0069CEE0 | -> 0x9CEF0 (clean) -> 0x887940 releaseBuffer |
| 0x423A1F | ??0Rva006ABC60 | -> 0xAACB90 (real ctor body, unrowed) |
| 0x43EF04 | ??1Rva006ABC60 | -> 0x6ABC60 (matched row, same name) |
| 0x43B2B9 | ??1Rva00478100 | -> 0x77FB0 (matched ??1 set<AsciiString> 5B row) |
| 0x422FA7 | ??0Rva00478100 | -> 0x78100 (pinned ??0 set + tg_ gen row) |

?j_ ILT rows exist for all seven thunks (matched, gen_small).

## What was tried

1. Plain `name,thunkRVA,pin` for all seven (following the accepted
   ??0Rva0069CEE0@0xEB65 precedent, commit 268f2f1). Scoped build went
   20/20 green with DIR32 OK and 0 baselined findings.
2. Pre-commit hook (`pin_consistency --delta`) refused three of them as
   `pin-on-other-identity`: the walked-to bodies already carry real
   identities (PlayingAudioRef dtor; set ctor/dtor). Four pins were
   accepted. Reverted all seven pins (an incomplete pin set leaves the TU
   red on the other three).
3. Renaming the placeholder classes to the true types (PlayingAudioRef,
   `_STL::set<AsciiString>`) breaks two `?dup_` EH-funclet rows: the
   complete STL type changes funclet codegen (inlined set-dtor unwind vs
   external call), mispairing funclet bodies. Reverted.

## Path forward (for the next attempt)

- The four accepted pins (??0Rva006967A0, ??1Rva0069CEE0, ??0Rva006ABC60,
  ??1Rva006ABC60 at thunks 0x31EDF/0x1E6F0/0x23A1F/0x3EF04) are safe and
  retire four baseline lines; they need the other three resolved first
  (the TU must build green as a whole).
- The three refused need the call sites to reference the TRUE names
  (??1PlayingAudioRef, ??0/??1 set<AsciiString>) AND resolve to the ILT.
  Per `load_symbol_map`, a matched name already maps to
  [auto-thunk, body] and the comparison picks whichever the target uses —
  so renaming may work with NO new pin if `build_call_thunks`
  auto-discovers these ILTs (verify by building after the rename).
  The funclet breakage from the complete set type is the hard part:
  likely needs the m_998 unwind funclets re-rowed, or the set used
  through an opaque wrapper that preserves the placeholder EH shape.
- Do NOT re-pin Rva names at these thunks; do NOT rename the class after
  the thunk address (ctor and dtor thunks differ, one name cannot encode
  both).
