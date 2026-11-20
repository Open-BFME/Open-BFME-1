# Native cleanup for GameInfoToAsciiString, RVA 0x00C3F560

The former blocker was the naked/misnamed parent at 0x00621600. The parent is
now readable, matched C++ in GameInfoParseOptions.cpp (843 bytes), so the
compiler emits its real exception state table and cleanup. No source body,
flag, helper declaration or ABI change is needed for this recovery.

Retail proves the relationship: the parent's handler operand at +3 names
0x00C3F5B1, whose FuncInfo is 0x00E2F048. The 11-entry unwind map at 0x00E2EFF0
binds state 0, predecessor -1, to action 0x00C3F560. The action ends at its
internal RET at +0x18, before the next action, giving exactly 25 bytes.
It conditionally destroys the guarded AsciiString return object.

Native eh_state_pins.tables/judge on the ordinary build object proves all
11 predecessor transitions and uniquely binds this action to $L9339:
verdict=proven, unique=true, ambiguous=false, twins=[]. The two existing
cleanup labels for the companion parser were renumbered independently; they
do not alter this parent's state-0 binding.

Native compile_function compares all 25 bytes without relocation masking or
unresolved symbols. Its only in-extent relocation, REL32 at +0x14, is the
existing AsciiString destructor symbol resolved to ILT 0x0000D828, forwarding
to 0x0005EE90. The same strict private control also verifies the 843-byte
formatter and 4834-byte companion parser. The ordinary pre-admission build
verifies all four existing rows, 38 literals, four empty strings and 59 DIR32
references under unchanged flags.

Land through add_match.py's compiler-label admission, then verify the ordinary
source and native EH-state checks. Keep the generated dump untouched. This is
25 additional bytes attributable to an existing readable C++ parent, not a
new main function or evidence of linking, crash or runtime improvement.

Reproduction and native-object proofs are retained in diagnostics/
continue-20261120-body-recovery-1656/agents/melee/:
C3F560-full-private-proof.json and C3F560-normal-object-proof.json.
