# 008CC940: return lifetime retry

Retail is 917 bytes: final RET 18h at +392 ends 008CCCD4, followed by
INT3. The EH handler operand at +3 routes to C5A167, whose FuncInfo
E491C4 has two states: -1/C5A150 and 0/C5A158. The native bank has
both predecessor states, with cleanup labels $L599 and $L600.
C5A158 is a complete 15-byte sized allocation cleanup: push16,
saved EBP+0C, call891A80, addESP8, RET C5A166 before the handler.
Ghidra raw bytes and retail PE decoding agree. Ghidra shows callers
from C93464/C935CC, CCD34A, CAD5E5 and others; no new owner name is
asserted by this retry. The bank retains its pre-existing experimental
six-argument thiscall view.

The corrected archive 14ea637319897332ae310d705edbee668cc0dec7db75e9b2fbc1c491ba46835d
reproduces 833 bytes /465 nonrelocation differences, quality0.3097.
The older preferred705-byte draft is not the starting point.

A concrete ordering difference is visible at retail +1EF and +2C7:
a successful lookup result is stored into escaped incoming argument1,
then the local string is destroyed, then argument1 is reloaded after
the free callback. An ordinary C++ return expression within that local
string's scope evaluates the result before destruction. This retry
exits the string scope to a common outer return label for those two
paths. This reproduces the after-destruction argument read and prevents
the previous wholesale return-tail merge; it is not a synthetic cleanup
or manual destructor call.

The new candidate is945 bytes /536 differences with37 relocations,
quality 1-(536+2*28)/917 =0.3544. Normalized instruction shape0.854 is
only diagnostic. The source still needs12 local bytes versus retail8,
and receiver/input/original-value register choices disagree. Scoped
frame-result and candidate reuse reproduce the same output. Reversed
aggregate fields yield539 differences; flat locals yield943/739;
early original-value declaration regresses to765/625 in the old form.
None is promoted to game/. Callee views and global bindings remain
experimental; a byte-and-reference gate is still required for landing.
