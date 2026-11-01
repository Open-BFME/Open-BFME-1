# Guard lookup: removing the wrong body has three ledger dependencies

Queue rank 69, claim 0xFF7E6B02. The queued consumer is the existing
293-byte AIGuardInnerState::update at 0x0015E180. Its call to
AIGuardMachine::lookForInnerTarget resolves through pin ILT 0x000317A5
to the still-generated 2514-byte body at 0x0015D530.

## New experiment and result

Hypothesis: remove the unmatched Zero Hour lookForInnerTarget definition
from AIGuard.cpp while retaining its AIGuard.h declaration. The source uses
a filter-pointer array, independently known to differ from BFME's linked
filter chain. This is a linking-emitter repair attempt, not another body
reconstruction or a reason to replace either existing bank.

Exact reversible transformation: delete from the comment
`// ?lookForInnerTarget@AIGuardMachine@@ present-unmatched` through the
function's closing brace immediately before the CRC section. Retain every
other function and include. No flags, names, pins or rows were changed.

Normal joint scoped build of AIGuard.cpp and AIGuardInnerStateUpdate.cpp
then failed precisely these three existing rows because their object symbols
were no longer emitted:

- ?dup_00801180@@YAXXZ, object-symbol setNemesisID@AIGuardMachine.
- ?setNemesisID@AIGuardMachine@@QAEXW4ObjectID@@@Z.
- ?getFrameObjectsChangedTriggerAreas@GameLogic@@QAEIXZ.

The other 15 of 18 rows, including the queued caller, survived. Thus removing
the bad lookup body alone would strand matched helper rows. A future repair
must establish valid natural provider objects for these exact helper copies
(and reconcile the aliases) before deleting the body. Do not retain synthetic
calls merely to force emission. No retained C++ edit or new byte recovery.
The experiment was reverted; the existing reconstruction banks are untouched.
The restored joint scoped build passes 18/18 rows and 13 DIR32 references.

Before preview: old e9a5ae5b4c census reports LINKED0->0, selected wrong
lookForInnerTarget plus three unrelated helper COMDAT conflicts. The current
census is incomplete in this worktree, so no linked-byte increase is claimed.

## Donor and context

Reviewed /home/yannick/projects/Open-BFME-2 at
2e97f871794a7b0cc6463976dd3b6fc3c1d780f8,
Code/GameEngine/Source/GameLogic/AI/AIGuard.cpp:777 onward and the
AIGuardStates.cpp callers. BFME 2 has a recovered 929-byte lookup, a different
search helper, position fallback and fields; that source is semantic context,
not a drop-in replacement for BFME 1's 2514-byte body. Its comments identify
WorldBuilder evidence and Zero Hour provenance. BFME 1's existing attempt log
already establishes the incompatible filter walk and stack-layout residue.
This experiment adds the concrete three-row emission prerequisite instead of
repeating those failed reconstructions. Compiler: MSVC7.1/3077, existing
/O2 defaults, /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc, existing ZH/shim includes.
