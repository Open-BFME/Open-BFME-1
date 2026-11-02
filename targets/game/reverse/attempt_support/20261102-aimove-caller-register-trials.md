# aiMoveToPosition: caller register experiments

Task 7 of the sequential ten-task session, starting at BFME 1 676d5307fc.
Queue rank 9 at census d08539a550, claim key 0xF4BB49DD.
This is compiler evidence, not a conversion or a linked-byte claim.

Read the existing `link4-aimovetoposition-scriptactions-20261101.md` and
`link4-aimovetoposition-tulocal-20261101.md` first. Reproduced their TU-local
macro removal plus volatile x/y/AI/z load sequence in an isolated copy of
ScriptActions.cpp. MSVC 7.1, unchanged source cl flags and include order,
normal experiment_store private output, probe 0x00300610 / 127 bytes.
The original matched source was never edited.

## Measured results

The baseline reproduces 127 bytes, six relocations, and precisely two
non-relocation differences: the ModRM byte at +0x6B and push at +0x6E.
Retail materializes the coordinate address in ECX; this candidate uses EAX.
The existing handoff describes the instruction start as +0x6A.

| New variation | Emitted bytes | Differing bytes in the 127-byte window | Result |
|---|---:|---:|---|
| Read x/y with `*src++`, z with `*src` | 135 | 51 | Worse; first difference +0x1A |
| Read x with `*src`, y/z with `*++src` | 135 | 51 | Same worse result |
| Make existing getAIUpdateInterface const volatile, call through a const volatile receiver instead of the pointer cast | 127 | 2 | Identical remaining +0x6B/+0x6E |
| Store coordinates through a postincrementing destination pointer | 127 | 2 | Identical remaining +0x6B/+0x6E |
| Increment the location pointer then subtract one at the source cast | 127 | 2 | Identical remaining +0x6B/+0x6E |

These test the prior handoff's outstanding folded-pointer and volatile-accessor
ideas. Neither supplies the missing scratch-register rotation. No new bank is
better than the retained preferred candidate; no pins, headers, aliases, or
production code are changed. No diagnostic object is reused for verification.

BFME 1 callees.py confirms the caller's four distinct targets, including ILT
0x3436A -> aiMoveToPosition 0xD86C0. Identity and boundary remain the existing
matched caller's, not an inference from the scratch byte match.

Donor context: reviewed BFME 2 59e3f8f825b698775df9e1728265fe962a5d0c02,
Code/GameEngine/Source/GameLogic/AI/AICommandInterfaceAttackCommands.cpp and
the existing donor provenance in the two handoffs. BFME 2's command ABI/body
is different; no donor body or layout was imported. Donor checkout population
is still running separately; no freshness success is asserted here.

Remaining prerequisite: remove ScriptActions' wrong inline provider while
retaining all 127 caller bytes. Header changes or broader class reconciliation
need provider/consumer verification. Link selection remains unknown with this
worktree's old/incomplete census. The restored production ScriptActions and
MovementOrders sources pass the normal scoped gate (176 rows).
