# TeamInQueue build predicates at 0x00160F80, 0x00160FF0, and 0x00161030

Pre-change identity review. The three bodies currently carry generic names.
The evidence below establishes their individual identities before any ledger
or source replacement. All three boundaries and sizes come from the retail
image; each body has no direct callees.

The retail `AIPlayer::checkQueuedTeams` body begins at 0x00161E20, a method
anchored independently by slot 17 of the `AIPlayer` vtable. It inlines three
different walks over the `TeamInQueue` work-order list at +0x14, rather than
calling these small methods. The native `AIPlayer.cpp` definition of
`checkQueuedTeams` calls `team->isMinimumBuilt()`, then
`team->areBuildsComplete()` in its expiration branch, and later
`team->isAllBuilt()` in its ready branch. The retail method has those same
three distinct checks, in that order and in those same branches:

| Retail check within 0x00161E20 | Observed behavior | Unique out-of-line body | Native name |
| --- | --- | --- | --- |
| +0x63 through +0x8B | For each order, count a live factory ID at +0x08 as one in progress; reject when required count +0x14 exceeds completed count +0x10 and required flag +0x18 is set. | 0x00160FF0, 43 bytes: same offsets, comparison, and false return. | `TeamInQueue::isMinimumBuilt` |
| +0x8C through +0x9D | Reject if any order has a nonzero factory ID at +0x08. | 0x00161030, 27 bytes: same walk and return condition. | `TeamInQueue::areBuildsComplete` |
| +0x12F through +0x14B | Track whether any order needs more units (required +0x14 greater than completed +0x10); accept only when none does. | 0x00160F80, 41 bytes: same walk, comparison, and accumulated boolean. | `TeamInQueue::isAllBuilt` |

The retail walks each advance by the order's +0x0C next pointer. This object
layout is also consistent with the independently matched `TeamInQueue`
destructor and queue operations, including its vtable at 0x00C96940. The
three predicates are distinguishable by their tested fields and results; the
mapping does not depend on a generic source name or on matching bytes alone.

The native Zero Hour method definitions in `Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp`
provide the semantic spellings and non-const, boolean thiscall signatures.
Those names are used only after the independently anchored retail caller's
control flow establishes which predicate each body implements. This change
corrects identities of already matched ranges and adds zero covered bytes.
