# Replay option comparison literal

The PUSH operand at000908C7 (+0x47 in the95B body00090880) names
VA0107C76C. Local PE and Ghidra read_memory agree on79657300: "yes"
including its NUL. The source instead emitted7900: "y". This changes
which preference value the imported _strcmpi accepts; the old prefix-only
literal check hid it. The exact key remains "UseCameraInReplays".

Correct just the comparison literal. Keep the inherited address-qualified
owner and method, native string lifetime, lookup declarations and callee
pins. Complete RET at000908DE thenINT3 proves95B; independent entry flow
covers the no-preference and comparison paths. Full byte and reviewed
complete-literal/DIR32 checks are required, not only relocation masking.
