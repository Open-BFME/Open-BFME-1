# Local-game quit: engine-input call binding

Control: d6bf2bfa317f0ed3aba2c29911f71dbd1dbbb6ca.
Caller: GameLogic::_bfme_quitLocalGame, RVA 003839E0, 221 retail bytes
(220 authored bytes plus padding). Its direct call through ILT 00045A1B
lands on 0043B260, the existing 20-byte
BfmeInGameUI_setInputEnabled::setEngineInputEnabled(bool) owner.
The native setter passes the engine flag at +0x0D to vslot +0x120 and
returns with RET 4. The neighboring script-input setter at 0043B280 uses
+0x0E and is a different function.

Replace only the caller's declaration-only _bfme_setEngineInputEnabled
spelling with the existing owner and an unchanged-pointer receiver view.
TheInGameUI retains its original global type and its +0x12BE field access.
No function, class or field is renamed; no pin, alias, header or row changes.

Normal build of caller and provider: all three functions byte-exact,
nine DIR32 references checked and zero body-guard findings. COFF comparison
keeps all 221 caller bytes exactly (SHA256
7913ca32fcb213ec0ca3c1d250c8f541eb59db1a516805f545b11511c8a1c54a);
only the REL32 reference at +153 changes its callee spelling. Every other
relocation is identical. Defined-function preflight passes.

Paired census-only prediction against 1d5131d3f1, measured 2026-10-30 12:21:
caller 0 -> 220 linked bytes; provider 40 -> 40; cohort 40 -> 260.
This is a prediction against fixed census definitions, not a new census or
runtime proof. The current whole-ledger preview cannot be established here:
22,731 other objects are unavailable. Confirmation is left to the next census.

BFME 2 donor b5a7b8290a0c4c20b03a3664609d434904e228eb was consulted at
Code/GameEngine/Source/GameLogic/System/GameLogicSetGamePaused.cpp:
it declares and calls InGameUI::setEngineInputEnabled(bool) in the
corresponding pause/input-restoration role. That supports the role only.
BFME 1's own target and existing provider establish the exact callee,
calling convention and flag offset; no donor layout or function body is copied.
The existing placeholder owner name is retained pending its naming lane.
