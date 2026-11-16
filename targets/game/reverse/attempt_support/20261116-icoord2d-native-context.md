# ICoord2D include refusal in ExamineCellsStruct::cellCallback

Baseline93073c1d21a7b8de5521f887b98192427404ba41; source
game/GameEngine/Source/GameLogic/AI/ExamineCellsStructCellCallback.cpp;
matched629B row at0x003E0DD0. Compiler MSVC13.10.3077, original TU flags
/DNDEBUG /MD. The only proposed source change replaces the one-line
struct ICoord2D { int x,y; }; with the registered data-only ICoord2D header.

Both private same-path wrapper controls compile with identical ordinary
runtime graphs and show the same8B two-int layout. This is insufficient:
the independent ordinary source build changes the final two register loads
from MOV EBP,[ESP+5C]; MOV EBX,[ESP+58] to the reverse instruction order.
The native row gate therefore fails despite unchanged629B extent.

The candidate was refused, the original source restored, and its normal
retail gate independently passed again. No ledger, callee, pin, identity,
extent or verifier repair is justified. Do not accept the private-wrapper
result without the ordinary compiler-context check or weaken byte equality.

Local retained evidence: diagnostics/continue-20261116-twohundred/batch-5/
014-native-before.log,014-native-after-initial.log,014-restored-native.log,
attempt-014.json and native-refusals.json. The minimal candidate source and
same-path control objects remain under
Open-BFME-1/build/codex-20261116-twohundred/batch-5/014-*.
The native diagnostic log preserves the complete expected/compiled bytes.

Observed: the include substitution changes ordinary-source code generation,
while the private wrapper does not distinguish the two variants. The precise
compiler cause is unproven. No additional source variations have been tried;
future work should investigate declaration/include context and register-load
scheduling with ordinary source builds. This source is not counted as a task.
