# Upgrade pool claim has a different retail owner

The matched row at RVA 0x00121FA0 (104 bytes) names
`?getClassMemoryPool@Upgrade@@CAPAVMemoryPool@@XZ`, compiled from
Player.cpp via the canonical Common/Upgrade.h pool machinery. Its source
literal is `Upgrade` plus NUL.

Retail operand +0x31 points to VA 0x0108AD58, containing the full C string
`UpgradeSoundSelectorClientBehavior` plus NUL. Local PE and independent
Ghidra read_memory agree. The reviewed complete-string verifier from
7bfaf884e4 reports the mismatch; the earlier prefix comparison did not.

The complete retail body reads initialization flag VA 0x012EF1C0 and pool
pointer VA 0x012EF1BC, calls ILT RVA 0x0003ADD7 (target 0x0008FFC0),
and has returns at 0x00121FF4 and 0x00122007. INT3 padding follows at
0x00122008. Thus the 104-byte extent is complete; this is a literal/owner
binding failure, not a truncated body. symbols.csv has no pin for the
claimed Upgrade pool name. Fetched origin/master still has the same row.

A dependent 14-byte unwind row at 0x00C01240 names this parent and selects
an EH state in Player.cpp. Replacing the string beneath Upgrade or blindly
renaming only this row would leave the owner/caller and EH contracts
unreconciled. Establish the real pool's identity, callers and emitted EH
parent before an opaque or fully named replacement. The source, row, pins
and baselines remain unchanged; this is a blocked audit result, not a fix.

AGENTS.md requires matched claims to be backed by source and byte
verification, and warns that a successful relocation candidate proves no
name. docs/naming_evidence.md requires independent evidence for identity
repairs. Severity: WRONG. Blocker: identity/pool-owner-binding.
