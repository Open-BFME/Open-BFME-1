# AIStateMachine duplicate constructor: emission prerequisite

Control: d6bf2bfa317f0ed3aba2c29911f71dbd1dbbb6ca.
Queue #41, lease FC07153E; census 1d5131d3f1 (2026-10-30 12:21).
AIUpdateMakeStateMachine.cpp has 490 authored bytes and the census-only
preview rejects the selected AIStateMachine constructor as non-retail.
The current global preview is UNKNOWN: 22,731 other objects are unavailable.

The native constructor at 00185A20/4930 is owned and byte-verified in
AIStateMachineConstructor.cpp; its 61 registrations have independent target
proof. AIStates.cpp still defines Zero Hour's 41-state constructor under the
same strong symbol. That is not the native body. Before changing it, the
AIStates, native constructor and five factory methods pass all 173 rows,
67 strings, eight constants and 81 DIR32 references with zero body findings.

Removing only the obsolete constructor and its stale marker does not preserve
coverage: 36 rows lose their definitions, comprising 32 MagicEnum placement
delete functions, AIBusyState::onEnter/update and two constructor unwind
funclets (C06430, C06438). The native constructor object defines none of the
32 MagicEnum deletes or two Busy methods, so redirecting the constructor's
caller alone cannot supply them. The failed zero-context patch is banked as
[ai-state-constructor-delete-20261030.patch](ai-state-constructor-delete-20261030.patch).
It is diagnostic only; replay requires --unidiff-zero and all normal checks.

Restore the original source: all 173 rows and 81 references pass again.
No source, ledger, pin, header or flag change is retained. Do not suppress the
constructor with a dummy emission anchor, alias, added import or row deletion.
First give the disappearing native methods legitimate owning definitions and
prove the two cleanup states in the native parent. A coherent class/TU repair
is needed; no TU merge or new source home is approved by this investigation.

BFME 2 donor b5a7b8290a0c4c20b03a3664609d434904e228eb was inspected:
Code/GameEngine/Source/GameLogic/AI/AIStateMachineCtor.cpp owns a distinct
3805-byte constructor at 00351C48. It uses an unsigned name key and a 0x68-byte
layout, whereas BFME 1 passes AsciiString and allocates 0x70. Its separate
native-owner strategy is relevant; copying its body or ABI is inapplicable.
No source-recovery, linked-byte, census or runtime gain is claimed here.
