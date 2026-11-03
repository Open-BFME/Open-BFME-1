# 0x002F8A50 is ScriptActions::changeObjectPanelFlagForSingleObject, not ScriptAction::ParseActionFalseDataChunk

Retail body 0x002F8A50, 413 B, `ret 0xC` (three stack arguments, `this` in ECX).
The ledger row was the naked lift `?ParseActionFalseDataChunk@ScriptAction@@SA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z`
(ScriptAction_ParseActionFalseDataChunk_Thunk.cpp), a static three-argument parser that
cannot read ECX as an object pointer.

## Identity (BFME 1 target evidence)

- `tools/ilt_oracle.py check '?changeObjectPanelFlagForSingleObject@ScriptActions@@IAEXPAVObject@@ABVAsciiString@@_N@Z' 0x2F8A50`:
  CONFIRMED (exact). The same check for the ParseActionFalseDataChunk spelling is CONTRADICTED.
- The body recurses through ILT 0x0002DD85, pinned in symbols.csv to this decorated name.
- Callers: the matched doAffectObjectPanelFlagsUnit/Team handlers (ScriptActions).
- The seven tested strings are Scripts.cpp's TheObjectFlagsNames (VA 0x012B3E78:
  "Enabled" .. "Player Targetable"), the Zero Hour function's table.
- ea_evidence.csv places 0x002F8A50 in GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp (wb1-run).

## Donor (BFME 2, open-bfme-2 45afcff3)

Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doAffectObjectPanelFlagsTeam.cpp
carries the same function with an else-if chain and a `propagate` flag guarding the
contain walk. That control shape is carried from donor source; adopting it removed the
last 4-byte register swap (the Zero Hour return-per-branch shape put the two contain
vtable temps in eax/edx instead of retail's edx/eax). The BFME 1 views (contain +0x1FC,
body +0x200, AI +0x204, contain slots +0x68/+0x104) come from the retail body itself.

Verified: 413/413 B exact modulo relocations (tools/probe.py, add_match.py).
