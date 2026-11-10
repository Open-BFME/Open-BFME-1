# GiantBird guard constructor emission trials

BFME 1 base 8d7f327c32; MSVC 7.1, original TU flags `/DNDEBUG /MD /EHsc`, stringinline include. Queue rank 26, census 90c15cdeca. No production change retained.

The in-class `GiantBirdGuardReturnState(void*)` helper emits an incorrect standalone constructor while reproducing the machine constructor. Two isolated sequential trials in the new queue worktree:

- Adding `__forceinline` passes all five existing rows, strings, constants, DIR32 and body guards, but COFF still defines `??0GiantBirdGuardReturnState@@QAE@PAX@Z`. Census preview still reports COMDAT and selected-provider failures, 0 linked bytes. Forceinline alone does not suppress this provider.
- Adding `__declspec(dllimport) __forceinline` removes that COFF symbol (objdump symbol search has no result), but the scoped gate fails 4/5 rows: EH label numbering changes and the existing `$L680` funclet becomes ambiguous among `$L672`, `$L671`, `$L670`, `$L669`. The gate explicitly refuses to choose among four masked-equal bodies. No manual label rebinding attempted.

Donor reviewed read-only at 2bac16a657d32220670e4b9c7ec056986de61692: `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardMachine.cpp`. Its return-state constructor has a different StateMachine-pointer ABI and calls its normal-flight base, so it cannot supply this BFME 1 void-pointer helper directly. BFME 1 boundary/identity facts remain those in the existing ledger; this experiment establishes only compiler emission behavior.

Next prerequisite: independently identifiable cleanup bodies or an evidenced helper/provider reconciliation that preserves the existing funclet identities. Do not repeat forceinline-only suppression. Both edits reverted.
