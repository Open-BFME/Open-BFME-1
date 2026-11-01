# 0x00329FB0 ScriptConditions team "attacked by unreachable attacker" (491 B) - session 520

Bank: targets/game/reverse/attempts/0x00329fb0.cpp (symbol
?rva00329FB0@ScriptConditions@@IAE_NPAVParameter@@_N@Z; intended home
game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsRva00329FB0.cpp).

Source of the shape: Open BFME 2 45afcff3 ScriptConditions::rva003EA228
(Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions_evaluateTeamStateIs.cpp),
the same address-named team form there. BFME 1 deltas taken from the body: AI slot 96,
body slots 15/16, damage window constant 25, dead byte +0x344, position +0x38,
filter vptr 0x010956C4 (recorded only as ?g_010956C4@@3PAPBXA), base PartitionFilter
dtor (0x00149E90) is the only unwind action, so the base must not be novtable.

Result: 498/491 B. Everything matches structurally; the only real difference is a
3-byte `lea ecx,[ecx]` loop-head alignment pad at +0x6D that retail lacks; the
remaining 4 bytes are jcc rel8 -> rel32 growth caused by that shift.
Levers that were needed: named `Int id = info->m_sourceID` before findObjectByID
(receiver load after the id), and two separate `matched = true; continue;` arms
(retail duplicates the store) with one shared `if (flag) return true`.
Inert on the pad: for / while / goto / do-while loop forms (all 498 B).
Open: what suppresses VC7.1's loop alignment here (retail neighbours with the same
DLINK PMF iterator, e.g. ScriptConditionsTeamAttackedByType.cpp 0x00327790, are the
place to compare: check whether its retail loop head is padded).
